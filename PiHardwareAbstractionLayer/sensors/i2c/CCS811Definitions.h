#pragma once

namespace hal
{
	namespace sensors
	{
		namespace i2c
		{
			namespace ccs811
			{
				enum class OperationMode : uint8_t
				{
					SLEEP = 0,
					PULSE_60_S = 1,
					PULSE_10_S = 2,
					CONSTANT_POWER_1_S = 3,
					CONSTANT_POWER_250_MS = 4
				};

				enum class State : uint8_t
				{
					BOOT = 0,
					READY = 1,
				};

				struct DeviceInfo
				{
					uint8_t device_id;
					uint8_t hardware_id;
					std::string hardware_version;
					std::string firmware_version;
					std::string application_version;
				};

				struct Thresholds
				{
					uint16_t low_medium_threshold;
					uint16_t medium_high_threshold;
					uint8_t hysteresis_threshold;
				};

				struct NTC
				{
					uint16_t v_over_resistor;
					uint16_t v_over_ntc;
				};

				struct Status
				{
					uint8_t raw_status_info;
					State current_state;
					bool firmware_loaded;
					bool data_ready;
					bool has_error;
					std::vector<std::string> error_message;
				};

				struct ModeInfo
				{
					uint8_t raw_mode_info;
					OperationMode current_mode;
					bool interrupt_generation;
					bool use_threshold;
				};

				struct RawData
				{
					uint8_t current; // in micro ampere
					uint16_t voltage; // in micro V
				};

				struct ResultData
				{
					uint16_t eco2_value;
					uint16_t tvoc_value;
					uint8_t status;
					uint8_t error_id;
					RawData raw_data;
				};
			}
		}
	}
}
