#include "I2CManager.h"
#include <cerrno>
#include <cstdio>
#include <iostream>
#include <cstdlib>
#include <unistd.h>
#include <fcntl.h>
#include <cstring>
#include <sys/stat.h>
#include <sys/ioctl.h>
#include <sys/types.h>
#include <linux/i2c-dev.h>

#include "../exceptions/HALException.h"
#include "../exceptions/I2CException.h"

void hal::utils::I2CManager::open_device(const std::string path, const uint8_t address, int& handle)
{
	handle = open(path.c_str(), O_RDWR);

	if (!device_open(handle))
	{
		throw exception::HALException("I2CManager", "open_device", std::string("Could not load I2C-Module! '")
																						.append(path).append("': ").append(strerror(errno)));
	}

	if (ioctl(handle, I2C_SLAVE, address) < 0)
	{
		throw exception::I2CException("I2CManager", "open_device", static_cast<uint8_t>(handle), address,
												std::string("ioctl error: ").append(strerror(errno)));
	}
}

void hal::utils::I2CManager::close_device(int& handle)
{
	if (device_open(handle) && close(handle) < 0)
	{
		throw exception::HALException("I2CManager", "close_device",
												std::string("Could not close device #").append(std::to_string(handle)).append("."));
	}
}

bool hal::utils::I2CManager::device_open(const int handle) noexcept
{
	return (handle > 0);
}

void hal::utils::I2CManager::read_from_device_sp(
	const int handle,
	const uint8_t address,
	std::unique_ptr<uint8_t[]>& data,
	const uint16_t length)
{
	read_from_device(handle, address, data.get(), length);
}

void hal::utils::I2CManager::read_from_device(const int handle, const uint8_t address, uint8_t* data, const uint16_t length)
{
	if (!device_open(handle))
	{
		throw exception::HALException("I2CManager", "read_from_device",
												std::string("Device #").append(std::to_string(handle)).append(" is not open."));
	}

	data[0] = address;
	if (write(handle, data, 1) != 1)
	{
		throw exception::I2CException("I2CManager", "read_from_device", static_cast<uint8_t>(handle), address,
												std::string("Could not get to read position. Error: ")
												.append(strerror(errno)));
	}
	if (read(handle, data, length) < 0)
	{
		throw exception::I2CException("I2CManager", "read_from_device", static_cast<uint8_t>(handle), address, std::string("Could not read ")
																																				.append(std::to_string(length)).
																																				append(
																																					" bytes. Error: ").append(
																																					strerror(errno)));
	}
}

void hal::utils::I2CManager::write_to_device_sp(
	const int handle,
	const uint8_t address,
	const std::unique_ptr<uint8_t[]>& data,
	const uint16_t length)
{
	write_to_device(handle, address, data.get(), length);
}

void hal::utils::I2CManager::write_to_device(const int handle, const uint8_t address, const uint8_t* data, const uint16_t length)
{
	if (!device_open(handle))
	{
		throw exception::HALException("I2CManager", "write_to_device",
												std::string("Device #").append(std::to_string(handle)).append(" is not open."));
	}

	const auto buf = static_cast<int8_t*>(malloc(length + 1));
	buf[0] = address;
	memcpy(buf + 1, data, length);
	if (write(handle, buf, length + 1) < length)
	{
		throw exception::I2CException("I2CManager", "write_to_device", static_cast<uint8_t>(handle), address,
												std::string("Could not write data of length '")
												.append(std::to_string(length)).append("'. Error: ").
												append(strerror(errno)));
	}
	free(buf);
}
