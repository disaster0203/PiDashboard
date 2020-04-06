#pragma once
#include "../../exceptions/HALException.h"
#include "../../utils/Timezone.h"

namespace hal
{
	namespace sensors
	{
		namespace i2c
		{
			namespace ds3231
			{
				enum class HourFormat : int8_t
				{
					HOUR_FORMAT_12 = 0x00,
					HOUR_FORMAT_24 = 0x01,
				};

				enum class AmPm : int8_t
				{
					AM = 0x00,
					PM = 0x01
				};

				enum class AlarmConfiguration : int8_t
				{
					EACH_SECOND = 0,
					EACH_MINUTE = 1,
					ONCE_PER_MINUTE = 2,
					ONCE_PER_HOUR = 3,
					ONCE_PER_DAY = 4,
					ONCE_PER_WEEK = 5,
					ONCE_PER_YEAR = 6
				};

				enum class OscillatorState : int8_t
				{
					START = 0x00,
					STOP = 0x01
				};

				enum class SquareWaveState : int8_t
				{
					START = 0x00,
					STOP = 0x01
				};

				enum class SquareWaveRate : int8_t
				{
					RATE_1_Hz = 0x00,
					RATE_1024_kHz = 0x01,
					RATE_4096_kHz = 0x02,
					RATE_8192_kHz = 0x03
				};

				enum class OutputFormat : int8_t
				{
					FORMATTED_STRING = 0x00,
					SECONDS_SINCE_EPOCH = 0x01
				};

				struct SettingsData
				{
					SettingsData()
					{
						hour_format = HourFormat::HOUR_FORMAT_12;
						alarm_1_active = false;
						alarm_1_configuration = AlarmConfiguration::EACH_SECOND;
						alarm_2_active = false;
						alarm_2_configuration = AlarmConfiguration::EACH_MINUTE;
						oscillator_state = OscillatorState::START;
						square_wave_state = SquareWaveState::STOP;
						square_wave_rate = SquareWaveRate::RATE_8192_kHz;
						timezone = utils::Timezone(utils::WorldTimezones::COORDINATED_UNIVERSAL_TIME__UTC__PLUS_H00M00);
						output_format = "%d.%m.%Y %H:%M:%S";
					}

					HourFormat hour_format;
					bool alarm_1_active;
					AlarmConfiguration alarm_1_configuration;
					bool alarm_2_active;
					AlarmConfiguration alarm_2_configuration;
					OscillatorState oscillator_state;
					SquareWaveState square_wave_state;
					SquareWaveRate square_wave_rate;
					utils::Timezone timezone;
					std::string output_format;
				};
			}
		}
	}
}