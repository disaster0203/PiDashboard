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

namespace manager
{
	class i2c_manager
	{
	public:
		i2c_manager() {}
		~i2c_manager() {}

		static int8_t open_device(const char* name, uint8_t address, int& handle);
		static int8_t close_device(int& handle);

		static bool device_open(int handle);

		static int8_t read_from_device(int handle, uint8_t address, uint8_t* data, uint16_t length);
		static int8_t write_to_device(int handle, uint8_t address, uint8_t* data, uint16_t length);
		static int8_t write_to_device(int handle, uint8_t address, const uint8_t* data, uint16_t length);

		static constexpr const char* DEFAULT_PI_I2C_ADDRESS = "/dev/i2c-1";
	};
}
