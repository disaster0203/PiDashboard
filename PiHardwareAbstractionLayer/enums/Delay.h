#pragma once

namespace hal
{
	/*! Defines the idle time between two sensor measurements. */
	enum class Delay
	{
		SLOW = 30000,
		/*!< 30 seconds */
		DEFAULT = 5000,
		/*! 5 seconds */
		FAST = 1000 /*! 1 second */
	};
}
