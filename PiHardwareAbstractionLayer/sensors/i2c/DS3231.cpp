#include "DS3231.h"
#include "../../utils/BitManipulation.h"
#include "../../utils/EnumConverter.h"
#include "../../utils/I2CManager.h"
#include <regex>
#include <ctime>
#include <iomanip>
#include <sstream>
#include <unistd.h>
#include "../../exceptions/I2CException.h"

void hal::sensors::i2c::ds3231::DS3231::trigger_measurement(const SensorType type)
{
	std::string val;
	for (auto i = m_callbacks[type].begin(); i != m_callbacks[type].end(); ++i)
	{
		switch (type)
		{
		case SensorType::CLOCK:
			try
			{
				val = get_time_and_date();
			}
			catch (exception::HALException& ex)
			{
				throw exception::HALException("DS3231", "trigger_measurement",
					std::string("Could not trigger time and date measurement:\n").append(ex.to_string()));
			}
			break;
		default:
			throw exception::HALException("DS3231", "trigger_measurement", "Invalid sensor type.");
		}
		(*i)->callback(val);
	}
}

void hal::sensors::i2c::ds3231::DS3231::configure(const SensorSetting setting, const std::string& configuration)
{
	if (setting == SensorSetting::OSCILLATOR_STATE)
	{
		try
		{
			set_oscillator_state(EnumConverter::string_to_oscillator_state(configuration));
		}
		catch (exception::HALException& ex)
		{
			throw exception::HALException("DS3231", "configure",
				std::string("Could not change oscillator state settings:\n").append(ex.to_string()));
		}
	}
	else if (setting == SensorSetting::SQUARE_WAVE_STATE)
	{
		try
		{
			set_square_wave_state(EnumConverter::string_to_square_wave_state(configuration));
		}
		catch (exception::HALException& ex)
		{
			throw exception::HALException("DS3231", "configure",
				std::string("Could not change square wave state settings:\n").append(ex.to_string()));
		}
	}
	else if (setting == SensorSetting::SQUARE_WAVE_RATE)
	{
		try
		{
			set_square_wave_rate(EnumConverter::string_to_square_wave_rate(configuration));
		}
		catch (exception::HALException& ex)
		{
			throw exception::HALException("DS3231", "configure",
				std::string("Could not change square wave rate settings:\n").append(ex.to_string()));
		}
	}
	else if (setting == SensorSetting::TIMEZONE)
	{
		set_timezone(EnumConverter::string_to_timezone(configuration));
	}
	else if (setting == SensorSetting::CLOCK_FORMAT)
	{
		set_clock_format(configuration);
	}
	else if (setting == SensorSetting::OUTPUT_FORMAT)
	{
		set_output_format(EnumConverter::string_to_output_format(configuration));
	}
	else if (setting == SensorSetting::TIME_SYNC)
	{
		sync_time();
	}
}

std::string hal::sensors::i2c::ds3231::DS3231::get_configuration(SensorSetting setting)
{
	if (setting == SensorSetting::OSCILLATOR_STATE)
	{
		try
		{
			return EnumConverter::enum_to_string(get_oscillator_state());
		}
		catch (exception::HALException& ex)
		{
			throw exception::HALException("DS3231", "get_configuration",
				std::string("Could not get oscillator state settings:\n").append(ex.to_string()));
		}
	}
	else if (setting == SensorSetting::SQUARE_WAVE_STATE)
	{
		try
		{
			return EnumConverter::enum_to_string(get_square_wave_state());
		}
		catch (exception::HALException& ex)
		{
			throw exception::HALException("DS3231", "get_configuration",
				std::string("Could not get square wave state settings:\n").append(ex.to_string()));
		}
	}
	else if (setting == SensorSetting::SQUARE_WAVE_RATE)
	{
		try
		{
			return EnumConverter::enum_to_string(get_square_wave_rate());
		}
		catch (exception::HALException& ex)
		{
			throw exception::HALException("DS3231", "get_configuration",
				std::string("Could not get square wave rate settings:\n").append(ex.to_string()));
		}
	}
	else if (setting == SensorSetting::TIMEZONE)
	{
		return EnumConverter::enum_to_string(get_timezone());
	}
	else if (setting == SensorSetting::CLOCK_FORMAT)
	{
		return get_clock_format();
	}
	else if (setting == SensorSetting::OUTPUT_FORMAT)
	{
		return EnumConverter::enum_to_string(get_output_format());
	}
	else if (setting == SensorSetting::TIME_SYNC)
	{
		return m_synced_during_this_run ? "Clock has been synchronized during this run" : "Clock has not yet been synchronized during this run";
	}
	throw exception::HALException("DS3231", "get_configuration", "The given setting type is not supported by this device.");
}

std::vector<hal::SensorSetting> hal::sensors::i2c::ds3231::DS3231::available_configurations() noexcept
{
	return { SensorSetting::OSCILLATOR_STATE, SensorSetting::SQUARE_WAVE_STATE,
		SensorSetting::SQUARE_WAVE_RATE, SensorSetting::TIMEZONE, SensorSetting::CLOCK_FORMAT,
		SensorSetting::OUTPUT_FORMAT, SensorSetting::TIME_SYNC };
}

void hal::sensors::i2c::ds3231::DS3231::close()
{
	try
	{
		I2CManager::close_device(m_file_handle);
	}
	catch (exception::HALException& ex)
	{
		throw exception::HALException("DS3231", "close", std::string("Could not close device connection:\n").append(ex.to_string()));
	}
}

uint8_t hal::sensors::i2c::ds3231::DS3231::init(const uint8_t device_reg)
{
	m_dev_id = device_reg;
	try
	{
		I2CManager::open_device(I2CManager::DEFAULT_PI_I2C_PATH, device_reg, m_file_handle);
	}
	catch (exception::HALException& ex)
	{
		throw exception::HALException("DS3231", "init", std::string("Could not establish connection with device:\n").append(ex.to_string()));
	}
	return 0;
}

std::string hal::sensors::i2c::ds3231::DS3231::get_time_and_date()
{
	struct tm time =
	{
		.tm_sec = get_seconds(),
		.tm_min = get_minutes(),
		.tm_hour = get_hours(),
		.tm_mday = get_date(),
		.tm_mon = get_month(),
		.tm_year = get_year() + 100, // equals to year + 2000 - 1900
		.tm_wday = get_day()
	};

	if (m_output_format == OutputFormat::FORMATTED_STRING)
	{
		// Apply timezone offset
		m_timezone.apply_timezone(time);

		std::stringstream ss;
		ss << std::put_time(&time, m_clock_format.c_str());
		return ss.str();
	}
	else
	{
		return std::to_string(static_cast<int>(mktime(&time)));
	}
}

void hal::sensors::i2c::ds3231::DS3231::sync_time()
{
	auto now = time(nullptr);
	const auto now_tm = gmtime(&now);

	try
	{
		// Seconds
		auto bcd_seconds = BitManipulation::to_bcd(static_cast<uint8_t>(now_tm->tm_sec));
		I2CManager::write_to_device(m_file_handle, SECONDS_REGISTER, &bcd_seconds, 1);

		// Minutes
		auto bcd_minutes = BitManipulation::to_bcd(static_cast<uint8_t>(now_tm->tm_min));
		I2CManager::write_to_device(m_file_handle, MINUTES_REGISTER, &bcd_minutes, 1);

		// Hours
		const auto bcd_hours = BitManipulation::to_bcd(static_cast<uint8_t>(now_tm->tm_hour));
		uint8_t hour_data[1];
		I2CManager::read_from_device(m_file_handle, HOURS_REGISTER, hour_data, 1);
		BitManipulation::set_bits(hour_data[0], 0, static_cast<uint8_t>(63)); // Clean all existing hour data
		if (get_hour_format() == HourFormat::HOUR_FORMAT_12) // 12 Hour format
		{
			if (now_tm->tm_hour > 12)
			{
				now_tm->tm_hour = now_tm->tm_hour - 12;
				BitManipulation::set_bit(hour_data[0], AM_PM_INDEX, true); // PM
			}
			else
			{
				if (now_tm->tm_hour == 0)
				{
					now_tm->tm_hour = 12;
				}
				BitManipulation::set_bit(hour_data[0], AM_PM_INDEX, false); // AM
			}
			hour_data[0] = BitManipulation::combine(hour_data[0], bcd_hours);
		}
		else // 24 Hour format
		{
			hour_data[0] = BitManipulation::combine(hour_data[0], bcd_hours);
		}
		I2CManager::write_to_device(m_file_handle, HOURS_REGISTER, &hour_data[0], 1);

		// Month
		const auto bcd_month = BitManipulation::to_bcd(static_cast<uint8_t>(now_tm->tm_mon));
		uint8_t month_data[1];
		I2CManager::read_from_device(m_file_handle, MONTH_REGISTER, month_data, 1);
		BitManipulation::set_bits(month_data[0], 0, static_cast<uint8_t>(127));
		month_data[0] = BitManipulation::combine(month_data[0], bcd_month);
		I2CManager::write_to_device(m_file_handle, MONTH_REGISTER, &month_data[0], 1);

		// Year
		// Need to do modulo 100 because tm stores year as current year - 1900
		// e.g. the year 2020 = 2020 - 1900 = 120 in tm struct
		// 120 % 100 = 20 = last two digits of the year and independent of current century
		auto bcd_year = BitManipulation::to_bcd(static_cast<uint8_t>(now_tm->tm_year % 100));
		I2CManager::write_to_device(m_file_handle, YEAR_REGISTER, &bcd_year, 1);

		// Date (day in month)
		auto bcd_date = BitManipulation::to_bcd(static_cast<uint8_t>(now_tm->tm_mday));
		I2CManager::write_to_device(m_file_handle, DATE_REGISTER, &bcd_date, 1);

		// Week day
		// Need to add one because tm struct stores weekdays from 0 to 6 and RTC awaits a value from 1 to 7.
		auto bcd_day = BitManipulation::to_bcd(static_cast<uint8_t>(now_tm->tm_wday + 1));
		I2CManager::write_to_device(m_file_handle, DAY_REGISTER, &bcd_day, 1);

		m_synced_during_this_run = true;
	}
	catch (exception::HALException& ex)
	{
		throw exception::HALException("DS3231", "sync_time", std::string("Could not sync time with the device:\n").append(ex.to_string()));
	}
}

void hal::sensors::i2c::ds3231::DS3231::set_hour_format(const HourFormat format) const
{
	uint8_t reg_data[1];
	try
	{
		I2CManager::read_from_device(m_file_handle, HOURS_REGISTER, reg_data, 1);
	}
	catch (exception::HALException& ex)
	{
		throw exception::I2CException("DS3231", "set_hour_format", m_dev_id, HOURS_REGISTER,
			std::string("Could not read hour register:\n").append(
				ex.to_string()));
	}

	try
	{
		switch (format)
		{
		case HourFormat::HOUR_FORMAT_12:
			BitManipulation::set_bit(reg_data[0], HOUR_FORMAT_INDEX, true);
			break;
		case HourFormat::HOUR_FORMAT_24:
			BitManipulation::set_bit(reg_data[0], HOUR_FORMAT_INDEX, false);
			break;
		default:
			throw exception::HALException("DS3231", "set_hour_format", "Invalid value for HourFormat enum.");
		}
	}
	catch (exception::HALException& ex)
	{
		throw exception::HALException("DS3231", "set_hour_format", std::string("Could not change hour format bit:\n").append(
			ex.to_string()));
	}

	try
	{
		I2CManager::write_to_device(m_file_handle, HOURS_REGISTER, reg_data, 1);
	}
	catch (exception::HALException& ex)
	{
		throw exception::I2CException("DS3231", "set_hour_format", m_dev_id, HOURS_REGISTER,
			std::string("Could not write hour format to device:\n").append(
				ex.to_string()));
	}
}

hal::sensors::i2c::ds3231::HourFormat hal::sensors::i2c::ds3231::DS3231::get_hour_format() const
{
	uint8_t reg_data[1];
	try
	{
		I2CManager::read_from_device(m_file_handle, HOURS_REGISTER, reg_data, 1);
	}
	catch (exception::HALException& ex)
	{
		throw exception::I2CException("DS3231", "get_hour_format", m_dev_id, HOURS_REGISTER,
			std::string("Could not read hour register:\n").append(
				ex.to_string()));
	}

	try
	{
		if (BitManipulation::is_bit_set(reg_data[0], HOUR_FORMAT_INDEX))
		{
			return HourFormat::HOUR_FORMAT_12;
		}
		return HourFormat::HOUR_FORMAT_24;
	}
	catch (exception::HALException& ex)
	{
		throw exception::HALException("DS3231", "get_hour_format",
			std::string("Could not check bit status because bit index is out of bounds:\n").append(
				ex.to_string()));
	}
}

void hal::sensors::i2c::ds3231::DS3231::set_oscillator_state(OscillatorState state) const
{
	uint8_t reg_data;
	try
	{
		reg_data = read_control_register();
	}
	catch (exception::HALException& ex)
	{
		throw exception::I2CException("DS3231", "set_oscillator_state", m_dev_id, CONTROL_REGISTER,
			std::string("Could not read control register:\n").append(
				ex.to_string()));
	}

	try
	{
		switch (state)
		{
		case OscillatorState::START:
			BitManipulation::set_bit(reg_data, EOSC_INDEX, false);
			break;
		case OscillatorState::STOP:
			BitManipulation::set_bit(reg_data, EOSC_INDEX, true);
			break;
		default:
			throw exception::HALException("DS3231", "set_oscillator_state",
				"Invalid value for OscillatorState enum.");
		}
	}
	catch (exception::HALException& ex)
	{
		throw exception::HALException("DS3231", "set_oscillator_state",
			std::string("Could not change oscillator state bit:\n").append(
				ex.to_string()));
	}

	try
	{
		I2CManager::write_to_device(m_file_handle, CONTROL_REGISTER, &reg_data, 1);
	}
	catch (exception::HALException& ex)
	{
		throw exception::I2CException("DS3231", "set_oscillator_state", m_dev_id, CONTROL_REGISTER,
			std::string("Could not write oscillator state to device:\n").append(
				ex.to_string()));
	}
}

hal::sensors::i2c::ds3231::OscillatorState hal::sensors::i2c::ds3231::DS3231::get_oscillator_state() const
{
	uint8_t reg_data;
	try
	{
		reg_data = read_status_register();
	}
	catch (exception::HALException& ex)
	{
		throw exception::I2CException("DS3231", "get_oscillator_state", m_dev_id, STATUS_REGISTER,
			std::string("Could not read status register:\n").append(ex.to_string()));
	}

	try
	{
		if (BitManipulation::is_bit_set(reg_data, OSF_INDEX))
		{
			return OscillatorState::STOP;
		}
		return OscillatorState::START;
	}
	catch (exception::HALException& ex)
	{
		throw exception::HALException("DS3231", "get_oscillator_state",
			std::string("Could not check bit status because bit index is out of bounds:\n").append(
				ex.to_string()));
	}
}

void hal::sensors::i2c::ds3231::DS3231::set_square_wave_state(SquareWaveState state) const
{
	uint8_t reg_data;
	try
	{
		reg_data = read_control_register();
	}
	catch (exception::HALException& ex)
	{
		throw exception::I2CException("DS3231", "set_square_wave_state", m_dev_id, CONTROL_REGISTER,
			std::string("Could not read control register:\n").append(ex.to_string()));
	}

	try
	{
		switch (state)
		{
		case SquareWaveState::STOP:
			BitManipulation::set_bit(reg_data, EOSC_INDEX, false);
			BitManipulation::set_bit(reg_data, INTCN_INDEX, true);
			break;
		case SquareWaveState::START:
			BitManipulation::set_bit(reg_data, EOSC_INDEX, true);
			BitManipulation::set_bit(reg_data, INTCN_INDEX, false);
			break;
		default:
			throw exception::HALException("DS3231", "set_square_wave_state",
				"Invalid value for SquareWaveState enum.");
		}
	}
	catch (exception::HALException& ex)
	{
		throw exception::HALException("DS3231", "set_square_wave_state",
			std::string("Could not change square wave state bit:\n").append(ex.to_string()));
	}

	try
	{
		I2CManager::write_to_device(m_file_handle, CONTROL_REGISTER, &reg_data, 1);
	}
	catch (exception::HALException& ex)
	{
		throw exception::I2CException("DS3231", "set_square_wave_state", m_dev_id, CONTROL_REGISTER,
			std::string("Could not write square wave state to device:\n").append(ex.to_string()));
	}
}

hal::sensors::i2c::ds3231::SquareWaveState hal::sensors::i2c::ds3231::DS3231::get_square_wave_state() const
{
	uint8_t reg_data;
	try
	{
		reg_data = read_status_register();
	}
	catch (exception::HALException& ex)
	{
		throw exception::I2CException("DS3231", "get_square_wave_state", m_dev_id, STATUS_REGISTER,
			std::string("Could not read status register:\n").append(ex.to_string()));
	}

	try
	{
		if (BitManipulation::is_bit_set(reg_data, EN32KHZ_INDEX))
		{
			return SquareWaveState::START;
		}
		return SquareWaveState::STOP;
	}
	catch (exception::HALException& ex)
	{
		throw exception::HALException("DS3231", "get_square_wave_state",
			std::string("Could not check bit status because bit index is out of bounds:\n").append(
				ex.to_string()));
	}
}

void hal::sensors::i2c::ds3231::DS3231::set_square_wave_rate(SquareWaveRate rate) const
{
	uint8_t reg_data;
	try
	{
		reg_data = read_control_register();
	}
	catch (exception::HALException& ex)
	{
		throw exception::I2CException("DS3231", "set_square_wave_rate", m_dev_id, CONTROL_REGISTER,
			std::string("Could not read control register:\n").append(ex.to_string()));
	}

	try
	{
		BitManipulation::set_bits(reg_data, static_cast<uint8_t>(rate), SQUARE_WAVE_RATE_MASK);
	}
	catch (exception::HALException& ex)
	{
		throw exception::HALException("DS3231", "set_square_wave_rate",
			std::string("Could not change square wave rate bits:\n").append(ex.to_string()));
	}

	try
	{
		I2CManager::write_to_device(m_file_handle, CONTROL_REGISTER, &reg_data, 1);
	}
	catch (exception::HALException& ex)
	{
		throw exception::I2CException("DS3231", "set_square_wave_rate", m_dev_id, CONTROL_REGISTER,
			std::string("Could not write square wave rate to device:\n").append(ex.to_string()));
	}
}

hal::sensors::i2c::ds3231::SquareWaveRate hal::sensors::i2c::ds3231::DS3231::get_square_wave_rate() const
{
	uint8_t reg_data;
	try
	{
		reg_data = read_status_register();
	}
	catch (exception::HALException& ex)
	{
		throw exception::I2CException("DS3231", "get_square_wave_rate", m_dev_id, STATUS_REGISTER,
			std::string("Could not read status register:\n").append(ex.to_string()));
	}

	try
	{
		const auto value = BitManipulation::value_of_bits(reg_data, RS1_INDEX, RS2_INDEX);
		switch (value)
		{
		case 0:
			return SquareWaveRate::RATE_1_Hz;
		case 1:
			return SquareWaveRate::RATE_1024_kHz;
		case 2:
			return SquareWaveRate::RATE_4096_kHz;
		case 3:
			return SquareWaveRate::RATE_8192_kHz;
		default:
			throw exception::HALException("DS3231", "get_square_wave_rate",
				std::string("Invalid value for square wave rate value: ").append(std::to_string(value)));
		}
	}
	catch (exception::HALException& ex)
	{
		throw exception::HALException("DS3231", "get_square_wave_rate",
			std::string("Could not check bit status because bit index is out of bounds:\n").append(
				ex.to_string()));
	}
}

void hal::sensors::i2c::ds3231::DS3231::set_timezone(const WorldTimezones timezone) noexcept
{
	m_timezone = Timezone(timezone);
}

WorldTimezones hal::sensors::i2c::ds3231::DS3231::get_timezone() const noexcept
{
	return m_timezone.get_timezone();
}

void hal::sensors::i2c::ds3231::DS3231::set_clock_format(const std::string& format) noexcept
{
	m_clock_format = format;
}

std::string hal::sensors::i2c::ds3231::DS3231::get_clock_format() const noexcept
{
	return m_clock_format;
}

void hal::sensors::i2c::ds3231::DS3231::set_output_format(const OutputFormat format) noexcept
{
	m_output_format = format;
}

hal::sensors::i2c::ds3231::OutputFormat hal::sensors::i2c::ds3231::DS3231::get_output_format() const noexcept
{
	return m_output_format;
}

void hal::sensors::i2c::ds3231::DS3231::set_settings(const SettingsData& settings)
{
	try
	{
		set_hour_format(settings.hour_format);
		set_oscillator_state(settings.oscillator_state);
		set_square_wave_state(settings.square_wave_state);
		set_square_wave_rate(settings.square_wave_rate);
		set_timezone(settings.timezone.get_timezone());
		set_clock_format(settings.output_format);
	}
	catch (exception::HALException& ex)
	{
		throw exception::HALException("DS3231", "set_settings",
			std::string("Could not change settings of device:\n").append(ex.to_string()));
	}
}

hal::sensors::i2c::ds3231::SettingsData hal::sensors::i2c::ds3231::DS3231::get_settings() const
{
	SettingsData settings;
	try
	{
		settings.hour_format = get_hour_format();
		settings.oscillator_state = get_oscillator_state();
		settings.square_wave_state = get_square_wave_state();
		settings.square_wave_rate = get_square_wave_rate();
		settings.timezone = Timezone(get_timezone());
		settings.output_format = get_clock_format();
		return settings;
	}
	catch (exception::HALException& ex)
	{
		throw exception::HALException("DS3231", "get_settings",
			std::string("Could not get settings of device:\n").append(ex.to_string()));
	}
}

uint8_t hal::sensors::i2c::ds3231::DS3231::get_seconds() const
{
	uint8_t reg_data[1];
	try
	{
		I2CManager::read_from_device(m_file_handle, SECONDS_REGISTER, reg_data, 1);
	}
	catch (exception::HALException& ex)
	{
		throw exception::I2CException("DS3231", "get_seconds", m_dev_id, SECONDS_REGISTER,
			std::string("Could not read seconds register:\n").append(ex.to_string()));
	}

	try
	{
		return BitManipulation::from_bcd(BitManipulation::value_of_bits(reg_data[0], FIRST_DECIMAL_BEGIN, FIRST_DECIMAL_END),
			BitManipulation::value_of_bits(reg_data[0], SECOND_DECIMAL_BEGIN, SECOND_DECIMAL_END_1));
	}
	catch (exception::HALException& ex)
	{
		throw exception::HALException("DS3231", "get_seconds",
			std::string("Could not combine both BCD parts to the resulting seconds value:\n").append(
				ex.to_string()));
	}
}

uint8_t hal::sensors::i2c::ds3231::DS3231::get_minutes() const
{
	uint8_t reg_data[1];
	try
	{
		I2CManager::read_from_device(m_file_handle, MINUTES_REGISTER, reg_data, 1);
	}
	catch (exception::HALException& ex)
	{
		throw exception::I2CException("DS3231", "get_minutes", m_dev_id, MINUTES_REGISTER,
			std::string("Could not read minutes register:\n").append(ex.to_string()));
	}

	try
	{
		return BitManipulation::from_bcd(BitManipulation::value_of_bits(reg_data[0], FIRST_DECIMAL_BEGIN, FIRST_DECIMAL_END),
			BitManipulation::value_of_bits(reg_data[0], SECOND_DECIMAL_BEGIN, SECOND_DECIMAL_END_1));
	}
	catch (exception::HALException& ex)
	{
		throw exception::HALException("DS3231", "get_minutes",
			std::string("Could not combine both BCD parts to the resulting minutes value:\n").append(
				ex.to_string()));
	}
}

uint8_t hal::sensors::i2c::ds3231::DS3231::get_hours() const
{
	uint8_t reg_data[1];
	try
	{
		I2CManager::read_from_device(m_file_handle, HOURS_REGISTER, reg_data, 1);
	}
	catch (exception::HALException& ex)
	{
		throw exception::I2CException("DS3231", "get_hours", m_dev_id, HOURS_REGISTER,
			std::string("Could not read hours register:\n").append(ex.to_string()));
	}

	try
	{
		switch (get_hour_format())
		{
		case HourFormat::HOUR_FORMAT_12:
			return BitManipulation::from_bcd(BitManipulation::value_of_bits(reg_data[0], FIRST_DECIMAL_BEGIN, FIRST_DECIMAL_END),
				BitManipulation::is_bit_set(reg_data[0], HOUR_10_DECIMAL_INDEX) ? 0x01 : 0x00);
		case HourFormat::HOUR_FORMAT_24:
			switch (BitManipulation::value_of_bits(reg_data[0], HOUR_10_DECIMAL_INDEX, HOUR_20_DECIMAL_INDEX))
			{
			case 0: // resulting value is between 0 and 9 -> 10-Hours = 0 and 20-Hours = 0
				return BitManipulation::from_bcd(BitManipulation::value_of_bits(reg_data[0], FIRST_DECIMAL_BEGIN, FIRST_DECIMAL_END), 0x00);
			case 1: // resulting value is between 10 and 19 -> 10-Hours = 1 and 20-Hours = 0
				return BitManipulation::from_bcd(BitManipulation::value_of_bits(reg_data[0], FIRST_DECIMAL_BEGIN, FIRST_DECIMAL_END), 0x01);
			case 2: // resulting value is between 20 and 23 -> 10-Hours = 0 and 20-Hours = 1
				return BitManipulation::from_bcd(BitManipulation::value_of_bits(reg_data[0], FIRST_DECIMAL_BEGIN, FIRST_DECIMAL_END), 0x02);
			default:// invalid case since only one of both places can be 1 -> 10-Hours = 1 and 20-Hours = 1
				throw exception::HALException("DS3231", "get_hours",
					"Could not combine both BCD parts to the resulting hours value, since 10-Hours bit and 20-Hours bit are 1 with is invalid");
			}
		default:
			throw exception::HALException("DS3231", "get_hours", "Invalid hour format value.");
		}
	}
	catch (exception::HALException& ex)
	{
		throw exception::HALException("DS3231", "get_hours",
			std::string("Could not combine both BCD parts to the resulting hours value:\n").append(
				ex.to_string()));
	}
}

hal::sensors::i2c::ds3231::AmPm hal::sensors::i2c::ds3231::DS3231::get_am_pm() const
{
	uint8_t reg_data[1];
	try
	{
		I2CManager::read_from_device(m_file_handle, HOURS_REGISTER, reg_data, 1);
	}
	catch (exception::HALException& ex)
	{
		throw exception::I2CException("DS3231", "get_am_pm", m_dev_id, HOURS_REGISTER,
			std::string("Could not read hours register:\n").append(ex.to_string()));
	}

	try
	{
		return BitManipulation::is_bit_set(reg_data[0], AM_PM_INDEX) ? AmPm::PM : AmPm::AM;
	}
	catch (exception::HALException& ex)
	{
		throw exception::HALException("DS3231", "get_am_pm",
			std::string("Could not check daytime bit:\n").append(ex.to_string()));
	}
}

uint8_t hal::sensors::i2c::ds3231::DS3231::get_day() const
{
	uint8_t reg_data[1];
	try
	{
		I2CManager::read_from_device(m_file_handle, DAY_REGISTER, reg_data, 1);
	}
	catch (exception::HALException& ex)
	{
		throw exception::I2CException("DS3231", "get_day", m_dev_id, HOURS_REGISTER,
			std::string("Could not read day register:\n").append(ex.to_string()));
	}

	try
	{
		return BitManipulation::value_of_bits(reg_data[0], FIRST_DECIMAL_BEGIN, FIRST_DECIMAL_END);
	}
	catch (exception::HALException& ex)
	{
		throw exception::HALException("DS3231", "get_day",
			std::string("Could not read day bits:\n").append(ex.to_string()));
	}
}

uint8_t hal::sensors::i2c::ds3231::DS3231::get_date() const
{
	uint8_t reg_data[1];
	try
	{
		I2CManager::read_from_device(m_file_handle, DATE_REGISTER, reg_data, 1);
	}
	catch (exception::HALException& ex)
	{
		throw exception::I2CException("DS3231", "get_date", m_dev_id, DATE_REGISTER,
			std::string("Could not read date register:\n").append(ex.to_string()));
	}

	try
	{
		return BitManipulation::from_bcd(BitManipulation::value_of_bits(reg_data[0], FIRST_DECIMAL_BEGIN, FIRST_DECIMAL_END),
			BitManipulation::value_of_bits(reg_data[0], SECOND_DECIMAL_BEGIN, SECOND_DECIMAL_END_1));
	}
	catch (exception::HALException& ex)
	{
		throw exception::HALException("DS3231", "get_date",
			std::string("Could not combine both BCD parts to the resulting date value:\n").append(
				ex.to_string()));
	}
}

uint8_t hal::sensors::i2c::ds3231::DS3231::get_month() const
{
	uint8_t reg_data[1];
	try
	{
		I2CManager::read_from_device(m_file_handle, MONTH_REGISTER, reg_data, 1);
	}
	catch (exception::HALException& ex)
	{
		throw exception::I2CException("DS3231", "get_month", m_dev_id, MONTH_REGISTER,
			std::string("Could not read month register:\n").append(ex.to_string()));
	}

	try
	{
		return BitManipulation::from_bcd(BitManipulation::value_of_bits(reg_data[0], FIRST_DECIMAL_BEGIN, FIRST_DECIMAL_END),
			BitManipulation::value_of_bits(reg_data[0], SECOND_DECIMAL_BEGIN, SECOND_DECIMAL_END_1));
	}
	catch (exception::HALException& ex)
	{
		throw exception::HALException("DS3231", "get_month",
			std::string("Could not combine both BCD parts to the resulting month value:\n").append(
				ex.to_string()));
	}
}

uint8_t hal::sensors::i2c::ds3231::DS3231::get_year() const
{
	uint8_t reg_data[1];
	try
	{
		I2CManager::read_from_device(m_file_handle, YEAR_REGISTER, reg_data, 1);
	}
	catch (exception::HALException& ex)
	{
		throw exception::I2CException("DS3231", "get_year", m_dev_id, YEAR_REGISTER,
			std::string("Could not read month register:\n").append(ex.to_string()));
	}

	try
	{
		return BitManipulation::from_bcd(BitManipulation::value_of_bits(reg_data[0], FIRST_DECIMAL_BEGIN, FIRST_DECIMAL_END),
			BitManipulation::value_of_bits(reg_data[0], SECOND_DECIMAL_BEGIN, SECOND_DECIMAL_END_3));
	}
	catch (exception::HALException& ex)
	{
		throw exception::HALException("DS3231", "get_year",
			std::string("Could not combine both BCD parts to the resulting year value:\n").append(
				ex.to_string()));
	}
}

void hal::sensors::i2c::ds3231::DS3231::calibrate_to_current_temperature()
{
	try
	{
		uint8_t try_count = 0;
		// For 1 second check the BSY flag. If it is still in busy mode throw an exception.
		do
		{
			usleep(100);
			try_count++;
		} while (BitManipulation::is_bit_set(read_status_register(), BSY_INDEX) && try_count < 10);

		if (try_count >= 10)
		{
			throw exception::HALException("DS3231", "calibrate_to_current_temperature",
				std::string("Could not trigger a manual calibration since the device was busy:\n"));
		}
		else
		{
			try
			{
				auto control_reg = read_control_register();
				BitManipulation::set_bit(control_reg, CONV_INDEX, true);
				I2CManager::write_to_device(m_file_handle, CONTROL_REGISTER, &control_reg, 1);
			}
			catch (exception::HALException& ex)
			{
				throw exception::HALException("DS3231", "calibrate_to_current_temperature",
					std::string("Could not change convert temperature bit in control register:\n").append(ex.to_string()));
			}
		}
	}
	catch (exception::HALException& ex)
	{
		throw exception::HALException("DS3231", "calibrate_to_current_temperature",
			std::string("Could not trigger a manual calibration:\n").append(ex.to_string()));
	}
}

double hal::sensors::i2c::ds3231::DS3231::get_current_device_temperature() const
{
	uint8_t decimal[1];
	try
	{
		I2CManager::read_from_device(m_file_handle, TEMPERATURE_MSB_REGISTER, decimal, 1);
	}
	catch (exception::HALException& ex)
	{
		throw exception::I2CException("DS3231", "get_current_device_temperature", m_dev_id, TEMPERATURE_MSB_REGISTER,
			std::string("Could not read decimal part of temperature from register:\n").append(ex.to_string()));
	}

	uint8_t fraction[1];
	try
	{
		I2CManager::read_from_device(m_file_handle, TEMPERATURE_LSB_REGISTER, fraction, 1);
	}
	catch (exception::HALException& ex)
	{
		throw exception::I2CException("DS3231", "get_current_device_temperature", m_dev_id, TEMPERATURE_LSB_REGISTER,
			std::string("Could not read fractional part of temperature from register:\n").append(ex.to_string()));
	}

	try
	{
		const auto value = static_cast<double>(BitManipulation::value_of_bits(decimal[0], TEMPERATURE_DECIMAL_BEGIN, TEMPERATURE_DECIMAL_END)) +
			static_cast<double>(BitManipulation::value_of_bits(fraction[0], TEMPERATURE_FRACTION_BEGIN, TEMPERATURE_FRACTION_END) / 100.0);
		return BitManipulation::is_bit_set(decimal[0], SIGN_INDEX) ? value * -1.0 : value;
	}
	catch (exception::HALException& ex)
	{
		throw exception::HALException("DS3231", "get_current_device_temperature",
			std::string("Could not combine decimal and fractional parts to the resulting temperature value:\n").append(
				ex.to_string()));
	}
}

uint8_t hal::sensors::i2c::ds3231::DS3231::read_control_register() const
{
	try
	{
		uint8_t reg_data[1];
		I2CManager::read_from_device(m_file_handle, CONTROL_REGISTER, reg_data, 1);
		return reg_data[0];
	}
	catch (exception::HALException& ex)
	{
		throw exception::I2CException("DS3231", "read_control_register", m_dev_id, CONTROL_REGISTER,
			std::string("Could not read control register:\n").append(ex.to_string()));
	}
}

uint8_t hal::sensors::i2c::ds3231::DS3231::read_status_register() const
{
	try
	{
		uint8_t reg_data[1];
		I2CManager::read_from_device(m_file_handle, STATUS_REGISTER, reg_data, 1);
		return reg_data[0];
	}
	catch (exception::HALException& ex)
	{
		throw exception::I2CException("DS3231", "read_status_register", m_dev_id, STATUS_REGISTER,
			std::string("Could not read status register:\n").append(ex.to_string()));
	}
}
