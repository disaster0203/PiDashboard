#pragma once

#include <mutex>
#include <cmath>

#include "../../enums/SensorSetting.h"
#include "../../interfaces/ISensor.h"
#include "../../utils/EnumConverter.h"
#include "../../utils/Helper.h"

using namespace hal::utils;

namespace hal
{
	namespace sensors
	{
		namespace analog
		{
			namespace ky018
			{
				//! Class that communicates with the KY-018 analog photo sensor via an analog-digital sensor.
				/*!
				* This class implements functions to read the sensors data by using an ad converter.
				*/
				template <class Converter, typename Multiplexer, typename Gain>
				class KY018 final : public interfaces::ISensor
				{
				public:
					//! Default constructor.
					/*!
					* Default constructor.
					*/
					KY018() = default;

					/*!
					* Tells the hardware to perform a new measurement. The result will be sent with a callback function.
					* If no callback is registered the measurement cannot be obtained.
					* \param[in] type: The type of measurement that has to do be done.
					* \throws HALException if triggering a light measurement fails.
					* \throws HALException if the sensor type is invalid.
					*/
					void trigger_measurement(const SensorType type) override
					{
						for (auto i = m_callbacks[type].begin(); i != m_callbacks[type].end(); ++i)
						{
							if (type == SensorType::LIGHT)
							{
								try
								{
									(*i)->callback(std::to_string(get_resistance()));
								}
								catch (exception::HALException& ex)
								{
									throw exception::HALException("KY018", "trigger_measurement",
																			std::string("Could not trigger light measurement:\n").append(ex.to_string()));
								}
							}
							else
							{
								throw exception::HALException("KY018", "trigger_measurement", "Invalid sensor type.");
							}
						}
					}

					/*!
					* Changes one specific setting of a sensor.
					* \param[in] setting: The type of setting to change. Use \sa { ISensor::available_configurations}
					* to get a list of supported settings for the current sensor.
					* \param[in] configuration: The new value to set for the desired setting. The value has to be converted
					* to string because each sensor needs its own data format and this way the specific conversion can be
					* done easily on each sensor.
					* If changing OVERSAMPLING setting: Configuration has to contain three uint8_t values in the order temperature, pressure and humidity.
					* If changing FILTER setting: Configuration has to contain one uint8_t value.
					* \throws HALException if configuring the devices AD-converter fails.
					*/
					void configure(const SensorSetting setting, const std::string& configuration) override
					{
						try
						{
							if (setting == SensorSetting::COMPARATOR_LATCHING)
							{
								m_converter->set_comparator_latching_setting(EnumConverter::string_to_alert_latching(configuration));
							}
							else if (setting == SensorSetting::COMPARATOR_MODE)
							{
								m_converter->set_comparator_mode_setting(EnumConverter::string_to_comparator_mode(configuration));
							}
							else if (setting == SensorSetting::COMPARATOR_QUEUE)
							{
								m_converter->set_comparator_queue_setting(EnumConverter::string_to_alert_queueing(configuration));
							}
							else if (setting == SensorSetting::DATA_RATE)
							{
								m_converter->set_data_rate_setting(EnumConverter::string_to_data_rate(configuration));
							}
							else if (setting == SensorSetting::GAIN_AMPLIFIER)
							{
								m_converter->set_gain_amplifier_setting(EnumConverter::string_to_gain_amplifier(configuration));
							}
							else if (setting == SensorSetting::THRESHOLD)
							{
								if (Helper::string_contains_separator(configuration))
								{
									std::vector<uint16_t> thresholds;
									Helper::string_to_array(thresholds, configuration);
									if (thresholds.size() == 2)
									{
										m_converter->set_thresholds(thresholds[0], thresholds[1]);
									}
								}
							}
							else if (setting == SensorSetting::MULTIPLEXER)
							{
								m_converter->set_multiplexer_setting(EnumConverter::string_to_multiplexer(configuration));
							}
						}
						catch (exception::HALException& ex)
						{
							throw exception::HALException("KY018", "configure",
																	std::string("Could not change a setting of the devices AD-converter:\n").append(
																		ex.to_string()));
						}
					}

					/*!
					* Returns one specific setting of a sensor.
					* \param[in] setting: The type of setting to return. For this sensor only OVERSAMPLING and FILTER settings can be returned.
					* \returns the current value of the given setting as string.
					* \throws HALException if getting a configuration from the devices AD-converter fails.
					*/
					std::string get_configuration(SensorSetting setting = SensorSetting::BASELINE) override
					{
						try
						{
							return m_converter->get_configuration(setting);
						}
						catch (exception::HALException& ex)
						{
							throw exception::HALException("KY018", "get_configuration",
																	std::string("Could not get a setting from the devices AD-converter:\n").append(
																		ex.to_string()));
						}
					}

					/*!
					* Returns a vector of \sa { HAL::Enums::SensorSetting } that are supported by this sensor.
					* \returns a vector of supported sensor settings.
					*/
					std::vector<SensorSetting> available_configurations() noexcept override
					{
						return m_converter->available_configurations();
					}

					//! Closes a device connection and performs some cleanup.
					/*!
					*  Closes a device connection and performs some cleanup.
					* \throws HALException if the connection to the devices AD-converter could not be closed.
					*/
					void close() override
					{
						try
						{
							m_converter->close();
						}
						catch (exception::HALException& ex)
						{
							throw exception::HALException("KY018", "close",
																	std::string("Could not close the devices AD-converter:\n").append(ex.to_string()));
						}
					}

					//! Opens a device connection and performs basic setup.
					/*!
					* Opens a device connection and performs basic setup.
					* \param[in] converter: The analog-digital converter used to access the sensor.
					* \param[in] sensor_multiplexer_mode: The multiplexer setting of the sensor/ad-converter.
					* \param[in] sensor_gain: The gain amplification setting of the sensor/ad-converter.
					* \throws HALException if the converter is not yet initialized and could not be setup.
					*/
					void init(std::shared_ptr<Converter> converter, Multiplexer sensor_multiplexer_mode, Gain sensor_gain)
					{
						m_converter = converter;
						m_sensor_multiplexer_mode = sensor_multiplexer_mode;
						m_sensor_gain = sensor_gain;

						// If the ADS1115 device is not yet fully setup, initialize it
						uint8_t try_count = 0;
						m_mutex.lock();
						while (!m_converter->is_initialized())
						{
							m_converter->init();
							try_count++;
							if (try_count == 5)
							{
								m_mutex.unlock();
								throw exception::HALException("KY018", "init", "Could not initialize analog digital converter (ADS1115).");
							}
						}
						m_mutex.unlock();
					}

					//! Reads the current voltage value via the ad converter and returns it.
					/*!
					* Reads the current voltage value via the ad converter and returns it.
					* \returns the current voltage of the sensor.
					* \throws HALException if getting the current converted value fails.
					*/
					double get_voltage()
					{
						try
						{
							m_mutex.lock(); // Lock the shared ADS1115 pointer to avoid conflicts (we need to change multiplexer and gain)
							m_converter->set_multiplexer_setting(m_sensor_multiplexer_mode); // Set multiplexer
							m_converter->set_gain_amplifier_setting(m_sensor_gain); // Set gain amplifier
							m_converter->start_single_conversion(); // Trigger new conversion
							auto voltage = m_converter->get_converted_data(); // Receive the new voltage data from the ADS1115
							m_mutex.unlock(); // Unlock ADS1115 pointer

							// Clamp voltage
							return std::fmaxl(std::fminl(m_max_voltage, voltage), m_min_voltage);
						}
						catch (exception::HALException& ex)
						{
							throw exception::HALException("KY018", "get_voltage",
																	std::string("Could not get a voltage value from the devices AD-converter:\n").append(
																		ex.to_string()));
						}
					}

					//! Reads the current resistance value via the ad converter and returns it.
					/*!
					* Reads the current voltage value via the ad converter, converts it to resistance and finally returns it.
					* \returns the current resistance of the sensor.
					* \throws HALException if getting the current voltage value fails.
					*/
					double get_resistance()
					{
						try
						{
							const auto voltage = get_voltage();
							return 10000 * voltage / (m_max_voltage - voltage);
						}
						catch (exception::HALException& ex)
						{
							throw exception::HALException("KY018", "get_resistance",
																	std::string("Could not get a voltage value from the devices AD-converter:\n").append(
																		ex.to_string()));
						}
					}

				private:
					std::shared_ptr<Converter> m_converter;
					Multiplexer m_sensor_multiplexer_mode;
					Gain m_sensor_gain;
					double m_max_voltage = 5.0;
					double m_min_voltage = 0.0;
					std::mutex m_mutex;
				};
			}
		}
	}
}
