#pragma once

#include <cstdint>
#include <functional>

namespace hal
{
	/*! 
	* Data structure to store a callback function together with its unique handle.
	*/
	struct CallbackHandle
	{
		/*!
		* Default constructor.
		*/
		CallbackHandle(const std::function<void(std::string)>& callback, const uint32_t handle)
			: callback(callback),
				callback_handle(handle)
		{
		}

		/*! The callback of this object. */
		const std::function<void(std::string)> callback;

		/*! A unique handle that is used to clearly identify its corresponding callback function. */
		const uint32_t callback_handle;
	};
}
