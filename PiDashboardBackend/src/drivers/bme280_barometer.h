#pragma once

#include "../manager/i2c_manager.h"
#include "bme280_barometer_definitions.h"
#include "bme280_barometer_constants.h"

#include <stdexcept>
#include <cerrno>
#include <cstring>
#include <functional>

namespace driver
{
	namespace sensors
	{
		namespace bme280
		{
			//! Class that communicates with the BME280 sensor (BOSCH) via I2C.
			/*!
			* This class implements various functions to configure the sensor and receive the measured data.
			*/
			class barometer
			{
			public:
				//! Default constructor.
				/*!
				* Default constructor.
				*/
				barometer() {}

				//! Default destructor.
				/*!
				* Default destructor.
				*/
				~barometer() {  }

				//! Opens a device connection and performs basic setup.
				/*!
				* Tries to open the device at the given i2c address in O_RDWR and I2C_SLAVE mode.
				* It also reads and stores the device id and the calibration constants.
				* \param[in] device_address: The address of the device to open.
				* \returns 0 if initializing the device was successful, a negative error value otherwise.
				*/
				int8_t init(uint8_t device_address = SENSOR_PRIMARY_I2C_ADDR,
					std::function<int8_t(int, uint8_t, uint8_t*, uint16_t)> read_function = manager::i2c_manager::read_from_device,
					std::function<int8_t(int, uint8_t, const uint8_t*, uint16_t)> write_function = manager::i2c_manager::write_to_device,
					std::function<int8_t(const char*, uint8_t, int&)> open_device_function = manager::i2c_manager::open_device,
					std::function<int8_t(int&)> close_device_function = manager::i2c_manager::close_device);

				//! Closes a device connection and performs some cleanup.
				/*!
				*  Closes a device connection and performs some cleanup.
				* \returns 0 if closing the device was successful, a negative error value otherwise.
				*/
				int8_t close();

				//! Writes temperature and pressure oversampling settings to the device.
				/*!
				* Writes temperature and pressure oversampling settings to the device.
				* \param desired_settings: selector that defines which oversampling setting should be set
				* (only temperature, only pressure or both).
				* \param[in] settings: A settings object containing the new oversampling settings.
				* \returns 0 if writing oversampling settings was successful, a negative error value otherwise.
				*/
				int8_t set_pressure_and_temperature_oversampling(uint8_t desired_settings, struct settings_data* settings);

				//! Writes humidity oversampling settings to the device.
				/*!
				* Writes humidity oversampling settings to the device.
				* \param[in] settings: A settings object containing the new oversampling settings.
				* \returns 0 if writing oversampling settings was successful, a negative error value otherwise.
				*/
				int8_t set_humidity_oversampling(struct settings_data* settings);

				//! Writes filter and standby settings to the device.
				/*!
				* Writes filter and standby settings to the device.
				* \param[in] desired_settings: selector that defines which setting should be set
				* \param[in] settings: A settings object containing the new settings.
				* \returns 0 if writing settings was successful, a negative error value otherwise.
				*/
				int8_t set_filter_and_standby_settings(uint8_t desired_settings, struct settings_data* settings);

				//! Changes the current sensor mode.
				/*!
				* After startup the device automatically enters SLEEP mode and delivers one measurement
				* by setting it to FORCED mode. After this measurement the sensor automatically goes back
				* to sleep mode. If NORMAL mode is used the device continuously delivers sensor data.
				* \param[in] mode: The mode to set (SLEEP, FORCED, NORMAL).
				* \returns 0 if changing the mode was successful (or unnecesarry), a negative error value otherwise.
				*/
				int8_t set_sensor_mode(enum bme280_mode mode);

				//! Returns the current sensor mode.
				/*!
				* After startup the device automatically enters SLEEP mode and delivers one measurement
				* by setting it to FORCED mode. After this measurement the sensor automatically goes back
				* to sleep mode. If NORMAL mode is used the device continuously delivers sensor data.
				* \param[out] mode: The current mode of the device.
				* \returns 0 if returning the mode was successful, a negative error value otherwise.
				*/
				int8_t get_sensor_mode(enum bme280_mode& mode);

				//! Writes the given settings to the device.
				/*!
				* Writes the given settings to the device.
				* \param[in] temperature: the new temperature oversampling setting.
				* \param[in] pressure: the new pressure oversampling setting.
				* \param[in] humidity: the new humidity oversampling setting.
				* \param[in] filter: the new filter setting.
				* \param[in] standby: the new standby setting.
				* \returns 0 if writing the settings was successful, a negative error value otherwise.
				*/
				int8_t set_settings(enum bme280_oversampling temperature, enum bme280_oversampling pressure, enum bme280_oversampling humidity, enum bme280_filter filter, enum bme280_standby_time standby);

				//! Reads the current settings from the device.
				/*!
				* Reads the current settings from the device.
				* \param[out] settings: A settings object into which the current settings are written.
				* \returns 0 if reading the settings was successful, a negative error value otherwise.
				*/
				int8_t get_settings(struct settings_data* settings);

				//! Performs a soft reset on the device.
				/*!
				* Performs a soft reset on the device.
				* \returns 0 if resetting the device was successful, a negative error value otherwise.
				*/
				int8_t soft_reset();

				//! Measures and returns the current temperature.
				/*!
				* Sets the device to FORCE mode, waits until the chip has done its calculations and receives the raw data.
				* Afterwards the data gets transfromed to the final results by compensating it with the corresponding
				* calibration values.
				* \param[out] temperature: The measured temperature.
				* \returns 0 if measuring the temperature was successful, a negative error value otherwise.
				*/
				int8_t get_temperature_data(double& temperature);

				//! Measures and returns the current air pressure.
				/*!
				* Sets the device to FORCE mode, waits until the chip has done its calculations and receives the raw data.
				* Afterwards the data gets transfromed to the final results by compensating it with the corresponding
				* calibration values.
				* \param[out] pressure: The measured air pressure.
				* \returns 0 if measuring the air pressure was successful, a negative error value otherwise.
				*/
				int8_t get_pressure_data(double& pressure);

				//! Measures and returns the current air humidity.
				/*!
				* Sets the device to FORCE mode, waits until the chip has done its calculations and receives the raw data.
				* Afterwards the data gets transfromed to the final results by compensating it with the corresponding
				* calibration values.
				* \param[out] humidity: The measured air humidity.
				* \returns 0 if measuring the air humidity was successful, a negative error value otherwise.
				*/
				int8_t get_humidity_data(double& humidity);

				//! Measures and returns all three sensor values at once.
				/*!
				* Sets the device to FORCE mode, waits until the chip has done its calculations and receives the raw data.
				* Afterwards the data gets transfromed to the final results by compensating it with the corresponding
				* calibration values.
				* \param[out] temperature: The measured temperature.
				* \param[out] pressure: The measured air pressure.
				* \param[out] humidity: The measured air humidity.
				* \returns 0 if measuring the sensor values was successful, a negative error value otherwise.
				*/
				int8_t get_all_data(double& temperature, double& pressure, double& humidity);

			private:
				//! Compensates raw temperature data to the final temperature.
				/*!
				*  Compensates raw temperature data to the final temperature.
				* \param[in] raw_data: A object containing the raw temperature value.
				* \returns the compensated temperature in degree celsius (range: -40°C - 85°C).
				*/
				double get_temperature_data(struct raw_data* raw_data);

				//! Compensates raw pressure data to the final air pressure.
				/*!
				*  Compensates raw pressure data to the final air pressure.
				* \param[in] raw_data: A object containing the raw pressure value.
				* \returns the compensated pressure in hPa (range: 300hPA - 1100hPA).
				*/
				double get_pressure_data(struct raw_data* raw_data);

				//! Compensates raw humidity data to the final air humidity.
				/*!
				*  Compensates raw humidity data to the final air humidity.
				* \param[in] raw_data: A object containing the raw humidity value.
				* \returns the compensated humidity in % (range: 0% - 100%).
				*/
				double get_humidity_data(struct raw_data* raw_data);

				//! Reads the calibration constants for compensation of the three sensor values from the device.
				/*!
				*  Reads the calibration constants for compensation of the three sensor values from the device.
				* \param[out] calibration_data: The calibration values.
				* \returns 0 if reading the calibration values was successful, a negative error value otherwise.
				*/
				int8_t get_calibration_data(struct calibration_data& calibration_data);

				//! Transforms the raw sensor value buffer into a struct.
				/*!
				*  Transforms the raw sensor value buffer into a struct.
				* \param[in] read_data: The buffer with the raw sensor values.
				* \param[out] raw_data: The resulting raw data struct.
				* \returns 0 if transforming the raw values was successful, a negative error value otherwise.
				*/
				int8_t parse_raw_data(uint8_t* read_data, struct raw_data* raw_data);

				//! Transforms the sensor settings buffer into a struct.
				/*!
				*  Transforms the sensor settings buffer into a struct.
				* \param[in] read_data: The buffer with the settings values.
				* \param[out] settings: The resulting settings struct.
				* \returns 0 if transforming the settings values was successful, a negative error value otherwise.
				*/
				void parse_settings(uint8_t* read_data, struct settings_data* settings);

				//! Calculates the compensated temperature by using temperature calibration constants and a raw value.
				/*!
				*  Calculates the compensated temperature by using temperature calibration constants and a raw value.
				*  The formula used can be found here https://usermanual.wiki/Pdf/BstBme280Ds00110.1570003573
				*  in chapter 4.2.3 (page 23, [01.27.2020]).
				* \param[in] calibration: A object containing the temperature calibration constants.
				* \param[in] raw_temperature: The raw temperature value to compensate.
				* \returns 0 if compensating the temperature value was successful, a negative error value otherwise.
				*/
				double compensate_temperature(struct calibration_data* calibration, int32_t raw_temperature);

				//! Calculates the compensated air pressure by using pressure calibration constants and a raw value.
				/*!
				*  Calculates the compensated air pressure by using pressure calibration constants and a raw value.
				*  The formula used can be found here https://usermanual.wiki/Pdf/BstBme280Ds00110.1570003573
				*  in chapter 4.2.3 (page 23, [01.27.2020]).
				* \param[in] calibration: A object containing the pressure calibration constants.
				* \param[in] raw_pressure: The raw pressure value to compensate.
				* \returns 0 if compensating the pressure value was successful, a negative error value otherwise.
				*/
				double compensate_pressure(struct calibration_data* calibration, int32_t raw_pressure);

				//! Calculates the compensated air humidity by using humidity calibration constants and a raw value.
				/*!
				*  Calculates the compensated air humidity by using humidity calibration constants and a raw value.
				*  The formula used can be found here https://usermanual.wiki/Pdf/BstBme280Ds00110.1570003573
				*  in chapter 4.2.3 (page 23-24, [01.27.2020]).
				* \param[in] calibration: A object containing the humidity calibration constants.
				* \param[in] raw_humidity: The raw humidity value to compensate.
				* \returns 0 if compensating the humidity value was successful, a negative error value otherwise.
				*/
				double compensate_humidity(struct calibration_data* calibration, int32_t raw_humidity);

				//! Calculates the time needed for one complete measurement.
				/*!
				*  Depending on the filter and oversampling settings a measurement takes some time to finish.
				*  This time can be calculated with the formula that can be found here
				*  https://usermanual.wiki/Pdf/BstBme280Ds00110.1570003573 in appendix B, 9.1 (page 51, [01.27.2020]).
				* \param[out] time: The calculated time in milliseconds.
				* \returns 0 if calculating the time was successful, a negative error value otherwise.
				*/
				int8_t calculate_wait_time(double& time);

				//! Pauses the current process until a measurement finishes.
				/*!
				*  Pauses the current process until a measurement finishes.
				*/
				void sleep_until_ready();

				//! Rewrites the given settings to the device.
				/*!
				*  Rewrites the given settings to the device.
				* \param[in] settings: The settings to reload.
				* \returns 0 if reloading the settings was successful, a negative error value otherwise.
				*/
				int8_t reload_device_settings(struct settings_data* settings);

				//! Compares old and new settings and decides whether the device settings have to be changed.
				/*!
				*  Compares old and new settings and decides whether the device settings have to be changed.
				* \param[in] old_settings: The old/current settings.
				* \param[in] desired_settings: The new/desired settings.
				* \returns true if both settings equal, false otherwise.
				*/
				bool are_settings_changed(uint8_t old_settings, uint8_t desired_settings);

				//! Checks if the given pointer is null.
				/*!
				*  Checks if the given pointer is null.
				* \param[in] pointer: The pointer to check.
				* \returns 0 if the pointer is not null and -1 if the pointer is null.
				*/
				int8_t null_check(void* pointer);

				//! Simply reads all content from the device at once.
				/*!
				*  Simply reads all content from the device at once. The function should only be used for
				*  debug purposes.
				* \param[out] all_data: A buffer to store the content.
				* \returns 0 if reading all data was successful, a negative error value otherwise.
				*/
				int8_t get_all_raw_data(uint8_t* all_data);

				bme280_device m_device;
				int m_file_handle;
				std::function<int8_t(const char*, uint8_t, int&)> m_open_device_function;
				std::function<int8_t(int&)> m_close_device_function;
				std::function<int8_t(int, uint8_t, uint8_t*, uint16_t)> m_read_function;
				std::function<int8_t(int, uint8_t, const uint8_t*, uint16_t)> m_write_function;
			};
		}
	}
}