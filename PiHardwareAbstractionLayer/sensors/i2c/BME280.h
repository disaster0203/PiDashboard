#pragma once

#include <memory>

#include "BME280Definitions.h"
#include "BME280Constants.h"
#include "../../enums/SensorSetting.h"
#include "../../interfaces/ISensor.h"
#include "../../utils/Constants.h"

using namespace hal::utils;

namespace hal
{
	namespace sensors
	{
		namespace i2c
		{
			namespace bme280
			{
				//! Class that communicates with the BME280 sensor (BOSCH) via i2c.
				/*!
				* This class implements various functions to configure the sensor and receive the measured data.
				*/
				class BME280 final : public interfaces::ISensor
				{
				public:
					//! Default constructor.
					/*!
					* Default constructor.
					*/
					BME280() = default;

					/*!
					* Tells the hardware to perform a new measurement. The result will be sent with a callback function.
					* If no callback is registered the measurement cannot be obtained.
					* \param[in] type: The type of measurement that has to do be done.
					* \throws HALException if triggering a temperature measurement fails.
					* \throws HALException if triggering an air pressure measurement fails.
					* \throws HALException if triggering an air humidity measurement fails.
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
					* \throws HALException if setting new oversampling values fails.
					* \throws HALException if setting new filter values fails.
					*/
					void configure(SensorSetting setting, const std::string& configuration) override;

					/*!
					* Returns one specific setting of a sensor.
					* \param[in] setting: The type of setting to return. For this sensor only OVERSAMPLING and FILTER settings can be returned.
					* \returns the current value of the given setting as string.
					* \throws HALException if reading the device settings fails.
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
					* Tries to open the device at the given i2c address in O_RDWR and I2C_SLAVE mode.
					* It also reads and stores the device id and the calibration constants.
					* \param[in] device_reg: The address of the device to open.
					* \returns the id of the connected device.
					* \throws HALException if opening a connection to the device fails (e.g. the device was not found).
					* \throws I2CException if reading the hardware id fails.
					*/
					uint8_t init(uint8_t device_reg = SENSOR_PRIMARY_I2C_REG);

					//! Writes temperature and pressure oversampling settings to the device.
					/*!
					* Writes temperature and pressure oversampling settings to the device.
					* \param desired_settings: selector that defines which oversampling setting should be set
					* (only temperature, only pressure or both).
					* \param[in] settings: A settings object containing the new oversampling settings.
					* \throws I2CException if reading the current oversampling data from the device fails.
					* \throws HALException if manipulating the temperature/pressure bits fails.
					* \throws I2CException if writing the new oversampling data to the device fails.
					*/
					void set_pressure_and_temperature_oversampling(uint8_t desired_settings, SettingsData settings) const;

					//! Writes humidity oversampling settings to the device.
					/*!
					* Writes humidity oversampling settings to the device.
					* \param[in] settings: A settings object containing the new oversampling settings.
					* \throws I2CException if writing the new oversampling data to the device fails.
					* \throws I2CException if reading the current settings data from the device fails.
					* \throws I2CException if writing settings data to the device fails. This is needed to enforce the new
					* humidity oversampling setting take effect.
					*/
					void set_humidity_oversampling(SettingsData settings) const;

					//! Writes filter and standby settings to the device.
					/*!
					* Writes filter and standby settings to the device.
					* \param[in] desired_settings: selector that defines which setting should be set
					* \param[in] settings: A settings object containing the new settings.
					* \throws I2CException if reading the current settings data from the device fails.
					* \throws HALException if manipulating the filter/standby bits fails.
					* \throws I2CException if writing the new settings data to the device fails.
					*/
					void set_filter_and_standby_settings(uint8_t desired_settings, struct SettingsData settings) const;

					//! Changes the current sensor mode.
					/*!
					* After startup the device automatically enters SLEEP mode and delivers one measurement
					* by setting it to FORCED mode. After this measurement the sensor automatically goes back
					* to sleep mode. If NORMAL mode is used the device continuously delivers sensor data.
					* \param[in] mode: The mode to set (SLEEP, FORCED, NORMAL).
					* \throws I2CException if reading the current settings data from the device fails.
					* \throws I2CException if writing the new settings data to the device fails.
					*/
					void set_sensor_mode(OperationMode mode) const;

					//! Returns the current sensor mode.
					/*!
					* After startup the device automatically enters SLEEP mode and delivers one measurement
					* by setting it to FORCED mode. After this measurement the sensor automatically goes back
					* to sleep mode. If NORMAL mode is used the device continuously delivers sensor data.
					* \throws I2CException if reading the current operation mode from the device fails.
					* \returns the current operation mode.
					*/
					OperationMode get_sensor_mode() const;

					//! Writes the given settings to the device.
					/*!
					* Writes the given settings to the device.
					* \param[in] temperature: the new temperature oversampling setting.
					* \param[in] pressure: the new pressure oversampling setting.
					* \param[in] humidity: the new humidity oversampling setting.
					* \param[in] filter: the new filter setting.
					* \param[in] standby: the new standby setting.
					* \throws HALException if reading the current operation mode from the device fails.
					* \throws HALException if reading the current settings from the device fails.
					* \throws HALException if performing a soft reset fails.
					* \throws HALException if applying new settings fails.
					*/
					void set_settings(
						Oversampling temperature,
						Oversampling pressure,
						Oversampling humidity,
						Filter filter,
						StandbyTime standby);

					//! Reads the current settings from the device.
					/*!
					* Reads the current settings from the device.
					* \returns a settings object with the current settings.
					* \throws I2CException if reading the current settings from the device fails.
					*/
					std::shared_ptr<struct SettingsData> get_settings() const;

					//! Performs a soft reset on the device.
					/*!
					* Performs a soft reset on the device.
					* \throws I2CException if writing the soft reset command to the device fails.
					* \throws I2CException if reading the device status fails.
					* \throws I2CException if copying NVM fails.
					*/
					void soft_reset() const;

					//! Measures and returns the current temperature.
					/*!
					* Sets the device to FORCE mode, waits until the chip has done its calculations and receives the raw data.
					* Afterwards the data gets transformed to the final results by compensating it with the corresponding
					* calibration values.
					* \returns The measured temperature.
					* \throws HALException if setting the device mode to FORCED fails.
					* \throws I2CException if reading raw data from the device fails.
					*/
					double get_temperature_data();

					//! Measures and returns the current air pressure.
					/*!
					* Sets the device to FORCE mode, waits until the chip has done its calculations and receives the raw data.
					* Afterwards the data gets transformed to the final results by compensating it with the corresponding
					* calibration values.
					* \returns The measured air pressure.
					* \throws HALException if setting the device mode to FORCED fails.
					* \throws I2CException if reading raw data from the device fails.
					*/
					double get_pressure_data() const;

					//! Measures and returns the current air humidity.
					/*!
					* Sets the device to FORCE mode, waits until the chip has done its calculations and receives the raw data.
					* Afterwards the data gets transformed to the final results by compensating it with the corresponding
					* calibration values.
					* \returns The measured air humidity.
					* \throws HALException if setting the device mode to FORCED fails.
					* \throws I2CException if reading raw data from the device fails.
					*/
					double get_humidity_data() const;

					//! Measures and returns all three sensor values at once.
					/*!
					* Sets the device to FORCE mode, waits until the chip has done its calculations and receives the raw data.
					* Afterwards the data gets transformed to the final results by compensating it with the corresponding
					* calibration values.
					* \param[out] temperature: The measured temperature.
					* \param[out] pressure: The measured air pressure.
					* \param[out] humidity: The measured air humidity.
					* \throws HALException if setting the device mode to FORCED fails.
					* \throws I2CException if reading raw data from the device fails.
					*/
					void get_all_data(double& temperature, double& pressure, double& humidity);

				protected:
					//! Reads the calibration constants for compensation of the three sensor values from the device.
					/*!
					*  Reads the calibration constants for compensation of the three sensor values from the device.
					* \returns The calibration values.
					* \throws I2CException if reading temperature and pressure calibration data from the device fails.
					* \throws I2CException if reading humidity calibration data from the device fails.
					*/
					CalibrationData get_calibration_data() const;

					//! Transforms the raw sensor value buffer into a struct.
					/*!
					*  Transforms the raw sensor value buffer into a struct.
					* \param[in] read_data: The buffer with the raw sensor values.
					* \returns The resulting raw data struct.
					*/
					std::shared_ptr<struct RawData> parse_raw_data(uint8_t* read_data) const noexcept;

					//! Transforms the sensor settings buffer into a struct.
					/*!
					*  Transforms the sensor settings buffer into a struct.
					* \param[in] read_data: The buffer with the settings values.
					* \returns The resulting settings struct.
					* \throws HALException if reading the value of certain bits from byte fails.
					*/
					std::shared_ptr<struct SettingsData> parse_settings(uint8_t* read_data) const;

					//! Simply reads all content from the device at once.
					/*!
					*  Simply reads all content from the device at once. The function should only be used for
					*  debug purposes.
					* \param[out] all_data: A buffer to store the content.
					* \throws I2CException if reading raw data from the device fails.
					*/
					void get_all_raw_data(uint8_t all_data[COMPLETE_FILE_LENGTH]) const;

					//! Calculates the compensated temperature by using temperature calibration constants and a raw value.
					/*!
					*  Calculates the compensated temperature by using temperature calibration constants and a raw value.
					*  The formula used can be found here https://usermanual.wiki/Pdf/BstBme280Ds00110.1570003573
					*  in chapter 4.2.3 (page 23, [01.27.2020]).
					* \param[out] calibration: A object containing the temperature calibration constants.
					* \param[in] raw_temperature: The raw temperature value to compensate.
					* \returns 0 if compensating the temperature value was successful, a negative error value otherwise.
					*/
					static double compensate_temperature(CalibrationData& calibration, int32_t raw_temperature) noexcept;

					//! Calculates the compensated air pressure by using pressure calibration constants and a raw value.
					/*!
					*  Calculates the compensated air pressure by using pressure calibration constants and a raw value.
					*  The formula used can be found here https://usermanual.wiki/Pdf/BstBme280Ds00110.1570003573
					*  in chapter 4.2.3 (page 23, [01.27.2020]).
					* \param[in] calibration: A object containing the pressure calibration constants.
					* \param[in] raw_pressure: The raw pressure value to compensate.
					* \returns 0 if compensating the pressure value was successful, a negative error value otherwise.
					*/
					static double compensate_pressure(CalibrationData calibration, int32_t raw_pressure) noexcept;

					//! Calculates the compensated air humidity by using humidity calibration constants and a raw value.
					/*!
					*  Calculates the compensated air humidity by using humidity calibration constants and a raw value.
					*  The formula used can be found here https://usermanual.wiki/Pdf/BstBme280Ds00110.1570003573
					*  in chapter 4.2.3 (page 23-24, [01.27.2020]).
					* \param[in] calibration: A object containing the humidity calibration constants.
					* \param[in] raw_humidity: The raw humidity value to compensate.
					* \returns 0 if compensating the humidity value was successful, a negative error value otherwise.
					*/
					static double compensate_humidity(struct CalibrationData calibration, int32_t raw_humidity) noexcept;

					//! Calculates the time needed for one complete measurement.
					/*!
					*  Depending on the filter and oversampling settings a measurement takes some time to finish.
					*  This time can be calculated with the formula that can be found here
					*  https://usermanual.wiki/Pdf/BstBme280Ds00110.1570003573 in appendix B, 9.1 (page 51, [01.27.2020]).
					* \returns The calculated time in milliseconds.
					* \throws HALException if reading device settings fails.
					*/
					double calculate_wait_time() const;

					//! Pauses the current process until a measurement finishes.
					/*!
					*  Pauses the current process until a measurement finishes.
					*/
					void sleep_until_ready() const noexcept;

					//! Rewrites the given settings to the device.
					/*!
					*  Rewrites the given settings to the device.
					* \param[in] settings: The settings to reload.
					*/
					void reload_device_settings(SettingsData settings) const;

					//! Compares old and new settings and decides whether the device settings have to be changed.
					/*!
					*  Compares old and new settings and decides whether the device settings have to be changed.
					* \param[in] old_settings: The old/current settings.
					* \param[in] desired_settings: The new/desired settings.
					* \returns true if both settings equal, false otherwise.
					*/
					static bool are_settings_changed(uint8_t old_settings, uint8_t desired_settings) noexcept;

					Device m_device{};
					int m_file_handle{};
					uint8_t m_dev_id{};
					uint8_t m_chip_id{};
				};
			}
		}
	}
}
