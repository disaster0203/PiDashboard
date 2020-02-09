#pragma once
#include <functional>
#include <iostream>
#include <string>
#include <thread>
#include <vector>
#include <wiringPi.h>

namespace driver
{
	namespace sensors
	{
		namespace am312
		{
			static constexpr const int8_t OK = 0;
			static constexpr const int8_t COMMUNICATION_FAIL = -4;

			//! Class that communicates via GPIO with the AM312 sensor to detect motions.
			/*!
			* Class that communicates via GPIO with the AM312 sensor to detect motions. If a motion is detected,
			* a callback function is called.
			*/
			class motion
			{
			public:
				//! Default constructor.
				/*!
				* Default constructor.
				*/
				motion() {}

				//! Default destructor.
				/*!
				* Default destructor.
				*/
				~motion() {}

				//! Opens a device connection and performs basic setup.
				/*!
				* Tries to open the device at the given gpio pin in INPUT mode.
				* It also starts the internal sensor loop that continuously reads the sensor data.
				* \param[in] pin: The GPIO pin to use. Use WiringPi simplified pin numbering (http://wiringpi.com/pins/).
				* \param[in] on_motion: Callback that will be called if the sensor detected a motion.
				*/
				int8_t init(uint8_t pin, std::function<void()> on_motion);

				//! Closes a device connection.
				/*!
				* Closes a device connection.
				*/
				void close();

			private:
				//! The internal loop that continuously reads sensor data.
				/*!
				* The internal loop that continuously reads sensor data.
				*/
				void sensor_loop();

				uint8_t m_pin;
				std::function<void()> m_on_motion;
				std::thread* m_thread;
				bool m_stop;
			};
		}
	}
}