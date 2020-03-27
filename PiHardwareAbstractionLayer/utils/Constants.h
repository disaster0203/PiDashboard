#pragma once

#include <cstdint>

namespace hal
{
	namespace utils
	{
		/*! Return value for functions that produced a warning. */
		static constexpr int8_t WARNING = 1;

		/*! Return value for functions where everything went fine. */
		static constexpr int8_t OK = 0;

		/*! Return value for functions where a null pointer exception occurred. */
		static constexpr int8_t NULL_PTR = -1;

		/*! Return value for function where a wrong type caused an error. */
		static constexpr int8_t WRONG_TYPE = -2;
	}
}
