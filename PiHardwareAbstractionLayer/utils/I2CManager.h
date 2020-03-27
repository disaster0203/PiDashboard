#pragma once

#include <bitset>
#include <memory>
#include <string>

namespace hal
{
	namespace utils
	{
		//! Class that allows communication over the i2c bus.
		/*!
		* This class implements various functions to communicate via the i2c bus.
		*/
		class I2CManager
		{
		public:
			I2CManager() = default;
			~I2CManager() = default;
			I2CManager(const I2CManager&) = delete;
			I2CManager(I2CManager&&) = delete;
			I2CManager& operator=(const I2CManager&) = delete;
			I2CManager& operator=(I2CManager&&) = delete;

			//! Opens a new connection to an i2c device.
			/*!
			*  Opens a new connection to an i2c device.
			* \param[in] path: The path to the i2c file on the file system (e.g. /dev/i2c-1).
			* \param[in] address: The devices i2c address (e.g. 0x76).
			* \param[out] handle: The handle that will be used to communicate over the i2c bus.
			* \returns 0 if opening the connection was successful, a negative error value otherwise.
			* \throws HALException if the device could not be opened.
			* \throws I2CException if calling ioctl failed.
			*/
			static void open_device(std::string path, uint8_t address, int& handle);

			//! Closes a connection over an i2c device.
			/*!
			*  Closes a connection over an i2c device.
			* \param[out] handle: The file handle to close.
			* \throws HALException if closing the device failed.
			*/
			static void close_device(int& handle);

			//! Checks whether the file handle is valid and open.
			/*!
			*  Checks whether the file handle is valid and open.
			* \param[in] handle: The file handle to check.
			* \returns true if the file handle is valid, false otherwise.
			*/
			static bool device_open(int handle) noexcept;

			//! Reads content from the given address to the smart pointer buffer.
			/*!
			*  First uses 'write' to set the file pointer to the desired address and afterwards
			*  reads the desired amount of bytes into the given buffer.
			* \param[in] handle: The handle that will be used to communicate over the i2c bus.
			* \param[in] address: The file address to read from.
			* \param[out] data: The buffer to which the file content will be read.
			* \param[in] length: The number of bytes to read.
			* \throws HALException if the device is not open.
			* \throws I2CException if going to the read register failed.
			* \throws I2CException if reading the desired number of bytes failed.
			*/
			static void read_from_device_sp(int handle, uint8_t address, std::unique_ptr<uint8_t[]>& data, uint16_t length);

			//! Reads content from the given address to the buffer.
			/*!
			*  First uses 'write' to set the file pointer to the desired address and afterwards
			*  reads the desired amount of bytes into the given buffer.
			* \param[in] handle: The handle that will be used to communicate over the i2c bus.
			* \param[in] address: The file address to read from.
			* \param[out] data: The buffer to which the file content will be read.
			* \param[in] length: The number of bytes to read.
			* \throws HALException if the device is not open.
			* \throws I2CException if going to the read register failed.
			* \throws I2CException if reading the desired number of bytes failed.
			*/
			static void read_from_device(int handle, uint8_t address, uint8_t* data, uint16_t length);

			//! Writes content to the given address from a smart pointer buffer.
			/*!
			*  Writes content to the given address from a buffer.
			* \param[in] handle: The handle that will be used to communicate over the i2c bus.
			* \param[in] address: The file address to write to.
			* \param[in] data: The buffer containing the content to write.
			* \param[in] length: The number of bytes to write.
			* \returns 0 if writing was successful, a negative error value otherwise.
			* \throws HALException if the device is not open.
			* \throws I2CException if writing the desired number of bytes failed.
			*/
			static void write_to_device_sp(int handle, uint8_t address, const std::unique_ptr<uint8_t[]>& data, uint16_t length);

			//! Writes content to the given address from a buffer.
			/*!
			*  Writes content to the given address from a buffer.
			* \param[in] handle: The handle that will be used to communicate over the i2c bus.
			* \param[in] address: The file address to write to.
			* \param[in] data: The buffer containing the content to write.
			* \param[in] length: The number of bytes to write.
			* \returns 0 if writing was successful, a negative error value otherwise.
			* \throws HALException if the device is not open.
			* \throws I2CException if writing the desired number of bytes failed.
			*/
			static void write_to_device(int handle, uint8_t address, const uint8_t* data, uint16_t length);

			/*! The default path for i2c device registers. */
			inline static std::string DEFAULT_PI_I2C_PATH = "/dev/i2c-1";
		};
	}
}
