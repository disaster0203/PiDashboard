#pragma once
#include <string>
#include "../sensors/i2c/ADS1115Definitions.h"
#include "../sensors/i2c/BME280Definitions.h"
#include "../exceptions/HALException.h"
#include "../enums/SensorName.h"
#include "../enums/SensorSetting.h"
#include "../enums/SensorType.h"

namespace hal
{
	namespace utils
	{
		class EnumConverter
		{
		public:
			//! Converts a string to a Oversampling enum.
			/*!
			*  Converts a string to a Oversampling enum.
			* \param[in] str: The string to convert.
			* \returns A Oversampling enum value that was generated from the input string.
			* \throws HALException if no enum value matches the input string.
			*/
			static sensors::i2c::bme280::Oversampling string_to_oversampling(const std::string& str)
			{
				if (str.compare("NO_OVERSAMPLING") == 0)
				{
					return sensors::i2c::bme280::Oversampling::NO_OVERSAMPLING;
				}
				if (str.compare("OVERSAMPLING_16X") == 0)
				{
					return sensors::i2c::bme280::Oversampling::OVERSAMPLING_16X;
				}
				if (str.compare("OVERSAMPLING_8X") == 0)
				{
					return sensors::i2c::bme280::Oversampling::OVERSAMPLING_8X;
				}
				if (str.compare("OVERSAMPLING_4X") == 0)
				{
					return sensors::i2c::bme280::Oversampling::OVERSAMPLING_4X;
				}
				if (str.compare("OVERSAMPLING_2X") == 0)
				{
					return sensors::i2c::bme280::Oversampling::OVERSAMPLING_2X;
				}
				if (str.compare("OVERSAMPLING_1X") == 0)
				{
					return sensors::i2c::bme280::Oversampling::OVERSAMPLING_1X;
				}
				throw exception::HALException("EnumConverter", "string_to_oversampling",
														std::string("Could not convert string '").append(str).append(
															"' to Oversampling enum. Invalid value."));
			}

			//! Converts a string to a Filter enum.
			/*!
			*  Converts a string to a Filter enum.
			* \param[in] str: The string to convert.
			* \returns A Filter enum value that was generated from the input string.
			* \throws HALException if no enum value matches the input string.
			*/
			static sensors::i2c::bme280::Filter string_to_filter(const std::string& str)
			{
				if (str.compare("NO_FILTER") == 0)
				{
					return sensors::i2c::bme280::Filter::NO_FILTER;
				}
				if (str.compare("FILTER_16X") == 0)
				{
					return sensors::i2c::bme280::Filter::FILTER_16X;
				}
				if (str.compare("FILTER_8X") == 0)
				{
					return sensors::i2c::bme280::Filter::FILTER_8X;
				}
				if (str.compare("FILTER_4X") == 0)
				{
					return sensors::i2c::bme280::Filter::FILTER_4X;
				}
				if (str.compare("FILTER_2X") == 0)
				{
					return sensors::i2c::bme280::Filter::FILTER_2X;
				}
				throw exception::HALException("EnumConverter", "string_to_filter",
														std::string("Could not convert string '").append(str).append("' to Filter enum. Invalid value."));
			}

			//! Converts a string to a Multiplexer enum.
			/*!
			*  Converts a string to a Multiplexer enum.
			* \param[in] str: The string to convert.
			* \returns A Multiplexer enum value that was generated from the input string.
			* \throws HALException if no enum value matches the input string.
			*/
			static sensors::i2c::ads1115::Multiplexer string_to_multiplexer(const std::string& str)
			{
				if (str.compare("POSITIVE_0_AND_NEGATIVE_1") == 0)
				{
					return sensors::i2c::ads1115::Multiplexer::POSITIVE_0_AND_NEGATIVE_1;
				}
				if (str.compare("POSITIVE_0_AND_NEGATIVE_3") == 0)
				{
					return sensors::i2c::ads1115::Multiplexer::POSITIVE_0_AND_NEGATIVE_3;
				}
				if (str.compare("POSITIVE_1_AND_NEGATIVE_3") == 0)
				{
					return sensors::i2c::ads1115::Multiplexer::POSITIVE_1_AND_NEGATIVE_3;
				}
				if (str.compare("POSITIVE_2_AND_NEGATIVE_3") == 0)
				{
					return sensors::i2c::ads1115::Multiplexer::POSITIVE_2_AND_NEGATIVE_3;
				}
				if (str.compare("POSITIVE_0_AND_NEGATIVE_GND") == 0)
				{
					return sensors::i2c::ads1115::Multiplexer::POSITIVE_0_AND_NEGATIVE_GND;
				}
				if (str.compare("POSITIVE_1_AND_NEGATIVE_GND") == 0)
				{
					return sensors::i2c::ads1115::Multiplexer::POSITIVE_1_AND_NEGATIVE_GND;
				}
				if (str.compare("POSITIVE_2_AND_NEGATIVE_GND") == 0)
				{
					return sensors::i2c::ads1115::Multiplexer::POSITIVE_2_AND_NEGATIVE_GND;
				}
				if (str.compare("POSITIVE_3_AND_NEGATIVE_GND") == 0)
				{
					return sensors::i2c::ads1115::Multiplexer::POSITIVE_3_AND_NEGATIVE_GND;
				}
				throw exception::HALException("EnumConverter", "string_to_multiplexer",
														std::string("Could not convert string '").append(str).append(
															"' to Multiplexer enum. Invalid value."));
			}

			//! Converts a string to a GainAmplifier enum.
			/*!
			*  Converts a string to a GainAmplifier enum.
			* \param[in] str: The string to convert.
			* \returns A GainAmplifier enum value that was generated from the input string.
			* \throws HALException if no enum value matches the input string.
			*/
			static sensors::i2c::ads1115::GainAmplifier string_to_gain_amplifier(const std::string& str)
			{
				if (str.compare("GAIN_6144_mV") == 0)
				{
					return sensors::i2c::ads1115::GainAmplifier::GAIN_6144_mV;
				}
				if (str.compare("GAIN_4096_mV") == 0)
				{
					return sensors::i2c::ads1115::GainAmplifier::GAIN_4096_mV;
				}
				if (str.compare("GAIN_2048_mV") == 0)
				{
					return sensors::i2c::ads1115::GainAmplifier::GAIN_2048_mV;
				}
				if (str.compare("GAIN_1024_mV") == 0)
				{
					return sensors::i2c::ads1115::GainAmplifier::GAIN_1024_mV;
				}
				if (str.compare("GAIN_512_mV") == 0)
				{
					return sensors::i2c::ads1115::GainAmplifier::GAIN_512_mV;
				}
				if (str.compare("GAIN_256_mV") == 0)
				{
					return sensors::i2c::ads1115::GainAmplifier::GAIN_256_mV;
				}
				throw exception::HALException("EnumConverter", "string_to_gain_amplifier",
														std::string("Could not convert string '").append(str).append(
															"' to GainAmplifier enum. Invalid value."));
			}

			//! Converts a string to a OperationMode enum.
			/*!
			*  Converts a string to a OperationMode enum.
			* \param[in] str: The string to convert.
			* \returns A OperationMode enum value that was generated from the input string.
			* \throws HALException if no enum value matches the input string.
			*/
			static sensors::i2c::ads1115::OperationMode string_to_operation_mode(const std::string& str)
			{
				if (str.compare("CONTINUOUS") == 0)
				{
					return sensors::i2c::ads1115::OperationMode::CONTINUOUS;
				}
				if (str.compare("SINGLE_SHOT") == 0)
				{
					return sensors::i2c::ads1115::OperationMode::SINGLE_SHOT;
				}
				throw exception::HALException("EnumConverter", "string_to_operation_mode",
														std::string("Could not convert string '").append(str).append(
															"' to OperationMode enum. Invalid value."));
			}

			//! Converts a string to a DataRate enum.
			/*!
			*  Converts a string to a DataRate enum.
			* \param[in] str: The string to convert.
			* \returns A DataRate enum value that was generated from the input string.
			* \throws HALException if no enum value matches the input string.
			*/
			static sensors::i2c::ads1115::DataRate string_to_data_rate(const std::string& str)
			{
				if (str.compare("RATE_8_SPS") == 0)
				{
					return sensors::i2c::ads1115::DataRate::RATE_8_SPS;
				}
				if (str.compare("RATE_16_SPS") == 0)
				{
					return sensors::i2c::ads1115::DataRate::RATE_16_SPS;
				}
				if (str.compare("RATE_32_SPS") == 0)
				{
					return sensors::i2c::ads1115::DataRate::RATE_32_SPS;
				}
				if (str.compare("RATE_64_SPS") == 0)
				{
					return sensors::i2c::ads1115::DataRate::RATE_64_SPS;
				}
				if (str.compare("RATE_128_SPS") == 0)
				{
					return sensors::i2c::ads1115::DataRate::RATE_128_SPS;
				}
				if (str.compare("RATE_250_SPS") == 0)
				{
					return sensors::i2c::ads1115::DataRate::RATE_250_SPS;
				}
				if (str.compare("RATE_475_SPS") == 0)
				{
					return sensors::i2c::ads1115::DataRate::RATE_475_SPS;
				}
				if (str.compare("RATE_860_SPS") == 0)
				{
					return sensors::i2c::ads1115::DataRate::RATE_860_SPS;
				}
				throw exception::HALException("EnumConverter", "string_to_data_rate",
														std::string("Could not convert string '")
														.append(str).append("' to DataRate enum. Invalid value."));
			}

			//! Converts a string to a ComparatorMode enum.
			/*!
			*  Converts a string to a ComparatorMode enum.
			* \param[in] str: The string to convert.
			* \returns A ComparatorMode enum value that was generated from the input string.
			* \throws HALException if no enum value matches the input string.
			*/
			static sensors::i2c::ads1115::ComparatorMode string_to_comparator_mode(const std::string& str)
			{
				if (str.compare("HYSTERESIS") == 0)
				{
					return sensors::i2c::ads1115::ComparatorMode::HYSTERESIS;
				}
				if (str.compare("WINDOW") == 0)
				{
					return sensors::i2c::ads1115::ComparatorMode::WINDOW;
				}
				throw exception::HALException("EnumConverter", "string_to_comparator_mode",
														std::string("Could not convert string '").append(str).append(
															"' to ComparatorMode enum. Invalid value."));
			}

			//! Converts a string to a AlertPolarity enum.
			/*!
			*  Converts a string to a AlertPolarity enum.
			* \param[in] str: The string to convert.
			* \returns A AlertPolarity enum value that was generated from the input string.
			* \throws HALException if no enum value matches the input string.
			*/
			static sensors::i2c::ads1115::AlertPolarity string_to_alert_polarity(const std::string& str)
			{
				if (str.compare("ACTIVE_LOW") == 0)
				{
					return sensors::i2c::ads1115::AlertPolarity::ACTIVE_LOW;
				}
				if (str.compare("ACTIVE_HIGH") == 0)
				{
					return sensors::i2c::ads1115::AlertPolarity::ACTIVE_HIGH;
				}
				throw exception::HALException("EnumConverter", "string_to_alert_polarity",
														std::string("Could not convert string '").append(str).append(
															"' to AlertPolarity enum. Invalid value."));
			}

			//! Converts a string to a AlertLatching enum.
			/*!
			*  Converts a string to a AlertLatching enum.
			* \param[in] str: The string to convert.
			* \returns A AlertLatching enum value that was generated from the input string.
			* \throws HALException if no enum value matches the input string.
			*/
			static sensors::i2c::ads1115::AlertLatching string_to_alert_latching(const std::string& str)
			{
				if (str.compare("DISABLED") == 0)
				{
					return sensors::i2c::ads1115::AlertLatching::DISABLED;
				}
				if (str.compare("ACTIVE") == 0)
				{
					return sensors::i2c::ads1115::AlertLatching::ACTIVE;
				}
				throw exception::HALException("EnumConverter", "string_to_alert_latching",
														std::string("Could not convert string '").append(str).append(
															"' to AlertLatching enum. Invalid value."));
			}

			//! Converts a string to a AlertQueueing enum.
			/*!
			*  Converts a string to a AlertQueueing enum.
			* \param[in] str: The string to convert.
			* \returns A AlertQueueing enum value that was generated from the input string.
			* \throws HALException if no enum value matches the input string.
			*/
			static sensors::i2c::ads1115::AlertQueueing string_to_alert_queueing(const std::string& str)
			{
				if (str.compare("ASSERT_1_CONVERSION") == 0)
				{
					return sensors::i2c::ads1115::AlertQueueing::ASSERT_1_CONVERSION;
				}
				if (str.compare("ASSERT_2_CONVERSIONS") == 0)
				{
					return sensors::i2c::ads1115::AlertQueueing::ASSERT_2_CONVERSIONS;
				}
				if (str.compare("ASSERT_4_CONVERSIONS") == 0)
				{
					return sensors::i2c::ads1115::AlertQueueing::ASSERT_4_CONVERSIONS;
				}
				if (str.compare("DISABLED") == 0)
				{
					return sensors::i2c::ads1115::AlertQueueing::DISABLED;
				}
				throw exception::HALException("EnumConverter", "string_to_alert_queueing",
														std::string("Could not convert string '").append(str).append(
															"' to AlertQueueing enum. Invalid value."));
			}

			//! Converts SensorName enums to strings.
			/*!
			* Converts SensorName enums to strings.
			* \param[in] value: The enum to convert.
			* \returns The enum value as string.
			* \throws HALException if no case matches the given enum value.
			*/
			static std::string enum_to_string(const SensorName value)
			{
				switch (value)
				{
				case SensorName::BME280:
					return "BME280";
				case SensorName::ADS1115:
					return "ADS1115";
				case SensorName::AM312:
					return "AM312";
				case SensorName::CCS811:
					return "CCS811";
				case SensorName::DS3231:
					return "DS3231";
				case SensorName::KY_018:
					return "KY_018";
				default:
					throw exception::HALException("EnumConverter", "enum_to_string",
															"Could not convert SensorName enum to string. Invalid enum value.");
				}
			}

			//! Converts SensorType enums to strings.
			/*!
			* Converts SensorType enums to strings.
			* \param[in] value: The enum to convert.
			* \returns The enum value as string.
			* \throws HALException if no case matches the given enum value.
			*/
			static std::string enum_to_string(const SensorType value)
			{
				switch (value)
				{
				case SensorType::TEMPERATURE:
					return "Temperature";
				case SensorType::AIR_HUMIDITY:
					return "Air Humidity";
				case SensorType::AIR_PRESSURE:
					return "Air Pressure";
				case SensorType::CLOCK:
					return "Clock";
				case SensorType::CO2:
					return "CO2";
				case SensorType::CONVERTER:
					return "AD-Converter";
				case SensorType::LIGHT:
					return "Light";
				case SensorType::MOTION:
					return "Motion";
				case SensorType::TVOC:
					return "TVOC";
				default:
					throw exception::HALException("EnumConverter", "enum_to_string",
															"Could not convert SensorType enum to string. Invalid enum value.");
				}
			}

			//! Converts SensorSetting enums to strings.
			/*!
			* Converts SensorSetting enums to strings.
			* \param[in] value: The enum to convert.
			* \returns The enum value as string.
			* \throws HALException if no case matches the given enum value.
			*/
			static std::string enum_to_string(const SensorSetting value)
			{
				switch (value)
				{
				case SensorSetting::BASELINE:
					return "Baseline";
				case SensorSetting::COMPARATOR_LATCHING:
					return "Comparator Latching";
				case SensorSetting::COMPARATOR_MODE:
					return "Comparator Mode";
				case SensorSetting::COMPARATOR_QUEUE:
					return "Comparator Queue";
				case SensorSetting::DATA_RATE:
					return "Data Rate";
				case SensorSetting::ENVIRONMENT_DATA:
					return "Environment Data";
				case SensorSetting::FILTER:
					return "Filter";
				case SensorSetting::GAIN_AMPLIFIER:
					return "Gain Amplifier";
				case SensorSetting::MULTIPLEXER:
					return "Multiplexer";
				case SensorSetting::OVERSAMPLING:
					return "Oversampling";
				case SensorSetting::PIN_POLARITY:
					return "Pin Polarity";
				case SensorSetting::THRESHOLD:
					return "Threshold";
				default:
					throw exception::HALException("EnumConverter", "enum_to_string",
															"Could not convert SensorSetting enum to string. Invalid enum value.");
				}
			}

			//! Converts Multiplexer enums to strings.
			/*!
			* Converts Multiplexer enums to strings.
			* \param[in] value: The enum to convert.
			* \returns The enum value as string.
			* \throws HALException if no case matches the given enum value.
			*/
			static std::string enum_to_string(const sensors::i2c::ads1115::Multiplexer value)
			{
				switch (value)
				{
				case sensors::i2c::ads1115::Multiplexer::POSITIVE_0_AND_NEGATIVE_1:
					return "POSITIVE_0_AND_NEGATIVE_1";
				case sensors::i2c::ads1115::Multiplexer::POSITIVE_0_AND_NEGATIVE_3:
					return "POSITIVE_0_AND_NEGATIVE_3";
				case sensors::i2c::ads1115::Multiplexer::POSITIVE_1_AND_NEGATIVE_3:
					return "POSITIVE_1_AND_NEGATIVE_3";
				case sensors::i2c::ads1115::Multiplexer::POSITIVE_2_AND_NEGATIVE_3:
					return "POSITIVE_2_AND_NEGATIVE_3";
				case sensors::i2c::ads1115::Multiplexer::POSITIVE_0_AND_NEGATIVE_GND:
					return "POSITIVE_0_AND_NEGATIVE_GND";
				case sensors::i2c::ads1115::Multiplexer::POSITIVE_1_AND_NEGATIVE_GND:
					return "POSITIVE_1_AND_NEGATIVE_GND";
				case sensors::i2c::ads1115::Multiplexer::POSITIVE_2_AND_NEGATIVE_GND:
					return "POSITIVE_2_AND_NEGATIVE_GND";
				case sensors::i2c::ads1115::Multiplexer::POSITIVE_3_AND_NEGATIVE_GND:
					return "POSITIVE_3_AND_NEGATIVE_GND";
				default:
					throw exception::HALException("EnumConverter", "enum_to_string",
															"Could not convert Multiplexer enum to string. Invalid enum value.");
				}
			}

			//! Converts GainAmplifier enums to strings.
			/*!
			* Converts GainAmplifier enums to strings.
			* \param[in] value: The enum to convert.
			* \returns The enum value as string.
			* \throws HALException if no case matches the given enum value.
			*/
			static std::string enum_to_string(const sensors::i2c::ads1115::GainAmplifier value)
			{
				switch (value)
				{
				case sensors::i2c::ads1115::GainAmplifier::GAIN_6144_mV:
					return "GAIN_6144_mV";
				case sensors::i2c::ads1115::GainAmplifier::GAIN_4096_mV:
					return "GAIN_4096_mV";
				case sensors::i2c::ads1115::GainAmplifier::GAIN_2048_mV:
					return "GAIN_2048_mV";
				case sensors::i2c::ads1115::GainAmplifier::GAIN_1024_mV:
					return "GAIN_1024_mV";
				case sensors::i2c::ads1115::GainAmplifier::GAIN_512_mV:
					return "GAIN_512_mV";
				case sensors::i2c::ads1115::GainAmplifier::GAIN_256_mV:
					return "GAIN_256_mV";
				default:
					throw exception::HALException("EnumConverter", "enum_to_string",
															"Could not convert GainAmplifier enum to string. Invalid enum value.");
				}
			}

			//! Converts OperationMode enums to strings.
			/*!
			* Converts OperationMode enums to strings.
			* \param[in] value: The enum to convert.
			* \returns The enum value as string.
			* \throws HALException if no case matches the given enum value.
			*/
			static std::string enum_to_string(const sensors::i2c::ads1115::OperationMode value)
			{
				switch (value)
				{
				case sensors::i2c::ads1115::OperationMode::CONTINUOUS:
					return "CONTINUOUS";
				case sensors::i2c::ads1115::OperationMode::SINGLE_SHOT:
					return "SINGLE_SHOT";
				default:
					throw exception::HALException("EnumConverter", "enum_to_string",
															"Could not convert OperationMode enum to string. Invalid enum value.");
				}
			}

			//! Converts DataRate enums to strings.
			/*!
			* Converts DataRate enums to strings.
			* \param[in] value: The enum to convert.
			* \returns The enum value as string.
			* \throws HALException if no case matches the given enum value.
			*/
			static std::string enum_to_string(const sensors::i2c::ads1115::DataRate value)
			{
				switch (value)
				{
				case sensors::i2c::ads1115::DataRate::RATE_8_SPS:
					return "RATE_8_SPS";
				case sensors::i2c::ads1115::DataRate::RATE_16_SPS:
					return "RATE_16_SPS";
				case sensors::i2c::ads1115::DataRate::RATE_32_SPS:
					return "RATE_32_SPS";
				case sensors::i2c::ads1115::DataRate::RATE_64_SPS:
					return "RATE_64_SPS";
				case sensors::i2c::ads1115::DataRate::RATE_128_SPS:
					return "RATE_128_SPS";
				case sensors::i2c::ads1115::DataRate::RATE_250_SPS:
					return "RATE_250_SPS";
				case sensors::i2c::ads1115::DataRate::RATE_475_SPS:
					return "RATE_475_SPS";
				case sensors::i2c::ads1115::DataRate::RATE_860_SPS:
					return "RATE_860_SPS";
				default:
					throw exception::HALException("EnumConverter", "enum_to_string",
															"Could not convert DataRate enum to string. Invalid enum value.");
				}
			}

			//! Converts ComparatorMode enums to strings.
			/*!
			* Converts ComparatorMode enums to strings.
			* \param[in] value: The enum to convert.
			* \returns The enum value as string.
			* \throws HALException if no case matches the given enum value.
			*/
			static std::string enum_to_string(const sensors::i2c::ads1115::ComparatorMode value)
			{
				switch (value)
				{
				case sensors::i2c::ads1115::ComparatorMode::HYSTERESIS:
					return "HYSTERESIS";
				case sensors::i2c::ads1115::ComparatorMode::WINDOW:
					return "WINDOW";
				default:
					throw exception::HALException("EnumConverter", "enum_to_string",
															"Could not convert ComparatorMode enum to string. Invalid enum value.");
				}
			}

			//! Converts AlertPolarity enums to strings.
			/*!
			* Converts AlertPolarity enums to strings.
			* \param[in] value: The enum to convert.
			* \returns The enum value as string.
			* \throws HALException if no case matches the given enum value.
			*/
			static std::string enum_to_string(const sensors::i2c::ads1115::AlertPolarity value)
			{
				switch (value)
				{
				case sensors::i2c::ads1115::AlertPolarity::ACTIVE_HIGH:
					return "ACTIVE_HIGH";
				case sensors::i2c::ads1115::AlertPolarity::ACTIVE_LOW:
					return "ACTIVE_LOW";
				default:
					throw exception::HALException("EnumConverter", "enum_to_string",
															"Could not convert AlertPolarity enum to string. Invalid enum value.");
				}
			}

			//! Converts AlertLatching enums to strings.
			/*!
			* Converts AlertLatching enums to strings.
			* \param[in] value: The enum to convert.
			* \returns The enum value as string.
			* \throws HALException if no case matches the given enum value.
			*/
			static std::string enum_to_string(const sensors::i2c::ads1115::AlertLatching value)
			{
				switch (value)
				{
				case sensors::i2c::ads1115::AlertLatching::ACTIVE:
					return "ACTIVE";
				case sensors::i2c::ads1115::AlertLatching::DISABLED:
					return "DISABLED";
				default:
					throw exception::HALException("EnumConverter", "enum_to_string",
															"Could not convert AlertLatching enum to string. Invalid enum value.");
				}
			}

			//! Converts AlertQueueing enums to strings.
			/*!
			* Converts AlertQueueing enums to strings.
			* \param[in] value: The enum to convert.
			* \returns The enum value as string.
			* \throws HALException if no case matches the given enum value.
			*/
			static std::string enum_to_string(const sensors::i2c::ads1115::AlertQueueing value)
			{
				switch (value)
				{
				case sensors::i2c::ads1115::AlertQueueing::ASSERT_1_CONVERSION:
					return "ASSERT_1_CONVERSION";
				case sensors::i2c::ads1115::AlertQueueing::ASSERT_2_CONVERSIONS:
					return "ASSERT_2_CONVERSIONS";
				case sensors::i2c::ads1115::AlertQueueing::ASSERT_4_CONVERSIONS:
					return "ASSERT_4_CONVERSIONS";
				case sensors::i2c::ads1115::AlertQueueing::DISABLED:
					return "DISABLED";
				default:
					throw exception::HALException("EnumConverter", "enum_to_string",
															"Could not convert AlertQueueing enum to string. Invalid enum value.");
				}
			}
		};
	}
}
