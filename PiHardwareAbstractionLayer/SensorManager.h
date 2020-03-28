#pragma once

#include "enums/Delay.h"
#include "enums/SensorType.h"
#include "enums/SensorSetting.h"
#include "enums/SensorName.h"
#include "interfaces/ISensor.h"
#include "sensors/i2c/CCS811.h"
#include "Sensor.h"

#include <cstdint>
#include <map>
#include <memory>

namespace hal
{
	class SensorManager
	{
	public:
		/*!
		* Access the singleton instance of this class.
		* \returns the singleton instance of this class.
		*/
		static SensorManager& instance();

		SensorManager(SensorManager const&) = delete;
		SensorManager(SensorManager&&) = delete;
		SensorManager& operator=(const SensorManager& rhs) = delete;
		SensorManager& operator=(SensorManager&&) = delete;

		/*!
		* Return a vector of supported hardware sensors for the given measurement type.
		* \param[in] type: The type of the sensor names to return.
		* \returns a vector of supported hardware sensors for the given measurement type.
		*/
		std::vector<SensorName> available_sensors_of_type(SensorType type);

		/*!
		* Return a sensor handle for the given type, name and pin.
		* \param[in] type: The type of the sensor to return.
		* \param[in] name: The name of the sensor to return.
		* \param[in] pin: The pin the sensor to return uses.
		* \param[in] delay: The time between two measurements.
		* \returns a sensor object that offers access to a hardware sensor.
		*/
		Sensor* get_sensor(SensorType type, SensorName name, uint8_t pin, Delay delay = Delay::DEFAULT);

		/*!
		* Closes the connection to a hardware sensor.
		* \param[in] name: The name of the sensor to shutdown.
		* \param[in] pin: The pin the sensor uses.
		*/
		void shutdown(SensorName name, uint8_t pin);

		/*!
		* Changes the given setting of a hardware sensor.
		* \param[in] name: The name of the sensor to configure.
		* \param[in] pin: The pin the sensor uses.
		* \param[in] setting: The setting to change.
		* \param[in] setting_value: The new value to set.
		*/
		void configure(SensorName name, uint8_t pin, SensorSetting setting, std::string setting_value);

		/*!
		* Checks whether a connection to a specific hardware sensor is active.
		* \param[in] name: The name of the sensor to check.
		* \param[in] pin: The pin the sensor uses.
		* \returns True if the desired sensor is already connected, false otherwise.
		*/
		bool is_hardware_running(SensorName name, uint8_t pin);

	protected:
		SensorManager() = default;
		~SensorManager() = default;

		/*!
		* Callback that will be called if it is save to delete a hardware sensor pointer.
		* \param[in] type: The type of the sensor to delete.
		* \param[in] name: The name of the sensor to delete.
		* \param[in] pin: The pin the sensor uses.
		*/
		void on_safe_to_delete(SensorType type, SensorName name, uint8_t pin);

		/*!
		* Creates a new hardware sensor and adds it to the sensor map.
		* \param[in] type: The type of the sensor to delete.
		* \param[in] name: The name of the sensor to delete.
		* \param[in] pin: The pin the sensor uses.
		*/
		void create_hardware_pointer(SensorType type, SensorName name, uint8_t pin);

		std::map<std::pair<SensorName, int>, interfaces::ISensor*> m_hardware_map;

		std::map<SensorType, std::vector<SensorName>> m_concrete_sensors = {
			{SensorType::AIR_HUMIDITY, {SensorName::BME280}},
			{SensorType::AIR_PRESSURE, {SensorName::BME280}},
			{SensorType::TEMPERATURE, {SensorName::BME280}},
			{SensorType::CLOCK, {SensorName::DS3231}},
			{SensorType::CO2, {SensorName::CCS811}},
			{SensorType::TVOC, {SensorName::CCS811}},
			{SensorType::LIGHT, {SensorName::KY_018}},
			{SensorType::MOTION, {SensorName::AM312}}
		};
	};
}
