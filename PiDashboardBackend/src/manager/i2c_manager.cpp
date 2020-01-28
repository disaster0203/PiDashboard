#include "i2c_manager.h"

int8_t manager::i2c_manager::open_device(const char* path, uint8_t address, int& handle)
{
	handle = open(path, O_RDWR);

	if (!device_open(handle))
	{
		std::cerr << "Could not load I2C-Module! " << path << " " << strerror(errno) << std::endl;
		return -1;
	}

	if (ioctl(handle, I2C_SLAVE, address) < 0)
	{
		std::cerr << path << " addr: 0x" << std::hex << address << std::dec << " error: " << strerror(errno) << std::endl;
		return -1;
	}

	std::cout << "Channel #" << handle << " for " << path << "0x" << std::hex << address << std::dec << " is open." << std::endl;
	return 0;
}

int8_t manager::i2c_manager::close_device(int& handle)
{
	if (!device_open(handle))
	{
		std::cerr << "Device #" << handle << " is not open." << std::endl;
		return -1;
	}

	if (close(handle) < 0)
	{
		std::cerr << "Could not close device #" << handle << std::endl;
		return -1;
	}
	else
	{
		handle = -1;
		std::cout << "Device #" << handle << " is closed." << std::endl;
		return 0;
	}
}

bool manager::i2c_manager::device_open(int handle)
{
	return (handle > 0);
}

int8_t manager::i2c_manager::read_from_device(int handle, uint8_t address, uint8_t* data, uint16_t length)
{
	if (!device_open(handle))
	{
		std::cerr << "Device #" << handle << " is not open." << std::endl;
		return -1;
	}

	data[0] = address;
	if (write(handle, data, 1) != 1)
	{
		std::cerr << "Could not got to read position 0x" << std::hex << address << std::dec << ". Error: " << strerror(errno) << std::endl;
		return -1;
	}
	if (read(handle, data, length) < 0)
	{
		std::cerr << "Could not read " << length << " bytes starting from 0x" << std::hex << address << std::dec << ". Error: " << strerror(errno) << std::endl;
		return -1;
	}

	return 0;
}

int8_t manager::i2c_manager::write_to_device(int handle, uint8_t address, const uint8_t* data, uint16_t length)
{
	if (!device_open(handle))
	{
		std::cerr << "Device #" << handle << " is not open." << std::endl;
		return -1;
	}

	int8_t* buf;

	buf = (int8_t*)malloc(length + 1);
	buf[0] = address;
	memcpy(buf + 1, data, length);
	if (write(handle, buf, length + 1) < length)
	{
		std::cerr << "Could not write data of length " << length << " to address 0x" << std::hex << address << std::dec << ". Error: " << strerror(errno) << std::endl;
		return -1;
	}
	free(buf);

	return 0;
}
