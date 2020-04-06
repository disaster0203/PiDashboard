#include "CCS811.h"

#include "../../utils/Constants.h"
#include "../../utils/BitManipulation.h"
#include "../../utils/Helper.h"
#include "../../structs/CallbackHandle.h"
#include "../../exceptions/GPIOException.h"
#include "../../exceptions/I2CException.h"

#include <unistd.h>

void hal::sensors::i2c::ccs811::CCS811::trigger_measurement(const SensorType type)
{
	uint16_t val = 0;
	for (auto i = m_callbacks[type].begin(); i != m_callbacks[type].end(); ++i)
	{
		switch (type)
		{
		case SensorType::CO2:
			try
			{
				get_eCO2_data(val);
			}
			catch (exception::HALException& ex)
			{
				throw exception::HALException("CCS811", "trigger_measurement",
														std::string("Could not trigger eCO2 measurement:\n").append(ex.to_string()));
			}
			break;
		case SensorType::TVOC:
			try
			{
				get_TVOC_data(val);
			}
			catch (exception::HALException& ex)
			{
				throw exception::HALException("CCS811", "trigger_measurement",
														std::string("Could not trigger TVOC measurement:\n").append(ex.to_string()));
			}
			break;
		default:
			throw exception::HALException("CCS811", "trigger_measurement", "Invalid sensor type.");
		}
		(*i)->callback(std::to_string(val));
	}
}

void hal::sensors::i2c::ccs811::CCS811::configure(const SensorSetting setting, const std::string& configuration)
{
	if (setting == SensorSetting::BASELINE)
	{
		std::vector<uint8_t> baselines = {0, 0};

		if (Helper::string_contains_separator(configuration))
		{
			Helper::string_to_array(baselines, configuration);
		}
		else
		{
			BitManipulation::split_bytes(Helper::string_to_uint16_t(configuration), baselines[0], baselines[1]);
		}

		if (baselines.size() == 2)
		{
			try
			{
				set_baseline(&baselines[0]);
			}
			catch (exception::HALException& ex)
			{
				throw exception::HALException("CCS811", "configure", std::string("Could not set baselines:\n").append(ex.to_string()));
			}
		}
	}
	else if (setting == SensorSetting::THRESHOLD)
	{
		std::vector<uint16_t> thresholds = {0, 0, 0};
		Helper::string_to_array(thresholds, configuration);
		const auto threshold = std::make_shared<Thresholds>(Thresholds());
		if (thresholds.size() == 3)
		{
			threshold->low_medium_threshold = thresholds[0];
			threshold->medium_high_threshold = thresholds[1];
			threshold->hysteresis_threshold = static_cast<uint8_t>(thresholds[2]);
			try
			{
				set_thresholds(threshold);
			}
			catch (exception::HALException& ex)
			{
				throw exception::HALException("CCS811", "configure", std::string("Could not set thresholds:\n").append(ex.to_string()));
			}
		}
	}
	else if (setting == SensorSetting::ENVIRONMENT_DATA)
	{
		std::vector<uint16_t> env = {0, 0};
		Helper::string_to_array(env, configuration);
		if (env.size() == 2)
		{
			try
			{
				set_environment_data(env[0], env[1]);
			}
			catch (exception::HALException& ex)
			{
				throw exception::HALException("CCS811", "configure", std::string("Could not set environment data:\n").append(ex.to_string()));
			}
		}
	}
}

std::string hal::sensors::i2c::ccs811::CCS811::get_configuration(const SensorSetting setting)
{
	if (setting == SensorSetting::BASELINE)
	{
		try
		{
			uint8_t baseline[BASELINE_LEN] = {0};
			get_current_baseline(baseline);
			const std::vector<uint8_t> bl(std::begin(baseline), std::end(baseline));
			return Helper::array_to_string(bl);
		}
		catch (exception::HALException& ex)
		{
			throw exception::HALException("CCS811", "get_configuration",
													std::string("Could not get baseline data:\n").append(ex.to_string()));
		}
	}

	return "";
}

std::vector<hal::SensorSetting> hal::sensors::i2c::ccs811::CCS811::available_configurations() noexcept
{
	return {SensorSetting::BASELINE, SensorSetting::THRESHOLD, SensorSetting::ENVIRONMENT_DATA};
}

void hal::sensors::i2c::ccs811::CCS811::close()
{
	try
	{
		I2CManager::close_device(m_file_handle);
	}
	catch (exception::HALException& ex)
	{
		throw exception::HALException("CCS811", "close", std::string("Could not close device connection:\n").append(ex.to_string()));
	}
}

uint8_t hal::sensors::i2c::ccs811::CCS811::init(
	const bool use_power_safe_mode,
	const int wake_gpio_pin_nr,
	const int int_gpio_pin_nr,
	const uint8_t device_reg)
{
	m_int_gpio_pin_nr = int_gpio_pin_nr;
	m_use_power_safe_mode = use_power_safe_mode;
	m_wake_gpio_pin = wake_gpio_pin_nr;
	m_dev_id = device_reg;

	if (wiringPiSetup() != OK)
	{
		throw exception::GPIOException("CCS811", "init", -1, "Could not initialize wiringPi.");
	}

	pinMode(m_int_gpio_pin_nr, INPUT);
	pinMode(m_wake_gpio_pin, OUTPUT);
	unwake_device();

	try
	{
		I2CManager::open_device(I2CManager::DEFAULT_PI_I2C_PATH, m_dev_id, m_file_handle);
	}
	catch (exception::HALException& ex)
	{
		throw exception::HALException("CCS811", "init", std::string("Could not establish connection with device:\n").append(ex.to_string()));
	}

	try
	{
		return get_device_information()->device_id;
	}
	catch (exception::HALException& ex)
	{
		throw exception::HALException("CCS811", "init", std::string("Could not read device id:\n").append(ex.to_string()));
	}
}

void hal::sensors::i2c::ccs811::CCS811::toggle_power_safe_mode(const bool use_power_safe_mode) noexcept
{
	m_use_power_safe_mode = use_power_safe_mode;

	if (!m_use_power_safe_mode) // Deactivate power safe mode
	{
		wake_device(); // Just put the pin to low and leave it. This way the processor is always running
	}
}

int8_t hal::sensors::i2c::ccs811::CCS811::start()
{
	const auto status = get_status_information();
	if (status->current_state == State::BOOT)
	{
		if (!status->firmware_loaded) // Firmware state not validated. Check it
		{
			auto fw_state = false;
			try
			{
				verify_firmware(fw_state);
			}
			catch (exception::HALException& ex)
			{
				throw exception::HALException("CCS811", "start",
														std::string("The device firmware could not be verified:\n").append(ex.to_string()));
			}
		}

		uint8_t start_byte = 0xF4;
		try
		{
			if (m_use_power_safe_mode) wake_device();
			I2CManager::write_to_device(m_file_handle, APP_START_BOOT_REG, &start_byte, 0);
			if (m_use_power_safe_mode) unwake_device();
		}
		catch (exception::HALException& ex)
		{
			if (m_use_power_safe_mode) unwake_device();
			throw exception::I2CException("CCS811", "start", m_dev_id, APP_START_BOOT_REG,
													std::string("Could not start device:\n").append(ex.to_string()));
		}

		try
		{
			if (get_status_information()->current_state != State::READY)
			{
				throw exception::HALException("CCS811", "start", "Could not start the device.");
			}
		}
		catch (exception::HALException& ex)
		{
			throw exception::HALException("CCS811", "start",
													std::string("Could not read device status information:\n").append(ex.to_string()));
		}

		try
		{
			auto current_mode = std::make_shared<struct ModeInfo>();
			get_operation_mode_information(current_mode);
			m_current_mode = current_mode->current_mode;
		}
		catch (exception::HALException& ex)
		{
			throw exception::HALException("CCS811", "start",
													std::string("Could not read device operation mode:\n").append(ex.to_string()));
		}
		return OK;
	}
	return WARNING;
}

std::shared_ptr<hal::sensors::i2c::ccs811::Status> hal::sensors::i2c::ccs811::CCS811::get_status_information() const
{
	uint8_t raw_status;
	try
	{
		if (m_use_power_safe_mode) wake_device();
		I2CManager::read_from_device(m_file_handle, STATUS_REG, &raw_status, STATUS_LEN);
		if (m_use_power_safe_mode) unwake_device();
	}
	catch (exception::HALException& ex)
	{
		if (m_use_power_safe_mode) unwake_device();
		throw exception::I2CException("CCS811", "get_status_information", m_dev_id, STATUS_REG,
												std::string("Could not read status information from the device:\n").append(ex.to_string()));
	}

	auto status = std::make_shared<Status>();
	// Check error bit
	if (BitManipulation::is_bit_set(raw_status, 0))
	{
		status->has_error = true;
		const auto error_code = read_error();

		if (BitManipulation::is_bit_set(error_code, 0)) // WRITE_REG_INVALID
		{
			status->error_message.push_back("CCS881 [get_status_information] Error WRITE_REG_INVALID: The CCS811 received an I²C write"
				"request addressed to this station but with invalid register address ID.");
		}
		if (BitManipulation::is_bit_set(error_code, 1)) // READ_REG_INVALID
		{
			status->error_message.push_back("CCS881 [get_status_information] Error READ_REG_INVALID: "
				"The CCS811 received an I²C read request to a mailbox ID that is invalid");
		}
		if (BitManipulation::is_bit_set(error_code, 2)) // MEASUREMODE_INVALID
		{
			status->error_message.push_back("CCS881 [get_status_information] Error MEASUREMODE_INVALID: "
				"The CCS811 received an I²C request to write an unsupported mode to	MEAS_MODE");
		}
		if (BitManipulation::is_bit_set(error_code, 3)) // MAX_RESISTANCE
		{
			status->error_message.push_back("CCS881 [get_status_information] Error: MAX_RESISTANCE: "
				"The sensor resistance measurement has reached or exceeded the maximum range");
		}
		if (BitManipulation::is_bit_set(error_code, 4)) // HEATER_FAULT
		{
			status->error_message.push_back("CCS881 [get_status_information] Error: HEATER_FAULT: "
				"The Heater current in the CCS811 is not in range");
		}
		if (BitManipulation::is_bit_set(error_code, 5)) // HEATER_SUPPLY_ERROR
		{
			status->error_message.push_back("CCS881 [get_status_information] Error: HEATER_SUPPLY_ERROR: "
				"The Heater voltage is not being applied correctly");
		}
	}

	status->raw_status_info = raw_status;
	status->data_ready = BitManipulation::is_bit_set(raw_status, 3);
	status->firmware_loaded = BitManipulation::is_bit_set(raw_status, 4);
	status->current_state = BitManipulation::is_bit_set(raw_status, 7) ? State::READY : State::BOOT;
	return status;
}

std::shared_ptr<struct hal::sensors::i2c::ccs811::DeviceInfo> hal::sensors::i2c::ccs811::CCS811::get_device_information() const
{
	uint8_t hw_id;
	if (m_use_power_safe_mode) wake_device();
	try
	{
		I2CManager::read_from_device(m_file_handle, HARDWARE_ID_REG, &hw_id, HARDWARE_ID_LEN);
	}
	catch (exception::HALException& ex)
	{
		if (m_use_power_safe_mode) unwake_device();
		throw exception::I2CException("CCS811", "get_device_information", m_dev_id, HARDWARE_ID_REG,
												std::string("Could not read hardware chip id from the device:\n").append(ex.to_string()));
	}

	if (hw_id != HARDWARE_ID_VALUE)
	{
		if (m_use_power_safe_mode) unwake_device();

		char wrong_id[70];
		sprintf(wrong_id, "Wrong hardware id. Awaited 0x81 but got 0x%x from the device", hw_id);
		throw exception::I2CException("CCS811", "get_device_information", m_dev_id, HARDWARE_ID_REG, wrong_id);
	}

	uint8_t hw_version_raw;
	try
	{
		I2CManager::read_from_device(m_file_handle, HARDWARE_VERSION_REG, &hw_version_raw, HARDWARE_VERSION_LEN);
	}
	catch (exception::HALException& ex)
	{
		if (m_use_power_safe_mode) unwake_device();
		throw exception::I2CException("CCS811", "get_device_information", m_dev_id, HARDWARE_VERSION_REG,
												std::string("Could not read hardware version from the device:\n").append(ex.to_string()));
	}

	uint8_t fw_version_raw[2] = {0, 0};
	try
	{
		I2CManager::read_from_device(m_file_handle, FIRMWARE_VERSION_REG, fw_version_raw, FIRMWARE_VERSION_LEN);
	}
	catch (exception::HALException& ex)
	{
		if (m_use_power_safe_mode) unwake_device();
		throw exception::I2CException("CCS811", "get_device_information", m_dev_id, FIRMWARE_VERSION_REG,
												std::string("Could not read firmware version from the device:\n").append(ex.to_string()));
	}

	uint8_t app_version_raw[2] = {0, 0};
	try
	{
		I2CManager::read_from_device(m_file_handle, APPLICATION_VERSION_REG, app_version_raw, APPLICATION_VERSION_LEN);
	}
	catch (exception::HALException& ex)
	{
		if (m_use_power_safe_mode) unwake_device();
		throw exception::I2CException("CCS811", "get_device_information", m_dev_id, APPLICATION_VERSION_REG,
												std::string("Could not read application version from the device:\n").append(ex.to_string()));
	}
	if (m_use_power_safe_mode) unwake_device();

	try
	{
		auto info = std::make_shared<DeviceInfo>();
		info->device_id = m_dev_id;
		info->hardware_id = hw_id;
		info->hardware_version = std::to_string(static_cast<int>(BitManipulation::value_of_bits(hw_version_raw, 4, 7))).append(".").append(
			std::to_string(
				static_cast<int>(
					BitManipulation
					::
					value_of_bits(
						hw_version_raw,
						0, 3))));
		info->firmware_version = std::to_string(static_cast<int>(BitManipulation::value_of_bits(fw_version_raw[0], 4, 7))).append(".").append(
			std::to_string(
				static_cast<
					int>(
					BitManipulation
					::
					value_of_bits(
						fw_version_raw
						[0], 0,
						3)))
			.append(".").
			append(
				std::
				to_string(
					static_cast
					<int>(
						fw_version_raw
						[1]))));
		info->application_version = std::to_string(static_cast<int>(BitManipulation::value_of_bits(app_version_raw[0], 4, 7)))
											.append(".").append(
												std::to_string(static_cast<int>(BitManipulation::value_of_bits(app_version_raw[0], 0, 3)))
												.append(".").append(std::to_string(static_cast<int>(app_version_raw[1]))));
		return info;
	}
	catch (exception::HALException& ex)
	{
		throw exception::I2CException("CCS811", "get_device_information", m_dev_id, APPLICATION_VERSION_REG,
												std::string("Could not read value of certain bits from byte:\n").append(ex.to_string()));
	}
}

int8_t hal::sensors::i2c::ccs811::CCS811::get_operation_mode_information(std::shared_ptr<struct ModeInfo>& mode) const
{
	int8_t device_mode;
	try
	{
		device_mode = check_device_mode();
	}
	catch (exception::HALException& ex)
	{
		throw exception::HALException("CCS811", "get_operation_mode_information",
												std::string("Could not read current device mode:\n").append(ex.to_string()));
	}

	if (device_mode == OK)
	{
		uint8_t raw_mode;
		try
		{
			if (m_use_power_safe_mode) wake_device();
			I2CManager::read_from_device(m_file_handle, MODE_REG, &raw_mode, MODE_LEN);
			if (m_use_power_safe_mode) unwake_device();
		}
		catch (exception::HALException& ex)
		{
			if (m_use_power_safe_mode) unwake_device();
			throw exception::I2CException("CCS811", "get_operation_mode_information", m_dev_id, MODE_REG,
													std::string("Could not read mode information from the device:\n").append(ex.to_string()));
		}

		mode->raw_mode_info = raw_mode;
		uint8_t mode_value;
		try
		{
			mode_value = BitManipulation::value_of_bits(raw_mode, 4, 6);
		}
		catch (exception::HALException& ex)
		{
			throw exception::HALException("CCS811", "get_operation_mode_information",
													std::string("Could not read value of certain bits from byte:\n").append(ex.to_string()));
		}

		switch (mode_value)
		{
		case 0:
			mode->current_mode = OperationMode::SLEEP;
			break;
		case 1:
			mode->current_mode = OperationMode::CONSTANT_POWER_1_S;
			break;
		case 2:
			mode->current_mode = OperationMode::PULSE_10_S;
			break;
		case 3:
			mode->current_mode = OperationMode::PULSE_60_S;
			break;
		case 4:
			mode->current_mode = OperationMode::CONSTANT_POWER_250_MS;
			break;
		default:
			throw exception::HALException("CCS811", "get_operation_mode_information",
													std::string("The device seems to have an invalid mode: ")
													.append(std::to_string(mode_value)).append("."));
		}

		try
		{
			mode->interrupt_generation = BitManipulation::is_bit_set(raw_mode, 3);
			mode->use_threshold = BitManipulation::is_bit_set(raw_mode, 2);
		}
		catch (exception::HALException& ex)
		{
			throw exception::HALException("CCS811", "get_operation_mode_information",
													std::string("Could not check interrupt and/or threshold bit:\n").append(ex.to_string()));
		}
		return OK;
	}
	return WRONG_MODE_WARNING;
}

int8_t hal::sensors::i2c::ccs811::CCS811::set_operation_mode(OperationMode mode, bool interrupt_mode, bool use_thresholds)
{
	int8_t device_mode;
	try
	{
		device_mode = check_device_mode();
	}
	catch (exception::HALException& ex)
	{
		throw exception::HALException("CCS811", "set_operation_mode",
												std::string("Could not read current device mode:\n").append(ex.to_string()));
	}

	if (device_mode == OK)
	{
		auto current_mode = std::make_shared<ModeInfo>();
		try
		{
			get_operation_mode_information(current_mode);
		}
		catch (exception::HALException& ex)
		{
			throw exception::HALException("CCS811", "set_operation_mode",
													std::string("Could not read operation mode information:\n").append(ex.to_string()));
		}

		// If interrupt generation is currently on, should stay on and private fields for this purpose or uninitialized / set false.
		if (current_mode->interrupt_generation && interrupt_mode && !m_use_interrupt_mode && m_interrupt_thread == nullptr)
		{
			// The device is in interrupt mode but our thread is not running...
			// Could be caused through a software restart which did not power off the device.
			start_interrupt_thread();
		}

		if (current_mode->current_mode == mode && current_mode->interrupt_generation == interrupt_mode && current_mode->use_threshold ==
			use_thresholds)
		{
			// Nothing changes -> abort
			m_current_mode = mode;
			return WARNING;
		}

		auto new_mode = SLEEP;
		// Switch to a slower mode -> wait 10 minutes in idle mode first.
		if (current_mode->current_mode > mode && mode != OperationMode::SLEEP)
		{
			// new_mode = SLEEP;
			mode = OperationMode::SLEEP;
			interrupt_mode = false;
			use_thresholds = false;
		}
		else // Switch to a faster mode or SLEEP mode -> can be instantly switched.
		{
			switch (mode)
			{
			case OperationMode::SLEEP:
				new_mode = SLEEP;
				break;
			case OperationMode::CONSTANT_POWER_1_S:
				new_mode = CONSTANT_POWER_1_S;
				break;
			case OperationMode::PULSE_10_S:
				new_mode = PULSE_10_S;
				break;
			case OperationMode::PULSE_60_S:
				new_mode = PULSE_60_S;
				break;
			case OperationMode::CONSTANT_POWER_250_MS:
				new_mode = CONSTANT_POWER_250_MS;
				break;
			}
		}

		// Write mode.
		try
		{
			BitManipulation::set_bits(current_mode->raw_mode_info, new_mode, MODE_MASK);
		}
		catch (exception::HALException& ex)
		{
			throw exception::HALException("CCS811", "set_operation_mode",
													std::string("Could not write new mode to mode byte:\n").append(ex.to_string()));
		}

		// Write interrupt mode.
		try
		{
			BitManipulation::set_bit(current_mode->raw_mode_info, 3, interrupt_mode);
		}
		catch (exception::HALException& ex)
		{
			throw exception::HALException("CCS811", "set_operation_mode",
													std::string("Could not set interrupt mode to false in mode byte:\n").append(ex.to_string()));
		}

		// Write threshold mode.
		try
		{
			BitManipulation::set_bit(current_mode->raw_mode_info, 2, use_thresholds);
		}
		catch (exception::HALException& ex)
		{
			throw exception::HALException("CCS811", "set_operation_mode",
													std::string("Could not set threshold mode to false in mode byte:\n").append(ex.to_string()));
		}

		// Write new mode information to device.
		try
		{
			if (m_use_power_safe_mode) wake_device();
			I2CManager::write_to_device(m_file_handle, MODE_REG, &current_mode->raw_mode_info, 1);
			if (m_use_power_safe_mode) unwake_device();
		}
		catch (exception::HALException& ex)
		{
			if (m_use_power_safe_mode) unwake_device();
			throw exception::I2CException("CCS811", "set_operation_mode", m_dev_id, MODE_REG,
													std::string("Could not write new operation mode '").append(std::to_string(static_cast<int>(mode)))
																														.append("' to device:\n").append(
																															ex.to_string()));
		}

		m_current_mode = mode;
		// Switch to a slower mode -> wait 10 minutes in idle mode first.
		if (current_mode->current_mode > mode && mode != OperationMode::SLEEP)
		{
			if (m_use_interrupt_mode && m_interrupt_thread != nullptr)
			{
				stop_interrupt_thread();
			}
			return MODE_SWITCH_WARNING;
		}

		// Switch to a faster mode or SLEEP mode -> can be instantly switched.
		// Start / Stop interrupt threads
		if (interrupt_mode && mode != OperationMode::SLEEP)
		{
			start_interrupt_thread();
		}
		else
		{
			stop_interrupt_thread();
		}
		return OK;
	}
	return WRONG_MODE_WARNING;
}

int8_t hal::sensors::i2c::ccs811::CCS811::get_eCO2_data(uint16_t& eCO2) const
{
	int8_t device_mode;
	try
	{
		device_mode = check_device_mode();
	}
	catch (exception::HALException& ex)
	{
		throw exception::HALException("CCS811", "get_eCO2_data",
												std::string("Could not read current device mode:\n").append(ex.to_string()));
	}

	if (device_mode == OK)
	{
		uint8_t raw_results[2] = {0, 0};
		try
		{
			if (m_use_power_safe_mode) wake_device();
			I2CManager::read_from_device(m_file_handle, RESULT_DATA_REG, raw_results, ECO2_LEN);
			if (m_use_power_safe_mode) unwake_device();
		}
		catch (exception::HALException& ex)
		{
			if (m_use_power_safe_mode) unwake_device();
			throw exception::I2CException("CCS811", "get_eCO2_data", m_dev_id, RESULT_DATA_REG,
													std::string("Could not read eCO2 data from the device:\n").append(ex.to_string()));
		}

		eCO2 = BitManipulation::combine_bytes(raw_results[0], raw_results[1]);
		return OK;
	}

	return WRONG_MODE_WARNING;
}

int8_t hal::sensors::i2c::ccs811::CCS811::get_TVOC_data(uint16_t& TVOC) const
{
	int8_t device_mode;
	try
	{
		device_mode = check_device_mode();
	}
	catch (exception::HALException& ex)
	{
		throw exception::HALException("CCS811", "get_TVOC_data",
												std::string("Could not read current device mode:\n").append(ex.to_string()));
	}

	if (device_mode == OK)
	{
		uint8_t raw_results[4] = {0, 0, 0, 0};
		try
		{
			if (m_use_power_safe_mode) wake_device();
			I2CManager::read_from_device(m_file_handle, RESULT_DATA_REG, raw_results, TVOC_LEN);
			if (m_use_power_safe_mode) unwake_device();
		}
		catch (exception::HALException& ex)
		{
			if (m_use_power_safe_mode) unwake_device();
			throw exception::I2CException("CCS811", "get_TVOC_data", m_dev_id, RESULT_DATA_REG,
													std::string("Could not read TVOC data from the device:\n").append(ex.to_string()));
		}

		TVOC = BitManipulation::combine_bytes(raw_results[2], raw_results[3]);
		return OK;
	}

	return WRONG_MODE_WARNING;
}

int8_t hal::sensors::i2c::ccs811::CCS811::get_raw_data(std::shared_ptr<RawData>& raw) const
{
	int8_t device_mode;
	try
	{
		device_mode = check_device_mode();
	}
	catch (exception::HALException& ex)
	{
		throw exception::HALException("CCS811", "get_raw_data",
												std::string("Could not read current device mode:\n").append(ex.to_string()));
	}

	if (device_mode == OK)
	{
		try
		{
			auto results = std::make_shared<ResultData>();
			get_all_result_data(results);
			raw = std::make_shared<RawData>(results->raw_data);
			return OK;
		}
		catch (exception::HALException& ex)
		{
			throw exception::HALException("CCS811", "get_raw_data",
													std::string("Could not read result data from the device:\n").append(ex.to_string()));
		}
	}
	return WRONG_MODE_WARNING;
}

int8_t hal::sensors::i2c::ccs811::CCS811::get_all_result_data(std::shared_ptr<ResultData>& result) const
{
	int8_t device_mode;
	try
	{
		device_mode = check_device_mode();
	}
	catch (exception::HALException& ex)
	{
		throw exception::HALException("CCS811", "get_all_result_data",
												std::string("Could not read current device mode:\n").append(ex.to_string()));
	}

	if (device_mode == OK)
	{
		uint8_t raw_results[8] = {0, 0, 0, 0, 0, 0, 0, 0};
		try
		{
			if (m_use_power_safe_mode) wake_device();
			I2CManager::read_from_device(m_file_handle, RESULT_DATA_REG, raw_results, RAW_DATA_LEN);
			if (m_use_power_safe_mode) unwake_device();
		}
		catch (exception::HALException& ex)
		{
			if (m_use_power_safe_mode) unwake_device();
			throw exception::I2CException("CCS811", "get_all_result_data", m_dev_id, RESULT_DATA_REG,
													std::string("Could not read all result data from the device:\n").append(ex.to_string()));
		}

		result->eco2_value = BitManipulation::combine_bytes(raw_results[0], raw_results[1]);
		result->tvoc_value = BitManipulation::combine_bytes(raw_results[2], raw_results[3]);
		result->status = raw_results[4];
		result->error_id = raw_results[5];
		try
		{
			result->raw_data.voltage = BitManipulation::combine_bytes(BitManipulation::value_of_bits(raw_results[6], 0, 1), raw_results[7]);
			result->raw_data.current = BitManipulation::value_of_bits(raw_results[6], 2, 7);
		}
		catch (exception::HALException& ex)
		{
			throw exception::HALException("CCS811", "get_all_result_data",
													std::string("Could not read value of certain bits from byte:\n").append(ex.to_string()));
		}
		return OK;
	}
	return WRONG_MODE_WARNING;
}

int8_t hal::sensors::i2c::ccs811::CCS811::set_environment_data(uint16_t temperature, const uint16_t humidity) const
{
	int8_t device_mode;
	try
	{
		device_mode = check_device_mode();
	}
	catch (exception::HALException& ex)
	{
		throw exception::HALException("CCS811", "set_environment_data",
												std::string("Could not read current device mode:\n").append(ex.to_string()));
	}

	if (device_mode == OK)
	{
		// Rounds humidity and temperature in 0.5 steps:
		// 35.1 -> 35.0
		// 35.3 -> 35.5
		// 35.7 -> 35.5
		// 35.8 -> 36.0
		uint8_t environment_data[4] = {0, 0, 0, 0};
		const auto hum_fraction = static_cast<uint8_t>(static_cast<uint8_t>(humidity % 100) / static_cast<uint8_t>(10));
		environment_data[0] = (hum_fraction > 7)
										? static_cast<uint8_t>((humidity / static_cast<uint8_t>(100 + 1)) << 1)
										: static_cast<uint8_t>(static_cast<uint8_t>(humidity / 100) << 1);
		// Rounds integral part up if fraction is greater 0.7
		if (hum_fraction > 2 && hum_fraction < 8)
		{
			environment_data[1] = 1; // Sets fractional part to 0.5 if it is in the range [0.2, 0.7]
		}

		temperature = static_cast<uint16_t>(temperature + static_cast<uint16_t>(2500));
		// The sensor needs an offset of 25°C (2500 = 25 * 100) to be applied to the actual temperature.
		const auto temp_fraction = static_cast<uint8_t>((temperature % 100) / static_cast<uint8_t>(10));
		environment_data[2] = (temp_fraction > 7)
										? static_cast<uint8_t>((temperature / static_cast<uint8_t>(100 + 1)) << 1)
										: static_cast<uint8_t>(static_cast<uint8_t>(temperature / 100) << 1);
		// Rounds integral part up if fraction is greater 0.7
		if (temp_fraction > 2 && temp_fraction < 8)
		{
			environment_data[3] = 1; // Sets fractional part to 0.5 if it is in the range [0.2, 0.7]
		}

		try
		{
			if (m_use_power_safe_mode) wake_device();
			I2CManager::write_to_device(m_file_handle, ENV_DATA_REG, environment_data, ENV_HUM_DATA_LEN + ENV_TEMP_DATA_LEN);
			if (m_use_power_safe_mode) unwake_device();
		}
		catch (exception::HALException& ex)
		{
			if (m_use_power_safe_mode) unwake_device();
			throw exception::I2CException("CCS811", "set_environment_data", m_dev_id, ENV_DATA_REG,
													std::string("Could not write environment data to the device:\n").append(ex.to_string()));
		}
		return OK;
	}
	return WRONG_MODE_WARNING;
}

int8_t hal::sensors::i2c::ccs811::CCS811::get_NTC_data(std::shared_ptr<NTC>& NTC) const
{
	int8_t device_mode;
	try
	{
		device_mode = check_device_mode();
	}
	catch (exception::HALException& ex)
	{
		throw exception::HALException("CCS811", "get_NTC_data",
												std::string("Could not read current device mode:\n").append(ex.to_string()));
	}

	if (device_mode == OK)
	{
		uint8_t ntc_results[4] = {0, 0, 0, 0};
		try
		{
			if (m_use_power_safe_mode) wake_device();
			I2CManager::read_from_device(m_file_handle, NTC_REG, ntc_results, NTC_LEN);
			if (m_use_power_safe_mode) unwake_device();
		}
		catch (exception::HALException& ex)
		{
			if (m_use_power_safe_mode) unwake_device();
			throw exception::I2CException("CCS811", "get_NTC_data", m_dev_id, NTC_REG,
													std::string("Could not read NTC data from the device:\n").append(ex.to_string()));
		}

		NTC->v_over_resistor = BitManipulation::combine_bytes(ntc_results[0], ntc_results[1]);
		NTC->v_over_ntc = BitManipulation::combine_bytes(ntc_results[2], ntc_results[3]);

		return OK;
	}

	return WRONG_MODE_WARNING;
}

int8_t hal::sensors::i2c::ccs811::CCS811::set_thresholds(std::shared_ptr<Thresholds> thresholds) const
{
	int8_t device_mode;
	try
	{
		device_mode = check_device_mode();
	}
	catch (exception::HALException& ex)
	{
		throw exception::HALException("CCS811", "set_thresholds",
												std::string("Could not read current device mode:\n").append(ex.to_string()));
	}

	if (device_mode == OK)
	{
		const auto data = reinterpret_cast<uint8_t*>(&thresholds->low_medium_threshold);
		try
		{
			if (m_use_power_safe_mode) wake_device();
			I2CManager::write_to_device(m_file_handle, THRESHOLDS_REG, data,
												THRESHOLDS_LOW_MEDIUM_LEN + THRESHOLDS_MEDIUM_HIGH_LEN + THRESHOLDS_HYSTERESIS_LEN);
			if (m_use_power_safe_mode) unwake_device();
		}
		catch (exception::HALException& ex)
		{
			if (m_use_power_safe_mode) unwake_device();
			throw exception::I2CException("CCS811", "set_thresholds", m_dev_id, THRESHOLDS_REG,
													std::string("Could not write thresholds to the device:\n").append(ex.to_string()));
		}
		return OK;
	}

	return WRONG_MODE_WARNING;
}

int8_t hal::sensors::i2c::ccs811::CCS811::get_current_baseline(uint8_t baseline[BASELINE_LEN]) const
{
	int8_t device_mode;
	try
	{
		device_mode = check_device_mode();
	}
	catch (exception::HALException& ex)
	{
		throw exception::HALException("CCS811", "get_current_baseline",
												std::string("Could not read current device mode:\n").append(ex.to_string()));
	}

	if (device_mode == OK)
	{
		try
		{
			if (m_use_power_safe_mode) wake_device();
			I2CManager::read_from_device(m_file_handle, BASELINE_REG, baseline, BASELINE_LEN);
			if (m_use_power_safe_mode) unwake_device();
		}
		catch (exception::HALException& ex)
		{
			if (m_use_power_safe_mode) unwake_device();
			throw exception::I2CException("CCS811", "get_current_baseline", m_dev_id, BASELINE_REG,
													std::string("Could not read baseline data from the device:\n").append(ex.to_string()));
		}
		return OK;
	}

	return WRONG_MODE_WARNING;
}

int8_t hal::sensors::i2c::ccs811::CCS811::set_baseline(uint8_t baseline[BASELINE_LEN]) const
{
	int8_t device_mode;
	try
	{
		device_mode = check_device_mode();
	}
	catch (exception::HALException& ex)
	{
		throw exception::HALException("CCS811", "set_baseline",
												std::string("Could not read current device mode:\n").append(ex.to_string()));
	}

	if (device_mode == OK)
	{
		try
		{
			if (m_use_power_safe_mode) wake_device();
			I2CManager::write_to_device(m_file_handle, BASELINE_REG, baseline, BASELINE_LEN);
			if (m_use_power_safe_mode) unwake_device();
		}
		catch (exception::HALException& ex)
		{
			if (m_use_power_safe_mode) unwake_device();
			throw exception::I2CException("CCS811", "set_baseline", m_dev_id, BASELINE_REG,
													std::string("Could not write baseline data to the device:\n").append(ex.to_string()));
		}
		return OK;
	}

	return WRONG_MODE_WARNING;
}

int8_t hal::sensors::i2c::ccs811::CCS811::delete_current_firmware() const
{
	int8_t device_mode;
	try
	{
		device_mode = check_device_mode();
	}
	catch (exception::HALException& ex)
	{
		throw exception::HALException("CCS811", "delete_current_firmware",
												std::string("Could not read current device mode:\n").append(ex.to_string()));
	}

	if (device_mode == 1) // Device is in BOOT mode
	{
		// ToDo: Implement
		return OK;
	}
	return WRONG_MODE_WARNING;
}

int8_t hal::sensors::i2c::ccs811::CCS811::write_new_firmware(std::shared_ptr<uint8_t[]> new_firmware, uint16_t byte_count) const
{
	int8_t device_mode;
	try
	{
		device_mode = check_device_mode();
	}
	catch (exception::HALException& ex)
	{
		throw exception::HALException("CCS811", "write_new_firmware",
												std::string("Could not read current device mode:\n").append(ex.to_string()));
	}

	if (device_mode == 1) // Device is in BOOT mode
	{
		// ToDo: Implement
		return OK;
	}
	return WRONG_MODE_WARNING;
}

int8_t hal::sensors::i2c::ccs811::CCS811::verify_firmware(bool& firmware_valid) const
{
	int8_t device_mode;
	try
	{
		device_mode = check_device_mode();
	}
	catch (exception::HALException& ex)
	{
		throw exception::HALException("CCS811", "verify_firmware",
												std::string("Could not read current device mode:\n").append(ex.to_string()));
	}

	if (device_mode == 1) // Device is in BOOT mode
	{
		// ToDo: Implement
		return OK;
	}
	return WRONG_MODE_WARNING;
}

int8_t hal::sensors::i2c::ccs811::CCS811::check_device_mode() const
{
	try
	{
		if (get_status_information()->current_state == State::BOOT)
		{
			return 1;
		}

		return OK;
	}
	catch (exception::HALException& ex)
	{
		throw exception::HALException("CCS811", "check_device_mode",
												std::string("Could not read current state from the device:\n").append(ex.to_string()));
	}
}

uint8_t hal::sensors::i2c::ccs811::CCS811::read_error() const
{
	uint8_t error_code[ERROR_LEN] = {0};
	try
	{
		if (m_use_power_safe_mode) wake_device();
		I2CManager::read_from_device(m_file_handle, ERROR_REG, error_code, ERROR_LEN);
		if (m_use_power_safe_mode) unwake_device();
	}
	catch (exception::HALException& ex)
	{
		if (m_use_power_safe_mode) unwake_device();
		throw exception::I2CException("CCS811", "read_error", m_dev_id, ERROR_REG,
												std::string("Could not read error data from the device:\n").append(ex.to_string()));
	}
	return error_code[0];
}

void hal::sensors::i2c::ccs811::CCS811::wake_device() const noexcept
{
	digitalWrite(m_wake_gpio_pin, LOW);
	usleep(AWAKE_TIME_IN_US);
}

void hal::sensors::i2c::ccs811::CCS811::unwake_device() const noexcept
{
	digitalWrite(m_wake_gpio_pin, HIGH);
	usleep(DWAKE_TIME_IN_US);
}

void hal::sensors::i2c::ccs811::CCS811::start_interrupt_thread() noexcept
{
	if (m_interrupt_thread == nullptr)
	{
		m_use_interrupt_mode = true;
		m_interrupt_thread = new std::thread(&CCS811::interrupt_mode_loop, this);
	}
}

void hal::sensors::i2c::ccs811::CCS811::stop_interrupt_thread() noexcept
{
	if (m_interrupt_thread != nullptr)
	{
		m_use_interrupt_mode = false;
		m_interrupt_thread->join();
	}
}

void hal::sensors::i2c::ccs811::CCS811::wait_for_data_flag() const noexcept
{
	auto data_available = false;
	while (!data_available && m_use_interrupt_mode)
	{
		mode_dependent_sleep();
		if (digitalRead(m_int_gpio_pin_nr) == LOW)
		{
			data_available = true;
		}
	}
}

void hal::sensors::i2c::ccs811::CCS811::interrupt_mode_loop()
{
	while (m_use_interrupt_mode)
	{
		if (m_int_check_thread == nullptr)
		{
			m_int_check_thread = new std::thread(&CCS811::wait_for_data_flag, this);
		}
		m_int_check_thread->join();
		m_int_check_thread = nullptr;

		// Read data
		auto results = std::make_shared<ResultData>();
		try
		{
			get_all_result_data(results);
		}
		catch (exception::HALException& ex)
		{
			throw exception::HALException("CCS811", "interrupt_mode_loop",
													std::string("Could not read result data:\n").append(ex.to_string()));
		}

		// Execute callbacks with new values
		for (auto miter = m_callbacks.begin(); miter != m_callbacks.end(); ++miter)
		{
			for (auto v_iterator = miter->second.begin(); v_iterator != miter->second.end(); ++v_iterator)
			{
				if ((*v_iterator)->callback != nullptr)
				{
					(*v_iterator)->callback(std::to_string(results->eco2_value));
				}
			}
		}
	}
}

void hal::sensors::i2c::ccs811::CCS811::mode_dependent_sleep() const noexcept
{
	switch (m_current_mode)
	{
	case OperationMode::PULSE_10_S:
		sleep(10);
		return;
	case OperationMode::PULSE_60_S:
		sleep(60);
		return;
	case OperationMode::CONSTANT_POWER_1_S:
		sleep(1);
		return;
	case OperationMode::CONSTANT_POWER_250_MS:
		usleep(250000);
		return;
	case OperationMode::SLEEP:
	default:
		return;
	}
}
