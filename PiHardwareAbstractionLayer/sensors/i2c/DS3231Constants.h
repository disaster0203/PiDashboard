#pragma once

namespace hal
{
	namespace sensors
	{
		namespace i2c
		{
			namespace ds3231
			{
				// General
				static constexpr uint8_t SENSOR_PRIMARY_I2C_REG = 0x68;


				// Register addresses
				static constexpr uint8_t SECONDS_REGISTER = 0x00;
				static constexpr uint8_t MINUTES_REGISTER = 0x01;
				static constexpr uint8_t HOURS_REGISTER = 0x02;
				static constexpr uint8_t DAY_REGISTER = 0x03;
				static constexpr uint8_t DATE_REGISTER = 0x04;
				static constexpr uint8_t MONTH_REGISTER = 0x05;
				static constexpr uint8_t YEAR_REGISTER = 0x06;
				static constexpr uint8_t ALARM_1_SECONDS_REGISTER = 0x07;
				static constexpr uint8_t ALARM_1_MINUTES_REGISTER = 0x08;
				static constexpr uint8_t ALARM_1_HOURS_REGISTER = 0x09;
				static constexpr uint8_t ALARM_1_DAY_AND_DATE_REGISTER = 0x0A;
				static constexpr uint8_t ALARM_2_MINUTES_REGISTER = 0x0B;
				static constexpr uint8_t ALARM_2_HOURS_REGISTER = 0x0C;
				static constexpr uint8_t ALARM_2_DAY_AND_DATE_REGISTER = 0x0D;
				static constexpr uint8_t CONTROL_REGISTER = 0x0E;
				static constexpr uint8_t STATUS_REGISTER = 0x0F;
				static constexpr uint8_t AGING_OFFSET_REGISTER = 0x10;
				static constexpr uint8_t TEMPERATURE_MSB_REGISTER = 0x11;
				static constexpr uint8_t TEMPERATURE_LSB_REGISTER = 0x12;
				
				// Indices and ranges
				static constexpr uint8_t SQUARE_WAVE_RATE_MASK = 0x18;
				static constexpr uint8_t FIRST_DECIMAL_BEGIN = 0;
				static constexpr uint8_t FIRST_DECIMAL_END = 3;
				static constexpr uint8_t SECOND_DECIMAL_BEGIN = 4;
				static constexpr uint8_t SECOND_DECIMAL_END_1 = 6;
				static constexpr uint8_t SECOND_DECIMAL_END_2 = 5;
				static constexpr uint8_t SECOND_DECIMAL_END_3 = 7;
				static constexpr uint8_t TEMPERATURE_DECIMAL_BEGIN = 0;
				static constexpr uint8_t TEMPERATURE_DECIMAL_END = 6;
				static constexpr uint8_t TEMPERATURE_FRACTION_BEGIN = 6;
				static constexpr uint8_t TEMPERATURE_FRACTION_END = 7;
				static constexpr uint8_t HOUR_FORMAT_INDEX = 6;
				static constexpr uint8_t HOUR_20_DECIMAL_INDEX = 5;
				static constexpr uint8_t HOUR_10_DECIMAL_INDEX = 4;
				static constexpr uint8_t AM_PM_INDEX = 5;
				static constexpr uint8_t CENTURY_INDEX = 7;
				static constexpr uint8_t ALARM_MASK_INDEX = 7;
				static constexpr uint8_t SIGN_INDEX = 7;
				static constexpr uint8_t DAY_DATE_INDEX = 6;
				static constexpr uint8_t EOSC_INDEX = 7;
				static constexpr uint8_t BBSQW_INDEX = 6;
				static constexpr uint8_t CONV_INDEX = 5;
				static constexpr uint8_t RS2_INDEX = 4;
				static constexpr uint8_t RS1_INDEX = 3;
				static constexpr uint8_t INTCN_INDEX = 2;
				static constexpr uint8_t A2IE_INDEX = 1;
				static constexpr uint8_t A1IE_INDEX = 0;
				static constexpr uint8_t OSF_INDEX = 7;
				static constexpr uint8_t EN32KHZ_INDEX = 3;
				static constexpr uint8_t BSY_INDEX = 2;
				static constexpr uint8_t A2F_INDEX = 1;
				static constexpr uint8_t A1F_INDEX = 0;
			}
		}
	}
}