#pragma once

namespace hal
{
	namespace sensors
	{
		namespace i2c
		{
			namespace ads1115
			{
				enum class OperationMode : int8_t
				{
					CONTINUOUS = 0,
					SINGLE_SHOT = 1
				};

				enum class Multiplexer : int8_t
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

				enum class GainAmplifier : int8_t
				{
					GAIN_6144_mV = 0,
					GAIN_4096_mV = 1,
					GAIN_2048_mV = 2,
					GAIN_1024_mV = 3,
					GAIN_512_mV = 4,
					GAIN_256_mV = 5
				};

				enum class DataRate : int8_t
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

				enum class ComparatorMode : int8_t
				{
					HYSTERESIS = 0,
					WINDOW = 1
				};

				enum class AlertPolarity : int8_t
				{
					ACTIVE_LOW = 0,
					ACTIVE_HIGH = 1
				};

				enum class AlertLatching : int8_t
				{
					DISABLED = 0,
					ACTIVE = 1
				};

				enum class AlertQueueing : int8_t
				{
					ASSERT_1_CONVERSION = 0,
					ASSERT_2_CONVERSIONS = 1,
					ASSERT_4_CONVERSIONS = 2,
					DISABLED = 3
				};

				struct Configuration
				{
					OperationMode operation_mode = OperationMode::SINGLE_SHOT;
					Multiplexer multiplexer = Multiplexer::POSITIVE_0_AND_NEGATIVE_1;
					GainAmplifier gain_amplifier = GainAmplifier::GAIN_2048_mV;
					DataRate data_rate = DataRate::RATE_128_SPS;
					ComparatorMode comparator_mode = ComparatorMode::HYSTERESIS;
					AlertPolarity alert_polarity = AlertPolarity::ACTIVE_LOW;
					AlertLatching alert_latching = AlertLatching::DISABLED;
					AlertQueueing alert_queueing = AlertQueueing::DISABLED;
				};
			}
		}
	}
}
