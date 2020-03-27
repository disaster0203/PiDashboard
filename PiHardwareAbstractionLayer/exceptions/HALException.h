#pragma once

#include <exception>
#include <string>
#include <utility>

namespace hal
{
	namespace exception
	{
		/*!
		* General hardware abstraction layer exception that is thrown if failed.
		*/
		class HALException : public std::exception
		{
		public:
			HALException() = delete;
			HALException(const HALException& ex) = delete;
			HALException(HALException&&) = delete;
			~HALException() = default;
			HALException& operator=(const HALException& ex) = delete;
			HALException& operator=(HALException&&) = delete;

			/*!
			* Default constructor
			*/
			HALException(const std::string& cls, const std::string& func, const std::string& msg)
				: m_class(std::move(cls)),
					m_function(std::move(func)),
					m_message(std::move(msg))
			{
			}

			/*!
			* Return the name of the class which caused the exception.
			* \returns the name of the class which caused the exception.
			*/
			std::string get_class() const { return m_class; }

			/*!
			* Return the name of the function which caused the exception.
			* \returns the name of the function which caused the exception.
			*/
			std::string get_function() const { return m_function; }

			/*!
			* Return the exception message that describes what went wrong.
			* \returns the description of what went wrong.
			*/
			std::string get_message() const { return m_message; }

			/*!
			* Return the type of the exception.
			* \returns the type of the exception.
			*/
			virtual std::string get_type() { return "HALException"; }

			/*!
			* Return the exception message as a formatted string.
			* \returns the exception message as a formatted string.
			*/
			virtual std::string to_string()
			{
				return get_type().append(" in ").append(get_class()).append("_").append(m_function).append(": ").append(get_message());
			}

		protected:
			const std::string m_class{};
			const std::string m_function{};
			const std::string m_message{};
		};
	}
}
