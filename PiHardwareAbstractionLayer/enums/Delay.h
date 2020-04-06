#pragma once

namespace hal
{
	/*! Defines the idle time between two sensor measurements. */
	enum class Delay
	{
		/*!< 30 seconds */
		SLOW = 30000,
		/*! 5 seconds */
		DEFAULT = 5000,
		/*! 1 second */
		FAST = 1000,
		/*! 750 milliseconds */
		VERY_FAST = 750
	};
}
