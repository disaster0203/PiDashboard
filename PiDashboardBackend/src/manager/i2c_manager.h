#pragma once

#include <bitset>
#include <errno.h>
#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/ioctl.h>
#include <sys/types.h>
#include <linux/i2c-dev.h>
#include <memory>
#include <string>

namespace manager
{
	//! Class that allows communication over the i2c bus.
	/*!
	* This class implements various functions to communicate via the i2c bus.
	*/
	class i2c_manager
	{
	public:
		//! Default constructor.
		/*!
		* Default constructor.
		*/
		i2c_manager() {}

		//! Default destructor.
		/*!
		* Default destructor.
		*/
		~i2c_manager() {}

		//! Opens a new connection to an i2c device.
		/*!
		*  Opens a new connection to an i2c device.
		* \param[in] path: The path to the i2c file on the file system (e.g. /dev/i2c-1).
		* \param[in] address: The devices i2c address (e.g. 0x76).
		* \param[out] handle: The handle that will be used to communicate over the i2c bus.
		* \returns 0 if opening the connection was successful, a negative error value otherwise.
		*/
		static int8_t open_device(const std::string path, uint8_t address, int& handle);

		//! Closes a connection over an i2c device.
		/*!
		*  Closes a connection over an i2c device.
		* \param[out] handle: The file handle to close.
		* \returns 0 if closing the connection was successful, a negative error value otherwise.
		*/
		static int8_t close_device(int& handle);

		//! Checks whether the file handle is valid and open.
		/*!
		*  Checks whether the file handle is valid and open.
		* \param[in] handle: The file handle to check.
		* \returns true if the file handle is valid, false otherwise.
		*/
		static bool device_open(int handle);

		//! Reads content from the given address to the smart pointer buffer.
		/*!
		*  First uses 'write' to set the file pointer to the desired address and afterwards
		*  reads the desired amount of bytes into the given buffer.
		* \param[in] handle: The handle that will be used to communicate over the i2c bus.
		* \param[in] address: The file address to read from.
		* \param[out] data: The buffer to which the file content will be read.
		* \param[in] length: The number of bytes to read.
		* \returns 0 if reading was successful, a negative error value otherwise.
		*/
		static int8_t read_from_device_sp(int handle, uint8_t address, std::unique_ptr<uint8_t[]>& data, uint16_t length);

		//! Reads content from the given address to the buffer.
		/*!
		*  First uses 'write' to set the file pointer to the desired address and afterwards
		*  reads the desired amount of bytes into the given buffer.
		* \param[in] handle: The handle that will be used to communicate over the i2c bus.
		* \param[in] address: The file address to read from.
		* \param[out] data: The buffer to which the file content will be read.
		* \param[in] length: The number of bytes to read.
		* \returns 0 if reading was successful, a negative error value otherwise.
		*/
		static int8_t read_from_device(int handle, uint8_t address, uint8_t* data, uint16_t length);

		//! Writes content to the given address from a smart pointer buffer.
		/*!
		*  Writes content to the given address from a buffer.
		* \param[in] handle: The handle that will be used to communicate over the i2c bus.
		* \param[in] address: The file address to write to.
		* \param[in] data: The buffer containing the content to write.
		* \param[in] length: The number of bytes to write.
		* \returns 0 if writing was successful, a negative error value otherwise.
		*/
		static int8_t write_to_device_sp(int handle, uint8_t address, const std::unique_ptr<uint8_t[]>& data, uint16_t length);

		//! Writes content to the given address from a buffer.
		/*!
		*  Writes content to the given address from a buffer.
		* \param[in] handle: The handle that will be used to communicate over the i2c bus.
		* \param[in] address: The file address to write to.
		* \param[in] data: The buffer containing the content to write.
		* \param[in] length: The number of bytes to write.
		* \returns 0 if writing was successful, a negative error value otherwise.
		*/
		static int8_t write_to_device(int handle, uint8_t address, const uint8_t* data, uint16_t length);

		static constexpr const char* DEFAULT_PI_I2C_PATH = "/dev/i2c-1";
	};
}
