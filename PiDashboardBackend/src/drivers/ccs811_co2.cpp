#include "ccs811_co2.h"

int8_t driver::sensors::ccs811::co2::init(uint8_t device_reg,
	std::function<int8_t(int, uint8_t, uint8_t*, uint16_t)> read_function,
	std::function<int8_t(int, uint8_t, const uint8_t*, uint16_t)> write_function,
	std::function<int8_t(const std::string, uint8_t, int&)> open_device_function,
	std::function<int8_t(int&)> close_device_function)
{
	m_dev_id = device_reg;
	m_read_function = read_function;
	m_write_function = write_function;
	m_open_device_function = open_device_function;
	m_close_device_function = close_device_function;

	if (m_open_device_function(manager::i2c_manager::DEFAULT_PI_I2C_PATH, m_dev_id, m_file_handle) != OK)
	{
		std::cerr << "CCS881 [init] Error: Could not establish connection with device." << std::endl;
		return DEVICE_NOT_FOUND;
	}

	std::shared_ptr<struct ccs811_device_info> info = std::make_shared<struct ccs811_device_info>();
	if (get_device_information(info) != OK)
	{
		std::cerr << "CCS881 [init] Error: Could not read device information." << std::endl;
		return DEVICE_NOT_FOUND;
	}

	return OK;
}

int8_t driver::sensors::ccs811::co2::init(bool use_power_save_mode, int wake_gpio_pin_nr, int int_gpio_pin_nr,
	std::function<void(uint16_t, uint16_t)> data_callback, uint8_t device_reg,
	std::function<int8_t(int, uint8_t, uint8_t*, uint16_t)> read_function,
	std::function<int8_t(int, uint8_t, const uint8_t*, uint16_t)> write_function,
	std::function<int8_t(const std::string, uint8_t, int&)> open_device_function,
	std::function<int8_t(int&)> close_device_function)
{
	m_int_gpio_pin_nr = int_gpio_pin_nr;
	m_use_power_safe_mode = use_power_save_mode;
	m_wake_gpio_pin = wake_gpio_pin_nr;
	m_data_callback = data_callback;

	if (wiringPiSetup() != OK)
	{
		std::cerr << "CCS881 [init] Error: Could not initialize wiringPi." << std::endl;
		return COMMUNICATION_FAIL;
	}

	pinMode(m_int_gpio_pin_nr, INPUT);
	pinMode(m_wake_gpio_pin, OUTPUT);
	unwake_device();

	if (init(device_reg, read_function, write_function, open_device_function, close_device_function) != OK)
	{
		std::cerr << "CCS881 [init] Error: Could not establish connection with device." << std::endl;
		return DEVICE_NOT_FOUND;
	}
	return OK;
}

int8_t driver::sensors::ccs811::co2::close()
{
	return m_close_device_function(m_file_handle);
}

int8_t driver::sensors::ccs811::co2::toggle_power_safe_mode(bool use_power_safe_mode)
{
	m_use_power_safe_mode = use_power_safe_mode;

	if (!m_use_power_safe_mode) // Deactivate power safe mode
	{
		wake_device(); // Just put the pin to low and leave it. This way the processor is always running
	}
	return OK;
}

int8_t driver::sensors::ccs811::co2::start()
{
	std::shared_ptr<struct ccs811_status> status = std::make_shared<struct ccs811_status>();
	if (get_status_information(status) != OK)
	{
		std::cerr << "CCS881 [start] Error: Could not read status information from the device before start request." << std::endl;
		return COMMUNICATION_FAIL;
	}

	if (status->current_state == ccs811_state::BOOT)
	{
		if (!status->firmware_loaded) // Firmware state not validated. Check it
		{
			bool fw_state = false;
			if (verify_firmware(fw_state) != OK)
			{
				std::cerr << "CCS881 [start] Error: The installed firmware is invalid or could not be validated." << std::endl;
				return DEVICE_ERROR;
			}
		}

		uint8_t start_byte = 0xF4;
		if (m_use_power_safe_mode) wake_device();
		int8_t i2c_res = m_write_function(m_file_handle, APP_START_BOOT_REG, &start_byte, 0);
		if (m_use_power_safe_mode) unwake_device();

		if (i2c_res != OK)
		{
			std::cerr << "CCS881 [start] Error: Could not start device." << std::endl;
			return DEVICE_ERROR;
		}

		if (get_status_information(status) != OK)
		{
			std::cerr << "CCS881 [start] Error: Could not read status information from the device after start request." << std::endl;
			return COMMUNICATION_FAIL;
		}

		if (status->current_state != ccs811_state::READY)
		{
			std::cerr << "CCS881 [start] Error: Could not start the device." << std::endl;
			return DEVICE_ERROR;
		}

		std::shared_ptr<struct ccs811_mode_info> current_mode = std::make_shared<struct ccs811_mode_info>();
		if (get_operation_mode_information(current_mode) != OK)
		{
			std::cerr << "CCS881 [start] Error: Could not read mode information from the device after start request." << std::endl;
			return COMMUNICATION_FAIL;
		}
		m_current_mode = current_mode->current_mode;

		return OK;
	}
	else
	{
		std::cout << "CCS881 [start] Warning: Device is already started and ready to measure. Nothing has been done through this method call." << std::endl;
		return WARNING;
	}
}

int8_t driver::sensors::ccs811::co2::get_status_information(std::shared_ptr<struct ccs811_status>& status)
{
	if (null_check(status.get()) != OK)
	{
		std::cerr << "CCS881 [get_status_information] Error: Status input struct is null" << std::endl;
		return NULL_PTR;
	}

	uint8_t raw_status;
	if (m_use_power_safe_mode) wake_device();
	int8_t i2c_res = m_read_function(m_file_handle, STATUS_REG, &raw_status, STATUS_LEN);
	if (m_use_power_safe_mode) unwake_device();
	if (i2c_res != OK)
	{
		std::cerr << "CCS881 [get_status_information] Error: Could not read status information from the device." << std::endl;
		return COMMUNICATION_FAIL;
	}

	// Check error bit
	if (is_bit_set(raw_status, 0))
	{
		status->has_error = true;
		uint8_t error_code;
		if (read_error(error_code) != OK)
		{
			status->error_message.push_back("CCS881 [get_status_information] Error: The device has an error that could not be read.");
			std::cerr << "CCS881 [get_status_information] Error: The device has an error that could not be read." << std::endl;
			return COMMUNICATION_FAIL;
		}
		else
		{
			if (is_bit_set(error_code, 0)) // WRITE_REG_INVALID
			{
				status->error_message.push_back("CCS881 [get_status_information] Error WRITE_REG_INVALID: The CCS811 received an I²C write"
					"request addressed to this station but with invalid register address ID.");
			}
			if (is_bit_set(error_code, 1)) // READ_REG_INVALID
			{
				status->error_message.push_back("CCS881 [get_status_information] Error READ_REG_INVALID: "
					"The CCS811 received an I²C read request to a mailbox ID that is invalid");
			}
			if (is_bit_set(error_code, 2)) // MEASUREMODE_INVALID
			{
				status->error_message.push_back("CCS881 [get_status_information] Error MEASUREMODE_INVALID: "
					"The CCS811 received an I²C request to write an unsupported mode to	MEAS_MODE");
			}
			if (is_bit_set(error_code, 3)) // MAX_RESISTANCE
			{
				status->error_message.push_back("CCS881 [get_status_information] Error: MAX_RESISTANCE: "
					"The sensor resistance measurement has reached or exceeded the maximum range");
			}
			if (is_bit_set(error_code, 4)) // HEATER_FAULT
			{
				status->error_message.push_back("CCS881 [get_status_information] Error: HEATER_FAULT: "
					"The Heater current in the CCS811 is not in range");
			}
			if (is_bit_set(error_code, 5)) // HEATER_SUPPLY_ERROR
			{
				status->error_message.push_back("CCS881 [get_status_information] Error: HEATER_SUPPLY_ERROR: "
					"The Heater voltage is not being applied correctly");
			}
		}
	}

	status->raw_status_info = raw_status;
	status->data_ready = is_bit_set(raw_status, 3);
	status->firmware_loaded = is_bit_set(raw_status, 4);
	status->current_state = is_bit_set(raw_status, 7) ? ccs811_state::READY : ccs811_state::BOOT;
	return OK;
}

int8_t driver::sensors::ccs811::co2::get_device_information(std::shared_ptr<struct ccs811_device_info>& info)
{
	uint8_t hw_id;
	if (m_use_power_safe_mode) wake_device();
	if (m_read_function(m_file_handle, HARDWARE_ID_REG, &hw_id, HARDWARE_ID_LEN) != OK)
	{
		if (m_use_power_safe_mode) unwake_device();
		std::cerr << "CCS881 [get_device_information] Error: Could not read hardware chip id from the device." << std::endl;
		return COMMUNICATION_FAIL;
	}
	if (hw_id != HARDWARE_ID_VALUE)
	{
		if (m_use_power_safe_mode) unwake_device();
		std::cerr << "CCS881 [get_device_information] Error: Wrong hardware id. Awaited 0x81 but got 0x" << std::hex << hw_id << std::dec <<
			" from the device." << std::endl;
		return DEVICE_NOT_FOUND;
	}

	uint8_t hw_vers_raw;
	if (m_read_function(m_file_handle, HARDWARE_VERSION_REG, &hw_vers_raw, HARDWARE_VERSION_LEN) != OK)
	{
		if (m_use_power_safe_mode) unwake_device();
		std::cerr << "CCS881 [get_device_information] Error: Could not read hardware version from the device." << std::endl;
		return COMMUNICATION_FAIL;
	}

	uint8_t fw_vers_raw[2] = { 0, 0 };
	if (m_read_function(m_file_handle, FIRMWARE_VERSION_REG, fw_vers_raw, FIRMWARE_VERSION_LEN) != OK)
	{
		if (m_use_power_safe_mode) unwake_device();
		std::cerr << "CCS881 [get_device_information] Error: Could not read firmware version from the device." << std::endl;
		return COMMUNICATION_FAIL;
	}

	uint8_t app_vers_raw[2] = { 0, 0 };
	if (m_read_function(m_file_handle, APPLICATION_VERSION_REG, app_vers_raw, APPLICATION_VERSION_LEN) != OK)
	{
		if (m_use_power_safe_mode) unwake_device();
		std::cerr << "CCS881 [get_device_information] Error: Could not read application version from the device." << std::endl;
		return COMMUNICATION_FAIL;
	}
	if (m_use_power_safe_mode) unwake_device();

	info->device_id = m_dev_id;
	info->hardware_id = hw_id;
	info->hardware_version = std::to_string((int)value_of_bits(hw_vers_raw, 4, 7)) + "." + std::to_string((int)value_of_bits(hw_vers_raw, 0, 3));
	info->firmware_version = std::to_string((int)value_of_bits(fw_vers_raw[0], 4, 7)) + "." + std::to_string((int)value_of_bits(fw_vers_raw[0], 0, 3)) + "." + std::to_string((int)fw_vers_raw[1]);
	info->application_version = std::to_string((int)value_of_bits(app_vers_raw[0], 4, 7)) + "." + std::to_string((int)value_of_bits(app_vers_raw[0], 0, 3)) + "." + std::to_string((int)app_vers_raw[1]);

	return OK;
}

int8_t driver::sensors::ccs811::co2::get_operation_mode_information(std::shared_ptr<struct ccs811_mode_info>& mode)
{
	if (check_device_mode() == OK)
	{
		uint8_t raw_mode;
		if (m_use_power_safe_mode) wake_device();
		int8_t i2c_res = m_read_function(m_file_handle, MODE_REG, &raw_mode, MODE_LEN);
		if (m_use_power_safe_mode) unwake_device();
		if (i2c_res != OK)
		{
			std::cerr << "CCS881 [get_operation_mode_information] Error: Could not read mode information from the device." << std::endl;
			return COMMUNICATION_FAIL;
		}

		mode->raw_mode_info = raw_mode;
		uint8_t mode_value = value_of_bits(raw_mode, 4, 6);
		switch (mode_value)
		{
		case 0:
			mode->current_mode = ccs811_operation_mode::SLEEP;
			break;
		case 1:
			mode->current_mode = ccs811_operation_mode::CONSTANT_POWER_1_S;
			break;
		case 2:
			mode->current_mode = ccs811_operation_mode::PULSE_10_S;
			break;
		case 3:
			mode->current_mode = ccs811_operation_mode::PULSE_60_S;
			break;
		case 4:
			mode->current_mode = ccs811_operation_mode::CONSTANT_POWER_250_MS;
			break;
		default:
			std::cerr << "CCS881 [get_operation_mode_information] Error: The device seems to have an invalid mode: " << mode_value << std::endl;
			return DEVICE_ERROR;
		}
		mode->interrupt_gerneration = is_bit_set(raw_mode, 3);
		mode->use_threshold = is_bit_set(raw_mode, 2);

		return OK;
	}

	return WRONG_MODE_WARNING;
}

int8_t driver::sensors::ccs811::co2::set_operation_mode(enum ccs811_operation_mode mode, bool interrupt_mode, bool use_thresholds)
{
	if (check_device_mode() == OK)
	{
		std::shared_ptr<struct ccs811_mode_info> current_mode = std::make_shared<struct ccs811_mode_info>();
		if (get_operation_mode_information(current_mode) != OK)
		{
			std::cerr << "CCS881 [set_operation_mode] Error: Could not read mode information from the device." << std::endl;
			return COMMUNICATION_FAIL;
		}

		// If interrupt generation is currently on, should stay on and private fields for this purpose or uninitialized / set false.
		if (current_mode->interrupt_gerneration && interrupt_mode && !m_use_interrupt_mode && m_interrupt_thread == nullptr)
		{
			// The device is in interrupt mode but our thread is not running...
			// Could be caused through a software restart which did not power off the device.
			start_interrupt_thread();
		}

		if (current_mode->current_mode == mode && current_mode->interrupt_gerneration == interrupt_mode && current_mode->use_threshold == use_thresholds)
		{
			// Nothing changes -> abort
			m_current_mode = mode;
			std::cout << "CCS881 [set_operation_mode] Warning: The device is already in mode '" << (int)mode << "'. Therefore this method call has no effect." << std::endl;
			return WARNING;
		}

		if (current_mode->current_mode > mode&& mode != ccs811_operation_mode::SLEEP)
		{
			// Switch to a slower mode -> wait 10 minutes in idle mode first.
			if (!set_bits(current_mode->raw_mode_info, SLEEP, MODE_MASK))
			{
				std::cerr << "CCS881 [set_operation_mode] Error: Could not write new mode to mode byte." << std::endl;
				return BIT_MANIPULATION_ERROR;
			}
			if (!set_bit(current_mode->raw_mode_info, 3, 0))
			{
				std::cerr << "CCS881 [set_operation_mode] Error: Could not set interrupt mode to false in mode byte." << std::endl;
				return BIT_MANIPULATION_ERROR;
			}
			if (!set_bit(current_mode->raw_mode_info, 2, 0))
			{
				std::cerr << "CCS881 [set_operation_mode] Error: Could not set threshold mode to false in mode byte." << std::endl;
				return BIT_MANIPULATION_ERROR;
			}

			if (m_use_power_safe_mode) wake_device();
			int8_t i2c_res = m_write_function(m_file_handle, MODE_REG, &current_mode->raw_mode_info, 1);
			if (m_use_power_safe_mode) unwake_device();
			if (i2c_res != OK)
			{
				std::cerr << "CCS881 [set_operation_mode] Error: Could not write new operation mode 'SLEEP' to device." << std::endl;
				return DEVICE_ERROR;
			}

			if (m_use_interrupt_mode && m_interrupt_thread != nullptr)
			{
				stop_interrupt_thread();
			}

			m_current_mode = ccs811_operation_mode::SLEEP;
			return MODE_SWITCH_WARNING;
		}
		else
		{
			// Switch to a faster mode or SLEEP mode -> can be instantly switched.
			uint8_t new_mode;
			switch (mode)
			{
			case ccs811_operation_mode::SLEEP:
				new_mode = SLEEP;
				break;
			case ccs811_operation_mode::CONSTANT_POWER_1_S:
				new_mode = CONSTANT_POWER_1_S;
				break;
			case ccs811_operation_mode::PULSE_10_S:
				new_mode = PULSE_10_S;
				break;
			case ccs811_operation_mode::PULSE_60_S:
				new_mode = PULSE_60_S;
				break;
			case ccs811_operation_mode::CONSTANT_POWER_250_MS:
				new_mode = CONSTANT_POWER_250_MS;
				break;
			}

			if (!set_bits(current_mode->raw_mode_info, new_mode, MODE_MASK))
			{
				std::cerr << "CCS881 [set_operation_mode] Error: Could not write new mode to mode byte." << std::endl;
				return BIT_MANIPULATION_ERROR;
			}
			if (!set_bit(current_mode->raw_mode_info, 3, interrupt_mode))
			{
				std::cerr << "CCS881 [set_operation_mode] Error: Could not set interrupt mode to " << interrupt_mode << " in mode byte." << std::endl;
				return BIT_MANIPULATION_ERROR;
			}
			if (!set_bit(current_mode->raw_mode_info, 2, use_thresholds))
			{
				std::cerr << "CCS881 [set_operation_mode] Error: Could not set threshold mode to " << use_thresholds << " in mode byte." << std::endl;
				return BIT_MANIPULATION_ERROR;
			}

			if (m_use_power_safe_mode) wake_device();
			int8_t i2c_res = m_write_function(m_file_handle, MODE_REG, &current_mode->raw_mode_info, 1);
			if (m_use_power_safe_mode) unwake_device();
			if (i2c_res != OK)
			{
				std::cerr << "CCS881 [set_operation_mode] Error: Could not write new operation mode '" << (int)mode << "' to device." << std::endl;
				return DEVICE_ERROR;
			}
			m_current_mode = mode;

			// Start / Stop interrupt threads
			if (interrupt_mode && mode != ccs811_operation_mode::SLEEP)
			{
				start_interrupt_thread();
			}
			else
			{
				stop_interrupt_thread();
			}
			return OK;
		}
	}

	return WRONG_MODE_WARNING;
}

int8_t driver::sensors::ccs811::co2::get_eCO2_data(uint16_t& eCO2)
{
	if (check_device_mode() == OK)
	{
		uint8_t raw_results[2] = { 0, 0 };
		if (m_use_power_safe_mode) wake_device();
		int8_t i2c_res = m_read_function(m_file_handle, RESULT_DATA_REG, raw_results, ECO2_LEN);
		if (m_use_power_safe_mode) unwake_device();
		if (i2c_res != OK)
		{
			std::cerr << "CCS881 [get_eCO2_data] Error: Could not read eCO2 data from the device." << std::endl;
			return COMMUNICATION_FAIL;
		}

		eCO2 = (uint16_t)((raw_results[0] << 8) | raw_results[1]);
		return OK;
	}

	return WRONG_MODE_WARNING;
}

int8_t driver::sensors::ccs811::co2::get_TVOC_data(uint16_t& TVOC)
{
	if (check_device_mode() == OK)
	{
		uint8_t raw_results[4] = { 0, 0, 0, 0 };
		if (m_use_power_safe_mode) wake_device();
		int8_t i2c_res = m_read_function(m_file_handle, RESULT_DATA_REG, raw_results, TVOC_LEN);
		if (m_use_power_safe_mode) unwake_device();
		if (i2c_res != OK)
		{
			std::cerr << "CCS881 [get_TVOC_data] Error: Could not read TVOC data from the device." << std::endl;
			return COMMUNICATION_FAIL;
		}

		TVOC = (uint16_t)((raw_results[2] << 8) | raw_results[3]);
		return OK;
	}

	return WRONG_MODE_WARNING;
}

int8_t driver::sensors::ccs811::co2::get_raw_data(std::shared_ptr<struct ccs811_raw_data>& raw)
{
	if (check_device_mode() == OK)
	{
		std::shared_ptr<struct ccs811_result_data> results = std::make_shared<struct ccs811_result_data>();
		if (get_all_result_data(results) != OK)
		{
			std::cerr << "CCS881 [get_raw_data] Error: Could not read raw data from the device." << std::endl;
			return COMMUNICATION_FAIL;
		}

		raw = std::make_shared<struct ccs811_raw_data>(results->raw_data);
		return OK;
	}

	return WRONG_MODE_WARNING;
}

int8_t driver::sensors::ccs811::co2::get_all_result_data(std::shared_ptr<struct ccs811_result_data>& result)
{
	if (check_device_mode() == OK)
	{
		uint8_t raw_results[8] = { 0, 0, 0, 0, 0, 0, 0, 0 };
		if (m_use_power_safe_mode) wake_device();
		int8_t i2c_res = m_read_function(m_file_handle, RESULT_DATA_REG, raw_results, RAW_DATA_LEN);
		if (m_use_power_safe_mode) unwake_device();
		if (i2c_res != OK)
		{
			std::cerr << "CCS881 [get_all_result_data] Error: Could not read all result data from the device." << std::endl;
			return COMMUNICATION_FAIL;
		}

		result->eco2_value = (uint16_t)((raw_results[0] << 8) | raw_results[1]);
		result->tvoc_value = (uint16_t)((raw_results[2] << 8) | raw_results[3]);
		result->status = raw_results[4];
		result->error_id = raw_results[5];
		result->raw_data.current = value_of_bits(raw_results[6], 2, 7);
		result->raw_data.voltage = (uint16_t)(value_of_bits(raw_results[6], 0, 1) << 8 | (raw_results[7]));

		return OK;
	}

	return WRONG_MODE_WARNING;
}

int8_t driver::sensors::ccs811::co2::set_environment_data(uint16_t temperature, uint16_t humidity)
{
	if (check_device_mode() == OK)
	{
		// Rounds humidity and temperature in 0.5 steps:
		// 35.1 -> 35.0
		// 35.3 -> 35.5
		// 35.7 -> 35.5
		// 35.8 -> 36.0
		uint8_t environment_data[4] = { 0, 0, 0, 0 };
		uint8_t hum_fraction = (uint8_t)((uint8_t)(humidity % 100) / (uint8_t)10);
		environment_data[0] = (hum_fraction > 7) ? (uint8_t)((humidity / (uint8_t)(100 + 1)) << 1) : (uint8_t)((uint8_t)(humidity / 100) << 1); // Rounds integral part up if fraction is greater 0.7
		if (hum_fraction > 2 && hum_fraction < 8)
		{
			environment_data[1] = 1; // Sets fractional part to 0.5 if it is in the range [0.2, 0.7]
		}

		temperature = (uint16_t)(temperature + (uint16_t)2500); // The sensor needs an offset of 25°C (2500 = 25 * 100) to be applied to the actual temperature.
		uint8_t temp_fraction = (uint8_t)((temperature % 100) / (uint8_t)10);
		environment_data[2] = (temp_fraction > 7) ? (uint8_t)((temperature / (uint8_t)(100 + 1)) << 1) : (uint8_t)((uint8_t)(temperature / 100) << 1); // Rounds integral part up if fraction is greater 0.7
		if (temp_fraction > 2 && temp_fraction < 8)
		{
			environment_data[3] = 1; // Sets fractional part to 0.5 if it is in the range [0.2, 0.7]
		}

		if (m_use_power_safe_mode) wake_device();
		int8_t i2c_res = m_write_function(m_file_handle, ENV_DATA_REG, environment_data, ENV_HUM_DATA_LEN + ENV_TEMP_DATA_LEN);
		if (m_use_power_safe_mode) unwake_device();
		if (i2c_res != OK)
		{
			std::cerr << "CCS881 [set_environment_data] Error: Could not write environment data to the device." << std::endl;
			return COMMUNICATION_FAIL;
		}

		return OK;
	}

	return WRONG_MODE_WARNING;
}

int8_t driver::sensors::ccs811::co2::get_NTC_data(std::shared_ptr<struct ccs811_ntc>& ntc)
{
	if (check_device_mode() == OK)
	{
		uint8_t ntc_results[4] = { 0, 0, 0, 0 };
		if (m_use_power_safe_mode) wake_device();
		int8_t i2c_res = m_read_function(m_file_handle, NTC_REG, ntc_results, NTC_LEN);
		if (m_use_power_safe_mode) unwake_device();
		if (i2c_res != OK)
		{
			std::cerr << "CCS881 [get_NTC_data] Error: Could not read NTC data from the device." << std::endl;
			return COMMUNICATION_FAIL;
		}

		ntc->v_over_resistor = (uint16_t)((ntc_results[0] << 8) | ntc_results[1]);
		ntc->v_over_ntc = (uint16_t)((ntc_results[2] << 8) | ntc_results[3]);

		return OK;
	}

	return WRONG_MODE_WARNING;
}

int8_t driver::sensors::ccs811::co2::set_thresholds(std::shared_ptr<struct ccs811_thresholds> thresholds)
{
	if (check_device_mode() == OK)
	{
		uint8_t* data = (uint8_t*)&thresholds->low_medium_threshold;
		if (m_use_power_safe_mode) wake_device();
		int8_t i2c_res = m_write_function(m_file_handle, THRESHOLDS_REG, data, THRESHOLDS_LOW_MEDIUM_LEN + THRESHOLDS_MEDIUM_HIGH_LEN + THRESHOLDS_HYSTERESIS_LEN);
		if (m_use_power_safe_mode) unwake_device();
		if (i2c_res != OK)
		{
			std::cerr << "CCS881 [set_thresholds] Error: Could not write thresholds to the device." << std::endl;
			return COMMUNICATION_FAIL;
		}
		return OK;
	}
	return WRONG_MODE_WARNING;
}

int8_t driver::sensors::ccs811::co2::get_current_baseline(uint8_t baseline[BASELINE_LEN])
{
	if (check_device_mode() == OK)
	{
		if (m_use_power_safe_mode) wake_device();
		int8_t i2c_res = m_read_function(m_file_handle, BASELINE_REG, baseline, BASELINE_LEN);
		if (m_use_power_safe_mode) unwake_device();
		if (i2c_res != OK)
		{
			std::cerr << "CCS881 [get_current_baseline] Error: Could not read baseline data from the device." << std::endl;
			return COMMUNICATION_FAIL;
		}
		return OK;
	}
	return WRONG_MODE_WARNING;
}

int8_t driver::sensors::ccs811::co2::set_baseline(uint8_t baseline[BASELINE_LEN])
{
	if (check_device_mode() == OK)
	{
		if (m_use_power_safe_mode) wake_device();
		int8_t i2c_res = m_write_function(m_file_handle, BASELINE_REG, baseline, BASELINE_LEN);
		if (m_use_power_safe_mode) unwake_device();
		if (i2c_res != OK)
		{
			std::cerr << "CCS881 [set_baseline] Error: Could not write baseline data to the device." << std::endl;
			return COMMUNICATION_FAIL;
		}
		return OK;
	}
	return WRONG_MODE_WARNING;
}

int8_t driver::sensors::ccs811::co2::delete_current_firmware()
{
	if (check_device_mode() == 1) // Device is in BOOT mode
	{
		// ToDo: Implement
		return OK;
	}
	return WRONG_MODE_WARNING;
}

int8_t driver::sensors::ccs811::co2::write_new_firmware(std::shared_ptr<uint8_t[]> new_firmware, uint16_t byte_count)
{
	if (check_device_mode() == 1) // Device is in BOOT mode
	{
		// ToDo: Implement
		return OK;
	}
	return WRONG_MODE_WARNING;
}

int8_t driver::sensors::ccs811::co2::verify_firmware(bool& firmware_valid)
{
	if (check_device_mode() == 1) // Device is in BOOT mode
	{
		// ToDo: Implement
		return OK;
	}
	return WRONG_MODE_WARNING;
}

int8_t driver::sensors::ccs811::co2::check_device_mode()
{
	std::shared_ptr<struct ccs811_status> status = std::make_shared<struct ccs811_status>();
	if (get_status_information(status) != OK)
	{
		std::cerr << "CCS881 [check_device_mode] Error: Could not read status information from the device." << std::endl;
		return COMMUNICATION_FAIL;
	}

	if (status->current_state == ccs811_state::BOOT)
	{
		return 1;
	}

	return OK;
}

int8_t driver::sensors::ccs811::co2::read_error(uint8_t& error_code)
{
	if (m_use_power_safe_mode) wake_device();
	int8_t i2c_res = m_read_function(m_file_handle, ERROR_REG, &error_code, ERROR_LEN);
	if (m_use_power_safe_mode) unwake_device();
	if (i2c_res != OK)
	{
		std::cerr << "CCS881 [read_error] Error: Could not read error data from the device." << std::endl;
		return COMMUNICATION_FAIL;
	}
	return OK;
}

void driver::sensors::ccs811::co2::wake_device()
{
	digitalWrite(m_wake_gpio_pin, LOW);
	usleep(AWAKE_TIME_IN_US);
}

void driver::sensors::ccs811::co2::unwake_device()
{
	digitalWrite(m_wake_gpio_pin, HIGH);
	usleep(DWAKE_TIME_IN_US);
}

void driver::sensors::ccs811::co2::start_interrupt_thread()
{
	if (m_interrupt_thread == nullptr)
	{
		m_use_interrupt_mode = true;
		m_interrupt_thread = new std::thread(&driver::sensors::ccs811::co2::interrupt_mode_loop, this);
	}
}

void driver::sensors::ccs811::co2::stop_interrupt_thread()
{
	if (m_interrupt_thread != nullptr)
	{
		m_use_interrupt_mode = false;
		m_interrupt_thread->join();
	}
}

void driver::sensors::ccs811::co2::wait_for_data_flag()
{
	bool data_available = false;
	while (!data_available && m_use_interrupt_mode)
	{
		mode_dependent_sleep();
		if (digitalRead(m_int_gpio_pin_nr) == LOW)
		{
			data_available = true;
		}
	}
}

void driver::sensors::ccs811::co2::interrupt_mode_loop()
{
	while (m_use_interrupt_mode)
	{
		if (m_int_check_thread == nullptr)
		{
			m_int_check_thread = new std::thread(&driver::sensors::ccs811::co2::wait_for_data_flag, this);
		}
		m_int_check_thread->join();
		m_int_check_thread = nullptr;


		// Read data
		std::shared_ptr<struct ccs811_result_data>results = std::make_shared<struct ccs811_result_data>();
		if (get_all_result_data(results) != OK)
		{
			std::cerr << "CCS881 [interrupt_mode_loop] Error: Could not read result data from the device." << std::endl;
			return;
		}

		// Execute callback with new values
		m_data_callback(results->eco2_value, results->tvoc_value);
	}
}

void driver::sensors::ccs811::co2::mode_dependent_sleep()
{
	switch (m_current_mode)
	{
	case ccs811_operation_mode::PULSE_10_S:
		sleep(10);
		return;
	case ccs811_operation_mode::PULSE_60_S:
		sleep(60);
		return;
	case ccs811_operation_mode::CONSTANT_POWER_1_S:
		sleep(1);
		return;
	case ccs811_operation_mode::CONSTANT_POWER_250_MS:
		usleep(250000);
		return;
	case ccs811_operation_mode::SLEEP:
	default:
		return;
	}
}

int8_t driver::sensors::ccs811::co2::soft_reset()
{
	// No need to implement this method for this sensor
	return int8_t();
}

int8_t driver::sensors::ccs811::co2::get_all_raw_data(uint8_t* all_data)
{
	// No need to implement this method for this sensor
	return int8_t();
}
