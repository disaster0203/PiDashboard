#pragma once

namespace hal
{
	namespace sensors
	{
		namespace i2c
		{
			namespace bme280
			{
				// General
				static constexpr uint8_t SOFT_RESET_VALUE = 0XB6;
				static constexpr uint8_t CHIP_ID = 0X60;
				static constexpr uint8_t STATUS_DURING_UPDATE = 0X01;

				static constexpr uint8_t SENSOR_PRIMARY_I2C_REG = 0x76;
				static constexpr uint8_t SENSOR_SECONDARY_I2C_REG = 0x77;

				// Temperature addresses
				static constexpr uint16_t TEMPERATURE_CALIBRATION_REG_1 = 0x88;
				static constexpr int16_t TEMPERATURE_CALIBRATION_REG_2 = 0x8A;
				static constexpr int16_t TEMPERATURE_CALIBRATION_REG_3 = 0x8C;

				// Pressure addresses
				static constexpr uint16_t PRESSURE_CALIBRATION_REG_1 = 0x8E;
				static constexpr int16_t PRESSURE_CALIBRATION_REG_2 = 0x90;
				static constexpr int16_t PRESSURE_CALIBRATION_REG_3 = 0x92;
				static constexpr int16_t PRESSURE_CALIBRATION_REG_4 = 0x94;
				static constexpr int16_t PRESSURE_CALIBRATION_REG_5 = 0x96;
				static constexpr int16_t PRESSURE_CALIBRATION_REG_6 = 0x98;
				static constexpr int16_t PRESSURE_CALIBRATION_REG_7 = 0x9A;
				static constexpr int16_t PRESSURE_CALIBRATION_REG_8 = 0x9C;
				static constexpr int16_t PRESSURE_CALIBRATION_REG_9 = 0x9E;

				// Humidity addresses
				static constexpr uint8_t HUMIDITY_CALIBRATION_REG_1 = 0xA1;
				static constexpr int16_t HUMIDITY_CALIBRATION_REG_2 = 0xE1;
				static constexpr uint8_t HUMIDITY_CALIBRATION_REG_3 = 0xE3;
				static constexpr int16_t HUMIDITY_CALIBRATION_REG_4 = 0xE4;
				static constexpr int16_t HUMIDITY_CALIBRATION_REG_5 = 0xE5;
				static constexpr int8_t HUMIDITY_CALIBRATION_REG_6 = (int8_t)0xE7;

				// General addresses
				static constexpr uint8_t FILE_BEGIN = 0X88;
				static constexpr uint8_t CHIP_ID_REG = 0XD0;
				static constexpr uint8_t SOFT_RESET_REG = 0XE0;
				static constexpr uint8_t MEASUREMENT_OVERSAMPLING_REG = 0XF4;
				static constexpr uint8_t MODE_REG = 0XF4;
				static constexpr uint8_t HUMIDITY_OVERSAMPLING_REG = 0XF2;
				static constexpr uint8_t CONFIG_REG = 0XF5;
				static constexpr uint8_t STATUS_REG = 0XF3;
				static constexpr uint8_t DATA_REG = 0XF7;

				// Settings selection
				static constexpr uint8_t PRESSURE_SETTING_SELECTION = 1;
				static constexpr uint8_t TEMPERATURE_SETTING_SELECTION = 1 << 1;
				static constexpr uint8_t HUMIDITY_SETTING_SELECTION = 1 << 2;
				static constexpr uint8_t FILTER_SETTING_SELECTION = 1 << 3;
				static constexpr uint8_t STANDBY_SETTING_SELECTION = 1 << 4;
				static constexpr uint8_t ALL_SETTING_SELECTION = 0x1F;
				static constexpr uint8_t OVERSAMPLING_SETTINGS = 0x07;
				static constexpr uint8_t FILTER_STANDBY_SETTINGS = 0x18;

				// Bit Masks
				static constexpr uint8_t SENSOR_MODE_MASK = 0x03;
				static constexpr uint8_t SENSOR_MODE_POS = 0x00;
				static constexpr uint8_t HUMIDITY_MASK = 0x07;
				static constexpr uint8_t HUMIDITY_POS = 0x00;
				static constexpr uint8_t PRESSURE_MASK = 0x1C;
				static constexpr uint8_t PRESSURE_POS = 0x02;
				static constexpr uint8_t TEMPERATURE_MASK = 0xE0;
				static constexpr uint8_t TEMPERATURE_POS = 0x05;
				static constexpr uint8_t FILTER_MASK = 0x1C;
				static constexpr uint8_t FILTER_POS = 0x02;
				static constexpr uint8_t STANDBY_MASK = 0xE0;
				static constexpr uint8_t STANDBY_POS = 0x05;

				// Lengths
				static constexpr uint8_t COMPLETE_FILE_LENGTH = 118;
				static constexpr uint8_t ALL_DATA_LENGTH = 8;
				static constexpr uint8_t TEMPERATURE_PRESSURE_CALIB_DATA_LENGTH = 26;
				static constexpr uint8_t HUMIDITY_CALIB_DATA_LENGTH = 7;

				// Extremas
				static constexpr double TEMPERATURE_MIN = -40.0;
				static constexpr double TEMPERATURE_MAX = 85.0;
				static constexpr double PRESSURE_MIN = 30000.0;
				static constexpr double PRESSURE_MAX = 110000.0;
				static constexpr double HUMIDITY_MIN = 0.0;
				static constexpr double HUMIDITY_MAX = 100.0;


				// Return codes (Warning, Ok, Error)
				static constexpr int8_t INVALID_OSR_WARNING = 1;
				static constexpr int8_t SLEEP_MODE_FAIL = -10;
				static constexpr int8_t NVM_COPY_FAILED = -11;
			}
		}
	}
}
