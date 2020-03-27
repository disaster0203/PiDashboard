#pragma once
#include <string>
#include <vector>

#include "../../enums/SensorSetting.h"
#include "../../interfaces/ISensor.h"

namespace hal
{
	namespace sensors
	{
		namespace digital
		{
			namespace am312
			{
				static constexpr int8_t OK = 0;
				static constexpr int8_t COMMUNICATION_FAIL = -4;

				//! Class that communicates via GPIO with the AM312 sensor to detect motions.
				/*!
				* Class that communicates via GPIO with the AM312 sensor to detect motions. If a motion is detected,
				* a callback function is called.
				*/
				class AM312 final : public interfaces::ISensor
				{
				public:
					//! Default constructor.
					/*!
					* Default constructor.
					*/
					AM312() = default;

					/*!
					* Tells the hardware to perform a new measurement. The result will be sent with a callback function.
					* If no callback is registered the measurement cannot be obtained.
					* \param[in] type: The type of measurement that has to do be done.
					* \throws HALException if triggering a motion measurement fails.
					* \throws HALException if the sensor type is invalid.
					*/
					void trigger_measurement(SensorType type) override;

					/*!
					* Changes one specific setting of a sensor.
					* \param[in] setting: The type of setting to change. Use \sa { ISensor::available_configurations}
					* to get a list of supported settings for the current sensor.
					* \param[in] configuration: The new value to set for the desired setting. The value has to be converted
					* to string because each sensor needs its own data format and this way the specific conversion can be
					* done easily on each sensor.
					* If changing OVERSAMPLING setting: Configuration has to contain three uint8_t values in the order temperature, pressure and humidity.
					* If changing FILTER setting: Configuration has to contain one uint8_t value.
					*/
					void configure(SensorSetting setting, const std::string& configuration) override;

					/*!
					* Returns one specific setting of a sensor.
					* \param[in] setting: The type of setting to return. For this sensor only OVERSAMPLING and FILTER settings can be returned.
					* \returns the current value of the given setting as string.
					*/
					std::string get_configuration(SensorSetting setting = SensorSetting::BASELINE) override;

					/*!
					* Returns a vector of \sa { HAL::Enums::SensorSetting } that are supported by this sensor.
					* \returns a vector of supported sensor settings.
					*/
					std::vector<SensorSetting> available_configurations() noexcept override;

					//! Closes a device connection and performs some cleanup.
					/*!
					*  Closes a device connection and performs some cleanup.
					* \throws HALException if the device connection could not be closed.
					*/
					void close() override;

					//! Opens a device connection and performs basic setup.
					/*!
					* Tries to open the device at the given GPIO pin in INPUT mode.
					* It also starts the internal sensor loop that continuously reads the sensor data.
					* \param[in] pin: The GPIO pin to use. Use WiringPi simplified pin numbering (http://wiringpi.com/pins/).
					* \throws HALException if WiringPi could not be initialized.
					*/
					void init(uint8_t pin);

				private:
					uint8_t m_pin{};
				};
			}
		}
	}
}
