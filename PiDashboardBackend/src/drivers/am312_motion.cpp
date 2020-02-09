#include "am312_motion.h"

int8_t driver::sensors::am312::motion::init(uint8_t pin, std::function<void()> on_motion)
{
	m_stop = false;
	m_pin = pin;
	m_on_motion = on_motion;

	if (wiringPiSetup() != OK)
	{
		std::cerr << "AM312 [init] Error: Could not initialize wiringPi." << std::endl;
		return COMMUNICATION_FAIL;
	}

	pinMode(m_pin, INPUT);
	m_thread = new std::thread(&driver::sensors::am312::motion::sensor_loop, this);
	return OK;
}

void driver::sensors::am312::motion::close()
{
	if (m_thread != nullptr)
	{
		m_stop = true;
		m_thread->join();
		m_thread = nullptr;
	}
}

void driver::sensors::am312::motion::sensor_loop()
{
	while (!m_stop)
	{
		if (digitalRead(m_pin) == HIGH)
		{
			m_on_motion();
		}
		delay(2300);
	}
}
