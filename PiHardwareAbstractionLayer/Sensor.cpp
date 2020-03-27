#include "Sensor.h"
#include "sensors/analog/KY018.h"
#include "sensors/digital/AM312.h"
#include "sensors/i2c/ADS1115.h"
#include "sensors/i2c/BME280.h"
#include "sensors/i2c/CCS811.h"
#include "utils/Helper.h"

hal::Sensor::~Sensor()
{
	shutdown();
}

hal::Sensor::Sensor(
	const SensorType type,
	const SensorName name,
	const uint8_t pin,
	const CommunicationType com_type,
	const std::string& vendor,
	const std::function<void(SensorType, SensorName, uint8_t)>& on_ready_to_delete,
	const int delay_milliseconds,
	interfaces::ISensor* sensor)
{
	m_type = type;
	m_name = name;
	m_pin = pin;
	m_com_type = com_type;
	m_vendor = vendor;
	m_sensor = sensor;
	m_on_ready_to_delete = on_ready_to_delete;
	m_delay_milliseconds = delay_milliseconds;
	m_is_running = true;
	m_is_sleeping = false;
	m_sensor_thread = new std::thread(&Sensor::thread_loop, this);
}

void hal::Sensor::configure(const SensorSetting setting, const std::string configuration)
{
	// Lock m_sensor
	std::lock_guard<std::mutex> guard(m_mutex);

	if (Helper::null_check(m_sensor) != OK)
	{
		throw exception::HALException("Sensor", "configure", "Sensor pointer is null.");
	}

	switch (m_name)
	{
	case SensorName::BME280:
		static_cast<sensors::i2c::bme280::BME280*>(m_sensor)->configure(setting, configuration);
		break;
	case SensorName::CCS811:
		static_cast<sensors::i2c::ccs811::CCS811*>(m_sensor)->configure(setting, configuration);
		break;
	case SensorName::KY_018:
		static_cast<sensors::i2c::ads1115::ADS1115*>(m_sensor)->configure(setting, configuration);
		break;
	case SensorName::ADS1115:
		//static_cast<sensors::analog::ky018::KY018*>(m_sensor)->configure(setting, configuration);
		break;
	case SensorName::AM312:
		static_cast<sensors::digital::am312::AM312*>(m_sensor)->configure(setting, configuration);
		break;
	case SensorName::DS3231:
		//static_cast<sensors::i2c::ds3231::DS3231*>(m_sensor)->configure(setting, configuration);
		break;
	default:
		break;
	}
}

std::string hal::Sensor::get_configuration(const SensorSetting setting)
{
	// Lock m_sensor
	std::lock_guard<std::mutex> guard(m_mutex);

	if (Helper::null_check(m_sensor) != OK)
	{
		throw exception::HALException("Sensor", "get_configuration", "Sensor pointer is null.");
	}

	std::string result = "";
	switch (m_name)
	{
	case SensorName::BME280:
		result = static_cast<sensors::i2c::bme280::BME280*>(m_sensor)->get_configuration(setting);
		break;
	case SensorName::CCS811:
		result = static_cast<sensors::i2c::ccs811::CCS811*>(m_sensor)->get_configuration(setting);
		break;
	case SensorName::KY_018:
		result = static_cast<sensors::i2c::ads1115::ADS1115*>(m_sensor)->get_configuration(setting);
		break;
	case SensorName::ADS1115:
		//result = static_cast<sensors::analog::ky018::KY018*>(m_sensor)->get_configuration(setting);
		break;
	case SensorName::AM312:
		result = static_cast<sensors::digital::am312::AM312*>(m_sensor)->get_configuration(setting);
		break;
	case SensorName::DS3231:
		//result = static_cast<sensors::i2c::ds3231::DS3231*>(m_sensor)->get_configuration(setting);
		break;
	default:
		break;
	}
	return result;
}

std::vector<hal::SensorSetting> hal::Sensor::available_configurations()
{
	// Lock m_sensor
	std::lock_guard<std::mutex> guard(m_mutex);

	if (Helper::null_check(m_sensor) != OK)
	{
		throw exception::HALException("Sensor", "available_configurations", "Sensor pointer is null.");
	}

	std::vector<SensorSetting> result;
	switch (m_name)
	{
	case SensorName::BME280:
		result = static_cast<sensors::i2c::bme280::BME280*>(m_sensor)->available_configurations();
		break;
	case SensorName::CCS811:
		result = static_cast<sensors::i2c::ccs811::CCS811*>(m_sensor)->available_configurations();
		break;
	case SensorName::KY_018:
		result = static_cast<sensors::i2c::ads1115::ADS1115*>(m_sensor)->available_configurations();
		break;
	case SensorName::ADS1115:
		//result = static_cast<sensors::analog::ky018::KY018*>(m_sensor)->available_configurations();
		break;
	case SensorName::AM312:
		result = static_cast<sensors::digital::am312::AM312*>(m_sensor)->available_configurations();
		break;
	case SensorName::DS3231:
		//result = static_cast<sensors::i2c::ds3231::DS3231*>(m_sensor)->available_configurations();
		break;
	default:
		break;
	}
	return result;
}

void hal::Sensor::put_to_sleep()
{
	if (m_is_running)
	{
		m_is_sleeping = true;
	}
}

void hal::Sensor::awake_from_sleep()
{
	if (m_is_running)
	{
		m_is_sleeping = false;
	}
}

void hal::Sensor::shutdown()
{
	if (m_is_running && m_sensor_thread != nullptr)
	{
		m_is_running = false;
		m_cv.notify_all(); // Interrupt sleeping during two measurements
		m_sensor_thread->join(); // Wait for thread to finish
		delete m_sensor_thread;
		delete m_sensor;

		if (m_on_ready_to_delete != nullptr)
		{
			m_on_ready_to_delete(m_type, m_name, m_pin);
			m_on_ready_to_delete = nullptr;
		}
	}
}

std::shared_ptr<hal::CallbackHandle> hal::Sensor::add_value_callback(const std::function<void(std::string)> on_value)
{
	auto handle = std::make_shared<CallbackHandle>(CallbackHandle(on_value, get_unique_handle()));
	std::lock_guard<std::mutex> guard(m_mutex);
	m_value_callbacks_to_add.push_back(handle);
	return handle;
}

void hal::Sensor::remove_value_callback(const std::shared_ptr<CallbackHandle> handle)
{
	std::lock_guard<std::mutex> guard(m_mutex);
	m_value_callbacks_to_remove.push_back(handle);
}

void hal::Sensor::thread_loop()
{
	std::unique_lock<std::mutex> lock(m_wait_mutex);
	while (m_is_running)
	{
		if (m_cv.wait_for(lock, std::chrono::milliseconds(m_delay_milliseconds)) == std::cv_status::timeout)
		{
			// Add new callbacks if necessary
			{
				std::lock_guard<std::mutex> guard(m_mutex);
				auto add_cb_iterator = m_value_callbacks_to_add.begin();
				while (add_cb_iterator != m_value_callbacks_to_add.end())
				{
					m_sensor->add_value_callback(m_type, *add_cb_iterator);
					add_cb_iterator = m_value_callbacks_to_add.erase(add_cb_iterator);
				}
			}

			// Remove existing callbacks if necessary
			{
				std::lock_guard<std::mutex> guard(m_mutex);
				auto remove_cb_iterator = m_value_callbacks_to_remove.begin();
				while (remove_cb_iterator != m_value_callbacks_to_remove.end())
				{
					m_sensor->remove_value_callback(m_type, *remove_cb_iterator);
					remove_cb_iterator = m_value_callbacks_to_remove.erase(remove_cb_iterator);
				}
			}

			// Trigger a new measurement if the sensor is currently not sleeping
			if (!m_is_sleeping)
			{
				std::lock_guard<std::mutex> guard(m_mutex);
				if (Helper::null_check(m_sensor) != OK)
				{
					throw exception::HALException("Sensor", "thread_loop", "Sensor pointer is null.");
				}

				// After measurement finished, the sensor will fire the appropriate 
				// callback function (if the callback is not a nullptr).
				m_sensor->trigger_measurement(m_type);
			}
		}
	}
}

uint32_t hal::Sensor::get_unique_handle()
{
	std::lock_guard<std::mutex> guard(m_mutex);
	uint32_t new_handle;
	auto valid_value = false;
	do
	{
		new_handle = rand();
		auto unique = true;

		for (auto iterator = m_registered_value_callbacks.begin(); iterator != m_registered_value_callbacks.end(); ++iterator)
		{
			if ((*iterator)->callback_handle == new_handle)
			{
				unique = false;
				break;
			}
		}

		if (unique) valid_value = true;
	} while (!valid_value);
	return new_handle;
}
