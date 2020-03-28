#include "ADS1115.h"
#include "../../exceptions/I2CException.h"
#include "../../utils/BitManipulation.h"
#include "../../utils/Helper.h"
#include "../../utils/I2CManager.h"

#include <cerrno>
#include <cstdio>
#include <unistd.h>
#include <fcntl.h>
#include <cstring>
#include <sys/stat.h>
#include <sys/types.h>
#include <bits/quoted_string.h>

void hal::sensors::i2c::ads1115::ADS1115::trigger_measurement(const SensorType type)
{
	for (auto i = m_callbacks[type].begin(); i != m_callbacks[type].end(); ++i)
	{
		if (type == SensorType::CONVERTER)
		{
			try
			{
				(*i)->callback(std::to_string(get_converted_data()));
			}
			catch (exception::HALException* ex)
			{
				throw exception::HALException("ADS1115", "trigger_measurement",
														std::string("Could not trigger conversion:\n").append(ex->to_string()));
			}
		}
		else
		{
			throw exception::HALException("ADS1115", "trigger_measurement", "Invalid sensor type.");
		}
	}
}

void hal::sensors::i2c::ads1115::ADS1115::configure(const SensorSetting setting, const std::string& configuration)
{
	if (setting == SensorSetting::COMPARATOR_LATCHING)
	{
		try
		{
			set_comparator_latching_setting(EnumConverter::string_to_alert_latching(configuration));
		}
		catch (exception::HALException* ex)
		{
			throw exception::HALException("ADS1115", "configure",
													std::string("Could not change comparator latching setting:\n").append(ex->to_string()));
		}
	}
	else if (setting == SensorSetting::COMPARATOR_MODE)
	{
		try
		{
			set_comparator_mode_setting(EnumConverter::string_to_comparator_mode(configuration));
		}
		catch (exception::HALException* ex)
		{
			throw exception::HALException("ADS1115", "configure",
													std::string("Could not change comparator mode setting:\n").append(ex->to_string()));
		}
	}
	else if (setting == SensorSetting::COMPARATOR_QUEUE)
	{
		try
		{
			set_comparator_queue_setting(EnumConverter::string_to_alert_queueing(configuration));
		}
		catch (exception::HALException* ex)
		{
			throw exception::HALException("ADS1115", "configure",
													std::string("Could not change comparator queue setting:\n").append(ex->to_string()));
		}
	}
	else if (setting == SensorSetting::PIN_POLARITY)
	{
		try
		{
			set_comparator_polarity_setting(EnumConverter::string_to_alert_polarity(configuration));
		}
		catch (exception::HALException* ex)
		{
			throw exception::HALException("ADS1115", "configure",
													std::string("Could not change pin polarity setting:\n").append(ex->to_string()));
		}
	}
	else if (setting == SensorSetting::DATA_RATE)
	{
		try
		{
			set_data_rate_setting(EnumConverter::string_to_data_rate(configuration));
		}
		catch (exception::HALException* ex)
		{
			throw exception::HALException("ADS1115", "configure",
													std::string("Could not change data rate setting:\n").append(ex->to_string()));
		}
	}
	else if (setting == SensorSetting::GAIN_AMPLIFIER)
	{
		try
		{
			set_gain_amplifier_setting(EnumConverter::string_to_gain_amplifier(configuration));
		}
		catch (exception::HALException* ex)
		{
			throw exception::HALException("ADS1115", "configure",
													std::string("Could not change gain amplifier setting:\n").append(ex->to_string()));
		}
	}
	else if (setting == SensorSetting::THRESHOLD)
	{
		try
		{
			if (Helper::string_contains_separator(configuration))
			{
				std::vector<uint16_t> thresholds;
				Helper::string_to_array(thresholds, configuration);
				if (thresholds.size() == 2)
				{
					set_thresholds(thresholds[0], thresholds[1]);
				}
			}
		}
		catch (exception::HALException* ex)
		{
			throw exception::HALException("ADS1115", "configure",
													std::string("Could not change threshold settings:\n").append(ex->to_string()));
		}
	}
	else if (setting == SensorSetting::MULTIPLEXER)
	{
		try
		{
			set_multiplexer_setting(EnumConverter::string_to_multiplexer(configuration));
		}
		catch (exception::HALException* ex)
		{
			throw exception::HALException("ADS1115", "configure",
													std::string("Could not change multiplexer setting:\n").append(ex->to_string()));
		}
	}
}

std::string hal::sensors::i2c::ads1115::ADS1115::get_configuration(const SensorSetting setting)
{
	if (setting == SensorSetting::COMPARATOR_QUEUE)
	{
		try
		{
			return EnumConverter::enum_to_string(get_comparator_queue_setting());
		}
		catch (exception::HALException* ex)
		{
			throw exception::HALException("ADS1115", "get_configuration",
													std::string("Could not get comparator queue setting:\n").append(ex->to_string()));
		}
	}
	if (setting == SensorSetting::COMPARATOR_LATCHING)
	{
		try
		{
			return EnumConverter::enum_to_string(get_comparator_latching_setting());
		}
		catch (exception::HALException* ex)
		{
			throw exception::HALException("ADS1115", "get_configuration",
													std::string("Could not get comparator latching setting:\n").append(ex->to_string()));
		}
	}
	if (setting == SensorSetting::PIN_POLARITY)
	{
		try
		{
			return EnumConverter::enum_to_string(get_comparator_polarity_setting());
		}
		catch (exception::HALException* ex)
		{
			throw exception::HALException("ADS1115", "get_configuration",
													std::string("Could not get comparator polarity setting:\n").append(ex->to_string()));
		}
	}
	if (setting == SensorSetting::COMPARATOR_MODE)
	{
		try
		{
			return EnumConverter::enum_to_string(get_comparator_mode_setting());
		}
		catch (exception::HALException* ex)
		{
			throw exception::HALException("ADS1115", "get_configuration",
													std::string("Could not get comparator mode setting:\n").append(ex->to_string()));
		}
	}
	if (setting == SensorSetting::DATA_RATE)
	{
		try
		{
			return EnumConverter::enum_to_string(get_data_rate_setting());
		}
		catch (exception::HALException* ex)
		{
			throw exception::HALException("ADS1115", "get_configuration",
													std::string("Could not get data rate setting:\n").append(ex->to_string()));
		}
	}
	if (setting == SensorSetting::GAIN_AMPLIFIER)
	{
		try
		{
			return EnumConverter::enum_to_string(get_gain_amplifier_setting());
		}
		catch (exception::HALException* ex)
		{
			throw exception::HALException("ADS1115", "get_configuration",
													std::string("Could not get gain amplifier setting:\n").append(ex->to_string()));
		}
	}
	if (setting == SensorSetting::MULTIPLEXER)
	{
		try
		{
			return EnumConverter::enum_to_string(get_multiplexer_setting());
		}
		catch (exception::HALException* ex)
		{
			throw exception::HALException("ADS1115", "get_configuration",
													std::string("Could not get multiplexer setting:\n").append(ex->to_string()));
		}
	}
	return "";
}

std::vector<hal::SensorSetting> hal::sensors::i2c::ads1115::ADS1115::available_configurations() noexcept
{
	return {
		SensorSetting::COMPARATOR_LATCHING,
		SensorSetting::COMPARATOR_MODE,
		SensorSetting::COMPARATOR_QUEUE,
		SensorSetting::DATA_RATE,
		SensorSetting::GAIN_AMPLIFIER,
		SensorSetting::THRESHOLD,
		SensorSetting::MULTIPLEXER
	};
}

void hal::sensors::i2c::ads1115::ADS1115::close()
{
	try
	{
		I2CManager::close_device(m_file_handle);
	}
	catch (exception::HALException* ex)
	{
		throw exception::HALException("ADS1115", "close", std::string("Could not close device connection:\n").append(ex->to_string()));
	}
}

void hal::sensors::i2c::ads1115::ADS1115::init(const uint8_t device_reg)
{
	m_dev_id = device_reg;

	try
	{
		I2CManager::open_device(I2CManager::DEFAULT_PI_I2C_PATH, m_dev_id, m_file_handle);
	}
	catch (exception::HALException* ex)
	{
		throw exception::HALException("ADS1115", "init",
												std::string("Could not establish connection with device:\n").append(ex->to_string()));
	}
}

bool hal::sensors::i2c::ads1115::ADS1115::is_initialized() const noexcept
{
	return m_file_handle != 0;
}

void hal::sensors::i2c::ads1115::ADS1115::soft_reset()
{
	uint8_t data[1] = {RESET_CMD};
	if (write_operation(m_file_handle, RESET_REG, data, 1) != OK)
	{
		throw exception::I2CException("ADS1115", "soft_reset", m_dev_id, RESET_REG, "Could not write soft reset command to device.");
	}
}

int8_t hal::sensors::i2c::ads1115::ADS1115::start_single_conversion()
{
	uint8_t current_settings[REG_READ_LEN] = {0, 0};
	// Reading only the first byte is enough since all necessary information is located there.
	if (read_operation(m_file_handle, CONFIG_REG, current_settings) != OK)
	{
		throw exception::I2CException("ADS1115", "start_single_conversion", m_dev_id, CONFIG_REG,
												"Could not read first byte of current device settings.");
	}

	if (static_cast<uint8_t>(BitManipulation::is_bit_set(current_settings[0], 0)) == static_cast<uint8_t>(OperationMode::CONTINUOUS))
	{
		return WARNING;
	}

	BitManipulation::set_bit(current_settings[0], 7, true); // Set OS bit (7th) to true
	if (write_operation(m_file_handle, CONFIG_REG, current_settings) != OK)
	{
		throw exception::I2CException("ADS1115", "start_single_conversion", m_dev_id, CONFIG_REG,
												"Could not write first byte of current device settings.");
	}

	return OK;
}

bool hal::sensors::i2c::ads1115::ADS1115::is_converting()
{
	uint8_t current_settings[REG_READ_LEN] = {0, 0};
	// Reading only the first byte is enough since all necessary information is located there.
	if (read_operation(m_file_handle, CONFIG_REG, current_settings) != OK)
	{
		throw exception::I2CException("ADS1115", "is_converting", m_dev_id, CONFIG_REG,
												"Could not read first byte of current device settings.");
	}

	try
	{
		return BitManipulation::is_bit_set(current_settings[0], 7);
	}
	catch (exception::HALException* ex)
	{
		throw exception::HALException("ADS1115", "is_converting",
												std::string("Could not check whether a certain bit of a byte is set:\n").append(ex->to_string()));
	}
}

hal::sensors::i2c::ads1115::Multiplexer hal::sensors::i2c::ads1115::ADS1115::get_multiplexer_setting()
{
	uint8_t current_settings[REG_READ_LEN] = {0, 0};
	// Reading only the first byte is enough since all necessary information is located there.
	if (read_operation(m_file_handle, CONFIG_REG, current_settings) != OK)
	{
		throw exception::I2CException("ADS1115", "get_multiplexer_setting", m_dev_id, CONFIG_REG,
												"Could not read first byte of current device settings.");
	}
	return parse_multiplexer_value(current_settings[0]);
}

hal::sensors::i2c::ads1115::GainAmplifier hal::sensors::i2c::ads1115::ADS1115::get_gain_amplifier_setting()
{
	uint8_t current_settings[REG_READ_LEN] = {0, 0};
	// Reading only the first byte is enough since all necessary information is located there.
	if (read_operation(m_file_handle, CONFIG_REG, current_settings) != OK)
	{
		throw exception::I2CException("ADS1115", "get_gain_amplifier_setting", m_dev_id, CONFIG_REG,
												"Could not read first byte of current device settings.");
	}
	return parse_gain_amplifier_value(current_settings[0]);
}

hal::sensors::i2c::ads1115::OperationMode hal::sensors::i2c::ads1115::ADS1115::get_operation_mode_setting()
{
	uint8_t current_settings[REG_READ_LEN] = {0, 0};
	// Reading only the first byte is enough since all necessary information is located there.
	if (read_operation(m_file_handle, CONFIG_REG, current_settings) != OK)
	{
		throw exception::I2CException("ADS1115", "get_operation_mode_setting", m_dev_id, CONFIG_REG,
												"Could not read first byte of current device settings.");
	}
	return parse_operation_mode_value(current_settings[0]);
}

hal::sensors::i2c::ads1115::DataRate hal::sensors::i2c::ads1115::ADS1115::get_data_rate_setting()
{
	uint8_t current_settings[REG_READ_LEN] = {0, 0};
	if (read_operation(m_file_handle, CONFIG_REG, current_settings) != OK)
	{
		throw exception::I2CException("ADS1115", "get_data_rate_setting", m_dev_id, CONFIG_REG,
												"Could not read first byte of current device settings.");
	}
	return parse_data_rate_value(current_settings[1]);
}

hal::sensors::i2c::ads1115::ComparatorMode hal::sensors::i2c::ads1115::ADS1115::get_comparator_mode_setting()
{
	uint8_t current_settings[REG_READ_LEN] = {0, 0};
	if (read_operation(m_file_handle, CONFIG_REG, current_settings) != OK)
	{
		throw exception::I2CException("ADS1115", "get_comparator_mode_setting", m_dev_id, CONFIG_REG,
												"Could not read first byte of current device settings.");
	}
	return parse_comparator_mode_value(current_settings[1]);
}

hal::sensors::i2c::ads1115::AlertPolarity hal::sensors::i2c::ads1115::ADS1115::get_comparator_polarity_setting()
{
	uint8_t current_settings[REG_READ_LEN] = {0, 0};
	if (read_operation(m_file_handle, CONFIG_REG, current_settings) != OK)
	{
		throw exception::I2CException("ADS1115", "get_comparator_polarity_setting", m_dev_id, CONFIG_REG,
												"Could not read first byte of current device settings.");
	}
	return parse_comparator_polarity_value(current_settings[1]);
}

hal::sensors::i2c::ads1115::AlertLatching hal::sensors::i2c::ads1115::ADS1115::get_comparator_latching_setting()
{
	uint8_t current_settings[REG_READ_LEN] = {0, 0};
	if (read_operation(m_file_handle, CONFIG_REG, current_settings) != OK)
	{
		throw exception::I2CException("ADS1115", "get_comparator_latching_setting", m_dev_id, CONFIG_REG,
												"Could not read first byte of current device settings.");
	}
	return parse_comparator_latching_value(current_settings[1]);
}

hal::sensors::i2c::ads1115::AlertQueueing hal::sensors::i2c::ads1115::ADS1115::get_comparator_queue_setting()
{
	uint8_t current_settings[REG_READ_LEN] = {0, 0};
	if (read_operation(m_file_handle, CONFIG_REG, current_settings) != OK)
	{
		throw exception::I2CException("ADS1115", "get_comparator_queue_setting", m_dev_id, CONFIG_REG,
												"Could not read first byte of current device settings.");
	}
	return parse_comparator_queueing_value(current_settings[1]);
}

hal::sensors::i2c::ads1115::Configuration hal::sensors::i2c::ads1115::ADS1115::get_settings()
{
	uint8_t current_raw_settings[REG_READ_LEN] = {0, 0};
	if (read_operation(m_file_handle, CONFIG_REG, current_raw_settings) != OK)
	{
		throw exception::I2CException("ADS1115", "get_settings", m_dev_id, CONFIG_REG,
												"Could not read first byte of current device settings.");
	}

	Configuration current_settings;
	current_settings.multiplexer = parse_multiplexer_value(current_raw_settings[0]);
	current_settings.gain_amplifier = parse_gain_amplifier_value(current_raw_settings[0]);
	current_settings.operation_mode = parse_operation_mode_value(current_raw_settings[0]);
	current_settings.data_rate = parse_data_rate_value(current_raw_settings[1]);
	current_settings.comparator_mode = parse_comparator_mode_value(current_raw_settings[1]);
	current_settings.alert_polarity = parse_comparator_polarity_value(current_raw_settings[1]);
	current_settings.alert_latching = parse_comparator_latching_value(current_raw_settings[1]);
	current_settings.alert_queueing = parse_comparator_queueing_value(current_raw_settings[1]);
	return current_settings;
}

void hal::sensors::i2c::ads1115::ADS1115::set_multiplexer_setting(Multiplexer new_multiplexer_setting)
{
	uint8_t raw_settings[REG_READ_LEN] = {0, 0};
	// Reading only the first byte is enough since all necessary information is located there.
	if (read_operation(m_file_handle, CONFIG_REG, raw_settings) != OK)
	{
		throw exception::I2CException("ADS1115", "set_multiplexer_setting", m_dev_id, CONFIG_REG, "Could not read current device settings.");
	}

	try
	{
		BitManipulation::set_bits(raw_settings[0], static_cast<uint8_t>(new_multiplexer_setting), MULTIPLEXER_MASK);
	}
	catch (exception::HALException* ex)
	{
		throw exception::HALException("ADS1115", "set_multiplexer_setting",
												std::string("Could not set multiplexer bits in config byte:\n").append(ex->to_string()));
	}

	if (write_operation(m_file_handle, CONFIG_REG, raw_settings) != OK)
	{
		throw exception::I2CException("ADS1115", "set_multiplexer_setting", m_dev_id, CONFIG_REG, "Could not write new device settings.");
	}
}

void hal::sensors::i2c::ads1115::ADS1115::set_gain_amplifier_setting(GainAmplifier new_gain_amplifier_setting)
{
	uint8_t raw_settings[REG_READ_LEN] = {0, 0};
	// Reading only the first byte is enough since all necessary information is located there.
	if (read_operation(m_file_handle, CONFIG_REG, raw_settings) != OK)
	{
		throw exception::I2CException("ADS1115", "set_gain_amplifier_setting", m_dev_id, CONFIG_REG,
												"Could not read current device settings.");
	}

	try
	{
		BitManipulation::set_bits(raw_settings[0], static_cast<uint8_t>(new_gain_amplifier_setting), GAIN_AMPLIFIER_MASK);
	}
	catch (exception::HALException* ex)
	{
		throw exception::HALException("ADS1115", "set_gain_amplifier_setting",
												std::string("Could not set gain amplifier bits in config byte:\n").append(ex->to_string()));
	}

	if (write_operation(m_file_handle, CONFIG_REG, raw_settings) != OK)
	{
		throw exception::I2CException("ADS1115", "set_gain_amplifier_setting", m_dev_id, CONFIG_REG, "Could not write new device settings.");
	}
}

void hal::sensors::i2c::ads1115::ADS1115::set_operation_mode_setting(OperationMode new_operation_mode_setting)
{
	uint8_t raw_settings[REG_READ_LEN] = {0, 0};
	// Reading only the first byte is enough since all necessary information is located there.
	if (read_operation(m_file_handle, CONFIG_REG, raw_settings) != OK)
	{
		throw exception::I2CException("ADS1115", "set_operation_mode_setting", m_dev_id, CONFIG_REG,
												"Could not read current device settings.");
	}

	try
	{
		BitManipulation::set_bits(raw_settings[0], static_cast<uint8_t>(new_operation_mode_setting), OPERATION_MODE_MASK);
	}
	catch (exception::HALException* ex)
	{
		throw exception::HALException("ADS1115", "set_operation_mode_setting",
												std::string("Could not set operation mode bits in config byte:\n").append(ex->to_string()));
	}

	if (write_operation(m_file_handle, CONFIG_REG, raw_settings) != OK)
	{
		throw exception::I2CException("ADS1115", "set_operation_mode_setting", m_dev_id, CONFIG_REG, "Could not write new device settings.");
	}
}

void hal::sensors::i2c::ads1115::ADS1115::set_data_rate_setting(DataRate new_data_rate_setting)
{
	uint8_t raw_settings[REG_READ_LEN] = {0, 0};
	if (read_operation(m_file_handle, CONFIG_REG, raw_settings) != OK)
	{
		throw exception::I2CException("ADS1115", "set_data_rate_setting", m_dev_id, CONFIG_REG, "Could not read current device settings.");
	}

	try
	{
		BitManipulation::set_bits(raw_settings[1], static_cast<uint8_t>(new_data_rate_setting), DATA_RATE_MASK);
	}
	catch (exception::HALException* ex)
	{
		throw exception::HALException("ADS1115", "set_data_rate_setting",
												std::string("Could not set data rate bits in config byte:\n").append(ex->to_string()));
	}

	if (write_operation(m_file_handle, CONFIG_REG, raw_settings) != OK)
	{
		throw exception::I2CException("ADS1115", "set_data_rate_setting", m_dev_id, CONFIG_REG, "Could not write new device settings.");
	}
}

void hal::sensors::i2c::ads1115::ADS1115::set_comparator_mode_setting(ComparatorMode new_comparator_mode_setting)
{
	uint8_t raw_settings[REG_READ_LEN] = {0, 0};
	if (read_operation(m_file_handle, CONFIG_REG, raw_settings) != OK)
	{
		throw exception::I2CException("ADS1115", "set_comparator_mode_setting", m_dev_id, CONFIG_REG,
												"Could not read current device settings.");
	}

	try
	{
		BitManipulation::set_bits(raw_settings[1], static_cast<uint8_t>(new_comparator_mode_setting), COMPARATOR_MODE_MASK);
	}
	catch (exception::HALException* ex)
	{
		throw exception::HALException("ADS1115", "set_comparator_mode_setting",
												std::string("Could not set comparator mode bits in config byte:\n").append(ex->to_string()));
	}

	if (write_operation(m_file_handle, CONFIG_REG, raw_settings) != OK)
	{
		throw exception::I2CException("ADS1115", "set_comparator_mode_setting", m_dev_id, CONFIG_REG, "Could not write new device settings.");
	}
}

void hal::sensors::i2c::ads1115::ADS1115::set_comparator_polarity_setting(AlertPolarity new_comparator_polarity_setting)
{
	uint8_t raw_settings[REG_READ_LEN] = {0, 0};
	if (read_operation(m_file_handle, CONFIG_REG, raw_settings) != OK)
	{
		throw exception::I2CException("ADS1115", "set_comparator_polarity_setting", m_dev_id, CONFIG_REG,
												"Could not read current device settings.");
	}

	try
	{
		BitManipulation::set_bits(raw_settings[1], static_cast<uint8_t>(new_comparator_polarity_setting), COMPARATOR_POLARITY_MASK);
	}
	catch (exception::HALException* ex)
	{
		throw exception::HALException("ADS1115", "set_comparator_polarity_setting",
												std::string("Could not set pin polarity bits in config byte:\n").append(ex->to_string()));
	}

	if (write_operation(m_file_handle, CONFIG_REG, raw_settings) != OK)
	{
		throw exception::I2CException("ADS1115", "set_comparator_polarity_setting", m_dev_id, CONFIG_REG,
												"Could not write new device settings.");
	}
}

void hal::sensors::i2c::ads1115::ADS1115::set_comparator_latching_setting(AlertLatching new_comparator_latching_setting)
{
	uint8_t raw_settings[REG_READ_LEN] = {0, 0};
	if (read_operation(m_file_handle, CONFIG_REG, raw_settings) != OK)
	{
		throw exception::I2CException("ADS1115", "set_comparator_latching_setting", m_dev_id, CONFIG_REG,
												"Could not read current device settings.");
	}

	try
	{
		BitManipulation::set_bits(raw_settings[1], static_cast<uint8_t>(new_comparator_latching_setting), COMPARATOR_LATCHING_MASK);
	}
	catch (exception::HALException* ex)
	{
		throw exception::HALException("ADS1115", "set_comparator_latching_setting",
												std::string("Could not set comparator latching bits in config byte:\n").append(ex->to_string()));
	}

	if (write_operation(m_file_handle, CONFIG_REG, raw_settings) != OK)
	{
		throw exception::I2CException("ADS1115", "set_comparator_latching_setting", m_dev_id, CONFIG_REG,
												"Could not write new device settings.");
	}
}

void hal::sensors::i2c::ads1115::ADS1115::set_comparator_queue_setting(AlertQueueing new_comparator_queue_setting)
{
	uint8_t raw_settings[REG_READ_LEN] = {0, 0};
	if (read_operation(m_file_handle, CONFIG_REG, raw_settings) != OK)
	{
		throw exception::I2CException("ADS1115", "set_comparator_queue_setting", m_dev_id, CONFIG_REG,
												"Could not read current device settings.");
	}

	try
	{
		BitManipulation::set_bits(raw_settings[1], static_cast<uint8_t>(new_comparator_queue_setting), COMPARATOR_QUEUEING_MASK);
	}
	catch (exception::HALException* ex)
	{
		throw exception::HALException("ADS1115", "set_comparator_queue_setting",
												std::string("Could not set comparator queue bits in config byte:\n").append(ex->to_string()));
	}

	if (write_operation(m_file_handle, CONFIG_REG, raw_settings) != OK)
	{
		throw exception::I2CException("ADS1115", "set_comparator_queue_setting", m_dev_id, CONFIG_REG,
												"Could not write new device settings.");
	}
}

void hal::sensors::i2c::ads1115::ADS1115::set_settings(Configuration new_settings)
{
	uint8_t raw_settings[REG_READ_LEN] = {0, 0};
	try
	{
		BitManipulation::set_bits(raw_settings[0], static_cast<uint8_t>(new_settings.multiplexer), MULTIPLEXER_MASK);
		BitManipulation::set_bits(raw_settings[0], static_cast<uint8_t>(new_settings.gain_amplifier), GAIN_AMPLIFIER_MASK);
		BitManipulation::set_bits(raw_settings[0], static_cast<uint8_t>(new_settings.operation_mode), OPERATION_MODE_MASK);
		BitManipulation::set_bits(raw_settings[1], static_cast<uint8_t>(new_settings.data_rate), DATA_RATE_MASK);
		BitManipulation::set_bits(raw_settings[1], static_cast<uint8_t>(new_settings.comparator_mode), COMPARATOR_MODE_MASK);
		BitManipulation::set_bits(raw_settings[1], static_cast<uint8_t>(new_settings.alert_polarity), COMPARATOR_POLARITY_MASK);
		BitManipulation::set_bits(raw_settings[1], static_cast<uint8_t>(new_settings.alert_latching), COMPARATOR_LATCHING_MASK);
		BitManipulation::set_bits(raw_settings[1], static_cast<uint8_t>(new_settings.alert_queueing), COMPARATOR_QUEUEING_MASK);
	}
	catch (exception::HALException* ex)
	{
		throw exception::HALException("ADS1115", "set_settings",
												std::string("Could not set setting bits in config byte:\n").append(ex->to_string()));
	}

	if (write_operation(m_file_handle, CONFIG_REG, raw_settings) != OK)
	{
		throw exception::I2CException("ADS1115", "set_settings", m_dev_id, CONFIG_REG, "Could not write new device settings.");
	}
}

void hal::sensors::i2c::ads1115::ADS1115::restore_default_settings()
{
	uint8_t default_settings[REG_READ_LEN] = {DEFAULT_SETTINGS_BYTE_1, DEFAULT_SETTINGS_BYTE_2};
	if (write_operation(m_file_handle, CONFIG_REG, default_settings) != OK)
	{
		throw exception::I2CException("ADS1115", "restore_default_settings", m_dev_id, CONFIG_REG,
												"Could not write default device settings.");
	}
}

double hal::sensors::i2c::ads1115::ADS1115::get_converted_data()
{
	uint8_t raw_converted[REG_READ_LEN] = {0, 0};
	if (read_operation(m_file_handle, CONVERSION_REG, raw_converted) != OK)
	{
		throw exception::I2CException("ADS1115", "get_converted_data", m_dev_id, CONVERSION_REG, "Could not read converted data.");
	}
	return convert_to_voltage(BitManipulation::combine_bytes(raw_converted[0], raw_converted[1]));
}

uint16_t hal::sensors::i2c::ads1115::ADS1115::get_upper_threshold()
{
	uint8_t raw_threshold[REG_READ_LEN] = {0, 0};
	if (read_operation(m_file_handle, HIGH_THRESHOLD_REG, raw_threshold) != OK)
	{
		throw exception::I2CException("ADS1115", "get_upper_threshold", m_dev_id, CONVERSION_REG, "Could not read upper threshold.");
	}

	return BitManipulation::combine_bytes(raw_threshold[0], raw_threshold[1]);
}

uint16_t hal::sensors::i2c::ads1115::ADS1115::get_lower_threshold()
{
	uint8_t raw_threshold[REG_READ_LEN] = {0, 0};
	if (read_operation(m_file_handle, LOW_THRESHOLD_REG, raw_threshold) != OK)
	{
		throw exception::I2CException("ADS1115", "get_lower_threshold", m_dev_id, CONVERSION_REG, "Could not read lower threshold.");
	}

	return BitManipulation::combine_bytes(raw_threshold[0], raw_threshold[1]);
}

void hal::sensors::i2c::ads1115::ADS1115::get_thresholds(uint16_t& lower_threshold, uint16_t& upper_threshold)
{
	try
	{
		upper_threshold = get_upper_threshold();
		lower_threshold = get_lower_threshold();
	}
	catch (exception::HALException* ex)
	{
		throw exception::HALException("ADS1115", "get_thresholds",
												std::string("Could not read current thresholds from device:\n").append(ex->to_string()));
	}
}

void hal::sensors::i2c::ads1115::ADS1115::set_upper_threshold(const uint16_t upper_threshold)
{
	uint8_t divided_threshold[REG_READ_LEN] = {0, 0};
	BitManipulation::split_bytes(upper_threshold, divided_threshold[0], divided_threshold[1]);
	if (write_operation(m_file_handle, HIGH_THRESHOLD_REG, divided_threshold) != OK)
	{
		throw exception::I2CException("ADS1115", "set_upper_threshold", m_dev_id, CONVERSION_REG, "Could not write upper threshold.");
	}
}

void hal::sensors::i2c::ads1115::ADS1115::set_lower_threshold(const uint16_t lower_threshold)
{
	uint8_t divided_threshold[REG_READ_LEN] = {0, 0};
	BitManipulation::split_bytes(lower_threshold, divided_threshold[0], divided_threshold[1]);
	if (write_operation(m_file_handle, LOW_THRESHOLD_REG, divided_threshold) != OK)
	{
		throw exception::I2CException("ADS1115", "set_lower_threshold", m_dev_id, CONVERSION_REG, "Could not write lower threshold.");
	}
}

void hal::sensors::i2c::ads1115::ADS1115::set_thresholds(const uint16_t lower_threshold, const uint16_t upper_threshold)
{
	try
	{
		set_upper_threshold(upper_threshold);
		set_lower_threshold(lower_threshold);
	}
	catch (exception::HALException* ex)
	{
		throw exception::HALException("ADS1115", "set_thresholds",
												std::string("Could not write new thresholds to device:\n").append(ex->to_string()));
	}
}

void hal::sensors::i2c::ads1115::ADS1115::restore_default_upper_thresholds()
{
	uint8_t default_threshold[REG_READ_LEN] = {DEFAULT_HIGH_THRES_BYTE_1, DEFAULT_HIGH_THRES_BYTE_2};
	if (write_operation(m_file_handle, HIGH_THRESHOLD_REG, default_threshold) != OK)
	{
		throw exception::I2CException("ADS1115", "restore_default_upper_thresholds", m_dev_id, CONVERSION_REG,
												"Could not restore default upper threshold.");
	}
}

void hal::sensors::i2c::ads1115::ADS1115::restore_default_lower_thresholds()
{
	uint8_t default_threshold[REG_READ_LEN] = {DEFAULT_LOW_THRES_BYTE_1, DEFAULT_LOW_THRES_BYTE_2};
	if (write_operation(m_file_handle, LOW_THRESHOLD_REG, default_threshold) != OK)
	{
		throw exception::I2CException("ADS1115", "restore_default_lower_thresholds", m_dev_id, CONVERSION_REG,
												"Could not restore default lower threshold.");
	}
}

void hal::sensors::i2c::ads1115::ADS1115::restore_default_thresholds()
{
	try
	{
		restore_default_upper_thresholds();
		restore_default_lower_thresholds();
	}
	catch (exception::HALException* ex)
	{
		throw exception::HALException("ADS1115", "restore_default_thresholds",
												std::string("Could not restore default thresholds:\n").append(ex->to_string()));
	}
}

hal::sensors::i2c::ads1115::Multiplexer hal::sensors::i2c::ads1115::ADS1115::parse_multiplexer_value(const uint8_t raw_data)
{
	try
	{
		switch (BitManipulation::value_of_bits(raw_data, MULTIPLEXER_BIT_1, MULTIPLEXER_BIT_3))
		{
		case 0:
			return Multiplexer::POSITIVE_0_AND_NEGATIVE_1;
		case 1:
			return Multiplexer::POSITIVE_0_AND_NEGATIVE_3;
		case 2:
			return Multiplexer::POSITIVE_1_AND_NEGATIVE_3;
		case 3:
			return Multiplexer::POSITIVE_2_AND_NEGATIVE_3;
		case 4:
			return Multiplexer::POSITIVE_0_AND_NEGATIVE_GND;
		case 5:
			return Multiplexer::POSITIVE_1_AND_NEGATIVE_GND;
		case 6:
			return Multiplexer::POSITIVE_2_AND_NEGATIVE_GND;
		case 7:
			return Multiplexer::POSITIVE_3_AND_NEGATIVE_GND;
		default:
			return Multiplexer::POSITIVE_0_AND_NEGATIVE_1;
		}
	}
	catch (exception::HALException* ex)
	{
		throw exception::HALException("ADS1115", "parse_multiplexer_value",
												std::string("Could not read value of multiplexer bits in config byte:\n").append(ex->to_string()));
	}
}

hal::sensors::i2c::ads1115::GainAmplifier hal::sensors::i2c::ads1115::ADS1115::parse_gain_amplifier_value(const uint8_t raw_data)
{
	try
	{
		switch (BitManipulation::value_of_bits(raw_data, GAIN_AMPLIFIER_BIT_1, GAIN_AMPLIFIER_BIT_3))
		{
		case 0:
			return GainAmplifier::GAIN_6144_mV;
		case 1:
			return GainAmplifier::GAIN_4096_mV;
		case 2:
			return GainAmplifier::GAIN_2048_mV;
		case 3:
			return GainAmplifier::GAIN_1024_mV;
		case 4:
			return GainAmplifier::GAIN_512_mV;
		case 5:
		case 6:
		case 7:
			return GainAmplifier::GAIN_256_mV;
		default:
			return GainAmplifier::GAIN_2048_mV;
		}
	}
	catch (exception::HALException* ex)
	{
		throw exception::HALException("ADS1115", "parse_gain_amplifier_value",
												std::string("Could not read value of gain amplifier bits in config byte:\n").append(ex->to_string()));
	}
}

hal::sensors::i2c::ads1115::OperationMode hal::sensors::i2c::ads1115::ADS1115::parse_operation_mode_value(const uint8_t raw_data)
{
	try
	{
		if (BitManipulation::is_bit_set(raw_data, OPERATION_MODE_BIT))
		{
			return OperationMode::SINGLE_SHOT;
		}
		return OperationMode::CONTINUOUS;
	}
	catch (exception::HALException* ex)
	{
		throw exception::HALException("ADS1115", "parse_operation_mode_value",
												std::string("Could not read value of operation mode bits in config byte:\n").append(ex->to_string()));
	}
}

hal::sensors::i2c::ads1115::DataRate hal::sensors::i2c::ads1115::ADS1115::parse_data_rate_value(const uint8_t raw_data)
{
	try
	{
		switch (BitManipulation::value_of_bits(raw_data, GAIN_AMPLIFIER_BIT_1, GAIN_AMPLIFIER_BIT_3))
		{
		case 0:
			return DataRate::RATE_8_SPS;
		case 1:
			return DataRate::RATE_16_SPS;
		case 2:
			return DataRate::RATE_32_SPS;
		case 3:
			return DataRate::RATE_64_SPS;
		case 4:
			return DataRate::RATE_128_SPS;
		case 5:
			return DataRate::RATE_250_SPS;
		case 6:
			return DataRate::RATE_475_SPS;
		case 7:
			return DataRate::RATE_860_SPS;
		default:
			return DataRate::RATE_128_SPS;
		}
	}
	catch (exception::HALException* ex)
	{
		throw exception::HALException("ADS1115", "parse_data_rate_value",
												std::string("Could not read value of data rate bits in config byte:\n").append(ex->to_string()));
	}
}

hal::sensors::i2c::ads1115::ComparatorMode hal::sensors::i2c::ads1115::ADS1115::parse_comparator_mode_value(const uint8_t raw_data)
{
	try
	{
		if (BitManipulation::is_bit_set(raw_data, COMPARATOR_MODE_BIT))
		{
			return ComparatorMode::WINDOW;
		}
		return ComparatorMode::HYSTERESIS;
	}
	catch (exception::HALException* ex)
	{
		throw exception::HALException("ADS1115", "parse_comparator_mode_value",
												std::string("Could not read value of comparator mode bits in config byte:\n").append(ex->to_string()));
	}
}

hal::sensors::i2c::ads1115::AlertPolarity hal::sensors::i2c::ads1115::ADS1115::parse_comparator_polarity_value(const uint8_t raw_data)
{
	try
	{
		if (BitManipulation::is_bit_set(raw_data, COMPARATOR_POL_BIT))
		{
			return AlertPolarity::ACTIVE_HIGH;
		}
		return AlertPolarity::ACTIVE_LOW;
	}
	catch (exception::HALException* ex)
	{
		throw exception::HALException("ADS1115", "parse_comparator_polarity_value",
												std::string("Could not read value of pin polarity bits in config byte:\n").append(ex->to_string()));
	}
}

hal::sensors::i2c::ads1115::AlertLatching hal::sensors::i2c::ads1115::ADS1115::parse_comparator_latching_value(const uint8_t raw_data)
{
	try
	{
		if (BitManipulation::is_bit_set(raw_data, COMPARATOR_LAT_BIT))
		{
			return AlertLatching::ACTIVE;
		}
		return AlertLatching::DISABLED;
	}
	catch (exception::HALException* ex)
	{
		throw exception::HALException("ADS1115", "parse_comparator_latching_value",
												std::string("Could not read value of comparator latching bits in config byte:\n").append(
													ex->to_string()));
	}
}

hal::sensors::i2c::ads1115::AlertQueueing hal::sensors::i2c::ads1115::ADS1115::parse_comparator_queueing_value(const uint8_t raw_data)
{
	try
	{
		switch (BitManipulation::value_of_bits(raw_data, COMPARATOR_QUEUE_BIT_1, COMPARATOR_QUEUE_BIT_2))
		{
		case 0:
			return AlertQueueing::ASSERT_1_CONVERSION;
		case 1:
			return AlertQueueing::ASSERT_2_CONVERSIONS;
		case 2:
			return AlertQueueing::ASSERT_4_CONVERSIONS;
		case 3:
			return AlertQueueing::DISABLED;
		default:
			return AlertQueueing::DISABLED;
		}
	}
	catch (exception::HALException* ex)
	{
		throw exception::HALException("ADS1115", "parse_comparator_queueing_value",
												std::string("Could not read value of comparator queue bits in config byte:\n").append(ex->to_string()));
	}
}

double hal::sensors::i2c::ads1115::ADS1115::convert_to_voltage(const uint16_t raw_data)
{
	try
	{
		const auto gain = get_gain_amplifier_setting();
		double bit_factor;
		switch (gain)
		{
		case GainAmplifier::GAIN_6144_mV:
			bit_factor = 6144.0 / 32767.0;
			break;
		case GainAmplifier::GAIN_4096_mV:
			bit_factor = 4096.0 / 32767.0;
			break;
		case GainAmplifier::GAIN_2048_mV:
			bit_factor = 2048.0 / 32767.0;
			break;
		case GainAmplifier::GAIN_1024_mV:
			bit_factor = 1024.0 / 32767.0;
			break;
		case GainAmplifier::GAIN_512_mV:
			bit_factor = 512.0 / 32767.0;
			break;
		case GainAmplifier::GAIN_256_mV:
			bit_factor = 256.0 / 32767.0;
			break;
		default:
			bit_factor = 1.0;
			break;
		}
		return (raw_data * bit_factor) / 1000.0;
	}
	catch (exception::HALException* ex)
	{
		throw exception::HALException("ADS1115", "convert_to_voltage",
												std::string("Could not read the current gain amplifier setting:\n").append(ex->to_string()));
	}
}

int8_t hal::sensors::i2c::ads1115::ADS1115::write_operation(int handle, uint8_t address, const uint8_t* buffer, uint16_t length)
{
	if (handle == 0)
	{
		return -1;
	}

	uint8_t write_buffer[3] = {0, 0, 0};
	write_buffer[0] = address;
	write_buffer[1] = buffer[0];
	write_buffer[2] = buffer[1];
	if (write(handle, write_buffer, length + 1) != length + 1)
	{
		std::stringstream stream1;
		stream1 << std::hex << buffer[0];
		std::stringstream stream2;
		stream2 << std::hex << buffer[1];
		throw exception::I2CException("ADS1115", "write_operation", m_dev_id, address,
												"Could not switch pointer to register address. and write data 0x" + stream1.str() + "', 0x" + stream2.
												str() + ". Error: " + strerror(errno));
	}

	return OK;
}

int8_t hal::sensors::i2c::ads1115::ADS1115::read_operation(int handle, uint8_t address, uint8_t* buffer, uint16_t length)
{
	if (handle == 0)
	{
		return -1;
	}

	if (write(handle, &address, 1) != 1)
	{
		std::stringstream address_stream;
		address_stream << std::hex << address;
		throw exception::I2CException("ADS1115", "read_operation", m_dev_id, address,
												"Could not switch to register with address 0x" + address_stream.str() + ". Error: " + strerror(errno));
	}

	if (read(handle, buffer, length) != length)
	{
		std::stringstream address_stream;
		address_stream << std::hex << address;
		throw exception::I2CException("ADS1115", "read_operation", m_dev_id, address,
												std::string("Could not read data of length ").append(std::to_string(length)).append(" from address 0x")
																											.append(address_stream.str()).append(". Error: ").append(
																												strerror(errno)));
	}

	return OK;
}
