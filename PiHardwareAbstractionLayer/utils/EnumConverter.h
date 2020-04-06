#pragma once
#include <string>
#include "../sensors/i2c/ADS1115Definitions.h"
#include "../sensors/i2c/BME280Definitions.h"
#include "../sensors/i2c/DS3231Definitions.h"
#include "../exceptions/HALException.h"
#include "../enums/SensorName.h"
#include "../enums/SensorSetting.h"
#include "../enums/SensorType.h"
#include "../utils/Timezone.h"

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
				if (str == "NO_OVERSAMPLING")
				{
					return sensors::i2c::bme280::Oversampling::NO_OVERSAMPLING;
				}
				if (str == "OVERSAMPLING_16X")
				{
					return sensors::i2c::bme280::Oversampling::OVERSAMPLING_16X;
				}
				if (str == "OVERSAMPLING_8X")
				{
					return sensors::i2c::bme280::Oversampling::OVERSAMPLING_8X;
				}
				if (str == "OVERSAMPLING_4X")
				{
					return sensors::i2c::bme280::Oversampling::OVERSAMPLING_4X;
				}
				if (str == "OVERSAMPLING_2X")
				{
					return sensors::i2c::bme280::Oversampling::OVERSAMPLING_2X;
				}
				if (str == "OVERSAMPLING_1X")
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
				if (str == "NO_FILTER")
				{
					return sensors::i2c::bme280::Filter::NO_FILTER;
				}
				if (str == "FILTER_16X")
				{
					return sensors::i2c::bme280::Filter::FILTER_16X;
				}
				if (str == "FILTER_8X")
				{
					return sensors::i2c::bme280::Filter::FILTER_8X;
				}
				if (str == "FILTER_4X")
				{
					return sensors::i2c::bme280::Filter::FILTER_4X;
				}
				if (str == "FILTER_2X")
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
				if (str == "POSITIVE_0_AND_NEGATIVE_1")
				{
					return sensors::i2c::ads1115::Multiplexer::POSITIVE_0_AND_NEGATIVE_1;
				}
				if (str == "POSITIVE_0_AND_NEGATIVE_3")
				{
					return sensors::i2c::ads1115::Multiplexer::POSITIVE_0_AND_NEGATIVE_3;
				}
				if (str == "POSITIVE_1_AND_NEGATIVE_3")
				{
					return sensors::i2c::ads1115::Multiplexer::POSITIVE_1_AND_NEGATIVE_3;
				}
				if (str == "POSITIVE_2_AND_NEGATIVE_3")
				{
					return sensors::i2c::ads1115::Multiplexer::POSITIVE_2_AND_NEGATIVE_3;
				}
				if (str == "POSITIVE_0_AND_NEGATIVE_GND")
				{
					return sensors::i2c::ads1115::Multiplexer::POSITIVE_0_AND_NEGATIVE_GND;
				}
				if (str == "POSITIVE_1_AND_NEGATIVE_GND")
				{
					return sensors::i2c::ads1115::Multiplexer::POSITIVE_1_AND_NEGATIVE_GND;
				}
				if (str == "POSITIVE_2_AND_NEGATIVE_GND")
				{
					return sensors::i2c::ads1115::Multiplexer::POSITIVE_2_AND_NEGATIVE_GND;
				}
				if (str == "POSITIVE_3_AND_NEGATIVE_GND")
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
				if (str == "GAIN_6144_mV")
				{
					return sensors::i2c::ads1115::GainAmplifier::GAIN_6144_mV;
				}
				if (str == "GAIN_4096_mV")
				{
					return sensors::i2c::ads1115::GainAmplifier::GAIN_4096_mV;
				}
				if (str == "GAIN_2048_mV")
				{
					return sensors::i2c::ads1115::GainAmplifier::GAIN_2048_mV;
				}
				if (str == "GAIN_1024_mV")
				{
					return sensors::i2c::ads1115::GainAmplifier::GAIN_1024_mV;
				}
				if (str == "GAIN_512_mV")
				{
					return sensors::i2c::ads1115::GainAmplifier::GAIN_512_mV;
				}
				if (str == "GAIN_256_mV")
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
				if (str == "CONTINUOUS")
				{
					return sensors::i2c::ads1115::OperationMode::CONTINUOUS;
				}
				if (str == "SINGLE_SHOT")
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
				if (str == "RATE_8_SPS")
				{
					return sensors::i2c::ads1115::DataRate::RATE_8_SPS;
				}
				if (str == "RATE_16_SPS")
				{
					return sensors::i2c::ads1115::DataRate::RATE_16_SPS;
				}
				if (str == "RATE_32_SPS")
				{
					return sensors::i2c::ads1115::DataRate::RATE_32_SPS;
				}
				if (str == "RATE_64_SPS")
				{
					return sensors::i2c::ads1115::DataRate::RATE_64_SPS;
				}
				if (str == "RATE_128_SPS")
				{
					return sensors::i2c::ads1115::DataRate::RATE_128_SPS;
				}
				if (str == "RATE_250_SPS")
				{
					return sensors::i2c::ads1115::DataRate::RATE_250_SPS;
				}
				if (str == "RATE_475_SPS")
				{
					return sensors::i2c::ads1115::DataRate::RATE_475_SPS;
				}
				if (str == "RATE_860_SPS")
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
				if (str == "HYSTERESIS")
				{
					return sensors::i2c::ads1115::ComparatorMode::HYSTERESIS;
				}
				if (str == "WINDOW")
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
				if (str == "ACTIVE_LOW")
				{
					return sensors::i2c::ads1115::AlertPolarity::ACTIVE_LOW;
				}
				if (str == "ACTIVE_HIGH")
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
				if (str == "DISABLED")
				{
					return sensors::i2c::ads1115::AlertLatching::DISABLED;
				}
				if (str == "ACTIVE")
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
				if (str == "ASSERT_1_CONVERSION")
				{
					return sensors::i2c::ads1115::AlertQueueing::ASSERT_1_CONVERSION;
				}
				if (str == "ASSERT_2_CONVERSIONS")
				{
					return sensors::i2c::ads1115::AlertQueueing::ASSERT_2_CONVERSIONS;
				}
				if (str == "ASSERT_4_CONVERSIONS")
				{
					return sensors::i2c::ads1115::AlertQueueing::ASSERT_4_CONVERSIONS;
				}
				if (str == "DISABLED")
				{
					return sensors::i2c::ads1115::AlertQueueing::DISABLED;
				}
				throw exception::HALException("EnumConverter", "string_to_alert_queueing",
					std::string("Could not convert string '").append(str).append(
						"' to AlertQueueing enum. Invalid value."));
			}

			//! Converts a string to a HourFormat enum.
			/*!
			*  Converts a string to a HourFormat enum.
			* \param[in] str: The string to convert.
			* \returns A HourFormat enum value that was generated from the input string.
			* \throws HALException if no enum value matches the input string.
			*/
			static sensors::i2c::ds3231::HourFormat string_to_hour_format(const std::string& str)
			{
				if (str == "HOUR_FORMAT_12")
				{
					return sensors::i2c::ds3231::HourFormat::HOUR_FORMAT_12;
				}
				if (str == "HOUR_FORMAT_24")
				{
					return sensors::i2c::ds3231::HourFormat::HOUR_FORMAT_24;
				}
				throw exception::HALException("EnumConverter", "string_to_hour_format",
					std::string("Could not convert string '").append(str).append(
						"' to HourFormat enum. Invalid value."));
			}

			//! Converts a string to a OscillatorState enum.
			/*!
			*  Converts a string to a OscillatorState enum.
			* \param[in] str: The string to convert.
			* \returns A OscillatorState enum value that was generated from the input string.
			* \throws HALException if no enum value matches the input string.
			*/
			static sensors::i2c::ds3231::OscillatorState string_to_oscillator_state(const std::string& str)
			{
				if (str == "START")
				{
					return sensors::i2c::ds3231::OscillatorState::START;
				}
				if (str == "STOP")
				{
					return sensors::i2c::ds3231::OscillatorState::STOP;
				}
				throw exception::HALException("EnumConverter", "string_to_oscillator_state",
					std::string("Could not convert string '").append(str).append(
						"' to OscillatorState enum. Invalid value."));
			}

			//! Converts a string to a SquareWaveState enum.
			/*!
			*  Converts a string to a SquareWaveState enum.
			* \param[in] str: The string to convert.
			* \returns A SquareWaveState enum value that was generated from the input string.
			* \throws HALException if no enum value matches the input string.
			*/
			static sensors::i2c::ds3231::SquareWaveState string_to_square_wave_state(const std::string& str)
			{
				if (str == "START")
				{
					return sensors::i2c::ds3231::SquareWaveState::START;
				}
				if (str == "STOP")
				{
					return sensors::i2c::ds3231::SquareWaveState::STOP;
				}
				throw exception::HALException("EnumConverter", "string_to_square_wave_state",
					std::string("Could not convert string '").append(str).append(
						"' to SquareWaveState enum. Invalid value."));
			}

			//! Converts a string to a SquareWaveRate enum.
			/*!
			*  Converts a string to a SquareWaveRate enum.
			* \param[in] str: The string to convert.
			* \returns A SquareWaveRate enum value that was generated from the input string.
			* \throws HALException if no enum value matches the input string.
			*/
			static sensors::i2c::ds3231::SquareWaveRate string_to_square_wave_rate(const std::string& str)
			{
				if (str == "RATE_1_Hz")
				{
					return sensors::i2c::ds3231::SquareWaveRate::RATE_1_Hz;
				}
				if (str == "RATE_1024_kHz")
				{
					return sensors::i2c::ds3231::SquareWaveRate::RATE_1024_kHz;
				}
				if (str == "RATE_4096_kHz")
				{
					return sensors::i2c::ds3231::SquareWaveRate::RATE_4096_kHz;
				}
				if (str == "RATE_8192_kHz")
				{
					return sensors::i2c::ds3231::SquareWaveRate::RATE_8192_kHz;
				}
				throw exception::HALException("EnumConverter", "string_to_square_wave_rate",
					std::string("Could not convert string '").append(str).append(
						"' to SquareWaveRate enum. Invalid value."));
			}

			//! Converts a string to a OutputFormat enum.
			/*!
			*  Converts a string to a OutputFormat enum.
			* \param[in] str: The string to convert.
			* \returns A OutputFormat enum value that was generated from the input string.
			* \throws HALException if no enum value matches the input string.
			*/
			static sensors::i2c::ds3231::OutputFormat string_to_output_format(const std::string& str)
			{
				if (str == "FORMATTED_STRING")
				{
					return sensors::i2c::ds3231::OutputFormat::FORMATTED_STRING;
				}
				if (str == "SECONDS_SINCE_EPOCH")
				{
					return sensors::i2c::ds3231::OutputFormat::SECONDS_SINCE_EPOCH;
				}
				throw exception::HALException("EnumConverter", "string_to_output_format",
					std::string("Could not convert string '").append(str).append(
						"' to OutputFormat enum. Invalid value."));
			}

			//! Converts a string to a Timezone enum.
			/*!
			*  Converts a string to a Timezone enum.
			* \param[in] str: The string to convert.
			* \returns A Timezone enum value that was generated from the input string.
			* \throws HALException if no enum value matches the input string.
			*/
			static WorldTimezones string_to_timezone(const std::string& str)
			{
				if (str == "ALPHA_TIME_ZONE__A__PLUS_H01M00")
				{
					return WorldTimezones::ALPHA_TIME_ZONE__A__PLUS_H01M00;
				}
				if (str == "AUSTRALIAN_CENTRAL_DAYLIGHT_TIME__ACST__PLUS_H09M30")
				{
					return WorldTimezones::AUSTRALIAN_CENTRAL_DAYLIGHT_TIME__ACST__PLUS_H09M30;
				}
				if (str == "ACRE_TIME__ACT__MINUS_H05M00")
				{
					return WorldTimezones::ACRE_TIME__ACT__MINUS_H05M00;
				}
				if (str == "AUSTRALIAN_CENTRAL_STANDARD_TIME__ACST__PLUS_H09M30")
				{
					return WorldTimezones::AUSTRALIAN_CENTRAL_STANDARD_TIME__ACST__PLUS_H09M30;
				}
				if (str == "AUSTRALIAN_CENTRAL_WESTERN_STANDARD_TIME__ACWST__PLUS_H08M45")
				{
					return WorldTimezones::AUSTRALIAN_CENTRAL_WESTERN_STANDARD_TIME__ACWST__PLUS_H08M45;
				}
				if (str == "ATLANTIC_DAYLIGHT_TIME__ADT__MINUS_H03M00")
				{
					return WorldTimezones::ATLANTIC_DAYLIGHT_TIME__ADT__MINUS_H03M00;
				}
				if (str == "AUSTRALIAN_EASTERN_DAYLIGHT_TIME__AEST__PLUS_H10M00")
				{
					return WorldTimezones::AUSTRALIAN_EASTERN_DAYLIGHT_TIME__AEST__PLUS_H10M00;
				}
				if (str == "AUSTRALIAN_EASTERN_STANDARD_TIME__AEST__PLUS_H10M00")
				{
					return WorldTimezones::AUSTRALIAN_EASTERN_STANDARD_TIME__AEST__PLUS_H10M00;
				}
				if (str == "AFGHANISTAN_TIME__AFT__PLUS_H04M30")
				{
					return WorldTimezones::AFGHANISTAN_TIME__AFT__PLUS_H04M30;
				}
				if (str == "ALASKA_STANDARD_TIME__AKST__MINUS_H09M00")
				{
					return WorldTimezones::ALASKA_STANDARD_TIME__AKST__MINUS_H09M00;
				}
				if (str == "ALMA_ATA_TIME__ALMT__PLUS_H06M00")
				{
					return WorldTimezones::ALMA_ATA_TIME__ALMT__PLUS_H06M00;
				}
				if (str == "AMAZON_TIME__AMT__MINUS_H04M00")
				{
					return WorldTimezones::AMAZON_TIME__AMT__MINUS_H04M00;
				}
				if (str == "ARMENIA_TIME__AMT__PLUS_H04M00")
				{
					return WorldTimezones::ARMENIA_TIME__AMT__PLUS_H04M00;
				}
				if (str == "ANADYR_TIME__ANAT__PLUS_H12M00")
				{
					return WorldTimezones::ANADYR_TIME__ANAT__PLUS_H12M00;
				}
				if (str == "AQTOBE_TIME__AQTT__PLUS_H05M00")
				{
					return WorldTimezones::AQTOBE_TIME__AQTT__PLUS_H05M00;
				}
				if (str == "ARGENTINA_TIME__ART__MINUS_H03M00")
				{
					return WorldTimezones::ARGENTINA_TIME__ART__MINUS_H03M00;
				}
				if (str == "ARABIA_STANDARD_TIME__AST__PLUS_H03M00")
				{
					return WorldTimezones::ARABIA_STANDARD_TIME__AST__PLUS_H03M00;
				}
				if (str == "ATLANTIC_STANDARD_TIME__AST__MINUS_H04M00")
				{
					return WorldTimezones::ATLANTIC_STANDARD_TIME__AST__MINUS_H04M00;
				}
				if (str == "ATLANTIC_DAYLIGHT_TIME__AT__MINUS_H04M00")
				{
					return WorldTimezones::ATLANTIC_DAYLIGHT_TIME__AT__MINUS_H04M00;
				}
				if (str == "AUSTRALIAN_WESTERN_STANDARD_TIME__AWST__PLUS_H08M00")
				{
					return WorldTimezones::AUSTRALIAN_WESTERN_STANDARD_TIME__AWST__PLUS_H08M00;
				}
				if (str == "AZORES_TIME__AZOT__MINUS_H01M00")
				{
					return WorldTimezones::AZORES_TIME__AZOT__MINUS_H01M00;
				}
				if (str == "AZERBAIJAN_TIME__AZT__PLUS_H04M00")
				{
					return WorldTimezones::AZERBAIJAN_TIME__AZT__PLUS_H04M00;
				}
				if (str == "ANYWHERE_ON_EARTH__AOE__MINUS_H12M00")
				{
					return WorldTimezones::ANYWHERE_ON_EARTH__AOE__MINUS_H12M00;
				}
				if (str == "BRAVO_TIME_ZONE__B__PLUS_H02M00")
				{
					return WorldTimezones::BRAVO_TIME_ZONE__B__PLUS_H02M00;
				}
				if (str == "BRUNEI_DARUSSALAM_TIME__BNT__PLUS_H08M00")
				{
					return WorldTimezones::BRUNEI_DARUSSALAM_TIME__BNT__PLUS_H08M00;
				}
				if (str == "BOLIVIA_TIME__BOT__MINUS_H04M00")
				{
					return WorldTimezones::BOLIVIA_TIME__BOT__MINUS_H04M00;
				}
				if (str == "BRASILIA_TIME__BRT__MINUS_H03M00")
				{
					return WorldTimezones::BRASILIA_TIME__BRT__MINUS_H03M00;
				}
				if (str == "BANGLADESH_STANDARD_TIME__BST__PLUS_H06M00")
				{
					return WorldTimezones::BANGLADESH_STANDARD_TIME__BST__PLUS_H06M00;
				}
				if (str == "BOUGAINVILLE_STANDARD_TIME__BST__PLUS_H11M00")
				{
					return WorldTimezones::BOUGAINVILLE_STANDARD_TIME__BST__PLUS_H11M00;
				}
				if (str == "BHUTAN_TIME__BTT__PLUS_H06M00")
				{
					return WorldTimezones::BHUTAN_TIME__BTT__PLUS_H06M00;
				}
				if (str == "CHARLIE_TIME_ZONE__C__PLUS_H03M00")
				{
					return WorldTimezones::CHARLIE_TIME_ZONE__C__PLUS_H03M00;
				}
				if (str == "CASEY_TIME__CAST__PLUS_H08M00")
				{
					return WorldTimezones::CASEY_TIME__CAST__PLUS_H08M00;
				}
				if (str == "CENTRAL_AFRICA_TIME__CAT__PLUS_H02M00")
				{
					return WorldTimezones::CENTRAL_AFRICA_TIME__CAT__PLUS_H02M00;
				}
				if (str == "COCOS_ISLANDS_TIME__CCT__PLUS_H06M30")
				{
					return WorldTimezones::COCOS_ISLANDS_TIME__CCT__PLUS_H06M30;
				}
				if (str == "CUBA_STANDARD_TIME__CST__MINUS_H05M00")
				{
					return WorldTimezones::CUBA_STANDARD_TIME__CST__MINUS_H05M00;
				}
				if (str == "CENTRAL_EUROPEAN_STANDARD_TIME__CET__PLUS_H01M00")
				{
					return WorldTimezones::CENTRAL_EUROPEAN_STANDARD_TIME__CET__PLUS_H01M00;
				}
				if (str == "CENTRAL_EUROPEAN_TIME__CET__PLUS_H01M00")
				{
					return WorldTimezones::CENTRAL_EUROPEAN_TIME__CET__PLUS_H01M00;
				}
				if (str == "CHATHAM_ISLAND_STANDARD_TIME__CHAST__PLUS_H12M45")
				{
					return WorldTimezones::CHATHAM_ISLAND_STANDARD_TIME__CHAST__PLUS_H12M45;
				}
				if (str == "CHOIBALSAN_TIME__CHOT__PLUS_H08M00")
				{
					return WorldTimezones::CHOIBALSAN_TIME__CHOT__PLUS_H08M00;
				}
				if (str == "CHUUK_TIME__CHUT__PLUS_H10M00")
				{
					return WorldTimezones::CHUUK_TIME__CHUT__PLUS_H10M00;
				}
				if (str == "COOK_ISLAND_TIME__CKT__MINUS_H10M00")
				{
					return WorldTimezones::COOK_ISLAND_TIME__CKT__MINUS_H10M00;
				}
				if (str == "CHILE_STANDARD_TIME__CLT__MINUS_H04M00")
				{
					return WorldTimezones::CHILE_STANDARD_TIME__CLT__MINUS_H04M00;
				}
				if (str == "COLOMBIA_TIME__COT__MINUS_H05M00")
				{
					return WorldTimezones::COLOMBIA_TIME__COT__MINUS_H05M00;
				}
				if (str == "CENTRAL_STANDARD_TIME__CST__MINUS_H06M00")
				{
					return WorldTimezones::CENTRAL_STANDARD_TIME__CST__MINUS_H06M00;
				}
				if (str == "CHINA_STANDARD_TIME__CST__PLUS_H08M00")
				{
					return WorldTimezones::CHINA_STANDARD_TIME__CST__PLUS_H08M00;
				}
				if (str == "CAPE_VERDE_TIME__CVT__MINUS_H01M00")
				{
					return WorldTimezones::CAPE_VERDE_TIME__CVT__MINUS_H01M00;
				}
				if (str == "CHRISTMAS_ISLAND_TIME__CXT__PLUS_H07M00")
				{
					return WorldTimezones::CHRISTMAS_ISLAND_TIME__CXT__PLUS_H07M00;
				}
				if (str == "CHAMORRO_STANDARD_TIME__CHST__PLUS_H10M00")
				{
					return WorldTimezones::CHAMORRO_STANDARD_TIME__CHST__PLUS_H10M00;
				}
				if (str == "DELTA_TIME_ZONE__D__PLUS_H04M00")
				{
					return WorldTimezones::DELTA_TIME_ZONE__D__PLUS_H04M00;
				}
				if (str == "DAVIS_TIME__DAVT__PLUS_H07M00")
				{
					return WorldTimezones::DAVIS_TIME__DAVT__PLUS_H07M00;
				}
				if (str == "DUMONT_D_URVILLE_TIME__DDUT__PLUS_H10M00")
				{
					return WorldTimezones::DUMONT_D_URVILLE_TIME__DDUT__PLUS_H10M00;
				}
				if (str == "ECHO_TIME_ZONE__E__PLUS_H05M00")
				{
					return WorldTimezones::ECHO_TIME_ZONE__E__PLUS_H05M00;
				}
				if (str == "EASTER_ISLAND_STANDARD_TIME__EAST__MINUS_H06M00")
				{
					return WorldTimezones::EASTER_ISLAND_STANDARD_TIME__EAST__MINUS_H06M00;
				}
				if (str == "EASTERN_AFRICA_TIME__EAT__PLUS_H03M00")
				{
					return WorldTimezones::EASTERN_AFRICA_TIME__EAT__PLUS_H03M00;
				}
				if (str == "ECUADOR_TIME__ECT__MINUS_H05M00")
				{
					return WorldTimezones::ECUADOR_TIME__ECT__MINUS_H05M00;
				}
				if (str == "EASTERN_EUROPEAN_TIME__EET__PLUS_H02M00")
				{
					return WorldTimezones::EASTERN_EUROPEAN_TIME__EET__PLUS_H02M00;
				}
				if (str == "EAST_GREENLAND_TIME__EGT__MINUS_H01M00")
				{
					return WorldTimezones::EAST_GREENLAND_TIME__EGT__MINUS_H01M00;
				}
				if (str == "EASTERN_STANDARD_TIME__EST__MINUS_H05M00")
				{
					return WorldTimezones::EASTERN_STANDARD_TIME__EST__MINUS_H05M00;
				}
				if (str == "EASTERN_DAYLIGHT_TIME__EST__MINUS_H05M00")
				{
					return WorldTimezones::EASTERN_DAYLIGHT_TIME__EST__MINUS_H05M00;
				}
				if (str == "FOXTROT_TIME_ZONE__F__PLUS_H06M00")
				{
					return WorldTimezones::FOXTROT_TIME_ZONE__F__PLUS_H06M00;
				}
				if (str == "FURTHER_EASTERN_EUROPEAN_TIME__FET__PLUS_H03M00")
				{
					return WorldTimezones::FURTHER_EASTERN_EUROPEAN_TIME__FET__PLUS_H03M00;
				}
				if (str == "FIJI_TIME__FJT__PLUS_H12M00")
				{
					return WorldTimezones::FIJI_TIME__FJT__PLUS_H12M00;
				}
				if (str == "FALKLAND_ISLAND_TIME__FKT__MINUS_H04M00")
				{
					return WorldTimezones::FALKLAND_ISLAND_TIME__FKT__MINUS_H04M00;
				}
				if (str == "FERNANDO_DE_NORONHA_TIME__FNT__MINUS_H02M00")
				{
					return WorldTimezones::FERNANDO_DE_NORONHA_TIME__FNT__MINUS_H02M00;
				}
				if (str == "GOLF_TIME_ZONE__G__PLUS_H07M00")
				{
					return WorldTimezones::GOLF_TIME_ZONE__G__PLUS_H07M00;
				}
				if (str == "GALAPAGOS_TIME__GALT__MINUS_H06M00")
				{
					return WorldTimezones::GALAPAGOS_TIME__GALT__MINUS_H06M00;
				}
				if (str == "GAMBIER_TIME__GAMT__MINUS_H09M00")
				{
					return WorldTimezones::GAMBIER_TIME__GAMT__MINUS_H09M00;
				}
				if (str == "GEORGIA_STANDARD_TIME__GET__PLUS_H04M00")
				{
					return WorldTimezones::GEORGIA_STANDARD_TIME__GET__PLUS_H04M00;
				}
				if (str == "FRENCH_GUIANA_TIME__GFT__MINUS_H03M00")
				{
					return WorldTimezones::FRENCH_GUIANA_TIME__GFT__MINUS_H03M00;
				}
				if (str == "GILBERT_ISLAND_TIME__GILT__PLUS_H12M00")
				{
					return WorldTimezones::GILBERT_ISLAND_TIME__GILT__PLUS_H12M00;
				}
				if (str == "GREENWICH_MEAN_TIME__GMT__PLUS_H00M00")
				{
					return WorldTimezones::GREENWICH_MEAN_TIME__GMT__PLUS_H00M00;
				}
				if (str == "GULF_STANDARD_TIME__GST__PLUS_H04M00")
				{
					return WorldTimezones::GULF_STANDARD_TIME__GST__PLUS_H04M00;
				}
				if (str == "SOUTH_GEORGIA_TIME__GST__MINUS_H02M00")
				{
					return WorldTimezones::SOUTH_GEORGIA_TIME__GST__MINUS_H02M00;
				}
				if (str == "GUYANA_TIME__GYT__MINUS_H04M00")
				{
					return WorldTimezones::GUYANA_TIME__GYT__MINUS_H04M00;
				}
				if (str == "HOTEL_TIME_ZONE__H__PLUS_H08M00")
				{
					return WorldTimezones::HOTEL_TIME_ZONE__H__PLUS_H08M00;
				}
				if (str == "HAWAII_ALEUTIAN_DAYLIGHT_TIME__HST__MINUS_H10M00")
				{
					return WorldTimezones::HAWAII_ALEUTIAN_DAYLIGHT_TIME__HST__MINUS_H10M00;
				}
				if (str == "HONG_KONG_TIME__HKT__PLUS_H08M00")
				{
					return WorldTimezones::HONG_KONG_TIME__HKT__PLUS_H08M00;
				}
				if (str == "HOVD_TIME__HOVT__PLUS_H07M00")
				{
					return WorldTimezones::HOVD_TIME__HOVT__PLUS_H07M00;
				}
				if (str == "HAWAII_STANDARD_TIME__HST__MINUS_H10M00")
				{
					return WorldTimezones::HAWAII_STANDARD_TIME__HST__MINUS_H10M00;
				}
				if (str == "INDIA_TIME_ZONE__I__PLUS_H09M00")
				{
					return WorldTimezones::INDIA_TIME_ZONE__I__PLUS_H09M00;
				}
				if (str == "INDOCHINA_TIME__ICT__PLUS_H07M00")
				{
					return WorldTimezones::INDOCHINA_TIME__ICT__PLUS_H07M00;
				}
				if (str == "INDIAN_CHAGOS_TIME__IOT__PLUS_H06M00")
				{
					return WorldTimezones::INDIAN_CHAGOS_TIME__IOT__PLUS_H06M00;
				}
				if (str == "IRKUTSK_TIME__IRKT__PLUS_H08M00")
				{
					return WorldTimezones::IRKUTSK_TIME__IRKT__PLUS_H08M00;
				}
				if (str == "IRAN_STANDARD_TIME__IRST__PLUS_H03M30")
				{
					return WorldTimezones::IRAN_STANDARD_TIME__IRST__PLUS_H03M30;
				}
				if (str == "INDIA_STANDARD_TIME__IST__PLUS_H05M30")
				{
					return WorldTimezones::INDIA_STANDARD_TIME__IST__PLUS_H05M30;
				}
				if (str == "IRISH_STANDARD_TIME__IST__PLUS_H01M00")
				{
					return WorldTimezones::IRISH_STANDARD_TIME__IST__PLUS_H01M00;
				}
				if (str == "ISRAEL_STANDARD_TIME__IST__PLUS_H02M00")
				{
					return WorldTimezones::ISRAEL_STANDARD_TIME__IST__PLUS_H02M00;
				}
				if (str == "JAPAN_STANDARD_TIME__JST__PLUS_H09M00")
				{
					return WorldTimezones::JAPAN_STANDARD_TIME__JST__PLUS_H09M00;
				}
				if (str == "KILO_TIME_ZONE__K__PLUS_H10M00")
				{
					return WorldTimezones::KILO_TIME_ZONE__K__PLUS_H10M00;
				}
				if (str == "KYRGYZSTAN_TIME__KGT__PLUS_H06M00")
				{
					return WorldTimezones::KYRGYZSTAN_TIME__KGT__PLUS_H06M00;
				}
				if (str == "KOSRAE_TIME__KOST__PLUS_H11M00")
				{
					return WorldTimezones::KOSRAE_TIME__KOST__PLUS_H11M00;
				}
				if (str == "KRASNOYARSK_TIME__KRAT__PLUS_H07M00")
				{
					return WorldTimezones::KRASNOYARSK_TIME__KRAT__PLUS_H07M00;
				}
				if (str == "KOREA_STANDARD_TIME__KST__PLUS_H09M00")
				{
					return WorldTimezones::KOREA_STANDARD_TIME__KST__PLUS_H09M00;
				}
				if (str == "KUYBYSHEV_TIME__KUYT__PLUS_H04M00")
				{
					return WorldTimezones::KUYBYSHEV_TIME__KUYT__PLUS_H04M00;
				}
				if (str == "LIMA_TIME_ZONE__L__PLUS_H11M00")
				{
					return WorldTimezones::LIMA_TIME_ZONE__L__PLUS_H11M00;
				}
				if (str == "LORD_HOWE_STANDARD_TIME__LHST__PLUS_H10M30")
				{
					return WorldTimezones::LORD_HOWE_STANDARD_TIME__LHST__PLUS_H10M30;
				}
				if (str == "LINE_ISLANDS_TIME__LINT__PLUS_H14M00")
				{
					return WorldTimezones::LINE_ISLANDS_TIME__LINT__PLUS_H14M00;
				}
				if (str == "MIKE_TIME_ZONE__M__PLUS_H12M00")
				{
					return WorldTimezones::MIKE_TIME_ZONE__M__PLUS_H12M00;
				}
				if (str == "MAGADAN_TIME__MAGT__PLUS_H11M00")
				{
					return WorldTimezones::MAGADAN_TIME__MAGT__PLUS_H11M00;
				}
				if (str == "MARQUESAS_TIME__MART__MINUS_H09M30")
				{
					return WorldTimezones::MARQUESAS_TIME__MART__MINUS_H09M30;
				}
				if (str == "MAWSON_TIME__MAWT__PLUS_H05M00")
				{
					return WorldTimezones::MAWSON_TIME__MAWT__PLUS_H05M00;
				}
				if (str == "MARSHALL_ISLANDS_TIME__MHT__PLUS_H12M00")
				{
					return WorldTimezones::MARSHALL_ISLANDS_TIME__MHT__PLUS_H12M00;
				}
				if (str == "MYANMAR_TIME__MMT__PLUS_H06M30")
				{
					return WorldTimezones::MYANMAR_TIME__MMT__PLUS_H06M30;
				}
				if (str == "MOSCOW_STANDARD_TIME__MSK__PLUS_H03M00")
				{
					return WorldTimezones::MOSCOW_STANDARD_TIME__MSK__PLUS_H03M00;
				}
				if (str == "MOUNTAIN_STANDARD_TIME__MST__MINUS_H07M00")
				{
					return WorldTimezones::MOUNTAIN_STANDARD_TIME__MST__MINUS_H07M00;
				}
				if (str == "MOUNTAIN_DAYLIGHT_TIME__MST__MINUS_H07M00")
				{
					return WorldTimezones::MOUNTAIN_DAYLIGHT_TIME__MST__MINUS_H07M00;
				}
				if (str == "MAURITIUS_TIME__MUT__PLUS_H04M00")
				{
					return WorldTimezones::MAURITIUS_TIME__MUT__PLUS_H04M00;
				}
				if (str == "MALDIVES_TIME__MVT__PLUS_H05M00")
				{
					return WorldTimezones::MALDIVES_TIME__MVT__PLUS_H05M00;
				}
				if (str == "MALAYSIA_TIME__MYT__PLUS_H08M00")
				{
					return WorldTimezones::MALAYSIA_TIME__MYT__PLUS_H08M00;
				}
				if (str == "NOVEMBER_TIME_ZONE__N__MINUS_H01M00")
				{
					return WorldTimezones::NOVEMBER_TIME_ZONE__N__MINUS_H01M00;
				}
				if (str == "NEW_CALEDONIA_TIME__NCT__PLUS_H11M00")
				{
					return WorldTimezones::NEW_CALEDONIA_TIME__NCT__PLUS_H11M00;
				}
				if (str == "NEWFOUNDLAND_STANDARD_TIME__NDT__MINUS_H03M30")
				{
					return WorldTimezones::NEWFOUNDLAND_STANDARD_TIME__NDT__MINUS_H03M30;
				}
				if (str == "NOVOSIBIRSK_TIME__NOVT__PLUS_H07M00")
				{
					return WorldTimezones::NOVOSIBIRSK_TIME__NOVT__PLUS_H07M00;
				}
				if (str == "NEPAL_TIME___NPT__PLUS_H05M45")
				{
					return WorldTimezones::NEPAL_TIME___NPT__PLUS_H05M45;
				}
				if (str == "NAURU_TIME__NRT__PLUS_H12M00")
				{
					return WorldTimezones::NAURU_TIME__NRT__PLUS_H12M00;
				}
				if (str == "NIUE_TIME__NUT__MINUS_H11M00")
				{
					return WorldTimezones::NIUE_TIME__NUT__MINUS_H11M00;
				}
				if (str == "NEW_ZEALAND_STANDARD_TIME__NZST__PLUS_H12M00")
				{
					return WorldTimezones::NEW_ZEALAND_STANDARD_TIME__NZST__PLUS_H12M00;
				}
				if (str == "OSCAR_TIME_ZONE__O__MINUS_H02M00")
				{
					return WorldTimezones::OSCAR_TIME_ZONE__O__MINUS_H02M00;
				}
				if (str == "OMSK_STANDARD_TIME__OMST__PLUS_H06M00")
				{
					return WorldTimezones::OMSK_STANDARD_TIME__OMST__PLUS_H06M00;
				}
				if (str == "ORAL_TIME__ORAT__PLUS_H05M00")
				{
					return WorldTimezones::ORAL_TIME__ORAT__PLUS_H05M00;
				}
				if (str == "PAPA_TIME_ZONE__P__MINUS_H03M00")
				{
					return WorldTimezones::PAPA_TIME_ZONE__P__MINUS_H03M00;
				}
				if (str == "PERU_TIME__PET__MINUS_H05M00")
				{
					return WorldTimezones::PERU_TIME__PET__MINUS_H05M00;
				}
				if (str == "KAMCHATKA_TIME__PETT__PLUS_H12M00")
				{
					return WorldTimezones::KAMCHATKA_TIME__PETT__PLUS_H12M00;
				}
				if (str == "PAPUA_NEW_GUINEA_TIME__PGT__PLUS_H10M00")
				{
					return WorldTimezones::PAPUA_NEW_GUINEA_TIME__PGT__PLUS_H10M00;
				}
				if (str == "PHOENIX_ISLAND_TIME__PHOT__PLUS_H13M00")
				{
					return WorldTimezones::PHOENIX_ISLAND_TIME__PHOT__PLUS_H13M00;
				}
				if (str == "PHILIPPINE_TIME__PHT__PLUS_H08M00")
				{
					return WorldTimezones::PHILIPPINE_TIME__PHT__PLUS_H08M00;
				}
				if (str == "PAKISTAN_STANDARD_TIME__PKT__PLUS_H05M00")
				{
					return WorldTimezones::PAKISTAN_STANDARD_TIME__PKT__PLUS_H05M00;
				}
				if (str == "PIERRE_MIQUELON_DAYLIGHT_TIME__PMDT__MINUS_H02M00")
				{
					return WorldTimezones::PIERRE_MIQUELON_DAYLIGHT_TIME__PMDT__MINUS_H02M00;
				}
				if (str == "PIERRE_MIQUELON_STANDARD_TIME__PMST__MINUS_H03M00")
				{
					return WorldTimezones::PIERRE_MIQUELON_STANDARD_TIME__PMST__MINUS_H03M00;
				}
				if (str == "POHNPEI_STANDARD_TIME__PONT__PLUS_H11M00")
				{
					return WorldTimezones::POHNPEI_STANDARD_TIME__PONT__PLUS_H11M00;
				}
				if (str == "PACIFIC_STANDARD_TIME__PST__MINUS_H08M00")
				{
					return WorldTimezones::PACIFIC_STANDARD_TIME__PST__MINUS_H08M00;
				}
				if (str == "PITCAIRN_STANDARD_TIME__PST__MINUS_H08M00")
				{
					return WorldTimezones::PITCAIRN_STANDARD_TIME__PST__MINUS_H08M00;
				}
				if (str == "PALAU_TIME__PWT__PLUS_H09M00")
				{
					return WorldTimezones::PALAU_TIME__PWT__PLUS_H09M00;
				}
				if (str == "PARAGUAY_TIME__PYT__MINUS_H04M00")
				{
					return WorldTimezones::PARAGUAY_TIME__PYT__MINUS_H04M00;
				}
				if (str == "PYONGYANG_TIME__PYT__PLUS_H08M30")
				{
					return WorldTimezones::PYONGYANG_TIME__PYT__PLUS_H08M30;
				}
				if (str == "QUEBEC_TIME_ZONE__Q__MINUS_H04M00")
				{
					return WorldTimezones::QUEBEC_TIME_ZONE__Q__MINUS_H04M00;
				}
				if (str == "QYZYLORDA_TIME__QYZT__PLUS_H06M00")
				{
					return WorldTimezones::QYZYLORDA_TIME__QYZT__PLUS_H06M00;
				}
				if (str == "ROMEO_TIME_ZONE__R__MINUS_H05M00")
				{
					return WorldTimezones::ROMEO_TIME_ZONE__R__MINUS_H05M00;
				}
				if (str == "REUNION_TIME__RET__PLUS_H04M00")
				{
					return WorldTimezones::REUNION_TIME__RET__PLUS_H04M00;
				}
				if (str == "ROTHERA_TIME__ROTT__MINUS_H03M00")
				{
					return WorldTimezones::ROTHERA_TIME__ROTT__MINUS_H03M00;
				}
				if (str == "SIERRA_TIME_ZONE__S__MINUS_H06M00")
				{
					return WorldTimezones::SIERRA_TIME_ZONE__S__MINUS_H06M00;
				}
				if (str == "SAKHALIN_TIME__SAKT__PLUS_H11M00")
				{
					return WorldTimezones::SAKHALIN_TIME__SAKT__PLUS_H11M00;
				}
				if (str == "SAMARA_TIME__SAMT__PLUS_H04M00")
				{
					return WorldTimezones::SAMARA_TIME__SAMT__PLUS_H04M00;
				}
				if (str == "SOUTH_AFRICA_STANDARD_TIME__SAST__PLUS_H02M00")
				{
					return WorldTimezones::SOUTH_AFRICA_STANDARD_TIME__SAST__PLUS_H02M00;
				}
				if (str == "SOLOMON_ISLANDS_TIME__SBT__PLUS_H11M00")
				{
					return WorldTimezones::SOLOMON_ISLANDS_TIME__SBT__PLUS_H11M00;
				}
				if (str == "SEYCHELLES_TIME__SCT__PLUS_H04M00")
				{
					return WorldTimezones::SEYCHELLES_TIME__SCT__PLUS_H04M00;
				}
				if (str == "SINGAPORE_TIME__SGT__PLUS_H08M00")
				{
					return WorldTimezones::SINGAPORE_TIME__SGT__PLUS_H08M00;
				}
				if (str == "SREDNEKOLYMSK_TIME__SRET__PLUS_H11M00")
				{
					return WorldTimezones::SREDNEKOLYMSK_TIME__SRET__PLUS_H11M00;
				}
				if (str == "SURINAME_TIME__SRT__MINUS_H03M00")
				{
					return WorldTimezones::SURINAME_TIME__SRT__MINUS_H03M00;
				}
				if (str == "SAMOA_STANDARD_TIME__SST__MINUS_H11M00")
				{
					return WorldTimezones::SAMOA_STANDARD_TIME__SST__MINUS_H11M00;
				}
				if (str == "SYOWA_TIME__SYOT__PLUS_H03M00")
				{
					return WorldTimezones::SYOWA_TIME__SYOT__PLUS_H03M00;
				}
				if (str == "TANGO_TIME_ZONE__T__MINUS_H07M00")
				{
					return WorldTimezones::TANGO_TIME_ZONE__T__MINUS_H07M00;
				}
				if (str == "TAHITI_TIME__TAHT__MINUS_H10M00")
				{
					return WorldTimezones::TAHITI_TIME__TAHT__MINUS_H10M00;
				}
				if (str == "FRENCH_SOUTHERN_AND_ANTARCTIC_TIME__TFT__PLUS_H05M00")
				{
					return WorldTimezones::FRENCH_SOUTHERN_AND_ANTARCTIC_TIME__TFT__PLUS_H05M00;
				}
				if (str == "TAJIKISTAN_TIME__TJT__PLUS_H05M00")
				{
					return WorldTimezones::TAJIKISTAN_TIME__TJT__PLUS_H05M00;
				}
				if (str == "TOKELAU_TIME__TKT__PLUS_H13M00")
				{
					return WorldTimezones::TOKELAU_TIME__TKT__PLUS_H13M00;
				}
				if (str == "EAST_TIMOR_TIME__TLT__PLUS_H09M00")
				{
					return WorldTimezones::EAST_TIMOR_TIME__TLT__PLUS_H09M00;
				}
				if (str == "TURKMENISTAN_TIME__TMT__PLUS_H05M00")
				{
					return WorldTimezones::TURKMENISTAN_TIME__TMT__PLUS_H05M00;
				}
				if (str == "TONGA_TIME__TOT__PLUS_H13M00")
				{
					return WorldTimezones::TONGA_TIME__TOT__PLUS_H13M00;
				}
				if (str == "TURKEY_TIME__TRT__PLUS_H03M00")
				{
					return WorldTimezones::TURKEY_TIME__TRT__PLUS_H03M00;
				}
				if (str == "TUVALU_TIME__TVT__PLUS_H12M00")
				{
					return WorldTimezones::TUVALU_TIME__TVT__PLUS_H12M00;
				}
				if (str == "UNIFORM_TIME_ZONE__U__MINUS_H08M00")
				{
					return WorldTimezones::UNIFORM_TIME_ZONE__U__MINUS_H08M00;
				}
				if (str == "ULAANBAATAR_TIME__ULAT__PLUS_H08M00")
				{
					return WorldTimezones::ULAANBAATAR_TIME__ULAT__PLUS_H08M00;
				}
				if (str == "COORDINATED_UNIVERSAL_TIME__UTC__PLUS_H00M00")
				{
					return WorldTimezones::COORDINATED_UNIVERSAL_TIME__UTC__PLUS_H00M00;
				}
				if (str == "URUGUAY_TIME__UYT__MINUS_H03M00")
				{
					return WorldTimezones::URUGUAY_TIME__UYT__MINUS_H03M00;
				}
				if (str == "UZBEKISTAN_TIME__UZT__PLUS_H05M00")
				{
					return WorldTimezones::UZBEKISTAN_TIME__UZT__PLUS_H05M00;
				}
				if (str == "VICTOR_TIME_ZONE__V__MINUS_H09M00")
				{
					return WorldTimezones::VICTOR_TIME_ZONE__V__MINUS_H09M00;
				}
				if (str == "VENEZUELAN_STANDARD_TIME__VET__MINUS_H04M00")
				{
					return WorldTimezones::VENEZUELAN_STANDARD_TIME__VET__MINUS_H04M00;
				}
				if (str == "VLADIVOSTOK_TIME__VLAT__PLUS_H10M00")
				{
					return WorldTimezones::VLADIVOSTOK_TIME__VLAT__PLUS_H10M00;
				}
				if (str == "VOSTOK_TIME__VOST__PLUS_H06M00")
				{
					return WorldTimezones::VOSTOK_TIME__VOST__PLUS_H06M00;
				}
				if (str == "VANUATU_TIME__VUT__PLUS_H11M00")
				{
					return WorldTimezones::VANUATU_TIME__VUT__PLUS_H11M00;
				}
				if (str == "WHISKEY_TIME_ZONE__W__MINUS_H10M00")
				{
					return WorldTimezones::WHISKEY_TIME_ZONE__W__MINUS_H10M00;
				}
				if (str == "WAKE_TIME__WAKT__PLUS_H12M00")
				{
					return WorldTimezones::WAKE_TIME__WAKT__PLUS_H12M00;
				}
				if (str == "WEST_AFRICA_TIME__WAT__PLUS_H01M00")
				{
					return WorldTimezones::WEST_AFRICA_TIME__WAT__PLUS_H01M00;
				}
				if (str == "WESTERN_EUROPEAN_TIME__WET__PLUS_H00M00")
				{
					return WorldTimezones::WESTERN_EUROPEAN_TIME__WET__PLUS_H00M00;
				}
				if (str == "WALLIS_AND_FUTUNA_TIME__WFT__PLUS_H12M00")
				{
					return WorldTimezones::WALLIS_AND_FUTUNA_TIME__WFT__PLUS_H12M00;
				}
				if (str == "WEST_GREENLAND_TIME__WGT__MINUS_H03M00")
				{
					return WorldTimezones::WEST_GREENLAND_TIME__WGT__MINUS_H03M00;
				}
				if (str == "WESTERN_INDONESIAN_TIME__WIB__PLUS_H07M00")
				{
					return WorldTimezones::WESTERN_INDONESIAN_TIME__WIB__PLUS_H07M00;
				}
				if (str == "EASTERN_INDONESIAN_TIME__WIT__PLUS_H09M00")
				{
					return WorldTimezones::EASTERN_INDONESIAN_TIME__WIT__PLUS_H09M00;
				}
				if (str == "CENTRAL_INDONESIAN_TIME__WITA__PLUS_H08M00")
				{
					return WorldTimezones::CENTRAL_INDONESIAN_TIME__WITA__PLUS_H08M00;
				}
				if (str == "WEST_SAMOA_TIME__WST__PLUS_H14M00")
				{
					return WorldTimezones::WEST_SAMOA_TIME__WST__PLUS_H14M00;
				}
				if (str == "WESTERN_SAHARA_STANDARD_TIME__WT__PLUS_H00M00")
				{
					return WorldTimezones::WESTERN_SAHARA_STANDARD_TIME__WT__PLUS_H00M00;
				}
				if (str == "X_RAY_TIME_ZONE__X__MINUS_H11M00")
				{
					return WorldTimezones::X_RAY_TIME_ZONE__X__MINUS_H11M00;
				}
				if (str == "YANKEE_TIME_ZONE__Y__MINUS_H12M00")
				{
					return WorldTimezones::YANKEE_TIME_ZONE__Y__MINUS_H12M00;
				}
				if (str == "YAKUTSK_TIME__YAKT__PLUS_H09M00")
				{
					return WorldTimezones::YAKUTSK_TIME__YAKT__PLUS_H09M00;
				}
				if (str == "YAP_TIME__YAPT__PLUS_H10M00")
				{
					return WorldTimezones::YAP_TIME__YAPT__PLUS_H10M00;
				}
				if (str == "YEKATERINBURG_TIME__YEKT__PLUS_H05M00")
				{
					return WorldTimezones::YEKATERINBURG_TIME__YEKT__PLUS_H05M00;
				}
				if (str == "ZULU_TIME_ZONE__Z__PLUS_H00M00")
				{
					return WorldTimezones::ZULU_TIME_ZONE__Z__PLUS_H00M00;
				}
				throw exception::HALException("EnumConverter", "string_to_timezone", std::string("Could not convert string ).append(str).append( to Timezone enum. Invalid value."));
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

			//! Converts HourFormat enums to strings.
			/*!
			* Converts HourFormat enums to strings.
			* \param[in] value: The enum to convert.
			* \returns The enum value as string.
			* \throws HALException if no case matches the given enum value.
			*/
			static std::string enum_to_string(const sensors::i2c::ds3231::HourFormat value)
			{
				switch (value)
				{
				case sensors::i2c::ds3231::HourFormat::HOUR_FORMAT_12:
					return "HOUR_FORMAT_12";
				case sensors::i2c::ds3231::HourFormat::HOUR_FORMAT_24:
					return "HOUR_FORMAT_24";
				default:
					throw exception::HALException("EnumConverter", "enum_to_string",
						"Could not convert HourFormat enum to string. Invalid enum value.");
				}
			}

			//! Converts OscillatorState enums to strings.
			/*!
			* Converts OscillatorState enums to strings.
			* \param[in] value: The enum to convert.
			* \returns The enum value as string.
			* \throws HALException if no case matches the given enum value.
			*/
			static std::string enum_to_string(const sensors::i2c::ds3231::OscillatorState value)
			{
				switch (value)
				{
				case sensors::i2c::ds3231::OscillatorState::START:
					return "START";
				case sensors::i2c::ds3231::OscillatorState::STOP:
					return "STOP";
				default:
					throw exception::HALException("EnumConverter", "enum_to_string",
						"Could not convert OscillatorState enum to string. Invalid enum value.");
				}
			}

			//! Converts SquareWaveState enums to strings.
			/*!
			* Converts SquareWaveState enums to strings.
			* \param[in] value: The enum to convert.
			* \returns The enum value as string.
			* \throws HALException if no case matches the given enum value.
			*/
			static std::string enum_to_string(const sensors::i2c::ds3231::SquareWaveState value)
			{
				switch (value)
				{
				case sensors::i2c::ds3231::SquareWaveState::START:
					return "START";
				case sensors::i2c::ds3231::SquareWaveState::STOP:
					return "STOP";
				default:
					throw exception::HALException("EnumConverter", "enum_to_string",
						"Could not convert SquareWaveState enum to string. Invalid enum value.");
				}
			}

			//! Converts SquareWaveRate enums to strings.
			/*!
			* Converts SquareWaveRate enums to strings.
			* \param[in] value: The enum to convert.
			* \returns The enum value as string.
			* \throws HALException if no case matches the given enum value.
			*/
			static std::string enum_to_string(const sensors::i2c::ds3231::SquareWaveRate value)
			{
				switch (value)
				{
				case sensors::i2c::ds3231::SquareWaveRate::RATE_1_Hz:
					return "RATE_1_Hz";
				case sensors::i2c::ds3231::SquareWaveRate::RATE_1024_kHz:
					return "RATE_1024_kHz";
				case sensors::i2c::ds3231::SquareWaveRate::RATE_4096_kHz:
					return "RATE_4096_kHz";
				case sensors::i2c::ds3231::SquareWaveRate::RATE_8192_kHz:
					return "RATE_8192_kHz";
				default:
					throw exception::HALException("EnumConverter", "enum_to_string",
						"Could not convert SquareWaveRate enum to string. Invalid enum value.");
				}
			}

			//! Converts OutputFormat enums to strings.
			/*!
			* Converts OutputFormat enums to strings.
			* \param[in] value: The enum to convert.
			* \returns The enum value as string.
			* \throws HALException if no case matches the given enum value.
			*/
			static std::string enum_to_string(const sensors::i2c::ds3231::OutputFormat value)
			{
				switch (value)
				{
				case sensors::i2c::ds3231::OutputFormat::FORMATTED_STRING:
					return "FORMATTED_STRING";
				case sensors::i2c::ds3231::OutputFormat::SECONDS_SINCE_EPOCH:
					return "SECONDS_SINCE_EPOCH";
				default:
					throw exception::HALException("EnumConverter", "enum_to_string",
						"Could not convert OutputFormat enum to string. Invalid enum value.");
				}
			}

			//! Converts Timezone enums to strings.
			/*!
			* Converts Timezone enums to strings.
			* \param[in] value: The enum to convert.
			* \returns The enum value as string.
			* \throws HALException if no case matches the given enum value.
			*/
			static std::string enum_to_string(const WorldTimezones value)
			{
				switch (value)
				{
				case WorldTimezones::ALPHA_TIME_ZONE__A__PLUS_H01M00:
					return "ALPHA_TIME_ZONE__A__PLUS_H01M00";
				case WorldTimezones::AUSTRALIAN_CENTRAL_DAYLIGHT_TIME__ACST__PLUS_H09M30:
					return "AUSTRALIAN_CENTRAL_DAYLIGHT_TIME__ACST__PLUS_H09M30";
				case WorldTimezones::ACRE_TIME__ACT__MINUS_H05M00:
					return "ACRE_TIME__ACT__MINUS_H05M00";
				case WorldTimezones::AUSTRALIAN_CENTRAL_STANDARD_TIME__ACST__PLUS_H09M30:
					return "AUSTRALIAN_CENTRAL_STANDARD_TIME__ACST__PLUS_H09M30";
				case WorldTimezones::AUSTRALIAN_CENTRAL_WESTERN_STANDARD_TIME__ACWST__PLUS_H08M45:
					return "AUSTRALIAN_CENTRAL_WESTERN_STANDARD_TIME__ACWST__PLUS_H08M45";
				case WorldTimezones::ATLANTIC_DAYLIGHT_TIME__ADT__MINUS_H03M00:
					return "ATLANTIC_DAYLIGHT_TIME__ADT__MINUS_H03M00";
				case WorldTimezones::AUSTRALIAN_EASTERN_DAYLIGHT_TIME__AEST__PLUS_H10M00:
					return "AUSTRALIAN_EASTERN_DAYLIGHT_TIME__AEST__PLUS_H10M00";
				case WorldTimezones::AUSTRALIAN_EASTERN_STANDARD_TIME__AEST__PLUS_H10M00:
					return "AUSTRALIAN_EASTERN_STANDARD_TIME__AEST__PLUS_H10M00";
				case WorldTimezones::AFGHANISTAN_TIME__AFT__PLUS_H04M30:
					return "AFGHANISTAN_TIME__AFT__PLUS_H04M30";
				case WorldTimezones::ALASKA_STANDARD_TIME__AKST__MINUS_H09M00:
					return "ALASKA_STANDARD_TIME__AKST__MINUS_H09M00";
				case WorldTimezones::ALMA_ATA_TIME__ALMT__PLUS_H06M00:
					return "ALMA_ATA_TIME__ALMT__PLUS_H06M00";
				case WorldTimezones::AMAZON_TIME__AMT__MINUS_H04M00:
					return "AMAZON_TIME__AMT__MINUS_H04M00";
				case WorldTimezones::ARMENIA_TIME__AMT__PLUS_H04M00:
					return "ARMENIA_TIME__AMT__PLUS_H04M00";
				case WorldTimezones::ANADYR_TIME__ANAT__PLUS_H12M00:
					return "ANADYR_TIME__ANAT__PLUS_H12M00";
				case WorldTimezones::AQTOBE_TIME__AQTT__PLUS_H05M00:
					return "AQTOBE_TIME__AQTT__PLUS_H05M00";
				case WorldTimezones::ARGENTINA_TIME__ART__MINUS_H03M00:
					return "ARGENTINA_TIME__ART__MINUS_H03M00";
				case WorldTimezones::ARABIA_STANDARD_TIME__AST__PLUS_H03M00:
					return "ARABIA_STANDARD_TIME__AST__PLUS_H03M00";
				case WorldTimezones::ATLANTIC_STANDARD_TIME__AST__MINUS_H04M00:
					return "ATLANTIC_STANDARD_TIME__AST__MINUS_H04M00";
				case WorldTimezones::ATLANTIC_DAYLIGHT_TIME__AT__MINUS_H04M00:
					return "ATLANTIC_DAYLIGHT_TIME__AT__MINUS_H04M00";
				case WorldTimezones::AUSTRALIAN_WESTERN_STANDARD_TIME__AWST__PLUS_H08M00:
					return "AUSTRALIAN_WESTERN_STANDARD_TIME__AWST__PLUS_H08M00";
				case WorldTimezones::AZORES_TIME__AZOT__MINUS_H01M00:
					return "AZORES_TIME__AZOT__MINUS_H01M00";
				case WorldTimezones::AZERBAIJAN_TIME__AZT__PLUS_H04M00:
					return "AZERBAIJAN_TIME__AZT__PLUS_H04M00";
				case WorldTimezones::ANYWHERE_ON_EARTH__AOE__MINUS_H12M00:
					return "ANYWHERE_ON_EARTH__AOE__MINUS_H12M00";
				case WorldTimezones::BRAVO_TIME_ZONE__B__PLUS_H02M00:
					return "BRAVO_TIME_ZONE__B__PLUS_H02M00";
				case WorldTimezones::BRUNEI_DARUSSALAM_TIME__BNT__PLUS_H08M00:
					return "BRUNEI_DARUSSALAM_TIME__BNT__PLUS_H08M00";
				case WorldTimezones::BOLIVIA_TIME__BOT__MINUS_H04M00:
					return "BOLIVIA_TIME__BOT__MINUS_H04M00";
				case WorldTimezones::BRASILIA_TIME__BRT__MINUS_H03M00:
					return "BRASILIA_TIME__BRT__MINUS_H03M00";
				case WorldTimezones::BANGLADESH_STANDARD_TIME__BST__PLUS_H06M00:
					return "BANGLADESH_STANDARD_TIME__BST__PLUS_H06M00";
				case WorldTimezones::BOUGAINVILLE_STANDARD_TIME__BST__PLUS_H11M00:
					return "BOUGAINVILLE_STANDARD_TIME__BST__PLUS_H11M00";
				case WorldTimezones::BHUTAN_TIME__BTT__PLUS_H06M00:
					return "BHUTAN_TIME__BTT__PLUS_H06M00";
				case WorldTimezones::CHARLIE_TIME_ZONE__C__PLUS_H03M00:
					return "CHARLIE_TIME_ZONE__C__PLUS_H03M00";
				case WorldTimezones::CASEY_TIME__CAST__PLUS_H08M00:
					return "CASEY_TIME__CAST__PLUS_H08M00";
				case WorldTimezones::CENTRAL_AFRICA_TIME__CAT__PLUS_H02M00:
					return "CENTRAL_AFRICA_TIME__CAT__PLUS_H02M00";
				case WorldTimezones::COCOS_ISLANDS_TIME__CCT__PLUS_H06M30:
					return "COCOS_ISLANDS_TIME__CCT__PLUS_H06M30";
				case WorldTimezones::CUBA_STANDARD_TIME__CST__MINUS_H05M00:
					return "CUBA_STANDARD_TIME__CST__MINUS_H05M00";
				case WorldTimezones::CENTRAL_EUROPEAN_STANDARD_TIME__CET__PLUS_H01M00:
					return "CENTRAL_EUROPEAN_STANDARD_TIME__CET__PLUS_H01M00";
				case WorldTimezones::CENTRAL_EUROPEAN_TIME__CET__PLUS_H01M00:
					return "CENTRAL_EUROPEAN_TIME__CET__PLUS_H01M00";
				case WorldTimezones::CHATHAM_ISLAND_STANDARD_TIME__CHAST__PLUS_H12M45:
					return "CHATHAM_ISLAND_STANDARD_TIME__CHAST__PLUS_H12M45";
				case WorldTimezones::CHOIBALSAN_TIME__CHOT__PLUS_H08M00:
					return "CHOIBALSAN_TIME__CHOT__PLUS_H08M00";
				case WorldTimezones::CHUUK_TIME__CHUT__PLUS_H10M00:
					return "CHUUK_TIME__CHUT__PLUS_H10M00";
				case WorldTimezones::COOK_ISLAND_TIME__CKT__MINUS_H10M00:
					return "COOK_ISLAND_TIME__CKT__MINUS_H10M00";
				case WorldTimezones::CHILE_STANDARD_TIME__CLT__MINUS_H04M00:
					return "CHILE_STANDARD_TIME__CLT__MINUS_H04M00";
				case WorldTimezones::COLOMBIA_TIME__COT__MINUS_H05M00:
					return "COLOMBIA_TIME__COT__MINUS_H05M00";
				case WorldTimezones::CENTRAL_STANDARD_TIME__CST__MINUS_H06M00:
					return "CENTRAL_STANDARD_TIME__CST__MINUS_H06M00";
				case WorldTimezones::CHINA_STANDARD_TIME__CST__PLUS_H08M00:
					return "CHINA_STANDARD_TIME__CST__PLUS_H08M00";
				case WorldTimezones::CAPE_VERDE_TIME__CVT__MINUS_H01M00:
					return "CAPE_VERDE_TIME__CVT__MINUS_H01M00";
				case WorldTimezones::CHRISTMAS_ISLAND_TIME__CXT__PLUS_H07M00:
					return "CHRISTMAS_ISLAND_TIME__CXT__PLUS_H07M00";
				case WorldTimezones::CHAMORRO_STANDARD_TIME__CHST__PLUS_H10M00:
					return "CHAMORRO_STANDARD_TIME__CHST__PLUS_H10M00";
				case WorldTimezones::DELTA_TIME_ZONE__D__PLUS_H04M00:
					return "DELTA_TIME_ZONE__D__PLUS_H04M00";
				case WorldTimezones::DAVIS_TIME__DAVT__PLUS_H07M00:
					return "DAVIS_TIME__DAVT__PLUS_H07M00";
				case WorldTimezones::DUMONT_D_URVILLE_TIME__DDUT__PLUS_H10M00:
					return "DUMONT_D_URVILLE_TIME__DDUT__PLUS_H10M00";
				case WorldTimezones::ECHO_TIME_ZONE__E__PLUS_H05M00:
					return "ECHO_TIME_ZONE__E__PLUS_H05M00";
				case WorldTimezones::EASTER_ISLAND_STANDARD_TIME__EAST__MINUS_H06M00:
					return "EASTER_ISLAND_STANDARD_TIME__EAST__MINUS_H06M00";
				case WorldTimezones::EASTERN_AFRICA_TIME__EAT__PLUS_H03M00:
					return "EASTERN_AFRICA_TIME__EAT__PLUS_H03M00";
				case WorldTimezones::ECUADOR_TIME__ECT__MINUS_H05M00:
					return "ECUADOR_TIME__ECT__MINUS_H05M00";
				case WorldTimezones::EASTERN_EUROPEAN_TIME__EET__PLUS_H02M00:
					return "EASTERN_EUROPEAN_TIME__EET__PLUS_H02M00";
				case WorldTimezones::EAST_GREENLAND_TIME__EGT__MINUS_H01M00:
					return "EAST_GREENLAND_TIME__EGT__MINUS_H01M00";
				case WorldTimezones::EASTERN_STANDARD_TIME__EST__MINUS_H05M00:
					return "EASTERN_STANDARD_TIME__EST__MINUS_H05M00";
				case WorldTimezones::EASTERN_DAYLIGHT_TIME__EST__MINUS_H05M00:
					return "EASTERN_DAYLIGHT_TIME__EST__MINUS_H05M00";
				case WorldTimezones::FOXTROT_TIME_ZONE__F__PLUS_H06M00:
					return "FOXTROT_TIME_ZONE__F__PLUS_H06M00";
				case WorldTimezones::FURTHER_EASTERN_EUROPEAN_TIME__FET__PLUS_H03M00:
					return "FURTHER_EASTERN_EUROPEAN_TIME__FET__PLUS_H03M00";
				case WorldTimezones::FIJI_TIME__FJT__PLUS_H12M00:
					return "FIJI_TIME__FJT__PLUS_H12M00";
				case WorldTimezones::FALKLAND_ISLAND_TIME__FKT__MINUS_H04M00:
					return "FALKLAND_ISLAND_TIME__FKT__MINUS_H04M00";
				case WorldTimezones::FERNANDO_DE_NORONHA_TIME__FNT__MINUS_H02M00:
					return "FERNANDO_DE_NORONHA_TIME__FNT__MINUS_H02M00";
				case WorldTimezones::GOLF_TIME_ZONE__G__PLUS_H07M00:
					return "GOLF_TIME_ZONE__G__PLUS_H07M00";
				case WorldTimezones::GALAPAGOS_TIME__GALT__MINUS_H06M00:
					return "GALAPAGOS_TIME__GALT__MINUS_H06M00";
				case WorldTimezones::GAMBIER_TIME__GAMT__MINUS_H09M00:
					return "GAMBIER_TIME__GAMT__MINUS_H09M00";
				case WorldTimezones::GEORGIA_STANDARD_TIME__GET__PLUS_H04M00:
					return "GEORGIA_STANDARD_TIME__GET__PLUS_H04M00";
				case WorldTimezones::FRENCH_GUIANA_TIME__GFT__MINUS_H03M00:
					return "FRENCH_GUIANA_TIME__GFT__MINUS_H03M00";
				case WorldTimezones::GILBERT_ISLAND_TIME__GILT__PLUS_H12M00:
					return "GILBERT_ISLAND_TIME__GILT__PLUS_H12M00";
				case WorldTimezones::GREENWICH_MEAN_TIME__GMT__PLUS_H00M00:
					return "GREENWICH_MEAN_TIME__GMT__PLUS_H00M00";
				case WorldTimezones::GULF_STANDARD_TIME__GST__PLUS_H04M00:
					return "GULF_STANDARD_TIME__GST__PLUS_H04M00";
				case WorldTimezones::SOUTH_GEORGIA_TIME__GST__MINUS_H02M00:
					return "SOUTH_GEORGIA_TIME__GST__MINUS_H02M00";
				case WorldTimezones::GUYANA_TIME__GYT__MINUS_H04M00:
					return "GUYANA_TIME__GYT__MINUS_H04M00";
				case WorldTimezones::HOTEL_TIME_ZONE__H__PLUS_H08M00:
					return "HOTEL_TIME_ZONE__H__PLUS_H08M00";
				case WorldTimezones::HAWAII_ALEUTIAN_DAYLIGHT_TIME__HST__MINUS_H10M00:
					return "HAWAII_ALEUTIAN_DAYLIGHT_TIME__HST__MINUS_H10M00";
				case WorldTimezones::HONG_KONG_TIME__HKT__PLUS_H08M00:
					return "HONG_KONG_TIME__HKT__PLUS_H08M00";
				case WorldTimezones::HOVD_TIME__HOVT__PLUS_H07M00:
					return "HOVD_TIME__HOVT__PLUS_H07M00";
				case WorldTimezones::HAWAII_STANDARD_TIME__HST__MINUS_H10M00:
					return "HAWAII_STANDARD_TIME__HST__MINUS_H10M00";
				case WorldTimezones::INDIA_TIME_ZONE__I__PLUS_H09M00:
					return "INDIA_TIME_ZONE__I__PLUS_H09M00";
				case WorldTimezones::INDOCHINA_TIME__ICT__PLUS_H07M00:
					return "INDOCHINA_TIME__ICT__PLUS_H07M00";
				case WorldTimezones::INDIAN_CHAGOS_TIME__IOT__PLUS_H06M00:
					return "INDIAN_CHAGOS_TIME__IOT__PLUS_H06M00";
				case WorldTimezones::IRKUTSK_TIME__IRKT__PLUS_H08M00:
					return "IRKUTSK_TIME__IRKT__PLUS_H08M00";
				case WorldTimezones::IRAN_STANDARD_TIME__IRST__PLUS_H03M30:
					return "IRAN_STANDARD_TIME__IRST__PLUS_H03M30";
				case WorldTimezones::INDIA_STANDARD_TIME__IST__PLUS_H05M30:
					return "INDIA_STANDARD_TIME__IST__PLUS_H05M30";
				case WorldTimezones::IRISH_STANDARD_TIME__IST__PLUS_H01M00:
					return "IRISH_STANDARD_TIME__IST__PLUS_H01M00";
				case WorldTimezones::ISRAEL_STANDARD_TIME__IST__PLUS_H02M00:
					return "ISRAEL_STANDARD_TIME__IST__PLUS_H02M00";
				case WorldTimezones::JAPAN_STANDARD_TIME__JST__PLUS_H09M00:
					return "JAPAN_STANDARD_TIME__JST__PLUS_H09M00";
				case WorldTimezones::KILO_TIME_ZONE__K__PLUS_H10M00:
					return "KILO_TIME_ZONE__K__PLUS_H10M00";
				case WorldTimezones::KYRGYZSTAN_TIME__KGT__PLUS_H06M00:
					return "KYRGYZSTAN_TIME__KGT__PLUS_H06M00";
				case WorldTimezones::KOSRAE_TIME__KOST__PLUS_H11M00:
					return "KOSRAE_TIME__KOST__PLUS_H11M00";
				case WorldTimezones::KRASNOYARSK_TIME__KRAT__PLUS_H07M00:
					return "KRASNOYARSK_TIME__KRAT__PLUS_H07M00";
				case WorldTimezones::KOREA_STANDARD_TIME__KST__PLUS_H09M00:
					return "KOREA_STANDARD_TIME__KST__PLUS_H09M00";
				case WorldTimezones::KUYBYSHEV_TIME__KUYT__PLUS_H04M00:
					return "KUYBYSHEV_TIME__KUYT__PLUS_H04M00";
				case WorldTimezones::LIMA_TIME_ZONE__L__PLUS_H11M00:
					return "LIMA_TIME_ZONE__L__PLUS_H11M00";
				case WorldTimezones::LORD_HOWE_STANDARD_TIME__LHST__PLUS_H10M30:
					return "LORD_HOWE_STANDARD_TIME__LHST__PLUS_H10M30";
				case WorldTimezones::LINE_ISLANDS_TIME__LINT__PLUS_H14M00:
					return "LINE_ISLANDS_TIME__LINT__PLUS_H14M00";
				case WorldTimezones::MIKE_TIME_ZONE__M__PLUS_H12M00:
					return "MIKE_TIME_ZONE__M__PLUS_H12M00";
				case WorldTimezones::MAGADAN_TIME__MAGT__PLUS_H11M00:
					return "MAGADAN_TIME__MAGT__PLUS_H11M00";
				case WorldTimezones::MARQUESAS_TIME__MART__MINUS_H09M30:
					return "MARQUESAS_TIME__MART__MINUS_H09M30";
				case WorldTimezones::MAWSON_TIME__MAWT__PLUS_H05M00:
					return "MAWSON_TIME__MAWT__PLUS_H05M00";
				case WorldTimezones::MARSHALL_ISLANDS_TIME__MHT__PLUS_H12M00:
					return "MARSHALL_ISLANDS_TIME__MHT__PLUS_H12M00";
				case WorldTimezones::MYANMAR_TIME__MMT__PLUS_H06M30:
					return "MYANMAR_TIME__MMT__PLUS_H06M30";
				case WorldTimezones::MOSCOW_STANDARD_TIME__MSK__PLUS_H03M00:
					return "MOSCOW_STANDARD_TIME__MSK__PLUS_H03M00";
				case WorldTimezones::MOUNTAIN_STANDARD_TIME__MST__MINUS_H07M00:
					return "MOUNTAIN_STANDARD_TIME__MST__MINUS_H07M00";
				case WorldTimezones::MOUNTAIN_DAYLIGHT_TIME__MST__MINUS_H07M00:
					return "MOUNTAIN_DAYLIGHT_TIME__MST__MINUS_H07M00";
				case WorldTimezones::MAURITIUS_TIME__MUT__PLUS_H04M00:
					return "MAURITIUS_TIME__MUT__PLUS_H04M00";
				case WorldTimezones::MALDIVES_TIME__MVT__PLUS_H05M00:
					return "MALDIVES_TIME__MVT__PLUS_H05M00";
				case WorldTimezones::MALAYSIA_TIME__MYT__PLUS_H08M00:
					return "MALAYSIA_TIME__MYT__PLUS_H08M00";
				case WorldTimezones::NOVEMBER_TIME_ZONE__N__MINUS_H01M00:
					return "NOVEMBER_TIME_ZONE__N__MINUS_H01M00";
				case WorldTimezones::NEW_CALEDONIA_TIME__NCT__PLUS_H11M00:
					return "NEW_CALEDONIA_TIME__NCT__PLUS_H11M00";
				case WorldTimezones::NEWFOUNDLAND_STANDARD_TIME__NDT__MINUS_H03M30:
					return "NEWFOUNDLAND_STANDARD_TIME__NDT__MINUS_H03M30";
				case WorldTimezones::NOVOSIBIRSK_TIME__NOVT__PLUS_H07M00:
					return "NOVOSIBIRSK_TIME__NOVT__PLUS_H07M00";
				case WorldTimezones::NEPAL_TIME___NPT__PLUS_H05M45:
					return "NEPAL_TIME___NPT__PLUS_H05M45";
				case WorldTimezones::NAURU_TIME__NRT__PLUS_H12M00:
					return "NAURU_TIME__NRT__PLUS_H12M00";
				case WorldTimezones::NEWFOUNDLAND_STANDARD_TIME__NST__MINUS_H03M30:
					return "NEWFOUNDLAND_STANDARD_TIME__NST__MINUS_H03M30";
				case WorldTimezones::NIUE_TIME__NUT__MINUS_H11M00:
					return "NIUE_TIME__NUT__MINUS_H11M00";
				case WorldTimezones::NEW_ZEALAND_STANDARD_TIME__NZST__PLUS_H12M00:
					return "NEW_ZEALAND_STANDARD_TIME__NZST__PLUS_H12M00";
				case WorldTimezones::OSCAR_TIME_ZONE__O__MINUS_H02M00:
					return "OSCAR_TIME_ZONE__O__MINUS_H02M00";
				case WorldTimezones::OMSK_STANDARD_TIME__OMST__PLUS_H06M00:
					return "OMSK_STANDARD_TIME__OMST__PLUS_H06M00";
				case WorldTimezones::ORAL_TIME__ORAT__PLUS_H05M00:
					return "ORAL_TIME__ORAT__PLUS_H05M00";
				case WorldTimezones::PAPA_TIME_ZONE__P__MINUS_H03M00:
					return "PAPA_TIME_ZONE__P__MINUS_H03M00";
				case WorldTimezones::PERU_TIME__PET__MINUS_H05M00:
					return "PERU_TIME__PET__MINUS_H05M00";
				case WorldTimezones::KAMCHATKA_TIME__PETT__PLUS_H12M00:
					return "KAMCHATKA_TIME__PETT__PLUS_H12M00";
				case WorldTimezones::PAPUA_NEW_GUINEA_TIME__PGT__PLUS_H10M00:
					return "PAPUA_NEW_GUINEA_TIME__PGT__PLUS_H10M00";
				case WorldTimezones::PHOENIX_ISLAND_TIME__PHOT__PLUS_H13M00:
					return "PHOENIX_ISLAND_TIME__PHOT__PLUS_H13M00";
				case WorldTimezones::PHILIPPINE_TIME__PHT__PLUS_H08M00:
					return "PHILIPPINE_TIME__PHT__PLUS_H08M00";
				case WorldTimezones::PAKISTAN_STANDARD_TIME__PKT__PLUS_H05M00:
					return "PAKISTAN_STANDARD_TIME__PKT__PLUS_H05M00";
				case WorldTimezones::PIERRE_MIQUELON_DAYLIGHT_TIME__PMDT__MINUS_H02M00:
					return "PIERRE_MIQUELON_DAYLIGHT_TIME__PMDT__MINUS_H02M00";
				case WorldTimezones::PIERRE_MIQUELON_STANDARD_TIME__PMST__MINUS_H03M00:
					return "PIERRE_MIQUELON_STANDARD_TIME__PMST__MINUS_H03M00";
				case WorldTimezones::POHNPEI_STANDARD_TIME__PONT__PLUS_H11M00:
					return "POHNPEI_STANDARD_TIME__PONT__PLUS_H11M00";
				case WorldTimezones::PACIFIC_STANDARD_TIME__PST__MINUS_H08M00:
					return "PACIFIC_STANDARD_TIME__PST__MINUS_H08M00";
				case WorldTimezones::PITCAIRN_STANDARD_TIME__PST__MINUS_H08M00:
					return "PITCAIRN_STANDARD_TIME__PST__MINUS_H08M00";
				case WorldTimezones::PALAU_TIME__PWT__PLUS_H09M00:
					return "PALAU_TIME__PWT__PLUS_H09M00";
				case WorldTimezones::PARAGUAY_TIME__PYT__MINUS_H04M00:
					return "PARAGUAY_TIME__PYT__MINUS_H04M00";
				case WorldTimezones::PYONGYANG_TIME__PYT__PLUS_H08M30:
					return "PYONGYANG_TIME__PYT__PLUS_H08M30";
				case WorldTimezones::QUEBEC_TIME_ZONE__Q__MINUS_H04M00:
					return "QUEBEC_TIME_ZONE__Q__MINUS_H04M00";
				case WorldTimezones::QYZYLORDA_TIME__QYZT__PLUS_H06M00:
					return "QYZYLORDA_TIME__QYZT__PLUS_H06M00";
				case WorldTimezones::ROMEO_TIME_ZONE__R__MINUS_H05M00:
					return "ROMEO_TIME_ZONE__R__MINUS_H05M00";
				case WorldTimezones::REUNION_TIME__RET__PLUS_H04M00:
					return "REUNION_TIME__RET__PLUS_H04M00";
				case WorldTimezones::ROTHERA_TIME__ROTT__MINUS_H03M00:
					return "ROTHERA_TIME__ROTT__MINUS_H03M00";
				case WorldTimezones::SIERRA_TIME_ZONE__S__MINUS_H06M00:
					return "SIERRA_TIME_ZONE__S__MINUS_H06M00";
				case WorldTimezones::SAKHALIN_TIME__SAKT__PLUS_H11M00:
					return "SAKHALIN_TIME__SAKT__PLUS_H11M00";
				case WorldTimezones::SAMARA_TIME__SAMT__PLUS_H04M00:
					return "SAMARA_TIME__SAMT__PLUS_H04M00";
				case WorldTimezones::SOUTH_AFRICA_STANDARD_TIME__SAST__PLUS_H02M00:
					return "SOUTH_AFRICA_STANDARD_TIME__SAST__PLUS_H02M00";
				case WorldTimezones::SOLOMON_ISLANDS_TIME__SBT__PLUS_H11M00:
					return "SOLOMON_ISLANDS_TIME__SBT__PLUS_H11M00";
				case WorldTimezones::SEYCHELLES_TIME__SCT__PLUS_H04M00:
					return "SEYCHELLES_TIME__SCT__PLUS_H04M00";
				case WorldTimezones::SINGAPORE_TIME__SGT__PLUS_H08M00:
					return "SINGAPORE_TIME__SGT__PLUS_H08M00";
				case WorldTimezones::SREDNEKOLYMSK_TIME__SRET__PLUS_H11M00:
					return "SREDNEKOLYMSK_TIME__SRET__PLUS_H11M00";
				case WorldTimezones::SURINAME_TIME__SRT__MINUS_H03M00:
					return "SURINAME_TIME__SRT__MINUS_H03M00";
				case WorldTimezones::SAMOA_STANDARD_TIME__SST__MINUS_H11M00:
					return "SAMOA_STANDARD_TIME__SST__MINUS_H11M00";
				case WorldTimezones::SYOWA_TIME__SYOT__PLUS_H03M00:
					return "SYOWA_TIME__SYOT__PLUS_H03M00";
				case WorldTimezones::TANGO_TIME_ZONE__T__MINUS_H07M00:
					return "TANGO_TIME_ZONE__T__MINUS_H07M00";
				case WorldTimezones::TAHITI_TIME__TAHT__MINUS_H10M00:
					return "TAHITI_TIME__TAHT__MINUS_H10M00";
				case WorldTimezones::FRENCH_SOUTHERN_AND_ANTARCTIC_TIME__TFT__PLUS_H05M00:
					return "FRENCH_SOUTHERN_AND_ANTARCTIC_TIME__TFT__PLUS_H05M00";
				case WorldTimezones::TAJIKISTAN_TIME__TJT__PLUS_H05M00:
					return "TAJIKISTAN_TIME__TJT__PLUS_H05M00";
				case WorldTimezones::TOKELAU_TIME__TKT__PLUS_H13M00:
					return "TOKELAU_TIME__TKT__PLUS_H13M00";
				case WorldTimezones::EAST_TIMOR_TIME__TLT__PLUS_H09M00:
					return "EAST_TIMOR_TIME__TLT__PLUS_H09M00";
				case WorldTimezones::TURKMENISTAN_TIME__TMT__PLUS_H05M00:
					return "TURKMENISTAN_TIME__TMT__PLUS_H05M00";
				case WorldTimezones::TONGA_TIME__TOT__PLUS_H13M00:
					return "TONGA_TIME__TOT__PLUS_H13M00";
				case WorldTimezones::TURKEY_TIME__TRT__PLUS_H03M00:
					return "TURKEY_TIME__TRT__PLUS_H03M00";
				case WorldTimezones::TUVALU_TIME__TVT__PLUS_H12M00:
					return "TUVALU_TIME__TVT__PLUS_H12M00";
				case WorldTimezones::UNIFORM_TIME_ZONE__U__MINUS_H08M00:
					return "UNIFORM_TIME_ZONE__U__MINUS_H08M00";
				case WorldTimezones::ULAANBAATAR_TIME__ULAT__PLUS_H08M00:
					return "ULAANBAATAR_TIME__ULAT__PLUS_H08M00";
				case WorldTimezones::COORDINATED_UNIVERSAL_TIME__UTC__PLUS_H00M00:
					return "COORDINATED_UNIVERSAL_TIME__UTC__PLUS_H00M00";
				case WorldTimezones::URUGUAY_TIME__UYT__MINUS_H03M00:
					return "URUGUAY_TIME__UYT__MINUS_H03M00";
				case WorldTimezones::UZBEKISTAN_TIME__UZT__PLUS_H05M00:
					return "UZBEKISTAN_TIME__UZT__PLUS_H05M00";
				case WorldTimezones::VICTOR_TIME_ZONE__V__MINUS_H09M00:
					return "VICTOR_TIME_ZONE__V__MINUS_H09M00";
				case WorldTimezones::VENEZUELAN_STANDARD_TIME__VET__MINUS_H04M00:
					return "VENEZUELAN_STANDARD_TIME__VET__MINUS_H04M00";
				case WorldTimezones::VLADIVOSTOK_TIME__VLAT__PLUS_H10M00:
					return "VLADIVOSTOK_TIME__VLAT__PLUS_H10M00";
				case WorldTimezones::VOSTOK_TIME__VOST__PLUS_H06M00:
					return "VOSTOK_TIME__VOST__PLUS_H06M00";
				case WorldTimezones::VANUATU_TIME__VUT__PLUS_H11M00:
					return "VANUATU_TIME__VUT__PLUS_H11M00";
				case WorldTimezones::WHISKEY_TIME_ZONE__W__MINUS_H10M00:
					return "WHISKEY_TIME_ZONE__W__MINUS_H10M00";
				case WorldTimezones::WAKE_TIME__WAKT__PLUS_H12M00:
					return "WAKE_TIME__WAKT__PLUS_H12M00";
				case WorldTimezones::WEST_AFRICA_TIME__WAT__PLUS_H01M00:
					return "WEST_AFRICA_TIME__WAT__PLUS_H01M00";
				case WorldTimezones::WESTERN_EUROPEAN_TIME__WET__PLUS_H00M00:
					return "WESTERN_EUROPEAN_TIME__WET__PLUS_H00M00";
				case WorldTimezones::WALLIS_AND_FUTUNA_TIME__WFT__PLUS_H12M00:
					return "WALLIS_AND_FUTUNA_TIME__WFT__PLUS_H12M00";
				case WorldTimezones::WEST_GREENLAND_TIME__WGT__MINUS_H03M00:
					return "WEST_GREENLAND_TIME__WGT__MINUS_H03M00";
				case WorldTimezones::WESTERN_INDONESIAN_TIME__WIB__PLUS_H07M00:
					return "WESTERN_INDONESIAN_TIME__WIB__PLUS_H07M00";
				case WorldTimezones::EASTERN_INDONESIAN_TIME__WIT__PLUS_H09M00:
					return "EASTERN_INDONESIAN_TIME__WIT__PLUS_H09M00";
				case WorldTimezones::CENTRAL_INDONESIAN_TIME__WITA__PLUS_H08M00:
					return "CENTRAL_INDONESIAN_TIME__WITA__PLUS_H08M00";
				case WorldTimezones::WEST_SAMOA_TIME__WST__PLUS_H14M00:
					return "WEST_SAMOA_TIME__WST__PLUS_H14M00";
				case WorldTimezones::WESTERN_SAHARA_STANDARD_TIME__WT__PLUS_H00M00:
					return "WESTERN_SAHARA_STANDARD_TIME__WT__PLUS_H00M00";
				case WorldTimezones::X_RAY_TIME_ZONE__X__MINUS_H11M00:
					return "X_RAY_TIME_ZONE__X__MINUS_H11M00";
				case WorldTimezones::YANKEE_TIME_ZONE__Y__MINUS_H12M00:
					return "YANKEE_TIME_ZONE__Y__MINUS_H12M00";
				case WorldTimezones::YAKUTSK_TIME__YAKT__PLUS_H09M00:
					return "YAKUTSK_TIME__YAKT__PLUS_H09M00";
				case WorldTimezones::YAP_TIME__YAPT__PLUS_H10M00:
					return "YAP_TIME__YAPT__PLUS_H10M00";
				case WorldTimezones::YEKATERINBURG_TIME__YEKT__PLUS_H05M00:
					return "YEKATERINBURG_TIME__YEKT__PLUS_H05M00";
				case WorldTimezones::ZULU_TIME_ZONE__Z__PLUS_H00M00:
					return "ZULU_TIME_ZONE__Z__PLUS_H00M00";
				default:
					throw exception::HALException("EnumConverter", "enum_to_string", "Could not convert Timezone enum to string. Invalid enum value.");
				}
			}

		};
	}
}
