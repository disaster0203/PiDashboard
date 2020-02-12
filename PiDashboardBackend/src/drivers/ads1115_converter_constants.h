#pragma once

namespace driver
{
	namespace sensors
	{
		namespace ads1115
		{
			// I2C device addresses
			static constexpr const uint8_t CONVERTER_ADDR_IS_GND_I2C_REG = 0X48;
			static constexpr const uint8_t CONVERTER_ADDR_IS_VDD_I2C_REG = 0X49;
			static constexpr const uint8_t CONVERTER_ADDR_IS_SDA_I2C_REG = 0X4A;
			static constexpr const uint8_t CONVERTER_ADDR_IS_SCL_I2C_REG = 0X4B;

			// Reset
			static constexpr const uint8_t RESET_REG = 0X00;
			static constexpr const uint8_t RESET_CMD = 0X06;

			// Register addresses
			static constexpr const uint8_t CONVERSION_REG = 0X00;
			static constexpr const uint8_t CONFIG_REG = 0X01;
			static constexpr const uint8_t LOW_THRESHOLD_REG = 0X02;
			static constexpr const uint8_t HIGH_THRESHOLD_REG = 0X03;

			// Read length
			static constexpr const uint8_t REG_READ_LEN = 2;

			// Bit indices
			static constexpr const uint8_t STATUS_BIT = 7;
			static constexpr const uint8_t MULTIPLEXER_BIT_3 = 6;
			static constexpr const uint8_t MULTIPLEXER_BIT_1 = 4;
			static constexpr const uint8_t GAIN_AMPLIFIER_BIT_3 = 3;
			static constexpr const uint8_t GAIN_AMPLIFIER_BIT_1 = 1;
			static constexpr const uint8_t OPERATION_MODE_BIT = 0;

			static constexpr const uint8_t DATA_RATE_BIT_3 = 7;
			static constexpr const uint8_t DATA_RATE_BIT_1 = 5;
			static constexpr const uint8_t COMPARATOR_MODE_BIT = 4;
			static constexpr const uint8_t COMPARATOR_POL_BIT = 3;
			static constexpr const uint8_t COMPARATOR_LAT_BIT = 2;
			static constexpr const uint8_t COMPARATOR_QUEUE_BIT_2 = 1;
			static constexpr const uint8_t COMPARATOR_QUEUE_BIT_1 = 0;

			// Bit masks
			static constexpr const uint8_t MULTIPLEXER_MASK = 0x70;
			static constexpr const uint8_t GAIN_AMPLIFIER_MASK = 0x0E;
			static constexpr const uint8_t OPERATION_MODE_MASK = 0x01;
			static constexpr const uint8_t DATA_RATE_MASK = 0xE0;
			static constexpr const uint8_t COMPARATOR_MODE_MASK = 0x10;
			static constexpr const uint8_t COMPARATOR_POLARITY_MASK = 0x08;
			static constexpr const uint8_t COMPARATOR_LATCHING_MASK = 0x04;
			static constexpr const uint8_t COMPARATOR_QUEUEING_MASK = 0x03;

			// Default values
			static constexpr const uint8_t DEFAULT_SETTINGS_BYTE_1 = 0x85;
			static constexpr const uint8_t DEFAULT_SETTINGS_BYTE_2 = 0x83;
			static constexpr const uint8_t DEFAULT_LOW_THRES_BYTE_1 = 0x80;
			static constexpr const uint8_t DEFAULT_LOW_THRES_BYTE_2 = 0x00;
			static constexpr const uint8_t DEFAULT_HIGH_THRES_BYTE_1 = 0x7F;
			static constexpr const uint8_t DEFAULT_HIGH_THRES_BYTE_2 = 0xFF;
		}
	}
}