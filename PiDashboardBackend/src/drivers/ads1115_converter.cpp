#include "ads1115_converter.h"

int8_t driver::sensors::ads1115::converter::init(uint8_t device_reg, std::function<int8_t(int, uint8_t, uint8_t*, uint16_t)> read_function, std::function<int8_t(int, uint8_t, const uint8_t*, uint16_t)> write_function, std::function<int8_t(const std::string, uint8_t, int&)> open_device_function, std::function<int8_t(int&)> close_device_function)
{
	m_dev_id = device_reg;
	m_read_function = read_function;
	m_write_function = write_function;
	m_open_device_function = open_device_function;
	m_close_device_function = close_device_function;

	if (m_open_device_function(manager::i2c_manager::DEFAULT_PI_I2C_PATH, m_dev_id, m_file_handle) != OK)
	{
		std::cerr << "ADS1115 [init] Error: Could not establish connection with device." << std::endl;
		return DEVICE_NOT_FOUND;
	}

	return OK;
}

bool driver::sensors::ads1115::converter::is_initialized()
{
	if (m_file_handle == 0)
	{
		return false;
	}
	else
	{
		return true;
	}
}

int8_t driver::sensors::ads1115::converter::close()
{
	return m_close_device_function(m_file_handle);
}

int8_t driver::sensors::ads1115::converter::soft_reset()
{
	uint8_t data[1] = { RESET_CMD };
	if (write_operation(m_file_handle, RESET_REG, data, 1) != OK)
	{
		std::cerr << "ADS1115 [soft_reset] Error: Could not write soft reset command to device" << std::endl;
		return COMMUNICATION_FAIL;
	}

	return OK;
}

int8_t driver::sensors::ads1115::converter::start_single_conversion()
{
	uint8_t current_settings[REG_READ_LEN] = { 0, 0 };
	// Reading only the first byte is enough since all neccessary information is located there.
	if (read_operation(m_file_handle, CONFIG_REG, current_settings) != OK)
	{
		std::cerr << "ADS1115 [start_single_conversion] Error: Could not read first byte of current device settings" << std::endl;
		return COMMUNICATION_FAIL;
	}

	if ((uint8_t)is_bit_set(current_settings[0], 0) == (uint8_t)ads1115_operation_mode::CONTINUOUS)
	{
		return WARNING;
	}

	set_bit(current_settings[0], 7, true); // Set OS bit (7th) to true
	if (write_operation(m_file_handle, CONFIG_REG, current_settings) != OK)
	{
		std::cerr << "ADS1115 [start_single_conversion] Error: Could not write first byte of current device settings" << std::endl;
		return COMMUNICATION_FAIL;
	}

	return OK;
}

int8_t driver::sensors::ads1115::converter::is_converting(bool& is_converting)
{
	uint8_t current_settings[REG_READ_LEN] = { 0, 0 };
	// Reading only the first byte is enough since all neccessary information is located there.
	if (read_operation(m_file_handle, CONFIG_REG, current_settings) != OK)
	{
		std::cerr << "ADS1115 [is_converting] Error: Could not read first byte of current device settings" << std::endl;
		return COMMUNICATION_FAIL;
	}

	is_bit_set(current_settings[0], 7) ? is_converting = false : is_converting = true;
	return OK;
}

int8_t driver::sensors::ads1115::converter::get_multiplexer_setting(ads1115_multiplexer& current_multiplexer_setting)
{
	uint8_t current_settings[REG_READ_LEN] = { 0, 0 };
	// Reading only the first byte is enough since all neccessary information is located there.
	if (read_operation(m_file_handle, CONFIG_REG, current_settings) != OK)
	{
		std::cerr << "ADS1115 [get_multiplexer_setting] Error: Could not read first byte of current device settings" << std::endl;
		return COMMUNICATION_FAIL;
	}
	current_multiplexer_setting = parse_multiplexer_value(current_settings[0]);

	return OK;
}

int8_t driver::sensors::ads1115::converter::get_gain_amplifier_setting(ads1115_gain_amplifier& current_gain_amplifier_setting)
{
	uint8_t current_settings[REG_READ_LEN] = { 0, 0 };
	// Reading only the first byte is enough since all neccessary information is located there.
	if (read_operation(m_file_handle, CONFIG_REG, current_settings) != OK)
	{
		std::cerr << "ADS1115 [get_gain_amplifier_setting] Error: Could not read first byte of current device settings" << std::endl;
		return COMMUNICATION_FAIL;
	}
	current_gain_amplifier_setting = parse_gain_amplifier_value(current_settings[0]);

	return OK;
}

int8_t driver::sensors::ads1115::converter::get_operation_mode_setting(ads1115_operation_mode& current_operation_mode_setting)
{
	uint8_t current_settings[REG_READ_LEN] = { 0, 0 };
	// Reading only the first byte is enough since all neccessary information is located there.
	if (read_operation(m_file_handle, CONFIG_REG, current_settings) != OK)
	{
		std::cerr << "ADS1115 [get_operation_mode_setting] Error: Could not read first byte of current device settings" << std::endl;
		return COMMUNICATION_FAIL;
	}
	current_operation_mode_setting = parse_operation_mode_value(current_settings[0]);

	return OK;
}

int8_t driver::sensors::ads1115::converter::get_data_rate_setting(ads1115_data_rate& current_data_rate_setting)
{
	uint8_t current_settings[REG_READ_LEN] = { 0, 0 };
	if (read_operation(m_file_handle, CONFIG_REG, current_settings) != OK)
	{
		std::cerr << "ADS1115 [get_data_rate_setting] Error: Could not read current device settings" << std::endl;
		return COMMUNICATION_FAIL;
	}
	current_data_rate_setting = parse_data_rate_value(current_settings[1]);

	return OK;
}

int8_t driver::sensors::ads1115::converter::get_comparator_mode_setting(ads1115_comparator_mode& current_comparator_mode_setting)
{
	uint8_t current_settings[REG_READ_LEN] = { 0, 0 };
	if (read_operation(m_file_handle, CONFIG_REG, current_settings) != OK)
	{
		std::cerr << "ADS1115 [get_comparator_mode_setting] Error: Could not read current device settings" << std::endl;
		return COMMUNICATION_FAIL;
	}
	current_comparator_mode_setting = parse_comparator_mode_value(current_settings[1]);

	return OK;
}

int8_t driver::sensors::ads1115::converter::get_comparator_polarity_setting(ads1115_alert_polarity& current_comparator_polarity_setting)
{
	uint8_t current_settings[REG_READ_LEN] = { 0, 0 };
	if (read_operation(m_file_handle, CONFIG_REG, current_settings) != OK)
	{
		std::cerr << "ADS1115 [get_comparator_polarity_setting] Error: Could not read current device settings" << std::endl;
		return COMMUNICATION_FAIL;
	}
	current_comparator_polarity_setting = parse_comparator_polarity_value(current_settings[1]);

	return OK;
}

int8_t driver::sensors::ads1115::converter::get_comparator_latching_setting(ads1115_alert_latching& current_comparator_latching_setting)
{
	uint8_t current_settings[REG_READ_LEN] = { 0, 0 };
	if (read_operation(m_file_handle, CONFIG_REG, current_settings) != OK)
	{
		std::cerr << "ADS1115 [get_comparator_latching_setting] Error: Could not read current device settings" << std::endl;
		return COMMUNICATION_FAIL;
	}
	current_comparator_latching_setting = parse_comparator_latching_value(current_settings[1]);

	return OK;
}

int8_t driver::sensors::ads1115::converter::get_comparator_queue_setting(ads1115_alert_queueing& current_comparator_queue_setting)
{
	uint8_t current_settings[REG_READ_LEN] = { 0, 0 };
	if (read_operation(m_file_handle, CONFIG_REG, current_settings) != OK)
	{
		std::cerr << "ADS1115 [get_comparator_queue_setting] Error: Could not read current device settings" << std::endl;
		return COMMUNICATION_FAIL;
	}
	current_comparator_queue_setting = parse_comparator_queueing_value(current_settings[1]);

	return OK;
}

int8_t driver::sensors::ads1115::converter::get_settings(ads1115_configuration& current_settings)
{
	uint8_t current_raw_settings[REG_READ_LEN] = { 0, 0 };
	if (read_operation(m_file_handle, CONFIG_REG, current_raw_settings) != OK)
	{
		std::cerr << "ADS1115 [get_settings] Error: Could not read current device settings" << std::endl;
		return COMMUNICATION_FAIL;
	}

	current_settings.multiplexer = parse_multiplexer_value(current_raw_settings[0]);
	current_settings.gain_amplifier = parse_gain_amplifier_value(current_raw_settings[0]);
	current_settings.operation_mode = parse_operation_mode_value(current_raw_settings[0]);
	current_settings.data_rate = parse_data_rate_value(current_raw_settings[1]);
	current_settings.comparator_mode = parse_comparator_mode_value(current_raw_settings[1]);
	current_settings.alert_polarity = parse_comparator_polarity_value(current_raw_settings[1]);
	current_settings.alert_latching = parse_comparator_latching_value(current_raw_settings[1]);
	current_settings.alert_queueing = parse_comparator_queueing_value(current_raw_settings[1]);

	return OK;
}

int8_t driver::sensors::ads1115::converter::set_multiplexer_setting(ads1115_multiplexer new_multiplexer_setting)
{
	uint8_t raw_settings[REG_READ_LEN] = { 0, 0 };
	// Reading only the first byte is enough since all neccessary information is located there.
	if (read_operation(m_file_handle, CONFIG_REG, raw_settings) != OK)
	{
		std::cerr << "ADS1115 [set_multiplexer_setting] Error: Could not read current device settings" << std::endl;
		return COMMUNICATION_FAIL;
	}

	set_bits(raw_settings[0], (uint8_t)new_multiplexer_setting, MULTIPLEXER_MASK);
	if (write_operation(m_file_handle, CONFIG_REG, raw_settings) != OK)
	{
		std::cerr << "ADS1115 [set_multiplexer_setting] Error: Could not write new device settings" << std::endl;
		return COMMUNICATION_FAIL;
	}

	return OK;
}

int8_t driver::sensors::ads1115::converter::set_gain_amplifier_setting(ads1115_gain_amplifier new_gain_amplifier_setting)
{
	uint8_t raw_settings[REG_READ_LEN] = { 0, 0 };
	// Reading only the first byte is enough since all neccessary information is located there.
	if (read_operation(m_file_handle, CONFIG_REG, raw_settings) != OK)
	{
		std::cerr << "ADS1115 [set_gain_amplifier_setting] Error: Could not read current device settings" << std::endl;
		return COMMUNICATION_FAIL;
	}

	set_bits(raw_settings[0], (uint8_t)new_gain_amplifier_setting, GAIN_AMPLIFIER_MASK);
	if (write_operation(m_file_handle, CONFIG_REG, raw_settings) != OK)
	{
		std::cerr << "ADS1115 [set_gain_amplifier_setting] Error: Could not write new device settings" << std::endl;
		return COMMUNICATION_FAIL;
	}

	return OK;
}

int8_t driver::sensors::ads1115::converter::set_operation_mode_setting(ads1115_operation_mode new_operation_mode_setting)
{
	uint8_t raw_settings[REG_READ_LEN] = { 0, 0 };
	// Reading only the first byte is enough since all neccessary information is located there.
	if (read_operation(m_file_handle, CONFIG_REG, raw_settings) != OK)
	{
		std::cerr << "ADS1115 [set_operation_mode_setting] Error: Could not read current device settings" << std::endl;
		return COMMUNICATION_FAIL;
	}

	set_bits(raw_settings[0], (uint8_t)new_operation_mode_setting, OPERATION_MODE_MASK);
	if (write_operation(m_file_handle, CONFIG_REG, raw_settings) != OK)
	{
		std::cerr << "ADS1115 [set_operation_mode_setting] Error: Could not write new device settings" << std::endl;
		return COMMUNICATION_FAIL;
	}

	return OK;
}

int8_t driver::sensors::ads1115::converter::set_data_rate_setting(ads1115_data_rate new_data_rate_setting)
{
	uint8_t raw_settings[REG_READ_LEN] = { 0, 0 };
	if (read_operation(m_file_handle, CONFIG_REG, raw_settings) != OK)
	{
		std::cerr << "ADS1115 [set_data_rate_setting] Error: Could not read current device settings" << std::endl;
		return COMMUNICATION_FAIL;
	}

	set_bits(raw_settings[1], (uint8_t)new_data_rate_setting, DATA_RATE_MASK);
	if (write_operation(m_file_handle, CONFIG_REG, raw_settings) != OK)
	{
		std::cerr << "ADS1115 [set_data_rate_setting] Error: Could not write new device settings" << std::endl;
		return COMMUNICATION_FAIL;
	}

	return OK;
}

int8_t driver::sensors::ads1115::converter::set_comparator_mode_setting(ads1115_comparator_mode new_comparator_mode_setting)
{
	uint8_t raw_settings[REG_READ_LEN] = { 0, 0 };
	if (read_operation(m_file_handle, CONFIG_REG, raw_settings) != OK)
	{
		std::cerr << "ADS1115 [set_comparator_mode_setting] Error: Could not read current device settings" << std::endl;
		return COMMUNICATION_FAIL;
	}

	set_bits(raw_settings[1], (uint8_t)new_comparator_mode_setting, COMPARATOR_MODE_MASK);
	if (write_operation(m_file_handle, CONFIG_REG, raw_settings) != OK)
	{
		std::cerr << "ADS1115 [set_comparator_mode_setting] Error: Could not write new device settings" << std::endl;
		return COMMUNICATION_FAIL;
	}

	return OK;
}

int8_t driver::sensors::ads1115::converter::set_comparator_polarity_setting(ads1115_alert_polarity new_comparator_polarity_setting)
{
	uint8_t raw_settings[REG_READ_LEN] = { 0, 0 };
	if (read_operation(m_file_handle, CONFIG_REG, raw_settings) != OK)
	{
		std::cerr << "ADS1115 [set_comparator_polarity_setting] Error: Could not read current device settings" << std::endl;
		return COMMUNICATION_FAIL;
	}

	set_bits(raw_settings[1], (uint8_t)new_comparator_polarity_setting, COMPARATOR_POLARITY_MASK);
	if (write_operation(m_file_handle, CONFIG_REG, raw_settings) != OK)
	{
		std::cerr << "ADS1115 [set_comparator_polarity_setting] Error: Could not write new device settings" << std::endl;
		return COMMUNICATION_FAIL;
	}

	return OK;
}

int8_t driver::sensors::ads1115::converter::set_comparator_latching_setting(ads1115_alert_latching new_comparator_latching_setting)
{
	uint8_t raw_settings[REG_READ_LEN] = { 0, 0 };
	if (read_operation(m_file_handle, CONFIG_REG, raw_settings) != OK)
	{
		std::cerr << "ADS1115 [set_comparator_latching_setting] Error: Could not read current device settings" << std::endl;
		return COMMUNICATION_FAIL;
	}

	set_bits(raw_settings[1], (uint8_t)new_comparator_latching_setting, COMPARATOR_LATCHING_MASK);
	if (write_operation(m_file_handle, CONFIG_REG, raw_settings) != OK)
	{
		std::cerr << "ADS1115 [set_comparator_latching_setting] Error: Could not write new device settings" << std::endl;
		return COMMUNICATION_FAIL;
	}

	return OK;
}

int8_t driver::sensors::ads1115::converter::set_comparator_queue_setting(ads1115_alert_queueing new_comparator_queue_setting)
{
	uint8_t raw_settings[REG_READ_LEN] = { 0, 0 };
	if (read_operation(m_file_handle, CONFIG_REG, raw_settings) != OK)
	{
		std::cerr << "ADS1115 [set_comparator_queue_setting] Error: Could not read current device settings" << std::endl;
		return COMMUNICATION_FAIL;
	}

	set_bits(raw_settings[1], (uint8_t)new_comparator_queue_setting, COMPARATOR_QUEUEING_MASK);
	if (write_operation(m_file_handle, CONFIG_REG, raw_settings) != OK)
	{
		std::cerr << "ADS1115 [set_comparator_queue_setting] Error: Could not write new device settings" << std::endl;
		return COMMUNICATION_FAIL;
	}

	return OK;
}

int8_t driver::sensors::ads1115::converter::set_settings(ads1115_configuration new_settings)
{
	uint8_t raw_settings[REG_READ_LEN] = { 0, 0 };
	set_bits(raw_settings[0], (uint8_t)new_settings.multiplexer, MULTIPLEXER_MASK);
	set_bits(raw_settings[0], (uint8_t)new_settings.gain_amplifier, GAIN_AMPLIFIER_MASK);
	set_bits(raw_settings[0], (uint8_t)new_settings.operation_mode, OPERATION_MODE_MASK);
	set_bits(raw_settings[1], (uint8_t)new_settings.data_rate, DATA_RATE_MASK);
	set_bits(raw_settings[1], (uint8_t)new_settings.comparator_mode, COMPARATOR_MODE_MASK);
	set_bits(raw_settings[1], (uint8_t)new_settings.alert_polarity, COMPARATOR_POLARITY_MASK);
	set_bits(raw_settings[1], (uint8_t)new_settings.alert_latching, COMPARATOR_LATCHING_MASK);
	set_bits(raw_settings[1], (uint8_t)new_settings.alert_queueing, COMPARATOR_QUEUEING_MASK);

	if (write_operation(m_file_handle, CONFIG_REG, raw_settings) != OK)
	{
		std::cerr << "ADS1115 [set_settings] Error: Could not write new device settings" << std::endl;
		return COMMUNICATION_FAIL;
	}

	return OK;
}

int8_t driver::sensors::ads1115::converter::restore_default_settings()
{
	uint8_t default_settings[REG_READ_LEN] = { DEFAULT_SETTINGS_BYTE_1, DEFAULT_SETTINGS_BYTE_2 };
	if (write_operation(m_file_handle, CONFIG_REG, default_settings) != OK)
	{
		std::cerr << "ADS1115 [restore_default_settings] Error: Could not restore default device settings" << std::endl;
		return COMMUNICATION_FAIL;
	}

	return OK;
}

int8_t driver::sensors::ads1115::converter::get_converted_data(double& converted_data)
{
	uint8_t raw_converted[REG_READ_LEN] = { 0, 0 };
	if (read_operation(m_file_handle, CONVERSION_REG, raw_converted) != OK)
	{
		std::cerr << "ADS1115 [get_converted_data] Error: Could not read converted data." << std::endl;
		return COMMUNICATION_FAIL;
	}


	converted_data = convert_to_voltage(combine_bytes(raw_converted[0], raw_converted[1]));
	return OK;
}

double driver::sensors::ads1115::converter::convert_to_voltage(uint16_t raw_data)
{
	ads1115_gain_amplifier gain;
	if (get_gain_amplifier_setting(gain) != OK)
	{
		std::cerr << "ADS1115 [get_converted_data] Error: Could not read current gain amplifier setting." << std::endl;
		return COMMUNICATION_FAIL;
	}
	double bit_factor;
	switch (gain)
	{
	case driver::sensors::ads1115::ads1115_gain_amplifier::GAIN_6144_mV:
		bit_factor = 6144.0 / 32767.0;
		break;
	case driver::sensors::ads1115::ads1115_gain_amplifier::GAIN_4096_mV:
		bit_factor = 4096.0 / 32767.0;
		break;
	case driver::sensors::ads1115::ads1115_gain_amplifier::GAIN_2048_mV:
		bit_factor = 2048.0 / 32767.0;
		break;
	case driver::sensors::ads1115::ads1115_gain_amplifier::GAIN_1024_mV:
		bit_factor = 1024.0 / 32767.0;
		break;
	case driver::sensors::ads1115::ads1115_gain_amplifier::GAIN_512_mV:
		bit_factor = 512.0 / 32767.0;
		break;
	case driver::sensors::ads1115::ads1115_gain_amplifier::GAIN_256_mV:
		bit_factor = 256.0 / 32767.0;
		break;
	default:
		bit_factor = 1.0;
		break;
	}
	return (raw_data * bit_factor) / 1000.0;
}

int8_t driver::sensors::ads1115::converter::get_upper_threshold(uint16_t& upper_threshold)
{
	uint8_t raw_threshold[REG_READ_LEN] = { 0, 0 };
	if (read_operation(m_file_handle, HIGH_THRESHOLD_REG, raw_threshold) != OK)
	{
		std::cerr << "ADS1115 [get_upper_threshold] Error: Could not read upper threshold." << std::endl;
		return COMMUNICATION_FAIL;
	}

	upper_threshold = combine_bytes(raw_threshold[0], raw_threshold[1]);
	return OK;
}

int8_t driver::sensors::ads1115::converter::get_lower_threshold(uint16_t& lower_threshold)
{
	uint8_t raw_threshold[REG_READ_LEN] = { 0, 0 };
	if (read_operation(m_file_handle, LOW_THRESHOLD_REG, raw_threshold) != OK)
	{
		std::cerr << "ADS1115 [get_lower_threshold] Error: Could not read lower threshold." << std::endl;
		return COMMUNICATION_FAIL;
	}

	lower_threshold = combine_bytes(raw_threshold[0], raw_threshold[1]);
	return OK;
}

int8_t driver::sensors::ads1115::converter::get_thresholds(uint16_t& lower_threshold, uint16_t& upper_threshold)
{
	if (get_upper_threshold(upper_threshold) != OK)
	{
		std::cerr << "ADS1115 [get_thresholds] Error: Could not read upper threshold." << std::endl;
		return COMMUNICATION_FAIL;
	}
	if (get_lower_threshold(lower_threshold) != OK)
	{
		std::cerr << "ADS1115 [get_thresholds] Error: Could not read lower threshold." << std::endl;
		return COMMUNICATION_FAIL;
	}

	return OK;
}

int8_t driver::sensors::ads1115::converter::set_upper_threshold(uint16_t upper_threshold)
{
	uint8_t splitted_threshold[REG_READ_LEN] = { 0, 0 };
	split_bytes(upper_threshold, splitted_threshold[0], splitted_threshold[1]);
	if (write_operation(m_file_handle, HIGH_THRESHOLD_REG, splitted_threshold) != OK)
	{
		std::cerr << "ADS1115 [set_upper_threshold] Error: Could not write upper threshold." << std::endl;
		return COMMUNICATION_FAIL;
	}

	return OK;
}

int8_t driver::sensors::ads1115::converter::set_lower_threshold(uint16_t lower_threshold)
{
	uint8_t splitted_threshold[REG_READ_LEN] = { 0, 0 };
	split_bytes(lower_threshold, splitted_threshold[0], splitted_threshold[1]);
	if (write_operation(m_file_handle, LOW_THRESHOLD_REG, splitted_threshold) != OK)
	{
		std::cerr << "ADS1115 [set_lower_threshold] Error: Could not write lower threshold." << std::endl;
		return COMMUNICATION_FAIL;
	}

	return OK;
}

int8_t driver::sensors::ads1115::converter::set_thresholds(uint16_t lower_threshold, uint16_t upper_threshold)
{
	if (set_upper_threshold(upper_threshold) != OK)
	{
		std::cerr << "ADS1115 [set_thresholds] Error: Could not read upper threshold." << std::endl;
		return COMMUNICATION_FAIL;
	}
	if (set_lower_threshold(lower_threshold) != OK)
	{
		std::cerr << "ADS1115 [set_thresholds] Error: Could not read lower threshold." << std::endl;
		return COMMUNICATION_FAIL;
	}

	return OK;
}

int8_t driver::sensors::ads1115::converter::restore_default_upper_thresholds()
{
	uint8_t default_threshold[REG_READ_LEN] = { DEFAULT_HIGH_THRES_BYTE_1, DEFAULT_HIGH_THRES_BYTE_2 };
	if (write_operation(m_file_handle, HIGH_THRESHOLD_REG, default_threshold) != OK)
	{
		std::cerr << "ADS1115 [restore_default_upper_thresholds] Error: Could not restore default high threshold" << std::endl;
		return COMMUNICATION_FAIL;
	}

	return OK;
}

int8_t driver::sensors::ads1115::converter::restore_default_lower_thresholds()
{
	uint8_t default_threshold[REG_READ_LEN] = { DEFAULT_LOW_THRES_BYTE_1, DEFAULT_LOW_THRES_BYTE_2 };
	if (write_operation(m_file_handle, LOW_THRESHOLD_REG, default_threshold) != OK)
	{
		std::cerr << "ADS1115 [restore_default_lower_thresholds] Error: Could not restore default low threshold" << std::endl;
		return COMMUNICATION_FAIL;
	}

	return OK;
}

int8_t driver::sensors::ads1115::converter::restore_default_thresholds()
{
	if (restore_default_upper_thresholds() != OK)
	{
		std::cerr << "ADS1115 [restore_default_thresholds] Error: Could not restore default upper threshold." << std::endl;
		return COMMUNICATION_FAIL;
	}
	if (restore_default_lower_thresholds() != OK)
	{
		std::cerr << "ADS1115 [restore_default_thresholds] Error: Could not restore default lower threshold." << std::endl;
		return COMMUNICATION_FAIL;
	}

	return OK;
}

int8_t driver::sensors::ads1115::converter::get_all_raw_data(uint8_t* all_data)
{
	// No need to implement this method for this device
	return OK;
}

driver::sensors::ads1115::ads1115_multiplexer driver::sensors::ads1115::converter::parse_multiplexer_value(uint8_t raw_data)
{
	switch (value_of_bits(raw_data, MULTIPLEXER_BIT_1, MULTIPLEXER_BIT_3))
	{
	case 0:
		return ads1115_multiplexer::POSITIVE_0_AND_NEGATIVE_1;
	case 1:
		return ads1115_multiplexer::POSITIVE_0_AND_NEGATIVE_3;
	case 2:
		return ads1115_multiplexer::POSITIVE_1_AND_NEGATIVE_3;
	case 3:
		return ads1115_multiplexer::POSITIVE_2_AND_NEGATIVE_3;
	case 4:
		return ads1115_multiplexer::POSITIVE_0_AND_NEGATIVE_GND;
	case 5:
		return ads1115_multiplexer::POSITIVE_1_AND_NEGATIVE_GND;
	case 6:
		return ads1115_multiplexer::POSITIVE_2_AND_NEGATIVE_GND;
	case 7:
		return ads1115_multiplexer::POSITIVE_3_AND_NEGATIVE_GND;
	default:
		return ads1115_multiplexer::POSITIVE_0_AND_NEGATIVE_1;
	}
}

driver::sensors::ads1115::ads1115_gain_amplifier driver::sensors::ads1115::converter::parse_gain_amplifier_value(uint8_t raw_data)
{
	switch (value_of_bits(raw_data, GAIN_AMPLIFIER_BIT_1, GAIN_AMPLIFIER_BIT_3))
	{
	case 0:
		return ads1115_gain_amplifier::GAIN_6144_mV;
	case 1:
		return ads1115_gain_amplifier::GAIN_4096_mV;
	case 2:
		return ads1115_gain_amplifier::GAIN_2048_mV;
	case 3:
		return ads1115_gain_amplifier::GAIN_1024_mV;
	case 4:
		return ads1115_gain_amplifier::GAIN_512_mV;
	case 5:
	case 6:
	case 7:
		return ads1115_gain_amplifier::GAIN_256_mV;
	default:
		return ads1115_gain_amplifier::GAIN_2048_mV;
	}
}

driver::sensors::ads1115::ads1115_operation_mode driver::sensors::ads1115::converter::parse_operation_mode_value(uint8_t raw_data)
{
	if (is_bit_set(raw_data, OPERATION_MODE_BIT))
	{
		return ads1115_operation_mode::SINGLE_SHOT;
	}
	else
	{
		return ads1115_operation_mode::CONTINUOUS;
	}
}

driver::sensors::ads1115::ads1115_data_rate driver::sensors::ads1115::converter::parse_data_rate_value(uint8_t raw_data)
{
	switch (value_of_bits(raw_data, GAIN_AMPLIFIER_BIT_1, GAIN_AMPLIFIER_BIT_3))
	{
	case 0:
		return ads1115_data_rate::RATE_8_SPS;
	case 1:
		return ads1115_data_rate::RATE_16_SPS;
	case 2:
		return ads1115_data_rate::RATE_32_SPS;
	case 3:
		return ads1115_data_rate::RATE_64_SPS;
	case 4:
		return ads1115_data_rate::RATE_128_SPS;
	case 5:
		return ads1115_data_rate::RATE_250_SPS;
	case 6:
		return ads1115_data_rate::RATE_475_SPS;
	case 7:
		return ads1115_data_rate::RATE_860_SPS;
	default:
		return ads1115_data_rate::RATE_128_SPS;
	}
}

driver::sensors::ads1115::ads1115_comparator_mode driver::sensors::ads1115::converter::parse_comparator_mode_value(uint8_t raw_data)
{
	if (is_bit_set(raw_data, COMPARATOR_MODE_BIT))
	{
		return ads1115_comparator_mode::WINDOW;
	}
	else
	{
		return ads1115_comparator_mode::HYSTERESIS;
	}
}

driver::sensors::ads1115::ads1115_alert_polarity driver::sensors::ads1115::converter::parse_comparator_polarity_value(uint8_t raw_data)
{
	if (is_bit_set(raw_data, COMPARATOR_POL_BIT))
	{
		return ads1115_alert_polarity::ACTIVE_HIGH;
	}
	else
	{
		return ads1115_alert_polarity::ACTIVE_LOW;
	}
}

driver::sensors::ads1115::ads1115_alert_latching driver::sensors::ads1115::converter::parse_comparator_latching_value(uint8_t raw_data)
{
	if (is_bit_set(raw_data, COMPARATOR_LAT_BIT))
	{
		return ads1115_alert_latching::ACTIVE;
	}
	else
	{
		return ads1115_alert_latching::DISABLED;
	}
}

driver::sensors::ads1115::ads1115_alert_queueing driver::sensors::ads1115::converter::parse_comparator_queueing_value(uint8_t raw_data)
{
	switch (value_of_bits(raw_data, COMPARATOR_QUEUE_BIT_1, COMPARATOR_QUEUE_BIT_2))
	{
	case 0:
		return ads1115_alert_queueing::ASSERT_1_CONVERSION;
	case 1:
		return ads1115_alert_queueing::ASSERT_2_CONVERSIONS;
	case 2:
		return ads1115_alert_queueing::ASSERT_4_CONVERSIONS;
	case 3:
		return ads1115_alert_queueing::DISABLED;
	default:
		return ads1115_alert_queueing::DISABLED;
	}
}

int8_t driver::sensors::ads1115::converter::write_operation(int handle, uint8_t address, const uint8_t* buffer, uint16_t length)
{
	if (handle == 0)
	{
		std::cerr << "Device #" << handle << " is not open." << std::endl;
		return -1;
	}

	if (m_write_function != nullptr)
	{
		return m_write_function(handle, address, buffer, length);
	}

	uint8_t write_buffer[3] = { 0, 0, 0 };
	write_buffer[0] = address;
	write_buffer[1] = buffer[0];
	write_buffer[2] = buffer[1];
	if (write(handle, write_buffer, length + 1) != length + 1)
	{
		std::cerr << "Could not switch pointer to register address 0x" << std::hex << address << std::dec << " and write data 0x" 
			<< std::hex << buffer[0] << std::dec << "', 0x" << std::hex << buffer[0] << std::dec << ". Error: " << strerror(errno) << std::endl;
		return COMMUNICATION_FAIL;
	}

	return OK;
}

int8_t driver::sensors::ads1115::converter::read_operation(int handle, uint8_t address, uint8_t* buffer, uint16_t length)
{
	if (handle == 0)
	{
		std::cerr << "Device #" << handle << " is not open." << std::endl;
		return -1;
	}

	if (m_read_function != nullptr)
	{
		return m_write_function(handle, address, buffer, length);
	}


	if (write(handle, &address, 1) != 1)
	{
		std::cerr << "Could not switch to register with address 0x" << std::hex << address << std::dec << ". Error: " << strerror(errno) << std::endl;
		return COMMUNICATION_FAIL;
	}

	if (read(handle, buffer, length) != length)
	{
		std::cerr << "Could not read data of length " << length << " from address 0x" << std::hex << address << std::dec << ". Error: " << strerror(errno) << std::endl;
		return COMMUNICATION_FAIL;
	}
	
	return OK;
}
