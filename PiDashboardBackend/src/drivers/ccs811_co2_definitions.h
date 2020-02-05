#pragma once

namespace driver
{
	namespace sensors
	{
		namespace ccs811
		{
			enum class ccs811_operation_mode : uint8_t
			{
				SLEEP = 0,
				PULSE_60_S = 1,
				PULSE_10_S = 2,
				CONSTANT_POWER_1_S = 3,
				CONSTANT_POWER_250_MS = 4
			};

			enum class ccs811_state : uint8_t
			{
				BOOT = 0,
				READY = 1,
			};

			struct ccs811_device_info
			{
				uint8_t device_id;
				uint8_t hardware_id;
				std::string hardware_version;
				std::string firmware_version;
				std::string application_version;
			};

			struct ccs811_thresholds
			{
				uint16_t low_medium_threshold;
				uint16_t medium_high_threshold;
				uint8_t hysteresis_threshold;
			};

			struct ccs811_ntc
			{
				uint16_t v_over_resistor;
				uint16_t v_over_ntc;
			};

			struct ccs811_status
			{
				uint8_t raw_status_info;
				ccs811_state current_state;
				bool firmware_loaded;
				bool data_ready;
				bool has_error;
				std::vector<std::string> error_message;
			};

			struct ccs811_mode_info
			{
				uint8_t raw_mode_info;
				ccs811_operation_mode current_mode;
				bool interrupt_gerneration;
				bool use_threshold;
			};

			struct ccs811_raw_data
			{
				uint8_t current; // in micro ampere
				uint16_t voltage; // in micro V
			};

			struct ccs811_result_data
			{
				uint16_t eco2_value;
				uint16_t tvoc_value;
				uint8_t status;
				uint8_t error_id;
				ccs811_raw_data raw_data;
			};
		}
	}
}