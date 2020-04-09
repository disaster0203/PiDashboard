#pragma once

#include <mutex>
#include <cmath>
#include <unistd.h>

#include "../../enums/SensorSetting.h"
#include "../../interfaces/ISensor.h"
#include "../../utils/EnumConverter.h"
#include "../../utils/Helper.h"
#include "../i2c/ADS1115.h"

using namespace hal::utils;

namespace hal
{
	namespace sensors
	{
		namespace analog
		{
			namespace mics6814
			{
				//! Class that communicates with the MICS-6814 analog gas sensor via an analog-digital converter.
				/*!
				* This class implements functions to read the sensors data by using an AD converter.
				*/
				class MICS6814 final : public interfaces::ISensor
				{
				public:
					//! Default constructor.
					/*!
					* Default constructor.
					*/
					MICS6814() = default;

					/*!
					* Tells the hardware to perform a new measurement. The result will be sent with a callback function.
					* If no callback is registered the measurement cannot be obtained.
					* \param[in] type: The type of measurement that has to do be done.
					* \throws HALException if triggering a CO measurement fails.
					* \throws HALException if triggering a NH3 measurement fails.
					* \throws HALException if triggering a NO2 measurement fails.
					* \throws HALException if the sensor type is invalid.
					*/
					void trigger_measurement(const SensorType type) override;
					
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
					void configure(const SensorSetting setting, const std::string& configuration) override;

					/*!
					* Returns one specific setting of a sensor.
					* \param[in] setting: The type of setting to return. For this sensor only OVERSAMPLING and FILTER settings can be returned.
					* \returns the current value of the given setting as string.
					* \throws HALException if getting a configuration from the devices AD-converter fails.
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
					* \throws HALException if the connection to the devices AD-converter could not be closed.
					*/
					void close() override;
					

					//! Opens a device connection and performs basic setup.
					/*!
					* Opens a device connection and performs basic setup.
					* \param[in] converter: The analog-digital converter used to access the sensor.
					* \param[in] sensor_multiplexer_mode: The multiplexer setting of the sensor/ad-converter.
					* \param[in] sensor_gain: The gain amplification setting of the sensor/ad-converter.
					* \throws HALException if the converter is not yet initialized and could not be setup.
					*/
					void init(interfaces::IConverter* converter, uint8_t analog_pin);
					

					//! Reads the current voltage value via the ad converter and returns it.
					/*!
					* Reads the current voltage value via the ad converter and returns it.
					* \returns the current voltage of the sensor.
					* \throws HALException if getting the current converted value fails.
					*/
					double get_voltage();
					

					//! Reads the current resistance value via the ad converter and returns it.
					/*!
					* Reads the current voltage value via the ad converter, converts it to resistance and finally returns it.
					* \returns the current resistance of the sensor.
					* \throws HALException if getting the current voltage value fails.
					*/
					double get_resistance();
					

					//! Reads the current carbon monoxide (CO) value via the ad converter and returns it.
					/*!
					* Reads the current carbon monoxide (CO) value via the ad converter and returns it.
					* \returns the current carbon monoxide (CO) value of the sensor.
					* \throws HALException if getting the current carbon monoxide (CO) value fails.
					*/
					double get_carbon_monoxide_co();
					

					//! Reads the current nitrogen dioxide (NO2) value via the ad converter and returns it.
					/*!
					* Reads the current nitrogen dioxide (NO2) value via the ad converter and returns it.
					* \returns the current nitrogen dioxide (NO2) value of the sensor.
					* \throws HALException if getting the current nitrogen dioxide (NO2) value fails.
					*/
					double get_nitrogen_dioxide_no2();
					

					//! Reads the current ammoniac (NH3) value via the ad converter and returns it.
					/*!
					* Reads the current ammoniac (NH3) value via the ad converter and returns it.
					* \returns the current ammoniac (NH3) value of the sensor.
					* \throws HALException if getting the current ammoniac (NH3) value fails.
					*/
					double get_ammoniac_nh3();
					

					//! Reads the current propane (C3H8) value via the ad converter and returns it.
					/*!
					* Reads the current propane (C3H8) value via the ad converter and returns it.
					* \returns the current propane (C3H8) value of the sensor.
					* \throws HALException if getting the current propane (C3H8) value fails.
					*/
					double get_propane_c3h8();
					

					//! Reads the current butane (C4H10) value via the ad converter and returns it.
					/*!
					* Reads the current butane (C4H10) value via the ad converter and returns it.
					* \returns the current butane (C4H10) value of the sensor.
					* \throws HALException if getting the current butane (C4H10) value fails.
					*/
					double get_butane_c4h10();
					

					//! Reads the current methane (CH4) value via the ad converter and returns it.
					/*!
					* Reads the current methane (CH4) value via the ad converter and returns it.
					* \returns the current methane (CH4) value of the sensor.
					* \throws HALException if getting the current methane (CH4) value fails.
					*/
					double get_methane_ch4();
					

					//! Reads the current hydrogen (H2) value via the ad converter and returns it.
					/*!
					* Reads the current hydrogen (H2) value via the ad converter and returns it.
					* \returns the current hydrogen (H2) value of the sensor.
					* \throws HALException if getting the current hydrogen (H2) value fails.
					*/
					double get_hydrogen_h2();
					

					//! Reads the current ethanol (C2H5OH) value via the ad converter and returns it.
					/*!
					* Reads the current ethanol (C2H5OH) value via the ad converter and returns it.
					* \returns the current ethanol (C2H5OH) value of the sensor.
					* \throws HALException if getting the current ethanol (C2H5OH) value fails.
					*/
					double get_ethanol_c2h5oh();
					

					//! Gets the current carbon monoxide (CO) calibration value.
					/*!
					* Gets the current carbon monoxide (CO) calibration value.
					* \returns the current carbon monoxide (CO) calibration value.
					*/
					double get_carbon_monoxide_co_calibration_voltage()
					{
						return m_co_clean_air;
					}

					//! Gets the current nitrogen dioxide (NO2) calibration value.
					/*!
					* Gets the current nitrogen dioxide (NO2) calibration value.
					* \returns the current nitrogen dioxide (NO2) calibration value.
					*/
					double get_nitrogen_dioxide_no2_calibration_voltage()
					{
						return m_no2_clean_air;
					}

					//! Gets the current ammoniac (NH3) calibration value.
					/*!
					* Gets the current ammoniac (NH3) calibration value.
					* \returns the current ammoniac (NH3) calibration value.
					*/
					double get_ammoniac_nh3_calibration_voltage()
					{
						return m_nh3_clean_air;
					}

					//! Gets the current propane (C3H8) calibration value.
					/*!
					* Gets the current propane (C3H8) calibration value. The value
					* equals the ammoniac calibration value.
					* \returns the current propane (C3H8) calibration value.
					*/
					double get_propane_c3h8_calibration_voltage()
					{
						return get_ammoniac_nh3_calibration_voltage();
					}

					//! Gets the current butane (C4H10) calibration value.
					/*!
					* Gets the current butane (C4H10) calibration value. The value
					* equals the ammoniac calibration value.
					* \returns the current butane (C4H10) calibration value.
					*/
					double get_butane_c4h10_calibration_voltage()
					{
						return get_ammoniac_nh3_calibration_voltage();
					}

					//! Gets the current methane (CH4) calibration value.
					/*!
					* Gets the current methane (CH4) calibration value. The value
					* equals the carbon monoxide calibration value.
					* \returns the current methane (CH4) calibration value.
					*/
					double get_methane_ch4_calibration_voltage()
					{
						return get_carbon_monoxide_co_calibration_voltage();
					}

					//! Gets the current hydrogen (H2) calibration value.
					/*!
					* Gets the current hydrogen (H2) calibration value. The value
					* equals the carbon monoxide calibration value.
					* \returns the current hydrogen (H2) calibration value.
					*/
					double get_hydrogen_h2_calibration_voltage()
					{
						return get_carbon_monoxide_co_calibration_voltage();
					}

					//! Gets the current ethanol (C3H5OH) calibration value.
					/*!
					* Gets the current ethanol (C3H5OH) calibration value. The value
					* equals the carbon monoxide calibration value.
					* \returns the current ethanol (C3H5OH) calibration value.
					*/
					double get_ethanol_c3h5oh_calibration_voltage()
					{
						return get_carbon_monoxide_co_calibration_voltage();
					}

					//! Sets the carbon monoxide (CO) calibration value.
					/*!
					* Sets the carbon monoxide (CO) calibration value.
					* \param[in] value: The carbon monoxide (CO) calibration value.
					*/
					void set_carbon_monoxide_co_calibration_voltage(double value)
					{
						m_co_clean_air = value;
					}

					//! Sets the nitrogen dioxide (NO2) calibration value.
					/*!
					* Sets the nitrogen dioxide (NO2) calibration value.
					* \param[in] value: The nitrogen dioxide (NO2) calibration value.
					*/
					void set_nitrogen_dioxide_no2_calibration_voltage(double value)
					{
						m_no2_clean_air = value;
					}

					//! Sets the ammoniac (NH3) calibration value.
					/*!
					* Sets the ammoniac (NH3) calibration value.
					* \param[in] value: The ammoniac (NH3) calibration value.
					*/
					void set_ammoniac_nh3_calibration_voltage(double value)
					{
						m_nh3_clean_air = value;
					}

					//! Sets the propane (C3H8) calibration value.
					/*!
					* Sets the propane (C3H8) calibration value. The value
					* equals the ammoniac calibration value.
					* \param[in] value: The propane (C3H8) calibration value.
					*/
					void set_propane_c3h8_calibration_voltage(double value)
					{
						set_ammoniac_nh3_calibration_voltage(value);
					}

					//! Sets the butane (C4H10) calibration value.
					/*!
					* Sets the butane (C4H10) calibration value. The value
					* equals the ammoniac calibration value.
					* \param[in] value: The butane (C4H10) calibration value.
					*/
					void set_butane_c4h10_calibration_voltage(double value)
					{
						set_ammoniac_nh3_calibration_voltage(value);
					}

					//! Sets the methane (CH4) calibration value.
					/*!
					* Sets the methane (CH4) calibration value. The value
					* equals the carbon monoxide calibration value.
					* \param[in] value: The methane (CH4) calibration value.
					*/
					void set_methane_ch4_calibration_voltage(double value)
					{
						set_carbon_monoxide_co_calibration_voltage(value);
					}

					//! Sets the hydrogen (H2) calibration value.
					/*!
					* Sets the hydrogen (H2) calibration value. The value
					* equals the carbon monoxide calibration value.
					* \param[in] value: The hydrogen (H2) calibration value.
					*/
					void set_hydrogen_h2_calibration_voltage(double value)
					{
						set_carbon_monoxide_co_calibration_voltage(value);
					}

					//! Sets the ethanol (C3H5OH) calibration value.
					/*!
					* Sets the ethanol (C3H5OH) calibration value. The value
					* equals the carbon monoxide calibration value.
					* \param[in] value: The ethanol (C3H5OH) calibration value.
					*/
					void set_ethanol_c3h5oh_calibration_voltage(double value)
					{
						set_carbon_monoxide_co_calibration_voltage(value);
					}

					//! Performs a recalibration of the device.
					/*!
					* Performs a recalibration of the device. Take care that the air is as fresh and
					* clean as possible. This process may take several minutes.
					* \param[in] type: The gas type to recalibrate.
					* \throws HALException if the sensor type is not a valid gas.
					*/
					void calibrate_sensor(SensorType type)
					{
						int new_value, temp_value;
						int count;
						int max_delta = 0.2;

						while (1)
						{
							new_value = get_resistance();
							count = 0;

							// read 20 times the current values
							for (auto i = 0; i < 20; i++)
							{
								temp_value = get_resistance();
								if (new_value - temp_value > max_delta || temp_value - new_value > max_delta)
								{
									count++;
								}

								// if more than 5 time difference in original reading
								if (count > 5)  break;

								// wait 1 second
								usleep(1);
							}
							// if NOT more than 5 times a difference was detected for the last 20 reading/seconds
							if (count <= 5) break;
							usleep(200);
						}

						switch (type)
						{
						case SensorType::CARBON_MONOXIDE_CO:
						case SensorType::METHANE_CH4:
						case SensorType::HYDROGEN_H2:
						case SensorType::ETHANOL_C2H5OH:
							m_co_clean_air = new_value;
							break;
						case SensorType::NITROGEN_DIOXIDE_NO2:
							m_no2_clean_air = new_value;
							break;
						case SensorType::AMMONIAC_NH3:
						case SensorType::PROPANE_C3H8:
						case SensorType::BUTANE_C4H10:
							m_nh3_clean_air = new_value;
							break;
						default:
							throw exception::HALException("MICS6814", "recalibrate_sensor", "Invalid sensor type:\n");
						}
					}

				protected:
					interfaces::IConverter* m_converter;
					uint8_t m_analog_pin;
					double m_max_voltage = 5.0;
					double m_min_voltage = 0.0;
					std::mutex m_mutex;
					double m_co_clean_air = 0;
					double m_no2_clean_air = 0;
					double m_nh3_clean_air = 0;
				};
			}
		}
	}
}