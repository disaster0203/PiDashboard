#pragma once

#include "../enums/SensorType.h"
#include "../enums/SensorSetting.h"
#include "../structs/CallbackHandle.h"

#include <map>
#include <memory>
#include <string>
#include <vector>

namespace hal
{
	namespace interfaces
	{
		/*!
		* Interface each sensor implements to offer a basic set of functionality.
		*/
		class ISensor
		{
		public:
			ISensor() = default;

			ISensor(const ISensor& rhs) { m_callbacks = rhs.m_callbacks; }

			ISensor(ISensor&&) = delete;
			virtual ~ISensor() = default;
			ISensor& operator=(const ISensor& ex) = delete;
			ISensor& operator=(ISensor&&) = delete;

			/*!
			* Tells the hardware to perform a new measurement. The result will be sent with a callback function. 
			* If no callback is registered the measurement cannot be obtained.
			* \param[in] type: The type of measurement that has to do be done.
			*/
			virtual void trigger_measurement(const SensorType type)
			{
			}

			/*!
			* Changes one specific setting of a sensor.
			* \param[in] setting: The type of setting to change. Use \sa { ISensor::available_configurations}
			* to get a list of supported settings for the current sensor.
			* \param[in] configuration: The new value to set for the desired setting. The value has to be converted 
			* to string because each sensor needs its own data format and this way the specific conversion can be 
			* done easily on each sensor.
			*/
			virtual void configure(SensorSetting setting, const std::string& configuration)
			{
			}

			/*!
			* Returns one specific setting of a sensor.
			* \param[in] setting: The type of setting to return. Use \sa { ISensor::available_configurations}
			* to get a list of supported settings for the current sensor.
			* \returns the current value of the given setting as string.
			*/
			virtual std::string get_configuration(SensorSetting setting) { return ""; }

			/*! 
			* Returns a vector of \sa { HAL::Enums::SensorSetting } that are supported by this sensor.
			* \returns a vector of supported sensor settings.
			*/
			virtual std::vector<SensorSetting> available_configurations() noexcept { return std::vector<SensorSetting>(); }

			/*!
			* Closes the connection to a sensor. This will deregister all callbacks wherefore no measurements
			* can be triggered anymore.
			*/
			virtual void close()
			{
			}

			/*!
			* Adds a new callback to this sensor and the specified measurement type.
			* \param[in] type: The measurement type the callback should listen to.
			* \param[in] callback: The callback to register.
			*/
			void add_value_callback(const SensorType type, const std::shared_ptr<CallbackHandle>& callback) noexcept
			{
				m_callbacks[type].push_back(callback);
			}

			/*!
			* Tries to remove an already registered callback from the sensor.
			* \param[in] type: The measurement type the callback listens to.
			* \param[in] callback: The callback to remove.
			*/
			void remove_value_callback(const SensorType type, const std::shared_ptr<CallbackHandle>& callback) noexcept
			{
				int index;
				if (has_value_callback(type, callback->callback_handle, index))
				{
					m_callbacks[type].erase(m_callbacks[type].begin() + index);
				}
			}

			/*!
			* Checks whether the given callback (handle) is registered to the given measurement type.
			* \param[in] type: The measurement type the callback should listen to.
			* \param[in] handle: A unique handle that clearly identifies one specific callback. This
			* mechanism is needed because std::functions cannot be compared.
			* \returns True if the callback is already registered, false otherwise.
			*/
			bool has_value_callback(const SensorType type, const uint32_t handle) noexcept
			{
				auto idx = 0; // Just a default assignment. Not needed anymore
				return has_value_callback(type, handle, idx);
			}

			/*!
			* Checks whether the given callback (handle) is registered to the given measurement type
			* and returns its index position if it is found.
			* \param[in] type: The measurement type the callback should listen to.
			* \param[in] handle: A unique handle that clearly identifies one specific callback. This
			* mechanism is needed because std::functions cannot be compared.
			* \param[out] index: The index of the callback or -1 if the callback is not yet registered.
			* \returns True if the callback is already registered, false otherwise.
			*/
			bool has_value_callback(const SensorType type, const uint32_t handle, int& index) noexcept
			{
				auto idx = 0;
				for (auto& i : m_callbacks[type])
				{
					if (i->callback_handle == handle)
					{
						index = idx;
						return true;
					}
					idx++;
				}
				index = -1;
				return false;
			}

		protected:
			/*! A map storing the registered callbacks of each measurement type this sensor supports. */
			std::map<SensorType, std::vector<std::shared_ptr<CallbackHandle>>> m_callbacks{};
		};
	}
}
