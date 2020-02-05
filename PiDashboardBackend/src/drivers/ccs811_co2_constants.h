#pragma once
#include <cstdint>

namespace driver
{
	namespace sensors
	{
		namespace ccs811
		{
			static constexpr const uint8_t HARDWARE_ID_VALUE = 0X81;
			static constexpr const uint8_t SENSOR_PRIMARY_I2C_REG = 0X5A;
			static constexpr const uint8_t SENSOR_SECONDARY_I2C_REG = 0X5B;

			// Operation mode addresses
			static constexpr const uint8_t STATUS_REG = 0X00;
			static constexpr const uint8_t MODE_REG = 0X01;
			static constexpr const uint8_t RESULT_DATA_REG = 0X02;
			static constexpr const uint8_t ENV_DATA_REG = 0X05;
			static constexpr const uint8_t NTC_REG = 0X06;
			static constexpr const uint8_t THRESHOLDS_REG = 0X10;
			static constexpr const uint8_t BASELINE_REG = 0X11;
			static constexpr const uint8_t HARDWARE_ID_REG = 0X20;
			static constexpr const uint8_t HARDWARE_VERSION_REG = 0X21;
			static constexpr const uint8_t FIRMWARE_VERSION_REG = 0X23;
			static constexpr const uint8_t APPLICATION_VERSION_REG = 0X24;
			static constexpr const uint8_t ERROR_REG = 0XE0;
			static constexpr const uint8_t RESET_REG = 0XFF;

			// Operation mode lengths
			static constexpr const uint8_t STATUS_LEN = 1;
			static constexpr const uint8_t MODE_LEN = 1;
			static constexpr const uint8_t ECO2_LEN = 2;
			static constexpr const uint8_t TVOC_LEN = 4;
			static constexpr const uint8_t RESULT_DATA_STATUS_LEN = 5;
			static constexpr const uint8_t RESULT_DATA_ERROR_LEN = 6;
			static constexpr const uint8_t RAW_DATA_LEN = 8;
			static constexpr const uint8_t ENV_TEMP_DATA_LEN = 2;
			static constexpr const uint8_t ENV_HUM_DATA_LEN = 2;
			static constexpr const uint8_t NTC_LEN = 2;
			static constexpr const uint8_t THRESHOLDS_LOW_MEDIUM_LEN = 2;
			static constexpr const uint8_t THRESHOLDS_MEDIUM_HIGH_LEN = 2;
			static constexpr const uint8_t THRESHOLDS_HYSTERESIS_LEN = 1;
			static constexpr const uint8_t BASELINE_LEN = 2;
			static constexpr const uint8_t HARDWARE_ID_LEN = 1;
			static constexpr const uint8_t HARDWARE_VERSION_LEN = 1;
			static constexpr const uint8_t FIRMWARE_VERSION_LEN = 2;
			static constexpr const uint8_t APPLICATION_VERSION_LEN = 2;
			static constexpr const uint8_t ERROR_LEN = 1;
			static constexpr const uint8_t RESET_LEN = 1;

			// Boot mode addresses
			static constexpr const uint8_t STATUS_BOOT_REG = 0X00;
			static constexpr const uint8_t APP_ERASE_BOOT_REG = 0XF1;
			static constexpr const uint8_t APP_DATA_BOOT_REG = 0XF2;
			static constexpr const uint8_t APP_VERIFY_BOOT_REG = 0XF3;
			static constexpr const uint8_t APP_START_BOOT_REG = 0XF4;

			// Boot mode lengths
			static constexpr const uint8_t STATUS_BOOT_LEN = 1;
			static constexpr const uint8_t APP_ERASE_BOOT_LEN = 4;
			static constexpr const uint8_t APP_DATA_BOOT_LEN = 9;
			static constexpr const uint8_t APP_VERIFY_BOOT_LEN = 1;
			static constexpr const uint8_t APP_START_LEN = 1;

			// Reset Codes
			static constexpr const uint8_t RESET_1 = 0X11;
			static constexpr const uint8_t RESET_2 = 0XE5;
			static constexpr const uint8_t RESET_3 = 0X72;
			static constexpr const uint8_t RESET_4 = 0X8A;
			static constexpr const uint8_t ERASE_1 = 0XE7;
			static constexpr const uint8_t ERASE_2 = 0XA7;
			static constexpr const uint8_t ERASE_3 = 0XE6;
			static constexpr const uint8_t ERASE_4 = 0X09;

			// Modes
			static constexpr const uint8_t SLEEP = 0 << 4;
			static constexpr const uint8_t CONSTANT_POWER_1_S = 1 << 4;
			static constexpr const uint8_t PULSE_10_S = 2 << 4;
			static constexpr const uint8_t PULSE_60_S = 3 << 4;
			static constexpr const uint8_t CONSTANT_POWER_250_MS = 4 << 4;
			static constexpr const uint8_t MODE_MASK = 0x70;

			// Extremas
			static constexpr const uint16_t LOW_MEDIUM_DEFAULT_THRES = 1500;
			static constexpr const uint16_t MEDIUM_HIGH_DEFAULT_THRES = 2500;
			static constexpr const uint8_t HYSTERESIS_DEFAULT_THRES = 50;
			static constexpr const uint16_t ECO2_MAX = 8192;
			static constexpr const uint16_t ECO2_MIN = 400;
			static constexpr const uint16_t TVOC_MAX = 1187;
			static constexpr const uint16_t TVOC_MIN = 0;
			static constexpr const uint8_t TEMPERATURE_BASELINE = 25;

			// Time constants
			static constexpr const uint32_t NEW_SENSOR_BURN_IN_TIME_IN_S = 172800; // 48h in seconds (for new sensors only)
			static constexpr const uint32_t SENSOR_WARM_UP_TIME_IN_S = 1200; // 20min in seconds (after changing to higher sampling mode)
			static constexpr const uint32_t BASELINE_THRESHOLD_IN_S = 1800000; // 500h in seconds (in 24/7 usage. First 500h save Baseline every 24h-48h, afterwards save it all 5-7 days)
			static constexpr const uint32_t BASELINE_EARLY_SAVE_TIME_IN_S = 129600; // 36h in seconds (in 24/7 usage. First 500h save Baseline every 24h-48h)
			static constexpr const uint32_t BASELINE_LATE_SAVE_TIME_IN_S = 518400; // 144h (6d) in seconds (in 24/7 usage. After 500h save Baseline every 5-7 days)
			static constexpr const uint32_t AWAKE_TIME_IN_US = 75; // 75 micro seconds. Datasheet says it takes minimum 50 micro seconds to awake the processor, so I decided to give him a little bit more time
			static constexpr const uint32_t DWAKE_TIME_IN_US = 45; // 35 micro seconds. Datasheet says the minimum time to deassert awake is 20 micro seconds to, so I decided to give it a little bit more time

			// Warnings
			static constexpr const int8_t MODE_SWITCH_WARNING = 34;
			static constexpr const int8_t WRONG_MODE_WARNING = 35;

			// Error codes
			static constexpr const int8_t WRITE_REG_INVALID = 1;
			static constexpr const int8_t READ_REG_INVALID = 1 << 1;
			static constexpr const int8_t MEASUREMODE_INVALID = 1 << 2;
			static constexpr const int8_t MAX_RESISTANCE = 1 << 3;
			static constexpr const int8_t HEATER_FAULT = 1 << 4;
			static constexpr const int8_t HEATER_SUPPLY_ERROR = 1 << 5;
		}
	}
}