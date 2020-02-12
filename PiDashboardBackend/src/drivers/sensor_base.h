#pragma once
#include <cstdint>
#include <iostream>
#include <functional>
#include <memory>
#include <bitset>

namespace driver
{
	namespace sensors
	{
		static constexpr const int8_t WARNING = 1;
		static constexpr const int8_t OK = 0;
		static constexpr const int8_t NULL_PTR = -1;
		static constexpr const int8_t DEVICE_NOT_FOUND = -2;
		static constexpr const int8_t INVALID_LENGTH = -3;
		static constexpr const int8_t COMMUNICATION_FAIL = -4;
		static constexpr const int8_t DEVICE_ERROR = -5;
		static constexpr const int8_t BIT_MANIPULATION_ERROR = -6;

		class sensor_base
		{
		public:
			//! Opens a device connection and performs basic setup.
			/*!
			* Tries to open the device at the given i2c address in O_RDWR and I2C_SLAVE mode.
			* It also reads and stores the device id.
			* \param[in] device_reg: The address of the device to open.
			* \param[in] read_function: Function pointer to the function that does i2c read operations.
			* \param[in] write_function: Function pointer to the function that does i2c write operations.
			* \param[in] open_device_function: Function pointer to the function that opens an i2c connection.
			* \param[in] close_device_function: Function pointer to the function that closes an i2c connection.
			* \returns 0 if initializing the device was successful, a negative error value otherwise.
			*/
			virtual int8_t init(uint8_t device_reg,
				std::function<int8_t(int, uint8_t, uint8_t*, uint16_t)> read_function,
				std::function<int8_t(int, uint8_t, const uint8_t*, uint16_t)> write_function,
				std::function<int8_t(const std::string, uint8_t, int&)> open_device_function,
				std::function<int8_t(int&)> close_device_function) = 0;

			//! Closes a device connection and performs some cleanup.
			/*!
			*  Closes a device connection and performs some cleanup.
			* \returns 0 if closing the device was successful, a negative error value otherwise.
			*/
			virtual int8_t close() = 0;

			//! Performs a soft reset on the device.
			/*!
			* Performs a soft reset on the device.
			* \returns 0 if resetting the device was successful, a negative error value otherwise.
			*/
			virtual int8_t soft_reset() = 0;

		protected:
			//! Checks if the bit at the given position in the byte is set (1) or not (0).
			/*!
			*  Checks if the bit at the given position in the byte is set (1) or not (0).
			*  The first bit is the right most number in the byte array and has the index 0.
			* \param[in] byte: The byte value.
			* \param[in] bit_index: The position of the bit inside the byte array.
			* \returns True if the bit is set (1) and false if the bit is not set (0).
			*/
			bool is_bit_set(uint8_t byte, uint8_t bit_index)
			{
				if (bit_index < 0 || bit_index > 7)
				{
					std::cerr << "SensorBase [is_bit_set] Error: The given bit index (" << bit_index << ") is out of Bounds." << std::endl;
					return false;
				}
				return (byte & (1 << bit_index)) != 0;
			}

			//! Sets the bit at the given index to the given value.
			/*!
			*  Sets the bit at the given index to the given value.
			*  The first bit is the right most number in the byte array and has the index 0.
			* \param[out] byte: The byte value.
			* \param[in] bit_index: The position of the bit inside the byte array.
			* \param[in] new_value: True for new value 1 and false for new value 0.
			* \returns True if modifying the bit was successful, false otherwise.
			*/
			bool set_bit(uint8_t& byte, uint8_t bit_index, bool new_value)
			{
				if (bit_index < 0 || bit_index > 7)
				{
					std::cerr << "SensorBase [set_bit] Error: The given bit index (" << bit_index << ") is out of Bounds." << std::endl;
					return false;
				}
				if (new_value)
				{
					byte |= (uint8_t)(1 << bit_index);
				}
				else
				{
					byte |= (uint8_t)(0 << bit_index);
				}
				return true;
			}

			//! Sets the bit at the given index to the given value.
			/*!
			*  Sets the bit at the given index to the given value.
			*  The first bit is the right most number in the byte array and has the index 0.
			* \param[out] byte: The byte value.
			* \param[in] value: The value to place at the position the mask defines
			* \param[in] mask: Defines the position where the new value should be placed inside the byte (1s for bits to affect, 0s for bits to ignore. 
			*  E.g. 01110000 only changes bits 6,5,4 and tries to place the value at these bits).
			* \returns True if modifying the bits was successful, false otherwise.
			*/
			bool set_bits(uint8_t& byte, uint8_t value, uint8_t mask)
			{
				if (count_active_bits(value) > count_active_bits(mask))
				{
					std::cerr << "SensorBase [set_bits] Error: The given mask has less bits set than the value. This would result in unintentional bit changes." << std::endl;
					return false;
				}

				int8_t index = (int8_t)(index_of_highest_active_bit(mask) - index_of_highest_active_bit(value));
				value = (uint8_t)(value << index);
				
				// Turn off currently set bits at mask position and afterwards set the desired bits.
				byte = (uint8_t)((byte & ~mask) | value);
				return true;
			}

			//! Returns the index of the highest active bit.
			/*!
			*  Returns the index of the highest active bit.
			* \param[in] byte: The byte value.
			* \returns The index of the highest active bit.
			*/
			int8_t index_of_highest_active_bit(uint8_t byte)
			{
				int8_t index = 0;
				while ((uint8_t)(byte >> index) != 0)
				{
					index++;
				}
				
				return (int8_t)(index - 1);
			}

			//! Counts the bits in a byte that are set to 1.
			/*!
			*  Counts the bits in a byte that are set to 1.
			* \param[in] byte: The byte value.
			* \returns The number of bits that are set to 1.
			*/
			uint8_t count_active_bits(uint8_t byte)
			{
				byte = (uint8_t)(byte - (uint8_t)((byte >> (uint8_t)1) & (uint8_t)0x55));
				byte = (uint8_t)((byte & (uint8_t)0x33) + (uint8_t)((byte >> 2) & (uint8_t)0x33));
				return ((byte + (byte >> (uint8_t)4)) & (uint8_t)0x0F) * (uint8_t)0x01;
			}

			//! Returns the value of the selected bit range from a given byte array as unsigned char.
			/*!
			* Returns the value of the selected bit range from a given byte array as unsigned char.
			* Since start and end are indices, counting starts from 0 and the maximum value is 7.
			* start_bit and end_bit are both included in the range: [start_bit, end_bit]
			* \param[in] byte: The byte value.
			* \param[in] start_bit: The start position of the bit range (inclusive). Range=[0,6] and must be less than end_bit.
			* \param[in] end_bit: The end position of the bit range (inclusive). Range=[1,7] and must be greater than start_bit.
			* \returns The value of the bit range as unsigned char. In case of an error 255 is returned and a message is written
			* via std::cerr.
			*/
			uint8_t value_of_bits(uint8_t byte, uint8_t start_bit, uint8_t end_bit)
			{
				if (start_bit < 0 || start_bit > 7)
				{
					std::cerr << "SensorBase [bit_set] Error: The given start bit index (" << start_bit << ") is out of Bounds." << std::endl;
					return 255;
				}

				if (end_bit < 0 || end_bit > 7)
				{
					std::cerr << "SensorBase [bit_set] Error: The given end bit index (" << end_bit << ") is out of Bounds." << std::endl;
					return 255;
				}

				if (start_bit >= end_bit)
				{
					std::cerr << "SensorBase [bit_set] Error: Start index (" << start_bit << ") is greater or equal (" << end_bit << ")." << std::endl;
					return 255;
				}

				uint8_t mask = 0;
				for (uint8_t i = start_bit; i <= end_bit; ++i)
				{
					mask |= (uint8_t)(1 << i);
				}

				return (uint8_t)((mask & byte) >> start_bit);
			}

			//! Combines two 8 bit values to one 16 bit value.
			/*!
			*  Combines two 8 bit values to one 16 bit value.
			* \param[in] high_byte: The first byte value. Represents the high part of the resulting 16 bit value.
			* \param[in] low_byte: The second byte value. Represents the low part of the resulting 16 bit value.
			* \returns The value of the combined bytes as 16 bit value.
			*/
			uint16_t combine_bytes(uint8_t high_byte, uint8_t low_byte)
			{
				return (uint16_t)((high_byte << 8) | low_byte);
			}

			//! Combines two 8 bit values to one 16 bit value.
			/*!
			*  Combines two 8 bit values to one 16 bit value.
			* \param[in] value: The 16 bit value to split.
			* \param[out] high_byte: The first byte value. Represents the high part of the resulting 16 bit value.
			* \param[out] low_byte: The second byte value. Represents the low part of the resulting 16 bit value.
			*/
			void split_bytes(uint16_t value, uint8_t& high_byte, uint8_t& low_byte)
			{
				high_byte = (uint8_t)(value & 0xFF);
				low_byte = (uint8_t)(value >> 8);
			}

			//! Checks if the given pointer is null.
			/*!
			*  Checks if the given pointer is null.
			* \param[in] pointer: The pointer to check.
			* \returns 0 if the pointer is not null and -1 if the pointer is null.
			*/
			int8_t null_check(void* pointer)
			{
				if (pointer)
				{
					return OK;
				}

				return NULL_PTR;
			}

			//! Simply reads all content from the device at once.
			/*!
			*  Simply reads all content from the device at once. The function should only be used for
			*  debug purposes.
			* \param[out] all_data: A buffer to store the content.
			* \returns 0 if reading all data was successful, a negative error value otherwise.
			*/
			virtual int8_t get_all_raw_data(uint8_t* all_data) = 0;

			int m_file_handle;
			uint8_t m_dev_id;
			uint8_t m_id;
			std::function<int8_t(const std::string, uint8_t, int&)> m_open_device_function;
			std::function<int8_t(int&)> m_close_device_function;
			std::function<int8_t(int, uint8_t, uint8_t*, uint16_t)> m_read_function;
			std::function<int8_t(int, uint8_t, const uint8_t*, uint16_t)> m_write_function;
		};
	}
}