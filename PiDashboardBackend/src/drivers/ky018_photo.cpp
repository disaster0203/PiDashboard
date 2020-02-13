#include "ky018_photo.h"

int8_t driver::sensors::ky018::photo::init(std::shared_ptr<ads1115::converter> ads1115_converter, ads1115::ads1115_multiplexer sensor_multiplexer_mode, ads1115::ads1115_gain_amplifier sensor_gain)
{
	m_ads1115_converter = ads1115_converter;
	m_sensor_multiplexer_mode = sensor_multiplexer_mode;
	m_sensor_gain = sensor_gain;

	// If the ADS1115 device is not yet fully setup, initialize it
	uint8_t try_count = 0;
	m_mutex.lock();
	while (!m_ads1115_converter->is_initialized())
	{
		m_ads1115_converter->init();
		try_count++;
		if (try_count == 5)
		{
			m_mutex.unlock();
			std::cerr << "KY018 [init] Error: Could not initialize ADS1115 device" << std::endl;
			return COMMUNICATION_FAIL;
		}
	}
	m_mutex.unlock();
}

double driver::sensors::ky018::photo::get_voltage()
{
	double voltage = 0.0;
	bool is_converting = true;

	m_mutex.lock(); // Lock the shared ADS1115 pointer to avoid conflicts (we need to change multiplexer and gain)
	m_ads1115_converter->set_multiplexer_setting(m_sensor_multiplexer_mode); // Set multiplexer
	m_ads1115_converter->set_gain_amplifier_setting(m_sensor_gain); // Set gain amplifier
	m_ads1115_converter->start_single_conversion(); // Trigger new conversion
	m_ads1115_converter->get_converted_data(voltage); // Receive the new voltage data from the ADS1115
	m_mutex.unlock(); // Unlock ADS1115 pointer

	// Clamp voltage
	return std::fmaxl(std::fminl(m_max_voltage, voltage), m_min_voltage);
}

double driver::sensors::ky018::photo::get_resistance()
{
	double voltage = get_voltage();
	return 10000 * voltage / (m_max_voltage - voltage);
}