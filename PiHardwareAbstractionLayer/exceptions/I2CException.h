#pragma once

#include "HALException.h"
#include <string>
#include <cstdio>

namespace hal
{
	namespace exception
	{
		/*!
		* Exception that is thrown if an i2c operation (read, write, open, close) failed.
		*/
		class I2CException final : public HALException
		{
		public:
			I2CException() = delete;
			I2CException(const I2CException& ex) = delete;
			I2CException(I2CException&&) = delete;
			~I2CException() = default;
			I2CException& operator=(const I2CException& ex) = delete;
			I2CException& operator=(I2CException&&) = delete;

			/*!
			* Default constructor
			*/
			I2CException(const std::string& cls, const std::string& func, const uint8_t device, const uint8_t reg, const std::string& msg)
				: HALException(cls, func, msg),
					m_device(device),
					m_reg(reg)
			{
			}

			/*!
			* Return the hardware id of the device that caused the exception uses.
			* \returns the hardware id of the device that throws the exception.
			*/
			uint8_t get_device() const { return m_device; }

			/*!
			* Return the hardware register where the exception occurs.
			* \returns the hardware register where the exception occurs.
			*/
			uint8_t get_register() const { return m_reg; }

			/*!
			* Return the type of the exception.
			* \returns the type of the exception.
			*/
			std::string get_type() override { return "I2CException"; }

			/*!
			* Return the exception message as a formatted string.
			* \returns the exception message as a formatted string.
			*/
			std::string to_string() override
			{
				char dev[8];
				sprintf(dev, "%x", get_device());
				char reg[8];
				sprintf(reg, "%x", get_register());

				return get_type().append(" in ").append(get_class()).append("_").append(m_function)
										.append(" during operation in Register 0x").append(reg).append(" of device 0x")
										.append(dev).append(": ").append(get_message());
			}

		protected:
			uint8_t m_device;
			uint8_t m_reg;
		};
	}
}
