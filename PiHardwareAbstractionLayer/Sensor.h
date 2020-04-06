#pragma once

#include "enums/CommunicationType.h"
#include "enums/SensorName.h"
#include "enums/SensorSetting.h"
#include "enums/SensorType.h"
#include "interfaces/ISensor.h"
#include "structs/CallbackHandle.h"

#include <atomic>
#include <condition_variable>
#include <functional>
#include <mutex>
#include <thread>
#include <string>
#include <vector>

namespace hal
{
	/*! Public class that abstracts hardware and is given to applications that need to interact with hardware sensors. 
	* This class holds an \sa { HAL::Interfaces::ISensor } pointer and offers various methods to interact with this
	* specific sensor.
	*/
	class Sensor
	{
	public:
		Sensor(const Sensor& sensor) = delete;
		Sensor(Sensor&&) = delete;
		Sensor& operator=(const Sensor& rhs) = delete;
		Sensor& operator=(Sensor&&) = delete;

		~Sensor();

		/*!
		* Constructor that does basic initialization of the sensor.
		* \param[in] type: The type of values this sensor offers.
		* \param[in] name: The hardware name of the sensor to use (since there may be multiple hardware sensors that measure temperature for example).
		* \param[in] pin: The GPIO pin the desired sensor is connected to. Use pin numbers, not GPIO numbers!
		* \param[in] com_type: The communication type the desired sensor uses.
		* \param[in] vendor: The vendor of the desired sensor.
		* \param[in] on_ready_to_delete: A callback that will be fired if the device has shutdown successfully (after an call of 
		* \sa { HAL::Interfaces::ISensor::close() }).
		* \param[in] delay_milliseconds: Specifies the time between two sensor measurements (e.g. the data rate).
		* \param[in] sensor: An internal sensor pointer.
		*/
		Sensor(
			SensorType type,
			SensorName name,
			uint8_t pin,
			CommunicationType com_type,
			const std::string& vendor,
			const std::function<void(SensorType, SensorName, uint8_t)>& on_ready_to_delete,
			int delay_milliseconds,
			interfaces::ISensor* sensor);

		/*!
		* Changes one specific setting of a sensor.
		* \param[in] setting: The type of setting to change. Use \sa { ISensor::available_configurations}
		* to get a list of supported settings for the current sensor.
		* \param[in] configuration: The new value to set for the desired setting. The value has to be converted
		* to string because each sensor needs its own data format and this way the specific conversion can be
		* done easily on each sensor.
		*/
		void configure(SensorSetting setting, const std::string& configuration);

		/*!
		* Returns one specific setting of a sensor.
		* \param[in] setting: The type of setting to return. Use \sa { ISensor::available_configurations}
		* to get a list of supported settings for the current sensor.
		* \returns the current value of the given setting as string.
		*/
		std::string get_configuration(SensorSetting setting);

		/*!
		* Returns a vector of \sa { HAL::Enums::SensorSetting } that are supported by this sensor.
		* \returns a vector of supported sensor settings.
		*/
		std::vector<SensorSetting> available_configurations();

		/*!
		* After calling this method the sensor will stop continuously sending measuring values. Use this if you do not
		* need the sensor at the moment. The sensor will not be shutdown and can easily be reactivated by calling
		* \sa { awake_from_sleep() }. A sensor in idle mode can still be configured and register / deregister callbacks.
		*/
		void put_to_sleep();

		/*! 
		* Reactivates the sensor if it is currently idling. After calling this method the sensor will restart to send
		* measuring results.
		*/
		void awake_from_sleep();

		/*!
		* Closes the connection to the sensor, deregister all callbacks and cleans everything up. You need to re-obtain
		* the sensor from \sa { HAL::SensorManager } if you want to use it later again. If you already know that the 
		* sensor will be needed again after a certain amount of time a better solution is to just put it to sleep with
		* \sa { put_to_sleep() }.
		*/
		void shutdown();

		/*!
		* Adds a new callback to the sensor.
		* \param[in] on_value: The new callback to add.
		* \returns a CallbackHandle object that contains the callback function together with its unique handle.
		*/
		std::shared_ptr<CallbackHandle> add_value_callback(const std::function<void(std::string)>& on_value);

		/*!
		* Removes a callback from the sensor.
		* \param[in] handle: The handle of the callback to remove.
		*/
		void remove_value_callback(const std::shared_ptr<CallbackHandle>& handle);

		/*!
		* Return the type of the sensor.
		* \returns the type of the sensor.
		*/
		SensorType get_type() const { return m_type; }

		/*!
		* Return the name of the sensor.
		* \returns the name of the sensor.
		*/
		SensorName get_name() const { return m_name; }

		/*!
		* Return the vendor of the sensor.
		* \returns the vendor of the sensor.
		*/
		std::string get_vendor() const { return m_vendor; }

		/*!
		* Return the communication type of the sensor.
		* \returns the communication type of the sensor.
		*/
		CommunicationType get_com_type() const { return m_com_type; }

		/*!
		* Return the pin the sensor is connected to.
		* \returns the pin the sensor is connected to.
		*/
		uint8_t get_pin() const { return m_pin; }

		/*!
		* Return whether the sensor is in sleep mode.
		* \returns True if the sensor is in sleep mode, False otherwise.
		*/
		bool is_sleeping() const { return m_is_sleeping; }

		/*!
		* Return whether the sensor is running.
		* \returns True if the sensor is running, False otherwise.
		*/
		bool is_running() const { return m_is_running; }

	protected:
		/*!
		* The function that is executed by the sensor thread.
		*/
		void thread_loop();

		//! Generates a new unique handle to identify a specific callback.
		/*!
		* Generates a new unique handle to identify a specific callback.
		*/
		uint32_t get_unique_handle();

		std::condition_variable m_cv;
		std::mutex m_mutex{};
		std::mutex m_wait_mutex{};
		std::thread* m_sensor_thread{};
		uint8_t m_pin;
		SensorType m_type{};
		SensorName m_name{};
		int m_delay_milliseconds;
		CommunicationType m_com_type{};
		std::string m_vendor{};
		std::string m_new_settings{};
		std::function<void(SensorType, SensorName, uint8_t)> m_on_ready_to_delete{};
		std::atomic_bool m_is_sleeping = ATOMIC_VAR_INIT(false);
		std::atomic_bool m_is_running = ATOMIC_VAR_INIT(false);;
		interfaces::ISensor* m_sensor{};
		std::vector<std::shared_ptr<CallbackHandle>> m_value_callbacks_to_add{};
		std::vector<std::shared_ptr<CallbackHandle>> m_value_callbacks_to_remove{};
		std::vector<std::shared_ptr<CallbackHandle>> m_registered_value_callbacks{};
		std::string m_new_config{};
	};
}
