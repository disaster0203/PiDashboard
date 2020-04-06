#include "SensorManager.h"
#include "exceptions/HALException.h"
#include "sensors/i2c/BME280.h"
#include "sensors/i2c/DS3231.h"

hal::SensorManager& hal::SensorManager::instance()
{
	static SensorManager inst;
	return inst;
}

std::vector<hal::SensorName> hal::SensorManager::available_sensors_of_type(const SensorType type)
{
	return m_concrete_sensors[type];
}

hal::Sensor* hal::SensorManager::get_sensor(const SensorType type, SensorName name, uint8_t pin, Delay delay)
{
	if (!is_hardware_running(name, pin))
	{
		create_hardware_pointer(type, name, pin);
	}

	CommunicationType com_type;
	std::string vendor;

	switch (name)
	{
	case SensorName::BME280:
		com_type = CommunicationType::I2C;
		vendor = "Bosch";
		break;
	case SensorName::CCS811:
		com_type = CommunicationType::I2C;
		vendor = "ams AG";
		break;
	case SensorName::KY_018:
		com_type = CommunicationType::ANALOG_I2C;
		vendor = "Texas Instruments";
		break;
	case SensorName::ADS1115:
		throw exception::HALException("SensorManager", "get_sensor", "Invalid combination of sensor name (ADS1115) and sensor type.");
	case SensorName::AM312:
		com_type = CommunicationType::DIGITAL;
		vendor = "NANYANG SENBA OPTICAL AND ELECTRONIC CO.,LTD.";
		break;
	case SensorName::DS3231:
		com_type = CommunicationType::I2C;
		vendor = "Maxim Integrated Products, Inc.";
		break;
	default:
		throw exception::HALException("SensorManager", "get_sensor", "Invalid combination of sensor name (Undefined) and sensor type.");
	}

	return new Sensor(type, name, pin, com_type, vendor,
		std::bind(&SensorManager::on_safe_to_delete, &instance(), std::placeholders::_1,
			std::placeholders::_2, std::placeholders::_3),
		static_cast<int>(delay), m_hardware_map[std::make_pair(name, pin)]);
}

void hal::SensorManager::shutdown(SensorName name, uint8_t pin)
{
	if (is_hardware_running(name, pin))
	{
		m_hardware_map[std::make_pair(name, pin)]->close();
	}
}

void hal::SensorManager::configure(SensorName name, uint8_t pin, const SensorSetting setting, const std::string setting_value)
{
	if (is_hardware_running(name, pin))
	{
		m_hardware_map[std::make_pair(name, pin)]->configure(setting, setting_value);
	}
}

bool hal::SensorManager::is_hardware_running(SensorName name, uint8_t pin)
{
	return m_hardware_map.find(std::make_pair(name, pin)) != m_hardware_map.end();
}

void hal::SensorManager::on_safe_to_delete(SensorType type, SensorName name, uint8_t pin)
{
	if (is_hardware_running(name, pin))
	{
		m_hardware_map.erase(std::make_pair(name, pin));
	}
}

void hal::SensorManager::create_hardware_pointer(const SensorType type, SensorName name, uint8_t pin)
{
	switch (name)
	{
	case SensorName::BME280:
	{
		if (type == SensorType::TEMPERATURE || type == SensorType::AIR_PRESSURE || type == SensorType::AIR_HUMIDITY)
		{
			auto sensor = new sensors::i2c::bme280::BME280();
			sensor->init();
			sensor->set_sensor_mode(sensors::i2c::bme280::OperationMode::FORCED);
			const auto oversampling = std::to_string(static_cast<uint8_t>(sensors::i2c::bme280::Oversampling::OVERSAMPLING_1X))
				.append(",").append(
					std::to_string(static_cast<uint8_t>(sensors::i2c::bme280::Oversampling::OVERSAMPLING_1X))).append(
						",").append(
							std::to_string(static_cast<uint8_t>(sensors::i2c::bme280::Oversampling::OVERSAMPLING_1X)));
			sensor->configure(SensorSetting::OVERSAMPLING, oversampling);
			const auto filter = std::to_string(static_cast<uint8_t>(sensors::i2c::bme280::Filter::NO_FILTER));
			sensor->configure(SensorSetting::FILTER, filter);

			m_hardware_map[std::make_pair(name, pin)] = sensor;
		}
		else
		{
			throw exception::HALException("SensorManager", "create_hardware_pointer",
				"Invalid combination of sensor name (BME280) and sensor type.");
		}
	}
	break;
	case SensorName::CCS811:
	{
		if (type == SensorType::CO2 || type == SensorType::TVOC)
		{
			auto sensor = new sensors::i2c::ccs811::CCS811();
			sensor->init(true, 4, 5); // Todo add correct pin numbers (wake, i2c)
			sensor->start();
			sensor->set_operation_mode(sensors::i2c::ccs811::OperationMode::CONSTANT_POWER_1_S, false, false);
			m_hardware_map[std::make_pair(name, pin)] = sensor;
		}
		else
		{
			throw exception::HALException("SensorManager", "create_hardware_pointer",
				"Invalid combination of sensor name (CCS811) and sensor type.");
		}
	}
	break;
	case SensorName::KY_018:
	{
		if (type == SensorType::LIGHT)
		{
			//auto sensor = new Sensors::Analog::KY_018::KY_018();
			//m_hardware_map[std::make_pair(name, pin)] = sensor;
		}
		else
		{
			throw exception::HALException("SensorManager", "create_hardware_pointer",
				"Invalid combination of sensor name (KY-018) and sensor type.");
		}
	}
	break;
	case SensorName::ADS1115:
	{
		throw exception::HALException("SensorManager", "create_hardware_pointer",
			"Invalid combination of sensor name (ADS1115) and sensor type.");
	}
	case SensorName::AM312:
	{
		if (type == SensorType::MOTION)
		{
			//auto sensor = new Sensors::Digital::AM312::AM312();
			//m_hardware_map[std::make_pair(name, pin)] = sensor;
		}
		else
		{
			throw exception::HALException("SensorManager", "create_hardware_pointer",
				"Invalid combination of sensor name (AM312) and sensor type.");
		}
	}
	break;
	case SensorName::DS3231:
	{
		if (type == SensorType::CLOCK)
		{
			auto sensor = new sensors::i2c::ds3231::DS3231();
			sensor->init();
			sensor->set_hour_format(sensors::i2c::ds3231::HourFormat::HOUR_FORMAT_24);
			m_hardware_map[std::make_pair(name, pin)] = sensor;
		}
		else
		{
			throw exception::HALException("SensorManager", "create_hardware_pointer",
				"Invalid combination of sensor name (DS3231) and sensor type.");
		}
	}
	break;
	default:
		throw exception::HALException("SensorManager", "create_hardware_pointer", "Invalid sensor name.");
	}
}
