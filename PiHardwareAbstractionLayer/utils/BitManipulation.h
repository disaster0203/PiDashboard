#pragma once

#include <cstdint>
#include <iostream>
#include "../exceptions/HALException.h"

namespace hal
{
	namespace utils
	{
		class BitManipulation
		{
		public:
			//! Checks if the bit at the given position in the byte is set (1) or not (0).
			/*!
			*  Checks if the bit at the given position in the byte is set (1) or not (0).
			*  The first bit is the right most number in the byte array and has the index 0.
			* \param[in] byte: The byte value.
			* \param[in] bit_index: The position of the bit inside the byte array.
			* \returns True if the bit is set (1) and false if the bit is not set (0).
			* \throws HALException if bit_index is out of bounds.
			*/
			static bool is_bit_set(const uint8_t byte, const uint8_t bit_index)
			{
				if (bit_index < 0 || bit_index > 7)
				{
					throw exception::HALException("BitManipulation", "is_bit_set",
															std::string("The given bit index (").append(std::to_string(bit_index)).append(
																") is out of bounds."));
				}
				return (byte & (1 << bit_index)) != 0;
			}

			//! Sets the bit at the given index to the given value.
			/*!
			*  Sets the bit at the given index to the given value.
			*  The first bit is the right most number in the byte array and has the index 0.
			* \param[in] byte: The byte to manipulate.
			* \param[in] bit_index: The position of the bit inside the byte array.
			* \param[in] new_value: True for new value 1 and false for new value 0.
			* \throws HALException if bit_index is out of bounds.
			*/
			static void set_bit(uint8_t& byte, const uint8_t bit_index, const bool new_value)
			{
				if (bit_index < 0 || bit_index > 7)
				{
					throw exception::HALException("BitManipulation", "set_bit",
															std::string("The given bit index (").append(std::to_string(bit_index)).append(
																") is out of bounds."));
				}
				if (new_value)
				{
					byte |= static_cast<uint8_t>(1 << bit_index);
				}

				byte |= static_cast<uint8_t>(0 << bit_index);
			}

			//! Sets the bit at the given index to the given value.
			/*!
			*  Sets the bit at the given index to the given value.
			*  The first bit is the right most number in the byte array and has the index 0.
			* \param[out] byte: The byte value.
			* \param[in] value: The value to place at the position the mask defines
			* \param[in] mask: Defines the position where the new value should be placed inside the byte (1s for bits to affect, 0s for bits to ignore.
			*  E.g. 01110000 only changes bits 6,5,4 and tries to place the value at these bits).
			* \throws HALException if the mask has less bits than the value to write to the byte.
			*/
			static void set_bits(uint8_t& byte, uint8_t value, const uint8_t mask)
			{
				if (count_active_bits(value) > count_active_bits(mask))
				{
					throw exception::HALException("BitManipulation", "set_bits",
															std::string(
																"The given mask has less bits set than the value. This would result in unintentional bit changes."));
				}

				const auto index = static_cast<int8_t>(index_of_highest_active_bit(mask) - index_of_highest_active_bit(value));
				value = static_cast<uint8_t>(value << index);

				// Turn off currently set bits at mask position and afterwards set the desired bits.
				byte = static_cast<uint8_t>((byte & ~mask) | value);
			}

			//! Returns the index of the highest active bit.
			/*!
			*  Returns the index of the highest active bit.
			* \param[in] byte: The byte value.
			* \returns The index of the highest active bit.
			*/
			static int8_t index_of_highest_active_bit(const uint8_t byte) noexcept
			{
				int8_t index = 0;
				while (static_cast<uint8_t>(byte >> index) != 0)
				{
					index++;
				}

				return static_cast<int8_t>(index - 1);
			}

			//! Counts the bits in a byte that are set to 1.
			/*!
			*  Counts the bits in a byte that are set to 1.
			* \param[in] byte: The byte value.
			* \returns The number of bits that are set to 1.
			*/
			static uint8_t count_active_bits(uint8_t byte) noexcept
			{
				byte = static_cast<uint8_t>(byte - static_cast<uint8_t>(byte >> static_cast<uint8_t>(1) & static_cast<uint8_t>(0x55)));
				byte = static_cast<uint8_t>((byte & static_cast<uint8_t>(0x33)) + static_cast<uint8_t>(byte >> 2 & static_cast<uint8_t>(0x33)));
				return ((byte + (byte >> static_cast<uint8_t>(4))) & static_cast<uint8_t>(0x0F)) * static_cast<uint8_t>(0x01);
			}

			//! Returns the value of the selected bit range from a given byte array as unsigned char.
			/*!
			* Returns the value of the selected bit range from a given byte array as unsigned char.
			* Since start and end are indices, counting starts from 0 and the maximum value is 7.
			* start_bit and end_bit are both included in the range: [start_bit, end_bit]
			* \param[in] byte: The byte value.
			* \param[in] start_bit: The start position of the bit range (inclusive). Range=[0,6] and must be less than end_bit.
			* \param[in] end_bit: The end position of the bit range (inclusive). Range=[1,7] and must be greater than start_bit.
			* \returns The value of the bit range as unsigned char.
			* \throws HALException if start_bit is out of bounds.
			* \throws HALException if end_bit is out of bounds.
			* \throws HALException if start_bit is greater or equal end_bit.
			*/
			static uint8_t value_of_bits(const uint8_t byte, const uint8_t start_bit, const uint8_t end_bit)
			{
				if (start_bit < 0 || start_bit > 7)
				{
					throw exception::HALException("BitManipulation", "value_of_bits",
															std::string("The given start bit index (").append(std::to_string(start_bit)).append(
																") is out of bounds."));
				}

				if (end_bit < 0 || end_bit > 7)
				{
					throw exception::HALException("BitManipulation", "value_of_bits",
															std::string("The given end bit index (").append(std::to_string(end_bit)).append(
																") is out of bounds."));
				}

				if (start_bit >= end_bit)
				{
					throw exception::HALException("BitManipulation", "value_of_bits",
															std::string("Start index (").append(std::to_string(start_bit)).append(
																									") is greater or equal End Index (")
																								.append(std::to_string(end_bit)).append(")."));
				}

				uint8_t mask = 0;
				for (auto i = start_bit; i <= end_bit; ++i)
				{
					mask |= static_cast<uint8_t>(1 << i);
				}

				return static_cast<uint8_t>((mask & byte) >> start_bit);
			}

			//! Performs a left shift operation on a given byte.
			/*!
			* Performs a left shift operation on a given byte by adding n zeros on the right.
			* \param[in] byte: The byte value.
			* \param[in] n: The number of places to shift.
			* \param[in] T: The output type (char, short, int, long, ...).
			* \returns The left shifted byte.
			*/
			template <typename T>
			static T multiply_by_2_power_n(const uint8_t byte, const uint8_t n, T type) noexcept
			{
				return static_cast<T>(byte << n);
			}

			//! Performs a right shift operation on a given byte.
			/*!
			* Performs a right shift operation on a given byte by removing n digits on the right.
			* \param[in] byte: The byte value.
			* \param[in] n: The number of places to shift.
			* \param[in] T: The output type (char, short, int, long, ...).
			* \returns The right shifted byte.
			*/
			template <typename T>
			static T divide_by_2_power_n(const uint8_t byte, const uint8_t n, T type) noexcept
			{
				return static_cast<T>(byte >> n);
			}

			//! Masks out a certain part of a byte.
			/*!
			* Masks out a certain part of a byte by using the bitwise AND (&) operator.
			* \param[in] byte: The byte value.
			* \param[in] mask: Defines the position of the part to mask out.
			* \returns The masked out byte.
			*/
			static uint8_t mask_out(const uint8_t byte, const uint8_t mask) noexcept
			{
				return static_cast<uint8_t>(byte & mask);
			}

			//! Combines two bytes to one byte.
			/*!
			* Combines two bytes to one byte by using the bitwise OR (|) operator.
			* \param[in] byte1: The first byte value.
			* \param[in] byte2: The second byte value.
			* \returns The combined value.
			*/
			template <typename T>
			static T combine(const T byte1, const T byte2) noexcept
			{
				return byte1 | byte2;
			}

			//! Combines two 8 bit values to one 16 bit value.
			/*!
			*  Combines two 8 bit values to one 16 bit value.
			* \param[in] high_byte: The first byte value. Represents the high part of the resulting 16 bit value.
			* \param[in] low_byte: The second byte value. Represents the low part of the resulting 16 bit value.
			* \returns The value of the combined bytes as 16 bit value.
			*/
			static uint16_t combine_bytes(const uint8_t high_byte, const uint8_t low_byte) noexcept
			{
				return static_cast<uint16_t>((high_byte << 8) | low_byte);
			}

			//! Combines two 8 bit values to one 16 bit value.
			/*!
			*  Combines two 8 bit values to one 16 bit value.
			* \param[in] value: The 16 bit value to split.
			* \param[out] high_byte: The first byte value. Represents the high part of the resulting 16 bit value.
			* \param[out] low_byte: The second byte value. Represents the low part of the resulting 16 bit value.
			*/
			static void split_bytes(const uint16_t value, uint8_t& high_byte, uint8_t& low_byte) noexcept
			{
				high_byte = static_cast<uint8_t>(value & 0xFF);
				low_byte = static_cast<uint8_t>(value >> 8);
			}
		};
	}
}
