#pragma once
#include "ads1115_converter.h"
#include <mutex>
#include <math.h>

namespace driver
{
	namespace sensors
	{
		namespace ky018
		{
			//! Class that communicates with the KY-018 analog photo sensor via an analog-digital sensor.
			/*!
			* This class implements functions to read the sensors data by using an ad converter.
			*/
			class photo
			{
			public:
				//! Default constructor.
				/*!
				* Default constructor.
				*/
				photo() {}

				//! Default destructor.
				/*!
				* Default destructor.
				*/
				~photo() {  }

				//! Opens a device connection and performs basic setup.
				/*!
				* Opens a device connection and performs basic setup.
				* \param[in] ads1115_converter: The analog-digital converter used to access the sensor.
				* \param[in] sensor_multiplexer_mode: The multiplexer setting of the sensor/ad-converter.
				* \param[in] sensor_gain: The gain amplification setting of the sensor/ad-converter.
				* \returns 0 if initializing the device was successful, a negative error value otherwise.
				*/
				int8_t init(std::shared_ptr<ads1115::converter> ads1115_converter, ads1115::ads1115_multiplexer sensor_multiplexer_mode, ads1115::ads1115_gain_amplifier sensor_gain);

				//! Reads the current voltage value via the ad converter and returns it.
				/*!
				* Reads the current voltage value via the ad converter and returns it.
				* \returns the current voltage of the sensor.
				*/
				double get_voltage();

				//! Reads the current resistance value via the ad converter and returns it.
				/*!
				* Reads the current voltage value via the ad converter, converts it to resistance and finally returns it.
				* \returns the current resistance of the sensor.
				*/
				double get_resistance();

			private:
				std::shared_ptr<ads1115::converter> m_ads1115_converter;
				ads1115::ads1115_multiplexer m_sensor_multiplexer_mode;
				ads1115::ads1115_gain_amplifier m_sensor_gain;
				double m_max_voltage = 5.0;
				double m_min_voltage = 0.0;
				std::mutex m_mutex;
			};
		}
	}
}