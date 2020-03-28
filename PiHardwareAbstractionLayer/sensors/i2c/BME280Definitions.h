#pragma once

namespace hal
{
	namespace sensors
	{
		namespace i2c
		{
			namespace bme280
			{
				enum class OperationMode : int8_t
				{
					SLEEP = 0,
					FORCED = 1,
					NORMAL = 3
				};

				enum class Oversampling : int8_t
				{
					NO_OVERSAMPLING = 0x00,
					OVERSAMPLING_1X = 0x01,
					OVERSAMPLING_2X = 0x02,
					OVERSAMPLING_4X = 0x03,
					OVERSAMPLING_8X = 0x04,
					OVERSAMPLING_16X = 0x05
				};

				enum class Filter : int8_t
				{
					NO_FILTER = 0x00,
					FILTER_2X = 0x01,
					FILTER_4X = 0x02,
					FILTER_8X = 0x03,
					FILTER_16X = 0x04
				};

				enum class StandbyTime : int8_t
				{
					STANDBY_0_5_MS = 0x00,
					STANDBY_62_5_MS = 0x01,
					STANDBY_125_MS = 0x02,
					STANDBY_250_MS = 0x03,
					STANDBY_500_MS = 0x04,
					STANDBY_1000_MS = 0x05,
					STANDBY_10_MS = 0x06,
					STANDBY_20_MS = 0x07
				};

				struct CalibrationData
				{
					int32_t fine_temperature;
					uint16_t temperature_calibration_reg_1;
					int16_t temperature_calibration_reg_2;
					int16_t temperature_calibration_reg_3;
					uint16_t pressure_calibration_reg_1;
					int16_t pressure_calibration_reg_2;
					int16_t pressure_calibration_reg_3;
					int16_t pressure_calibration_reg_4;
					int16_t pressure_calibration_reg_5;
					int16_t pressure_calibration_reg_6;
					int16_t pressure_calibration_reg_7;
					int16_t pressure_calibration_reg_8;
					int16_t pressure_calibration_reg_9;
					uint8_t humidity_calibration_reg_1;
					int16_t humidity_calibration_reg_2;
					uint8_t humidity_calibration_reg_3;
					int16_t humidity_calibration_reg_4;
					int16_t humidity_calibration_reg_5;
					int8_t humidity_calibration_reg_6;
				};

				struct SettingsData
				{
					uint8_t standby_time;
					uint8_t filter;
					uint8_t temperature_oversampling;
					uint8_t pressure_oversampling;
					uint8_t humidity_oversampling;
				};

				struct RawData
				{
					uint32_t temperature;
					uint32_t pressure;
					uint32_t humidity;
				};

				struct Device
				{
					CalibrationData calibration_data;
					SettingsData settings;
					double wait_time;
				};
			}
		}
	}
}
