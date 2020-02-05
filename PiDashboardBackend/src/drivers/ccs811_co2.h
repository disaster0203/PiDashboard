#pragma once
#include <cstdint>
#include <functional>
#include <memory>
#include <string>
#include <wiringPi.h>
#include <thread>
#include <vector>

#include "sensor_base.h"
#include "ccs811_co2_constants.h"
#include "ccs811_co2_definitions.h"
#include "../manager/i2c_manager.h"

namespace driver
{
	namespace sensors
	{
		namespace ccs811
		{
			//! Class that communicates with the CCS811 sensor (AMS) via I2C.
			/*!
			* This class implements various functions to configure the sensor and receive the measured data.
			*/
			class co2 : sensor_base
			{
			protected:
				//! Opens a device connection and performs basic setup.
				/*!
				* Tries to open the device at the given i2c address in O_RDWR and I2C_SLAVE mode.
				* It also reads and stores the device id and the calibration constants.
				* \param[in] device_reg: The address of the device to open.
				* \param[in] read_function: Function pointer to the function that does i2c read operations.
				* \param[in] write_function: Function pointer to the function that does i2c write operations.
				* \param[in] open_device_function: Function pointer to the function that opens an i2c connection.
				* \param[in] close_device_function: Function pointer to the function that closes an i2c connection.
				* \returns 0 if initializing the device was successful, a negative error value otherwise.
				*/
				int8_t init(uint8_t device_reg = SENSOR_PRIMARY_I2C_REG,
					std::function<int8_t(int, uint8_t, uint8_t*, uint16_t)> read_function = manager::i2c_manager::read_from_device,
					std::function<int8_t(int, uint8_t, const uint8_t*, uint16_t)> write_function = manager::i2c_manager::write_to_device,
					std::function<int8_t(const std::string, uint8_t, int&)> open_device_function = manager::i2c_manager::open_device,
					std::function<int8_t(int&)> close_device_function = manager::i2c_manager::close_device);

			public:
				//! Default constructor.
				/*!
				* Default constructor.
				*/
				co2() {}

				//! Default destructor.
				/*!
				* Default destructor.
				*/
				~co2() {  }


				//! Opens a device connection and performs basic setup.
				/*!
				* Tries to open the device at the given i2c address in O_RDWR and I2C_SLAVE mode.
				* It also reads and stores the device id and the calibration constants.
				* \param[in] use_power_safe_mode: Whether the devices processor should be put to sleep mode between i2c requests or not.
				* \param[in] wake_gpio_pin_nr: The GPIO pin number of the nWAKE pin that is used to put the device to sleep and wake it up.
				* \param[in] int_gpio_pin_nr: The GPIO pin number of the INT pin that is used to notify if new data is available.
				* \param[in] data_callback: A callback function that gets called if the device is operated in Interrupt mode and new
				* data gets available. It gets called with the new measured eCO2 and TVOC values as parameters.
				* \param[in] device_reg: The address of the device to open.
				* \param[in] read_function: Function pointer to the function that does i2c read operations.
				* \param[in] write_function: Function pointer to the function that does i2c write operations.
				* \param[in] open_device_function: Function pointer to the function that opens an i2c connection.
				* \param[in] close_device_function: Function pointer to the function that closes an i2c connection.
				* \returns 0 if initializing the device was successful, a negative error value otherwise.
				*/
				int8_t init(bool use_power_safe_mode, int wake_gpio_pin_nr, int int_gpio_pin_nr,
					std::function<void(uint16_t, uint16_t)> data_callback,
					uint8_t device_reg = SENSOR_PRIMARY_I2C_REG,
					std::function<int8_t(int, uint8_t, uint8_t*, uint16_t)> read_function = manager::i2c_manager::read_from_device,
					std::function<int8_t(int, uint8_t, const uint8_t*, uint16_t)> write_function = manager::i2c_manager::write_to_device,
					std::function<int8_t(const std::string, uint8_t, int&)> open_device_function = manager::i2c_manager::open_device,
					std::function<int8_t(int&)> close_device_function = manager::i2c_manager::close_device);

				//! Closes a device connection and performs some cleanup.
				/*!
				*  Closes a device connection and performs some cleanup.
				* \returns 0 if closing the device was successful, a negative error value otherwise.
				*/
				int8_t close();

				//! Activates or deactivates the power safe mode.
				/*!
				*  Activates or deactivates the power safe mode.
				* \param[in] use_power_safe_mode: True to activate the power safe mode, false to deactivate it.
				* \returns 0 if toggling the power safe mode was successful, a negative error value otherwise.
				*/
				int8_t toggle_power_safe_mode(bool use_power_safe_mode);

				//! Changes the device state from BOOT to READY.
				/*!
				* Changes the device state from BOOT to READY. This tries to load the firmware and start the
				* device application. After the device entered READY state it can be used to receive measurements.
				* The sensor might need some time to deliver trustful sensor values. On average this warm up phase
				* takes about 20 minutes.
				* \returns 0 if starting the device was successful, a negative error value otherwise.
				*/
				int8_t start();

				//! Returns the status information of this device.
				/*!
				*  Returns the status information of this device.
				* \param[out] status: The status information of the device.
				* \returns 0 if getting the device status was successful, a negative error value otherwise.
				*/
				int8_t get_status_information(std::shared_ptr<struct ccs811_status>& status);

				//! Returns information about this device.
				/*!
				*  Returns information about this device. Included are device id, hardware id, hardware version,
				*  firmware version and application version.
				* \param[out] info: The information about the device.
				* \returns 0 if getting the device information was successful, a negative error value otherwise.
				*/
				int8_t get_device_information(std::shared_ptr<struct ccs811_device_info>& info);

				//! Returns the operation mode information of this device.
				/*!
				*  Returns the operation mode information of this device.
				* \param[out] mode: The operation mode information of the device.
				* \returns 0 if getting the device operation mode was successful, a negative error value otherwise.
				*/
				int8_t get_operation_mode_information(std::shared_ptr<struct ccs811_mode_info>& mode);

				//! Sets the operation mode of this device.
				/*!
				*  Sets the operation mode of this device.
				* \param[in] mode: The new operation mode of the device.
				* \param[in] interrupt_mode: True if interrupt mode should be used.
				* \param[in] use_thresholds: True if thresholds should be used.
				* \returns 0 if setting the device mode was successful, a negative error value otherwise.
				*/
				int8_t set_operation_mode(enum ccs811_operation_mode mode, bool interrupt_mode, bool use_thresholds);

				//! Returns the current eCO2 value.
				/*!
				* Returns the current eCO2 value.
				* \param[out] eCO2: The measured eCO2 value.
				* \returns 0 if measuring the eCO2 was successful, a negative error value otherwise.
				*/
				int8_t get_eCO2_data(uint16_t& eCO2);

				//! Returns the current TVOC value.
				/*!
				* Returns the current TVOC value.
				* \param[out] TVOC: The measured TVOC value.
				* \returns 0 if measuring the TVOC was successful, a negative error value otherwise.
				*/
				int8_t get_TVOC_data(uint16_t& TVOC);

				//! Returns the current raw data (current and voltage).
				/*!
				* Returns the current raw data (current and voltage).
				* \param[out] raw: The current raw values.
				* \returns 0 if getting the raw data was successful, a negative error value otherwise.
				*/
				int8_t get_raw_data(std::shared_ptr<struct ccs811_raw_data>& raw);

				//! Returns all data at the result register address.
				/*!
				* Returns all data at the result register address. The data consists of eCO2 and TVOC values
				* a status, an error id and the raw data.
				* \param[out] result: The current result data.
				* \returns 0 if getting the result data was successful, a negative error value otherwise.
				*/
				int8_t get_all_result_data(std::shared_ptr<struct ccs811_result_data>& result);

				//! Sets the current temperature and humidity.
				/*!
				* Sets the current temperature and humidity in order to improve the calculation of
				* the eCO2 and TVOC values.
				* \param[in] temperature: The current temperature in degree celsius. The value is assumed to
				* be 2 orders of magnitude greater than the usual value (e.g. 25.3°C will be 2530). At the
				* moment the CCS811 only supports 0.5 and 0 as fractions. Therefore all values will be rounded.
				* \param[in] humidity: The current humidity in percent. The value is assumed to be 2 orders of
				* magnitude greater than the usual value (e.g. 37.45% will be 3745). At the moment the CCS811
				* only supports 0.5 and 0 as fractions. Therefore all values will be rounded.
				* \returns 0 if setting the environment data was successful, a negative error value otherwise.
				*/
				int8_t set_environment_data(uint16_t temperature, uint16_t humidity);

				//! Returns the current voltage over the resistor and the NTC resistor.
				/*!
				* Returns the current voltage over the resistor and the NTC resistor. Can be used to calculate
				* the current temperature.
				* \param[out] ntc: The current voltages over resistor and NTC.
				* \returns 0 if getting the NTC data was successful, a negative error value otherwise.
				*/
				int8_t get_NTC_data(std::shared_ptr<struct ccs811_ntc>& ntc);

				//! Sets thresholds to control whether a new eCO2 is treated as new value.
				/*!
				* Only if a eCO2 measurement exceeds a threshold it is treated as a new value and can be
				* read by the host. "interrupt on threshold change" has to be activated in mode register.
				* \param[in] thresholds: The new thresholds to set. Low and High thresholds may have the
				* same value if only one threshold is needed.
				* \returns 0 if setting the thresholds was successful, a negative error value otherwise.
				*/
				int8_t set_thresholds(std::shared_ptr<struct ccs811_thresholds> thresholds);

				//! Returns the current baseline.
				/*!
				* Returns the current baseline that is used to normalize the measured values. Since
				* temperature, humidity or other environmental conditions change over time, the baseline
				* has to be recalculated continuously. The sensor does this automatically and thus improves
				* the baseline more and more. However to compensate outer condition changes the baseline
				* should be saved on the host from time to time. This way you can correct the baseline if
				* outliers distored it.
				* The frequency to store baselines depends on the operation mode. If the sensor runs 24/7,
				* the host should save baselines every 24h-48h during the first 500h (~21 days) of operation
				* time. Afterwards the frequency can be lowered to one baseline each 5-7 days.
				* If the sensor only runs sporadic the host should try to save a baseline at least before
				* a power off. The host also should save a serparate baseline for each operation mode to
				* reduce measurement errors.
				*
				* \param[out] baseline: The current baseline values.
				* \returns 0 if getting the baseline was successful, a negative error value otherwise.
				*/
				int8_t get_current_baseline(uint8_t baseline[BASELINE_LEN]);

				//! Sets the current baseline.
				/*!
				* Sets a previously stored baseline. The baseline should have been saved during clean air
				* conditions in order to not distort the sensors measure results.
				*
				* \param[in] baseline: The baseline values to set.
				* \returns 0 if setting the baseline was successful, a negative error value otherwise.
				*/
				int8_t set_baseline(uint8_t baseline[BASELINE_LEN]);

				//! WARNING: Deletes the firmware of the device.
				/*!
				* This operation might take some time and can only be performed in BOOT state. Read the status
				* register to check if the operation has finished.
				*
				* WARNING: Deletes the firmware of the device. The device can not be used anymore to measure
				*          eCO2 and TVOC values after deleting the firmware.
				*          You have to copy a new firmware to the device in order to restore its functionality.
				* WARNING: This class does not store any fallback firmware version in case you deleted the one
				*          on the sensor!
				* \returns 0 if deleting the firmware was successful, a negative error value otherwise.
				*/
				int8_t delete_current_firmware();

				//! Writes new a firmware version to the device.
				/*!
				* This operation might take some time and can only be performed in BOOT state. Read the status
				* register to check if the operation has finished.
				*
				* WARNING: There will be no backup of the old firmware version.
				* WARNING: Please delete the old firmware by calling "delete_current_firmware()" first.
				* WARNING: The device might not work as expected after changing the firmware version.
				*
				* \param[in] new_firmware: The new firmware to write to the device.
				* \param[in] byte_count: The size of the new firmware. Since only 9 bytes can be written at once
				* this value is used to cut the firmware in 9-byte parts.
				* \returns 0 if writing the new firmware to the device was successful, a negative error value otherwise.
				*/
				int8_t write_new_firmware(std::shared_ptr<uint8_t[]> new_firmware, uint16_t byte_count);

				//! Verifies the currently installed firmware.
				/*!
				* Verifies the currently installed firmware. This only has to be done after installing
				* a new firmware since the result will be stored directly on the device. The verification
				* can only be done in BOOT state and might take some time to complete. Read the status
				* register to check if the operation has finished.
				*
				* \param[out] firmware_valid: True if the firmware is valid, false otherwise.
				* \returns 0 if verifying the firmware was successful, a negative error value otherwise.
				*/
				int8_t verify_firmware(bool& firmware_valid);

				//! Performs a soft reset on the device.
				/*!
				* Performs a soft reset on the device.
				* \returns 0 if resetting the device was successful, a negative error value otherwise.
				*/
				virtual int8_t soft_reset() override;

			private:
				//! Checks whether the device is currently in BOOT or normal operation mode.
				/*!
				* Checks whether the device is currently in BOOT or normal operation mode.

				* \returns 0 for normal operation mode, 1 for BOOT mode and a negative error value otherwise.
				*/
				int8_t check_device_mode();

				//! Tries to read an error code from the device register.
				/*!
				* Tries to read an error code from the device register.
				* \param[out] error_code: The error code that was read from the device.
				* \returns 0 if reading the error code was successful, a negative error value otherwise.
				*/
				int8_t read_error(uint8_t& error_code);

				//! Simply reads all content from the device at once.
				/*!
				*  Simply reads all content from the device at once. The function should only be used for
				*  debug purposes.
				* \param[out] all_data: A buffer to store the content.
				* \returns 0 if reading all data was successful, a negative error value otherwise.
				*/
				virtual int8_t get_all_raw_data(uint8_t* all_data) override;

				//! Sets the nWAKE pin to low which wakes the device processor up.
				/*!
				* Sets the nWAKE pin to low which wakes the device processor up. By waking the
				* device before every i2c request its power consumption can be drastically reduced
				* compared to the nWAKE pin being always low.
				*/
				void wake_device();

				//! Sets the nWAKE pin to high which puts the device processor to sleep mode.
				/*!
				* Sets the nWAKE pin to high which puts the device processor to sleep mode. By
				* setting the device to sleep mode after every i2c request its power consumption
				* can be drastically reduced compared to the nWAKE pin being always low.
				*/
				void unwake_device();

				//! Starts a new thread that executes the <wait_for_data_flag>"() method.
				/*!
				* Starts a new thread that executes the <wait_for_data_flag>"() method.
				* Measure mode has to be set to interrupt to activate this kind of notification
				* and data access.
				*/
				void start_interrupt_thread();

				//! Stops the interrupt mode thread if it is running.
				/*!
				* Stops the interrupt mode thread if it is running.
				*/
				void stop_interrupt_thread();

				//! Funktion that continuously checks the state of the nINT gpio pin.
				/*!
				* Funktion that continuously checks the state of the nINT gpio pin. If the pin goes
				* LOW it means that new data is available on the sensor. As a result <new_data_ready>"()"
				* will be called and this method finishes. This method should be executed inside a thread.
				* Measure mode has to be set to interrupt to activate this kind of notification and data
				* access.
				*/
				void wait_for_data_flag();

				//! Thread function that controls the inner interupt check thread.
				/*!
				* The function checks if the int check thread finished. If this is the case, it reads
				* data from the sensor and restarts the thread.
				*/
				void interrupt_mode_loop();

				//! Puts the calling thread to sleep mode by calling sleep().
				/*!
				* Puts the calling thread to sleep mode by calling sleep(). The sleep time depends on the
				* current operation mode:
				* - SLEEP -> 0 seconds
				* - PULSE_60_S -> 60 seconds
				* - PULSE_10_S -> 10 seconds
				* - CONSTANT_POWER_1_S -> 1 second
				* - CONSTANT_POWER_250_MS -> 0.25 seconds
				*/
				void mode_dependent_sleep();

				bool m_use_power_safe_mode;
				bool m_use_interrupt_mode;
				int m_wake_gpio_pin;
				int m_int_gpio_pin_nr;
				std::thread* m_interrupt_thread;
				std::thread* m_int_check_thread;
				std::function<void(uint16_t, uint16_t)> m_data_callback;
				enum ccs811_operation_mode m_current_mode;
			};
		}
	}
}

