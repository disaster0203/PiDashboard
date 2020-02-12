#pragma once

namespace driver
{
	namespace sensors
	{
		namespace ads1115
		{
			enum class ads1115_operation_mode : int8_t
			{
				CONTINUOUS = 0,
				SINGLE_SHOT = 1
			};

			enum class ads1115_multiplexer : int8_t
			{
				POSITIVE_0_AND_NEGATIVE_1 = 0,
				POSITIVE_0_AND_NEGATIVE_3 = 1,
				POSITIVE_1_AND_NEGATIVE_3 = 2,
				POSITIVE_2_AND_NEGATIVE_3 = 3,
				POSITIVE_0_AND_NEGATIVE_GND = 4,
				POSITIVE_1_AND_NEGATIVE_GND = 5,
				POSITIVE_2_AND_NEGATIVE_GND = 6,
				POSITIVE_3_AND_NEGATIVE_GND = 7
			};

			enum class ads1115_gain_amplifier : int8_t
			{
				GAIN_6144_mV = 0,
				GAIN_4096_mV = 1,
				GAIN_2048_mV = 2,
				GAIN_1024_mV = 3,
				GAIN_512_mV = 4,
				GAIN_256_mV = 5

			};

			enum class ads1115_data_rate : int8_t
			{
				RATE_8_SPS = 0,
				RATE_16_SPS = 1,
				RATE_32_SPS = 2,
				RATE_64_SPS = 3,
				RATE_128_SPS = 4,
				RATE_250_SPS = 5,
				RATE_475_SPS = 6,
				RATE_860_SPS = 7
			};

			enum class ads1115_comparator_mode : int8_t
			{
				HYSTERESIS = 0,
				WINDOW = 1
			};

			enum class ads1115_alert_polarity : int8_t
			{
				ACTIVE_LOW = 0,
				ACTIVE_HIGH = 1
			};

			enum class ads1115_alert_latching : int8_t
			{
				DISABLED = 0,
				ACTIVE = 1
			};

			enum class ads1115_alert_queueing : int8_t
			{
				ASSERT_1_CONVERSION = 0,
				ASSERT_2_CONVERSIONS = 1,
				ASSERT_4_CONVERSIONS = 2,
				DISABLED = 3
			};

			struct ads1115_configuration
			{
				ads1115_operation_mode operation_mode = ads1115_operation_mode::SINGLE_SHOT;
				ads1115_multiplexer multiplexer = ads1115_multiplexer::POSITIVE_0_AND_NEGATIVE_1;
				ads1115_gain_amplifier gain_amplifier = ads1115_gain_amplifier::GAIN_2048_mV;
				ads1115_data_rate data_rate = ads1115_data_rate::RATE_128_SPS;
				ads1115_comparator_mode comparator_mode = ads1115_comparator_mode::HYSTERESIS;
				ads1115_alert_polarity alert_polarity = ads1115_alert_polarity::ACTIVE_LOW;
				ads1115_alert_latching alert_latching = ads1115_alert_latching::DISABLED;
				ads1115_alert_queueing alert_queueing = ads1115_alert_queueing::DISABLED;
			};
		}
	}
}