#include "AM312.h"
#include <wiringPi.h>
#include "../../exceptions/HALException.h"

void hal::sensors::digital::am312::AM312::trigger_measurement(const SensorType type)
{
	for (auto i = m_callbacks[type].begin(); i != m_callbacks[type].end(); ++i)
	{
		switch (type)
		{
		case SensorType::MOTION:
			try
			{
				(*i)->callback(std::to_string(digitalRead(m_pin)));
			}
			catch (exception::HALException* ex)
			{
				throw exception::HALException("AM312", "trigger_measurement",
														std::string("Could not trigger motion measurement:\n").append(ex->to_string()));
			}
			break;
		default:
			throw exception::HALException("AM312", "trigger_measurement", "Invalid sensor type.");
		}
	}
}

void hal::sensors::digital::am312::AM312::configure(const SensorSetting setting, const std::string& configuration)
{
	// Intentionally empty since this sensor cannot be configured.
}

std::string hal::sensors::digital::am312::AM312::get_configuration(SensorSetting setting)
{
	// Intentionally empty since this sensor cannot be configured.
	return "";
}

std::vector<hal::SensorSetting> hal::sensors::digital::am312::AM312::available_configurations() noexcept
{
	// Intentionally empty since this sensor cannot be configured.
	return std::vector<SensorSetting>();
}

void hal::sensors::digital::am312::AM312::close()
{
	// Intentionally empty since this sensor cannot be closed. Just stop listening to it.
}

void hal::sensors::digital::am312::AM312::init(const uint8_t pin)
{
	m_pin = pin;

	if (wiringPiSetup() != OK)
	{
		throw exception::HALException("AM312", "init", "Could not initialize wiringPi.");
	}

	pinMode(m_pin, INPUT);
}
