#pragma once

namespace driver
{
	namespace sensors
	{
		namespace bme280
		{
			enum class bme280_mode : int8_t
			{
				SLEEP = 0,
				FORCED = 1,
				NORMAL = 3
			};

			enum class bme280_oversampling : int8_t
			{
				NO_OVERSAMPLING = 0x00,
				OVERSAMPLING_1X = 0x01,
				OVERSAMPLING_2X = 0x02,
				OVERSAMPLING_4X = 0x03,
				OVERSAMPLING_8X = 0x04,
				OVERSAMPLING_16X = 0x05
			};

			enum class bme280_filter : int8_t
			{
				NO_FILTER = 0x00,
				FILTER_2X = 0x01,
				FILTER_4X = 0x02,
				FILTER_8X = 0x03,
				FILTER_16X = 0x04
			};

			enum class bme280_standby_time : int8_t
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

			struct calibration_data
			{
				int32_t fine_temperature;
				uint16_t temperature_calibration_addr_1;
				int16_t temperature_calibration_addr_2;
				int16_t temperature_calibration_addr_3;
				uint16_t pressure_calibration_addr_1;
				int16_t pressure_calibration_addr_2;
				int16_t pressure_calibration_addr_3;
				int16_t pressure_calibration_addr_4;
				int16_t pressure_calibration_addr_5;
				int16_t pressure_calibration_addr_6;
				int16_t pressure_calibration_addr_7;
				int16_t pressure_calibration_addr_8;
				int16_t pressure_calibration_addr_9;
				uint8_t humidity_calibration_addr_1;
				int16_t humidity_calibration_addr_2;
				uint8_t humidity_calibration_addr_3;
				int16_t humidity_calibration_addr_4;
				int16_t humidity_calibration_addr_5;
				int8_t humidity_calibration_addr_6;
			};

			struct settings_data
			{
				uint8_t standby_time;
				uint8_t filter;
				uint8_t temperature_oversampling;
				uint8_t pressure_oversampling;
				uint8_t humidity_oversampling;
			};

			struct raw_data
			{
				uint32_t temperature;
				uint32_t pressure;
				uint32_t humidity;
			};

			struct bme280_device
			{
				uint8_t chip_id;
				uint8_t dev_id;
				struct calibration_data calibration_data;
				struct settings_data settings;
				double wait_time;
			};
		}
	}
}