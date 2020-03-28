#pragma once

#include "HALException.h"
#include <string>

namespace hal
{
	namespace exception
	{
		/*!
		* Exception that is thrown if an GPIO operation (read, write, init) failed.
		*/
		class GPIOException final : public HALException
		{
		public:
			GPIOException() = delete;
			GPIOException(const GPIOException& ex) = delete;
			GPIOException(GPIOException&&) = delete;
			~GPIOException() = default;
			GPIOException& operator=(const GPIOException& ex) = delete;
			GPIOException& operator=(GPIOException&&) = delete;

			/*!
			* Default constructor
			*/
			GPIOException(const std::string& cls, const std::string& func, uint8_t pin, const std::string& msg)
				: HALException(cls, func, msg),
					m_pin(pin)
			{
			}

			/*!
			* Return the pin the sensor that caused the exception uses.
			* \returns the pin of the sensor that throws the exception.
			*/
			uint8_t get_pin() const { return m_pin; }

			/*!
			* Return the type of the exception.
			* \returns the type of the exception.
			*/
			std::string get_type() override { return "GPIOException"; }

			/*!
			* Return the exception message as a formatted string.
			* \returns the exception message as a formatted string.
			*/
			std::string to_string() override
			{
				return get_type().append(" in ").append(get_class()).append("_").append(m_function)
										.append(" with Pin ").append(std::to_string(get_pin())).append(": ").append(get_message());
			}

		protected:
			uint8_t m_pin;
		};
	}
}
