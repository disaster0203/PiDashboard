#pragma once
#include <cstdint>
#include <memory>
#include <string>
#include <wiringPi.h>
#include <thread>
#include <vector>

#include "CCS811Constants.h"
#include "CCS811Definitions.h"
#include "../../enums/SensorSetting.h"
#include "../../interfaces/ISensor.h"
#include "../../utils/I2CManager.h"

using namespace hal::utils;

namespace hal
{
	namespace sensors
	{
		namespace i2c
		{
			namespace ccs811
			{
				//! Class that communicates with the CCS811 sensor (AMS) via i2c.
				/*!
				* This class implements various functions to configure the sensor and receive the measured data.
				*/
				class CCS811 final : public interfaces::ISensor
				{
				public:
					/*!
					* Default constructor.
					*/
					CCS811() = default;

					/*!
					* Tells the hardware to perform a new measurement. The result will be sent with a callback function.
					* If no callback is registered the measurement cannot be obtained.
					* \param[in] type: The type of measurement that has to do be done.
					* \throws HALException if triggering a eCO2 measurement fails.
					* \throws HALException if triggering a TVOC measurement fails.
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
					* If changing BASELINE setting: Configuration has to contain two uint8_t values or one uint16_t value.
					* If changing THRESHOLD setting: Configuration has to contain two uint16_t values (fist low-to-medium, second medium-to-high)
					*                                and afterwards one uint8_t value (hysteresis).
					* If changing ENVIRONMENT_DATA setting: Configuration has to contain two uint16_t values (first temperature, second humidity).
					*                                       Both factors have to be scaled by factor 100 (= 2 decimals; e.g. 25.45C will be 2545).
					* \throws HALException if setting new baseline values fails.
					* \throws HALException if setting new threshold values fails.
					* \throws HALException if setting new environment data fails.
					*/
					void configure(SensorSetting setting, const std::string& configuration) override;

					/*!
					* Returns one specific setting of a sensor.
					* \param[in] setting: The type of setting to return. For this sensor only the BASELINE setting can be returned.
					* \returns the current value of the given setting as string.
					* \throws HALException if getting baseline values fails.
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
					* \param[in] use_power_safe_mode: Whether the devices processor should be put to sleep mode between i2c requests or not.
					* \param[in] wake_gpio_pin_nr: The GPIO pin number of the nWAKE pin that is used to put the device to sleep and wake it up.
					* \param[in] int_gpio_pin_nr: The GPIO pin number of the INT pin that is used to notify if new data is available.
					* \param[in] device_reg: The address of the device to open.
					* \returns the id of the connected device.
					* \throws GPIOException if initializing wiringPi fails.
					* \throws HALException if opening a connection to the device fails (e.g. the device was not found).
					* \throws I2CException if reading the hardware id fails.
					* \throws I2CException if the device id is not 0x81 (e.g. a wrong device is connected).
					* \throws I2CException if reading the hardware version fails.
					* \throws I2CException if reading the firmware version fails.
					* \throws I2CException if reading the application version fails.
					*/
					uint8_t init(
						bool use_power_safe_mode,
						int wake_gpio_pin_nr,
						int int_gpio_pin_nr,
						uint8_t device_reg = SENSOR_PRIMARY_I2C_REG);

					//! Activates or deactivates the power safe mode.
					/*!
					*  Activates or deactivates the power safe mode.
					* \param[in] use_power_safe_mode: True to activate the power safe mode, false to deactivate it.
					*/
					void toggle_power_safe_mode(bool use_power_safe_mode) noexcept;

					//! Changes the device state from BOOT to READY.
					/*!
					* Changes the device state from BOOT to READY. This tries to load the firmware and start the
					* device application. After the device entered READY state it can be used to receive measurements.
					* The sensor might need some time to deliver trustful sensor values. On average this warm up phase
					* takes about 20 minutes.
					* \returns 0 if starting the device was successful, a warning value otherwise.
					* \throws HALException if the firmware could not be verified.
					* \throws I2CException if reading the device status information fails.
					* \throws I2CException if writing to the device start register fails.
					* \throws HALException if the device could not be started.
					* \throws I2CException if reading the current device operation mode fails.
					* \throws HALException if the operation mode that was read from the device is invalid.
					*/
					int8_t start();

					//! Returns the status information of this device.
					/*!
					*  Returns the status information of this device.
					* \returns A Status struct pointer containing status information of the device.
					* \throws I2CException if reading the device status information fails.
					*/
					std::shared_ptr<Status> get_status_information() const;

					//! Returns information about this device.
					/*!
					*  Returns information about this device. Included are device id, hardware id, hardware version,
					*  firmware version and application version.
					* \returns A DeviceInfo struct pointer containing information about the device.
					* \throws I2CException if reading the hardware id fails.
					* \throws I2CException if the device id is not 0x81 (e.g. a wrong device is connected).
					* \throws I2CException if reading the hardware version fails.
					* \throws I2CException if reading the firmware version fails.
					* \throws I2CException if reading the application version fails.
					*/
					std::shared_ptr<struct DeviceInfo> get_device_information() const;

					//! Returns the operation mode information of this device.
					/*!
					*  Returns the operation mode information of this device.
					* \param[out] mode: The operation mode information of the device.
					* \returns 0 if getting the device operation mode was successful, a warning if the device is still in BOOT mode.
					* \throws HALException if reading the current device operation mode fails.
					* \throws HALException if the operation mode that was read from the device is invalid.
					*/
					int8_t get_operation_mode_information(std::shared_ptr<struct ModeInfo>& mode) const;

					//! Sets the operation mode of this device.
					/*!
					*  Sets the operation mode of this device.
					* \param[in] mode: The new operation mode of the device.
					* \param[in] interrupt_mode: True if interrupt mode should be used.
					* \param[in] use_thresholds: True if thresholds should be used.
					* \returns 0 if setting the device mode was successful, a warning value otherwise.
					* \throws HALException if reading the current device operation mode fails.
					* \throws HALException if the operation mode that was read from the device is invalid.
					* \throws HALException if setting the mode bits fails.
					* \throws HALException if getting/setting the interrupt mode bit fails.
					* \throws HALException if getting/setting the threshold mode bit fails.
					* \throws I2CException if writing the new operation mode fails.
					*/
					int8_t set_operation_mode(OperationMode mode, bool interrupt_mode, bool use_thresholds);
					// Todo implement wait time correctly

					//! Returns the current eCO2 value.
					/*!
					* Returns the current eCO2 value.
					* \param[out] eCO2: The measured eCO2 value.
					* \returns 0 if measuring the eCO2 was successful, a warning if the device is still in BOOT mode.
					* \throws HALException if reading the current device operation mode fails.
					* \throws I2CException if reading eCO2 data from the device fails.
					*/
					int8_t get_eCO2_data(uint16_t& eCO2) const;

					//! Returns the current TVOC value.
					/*!
					* Returns the current TVOC value.
					* \param[out] TVOC: The measured TVOC value.
					* \returns 0 if measuring the TVOC was successful, a warning if the device is still in BOOT mode.
					* \throws HALException if reading the current device operation mode fails.
					* \throws I2CException if reading TVOC data from the device fails.
					*/
					int8_t get_TVOC_data(uint16_t& TVOC) const;

					//! Returns the current raw data (current and voltage).
					/*!
					* Returns the current raw data (current and voltage).
					* \param[out] raw: The current raw values.
					* \returns 0 if getting the raw data was successful, a warning if the device is still in BOOT mode.
					* \throws HALException if reading the current device operation mode fails.
					* \throws HALException if reading raw data from the device fails.
					*/
					int8_t get_raw_data(std::shared_ptr<RawData>& raw) const;

					//! Returns all data at the result register address.
					/*!
					* Returns all data at the result register address. The data consists of eCO2 and TVOC values
					* a status, an error id and the raw data.
					* \param[out] result: The current result data.
					* \returns 0 if getting the result data was successful, a warning if the device is still in BOOT mode.
					* \throws HALException if reading the current device operation mode fails.
					* \throws I2CException if reading the result data from the device fails.
					* \throws HALException if reading the value of certain bits from byte fails.
					*/
					int8_t get_all_result_data(std::shared_ptr<ResultData>& result) const;

					//! Sets the current temperature and humidity.
					/*!
					* Sets the current temperature and humidity in order to improve the calculation of
					* the eCO2 and TVOC values.
					* \param[in] temperature: The current temperature in Degree Celsius. The value is assumed to
					* be 2 orders of magnitude greater than the usual value (e.g. 25.3°C will be 2530). At the
					* moment the CCS811 only supports 0.5 and 0 as fractions. Therefore all values will be rounded.
					* \param[in] humidity: The current humidity in percent. The value is assumed to be 2 orders of
					* magnitude greater than the usual value (e.g. 37.45% will be 3745). At the moment the CCS811
					* only supports 0.5 and 0 as fractions. Therefore all values will be rounded.
					* \returns 0 if setting the environment data was successful, a warning if the device is still in BOOT mode.
					* \throws HALException if reading the current device operation mode fails.
					* \throws I2CException if writing the environment data to the device fails.
					*/
					int8_t set_environment_data(uint16_t temperature, uint16_t humidity) const;

					//! Returns the current voltage over the resistor and the NTC resistor.
					/*!
					* Returns the current voltage over the resistor and the NTC resistor. Can be used to calculate
					* the current temperature.
					* \param[out] NTC: The current voltages over resistor and NTC.
					* \returns 0 if getting the NTC data was successful, a warning if the device is still in BOOT mode.
					* \throws HALException if reading the current device operation mode fails.
					* \throws I2CException if reading the NTC data from the device fails.
					*/
					int8_t get_NTC_data(std::shared_ptr<NTC>& NTC) const;

					//! Sets thresholds to control whether a new eCO2 is treated as new value.
					/*!
					* Only if a eCO2 measurement exceeds a threshold it is treated as a new value and can be
					* read by the host. "interrupt on threshold change" has to be activated in mode register.
					* \param[in] thresholds: The new thresholds to set. Low and High thresholds may have the
					* same value if only one threshold is needed.
					* \returns 0 if setting the thresholds was successful, a warning if the device is still in BOOT mode.
					* \throws HALException if reading the current device operation mode fails.
					* \throws I2CException if writing the thresholds to the device fails.
					*/
					int8_t set_thresholds(std::shared_ptr<Thresholds> thresholds) const;

					//! Returns the current baseline.
					/*!
					* Returns the current baseline that is used to normalize the measured values. Since
					* temperature, humidity or other environmental conditions change over time, the baseline
					* has to be recalculated continuously. The sensor does this automatically and thus improves
					* the baseline more and more. However to compensate outer condition changes the baseline
					* should be saved on the host from time to time. This way you can correct the baseline if
					* outliers distorted it.
					* The frequency to store baselines depends on the operation mode. If the sensor runs 24/7,
					* the host should save baselines every 24h-48h during the first 500h (~21 days) of operation
					* time. Afterwards the frequency can be lowered to one baseline each 5-7 days.
					* If the sensor only runs sporadic the host should try to save a baseline at least before
					* a power off. The host also should save a separate baseline for each operation mode to
					* reduce measurement errors.
					*
					* \param[out] baseline: The current baseline values.
					* \returns 0 if getting the baseline was successful, a warning if the device is still in BOOT mode.
					* \throws HALException if reading the current device operation mode fails.
					* \throws I2CException if reading the current baseline data from the device fails.
					*/
					int8_t get_current_baseline(uint8_t baseline[BASELINE_LEN]) const;
					// Todo enforce reading baseline continuously depending on operation mode and store it.

					//! Sets the current baseline.
					/*!
					* Sets a previously stored baseline. The baseline should have been saved during clean air
					* conditions in order to not distort the sensors measure results.
					*
					* \param[in] baseline: The baseline values to set.
					* \returns 0 if setting the baseline was successful, a warning if the device is still in BOOT mode.
					* \throws HALException if reading the current device operation mode fails.
					* \throws I2CException if writing a new baseline to the device fails.
					*/
					int8_t set_baseline(uint8_t baseline[BASELINE_LEN]) const;

					//! WARNING: Deletes the firmware of the device.
					/*!
					* This operation might take some time and can only be performed in BOOT state. Read the status
					* register to check if the operation has finished.
					*
					* WARNING: Deletes the firmware of the device. The device can not be used anymore to measure
					*          eCO2 and TVOC values after deleting the firmware.
					*          You have to copy a new firmware to the device in order to restore its functionality.
					* WARNING: This class does not store any fall-back firmware version in case you deleted the one
					*          on the sensor!
					* \returns 0 if deleting the firmware was successful, a negative error value otherwise.
					* \throws HALException if reading the current device operation mode fails.
					*/
					int8_t delete_current_firmware() const;

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
					* \throws HALException if reading the current device operation mode fails.
					*/
					int8_t write_new_firmware(std::shared_ptr<uint8_t[]> new_firmware, uint16_t byte_count) const;

					//! Verifies the currently installed firmware.
					/*!
					* Verifies the currently installed firmware. This only has to be done after installing
					* a new firmware since the result will be stored directly on the device. The verification
					* can only be done in BOOT state and might take some time to complete. Read the status
					* register to check if the operation has finished.
					*
					* \param[out] firmware_valid: True if the firmware is valid, false otherwise.
					* \returns 0 if verifying the firmware was successful, a negative error value otherwise.
					* \throws HALException if reading the current device operation mode fails.
					*/
					int8_t verify_firmware(bool& firmware_valid) const;

				protected:
					//! Checks whether the device is currently in BOOT or normal operation mode.
					/*!
					* Checks whether the device is currently in BOOT or normal operation mode.

					* \returns 0 for normal operation mode, 1 for BOOT mode and a negative error value otherwise.
					* \throws HALException if reading the device status information fails.
					*/
					int8_t check_device_mode() const;

					//! Tries to read an error code from the device register.
					/*!
					* Tries to read an error code from the device register.
					* \returns the error code that was read from the device.
					* \throws I2CException if reading the error code from the device fails.
					*/
					uint8_t read_error() const;

					//! Sets the nWAKE pin to low which wakes the device processor up.
					/*!
					* Sets the nWAKE pin to low which wakes the device processor up. By waking the
					* device before every i2c request its power consumption can be drastically reduced
					* compared to the nWAKE pin being always low.
					*/
					void wake_device() const noexcept;

					//! Sets the nWAKE pin to high which puts the device processor to sleep mode.
					/*!
					* Sets the nWAKE pin to high which puts the device processor to sleep mode. By
					* setting the device to sleep mode after every i2c request its power consumption
					* can be drastically reduced compared to the nWAKE pin being always low.
					*/
					void unwake_device() const noexcept;

					//! Starts a new thread that executes the <wait_for_data_flag>"() method.
					/*!
					* Starts a new thread that executes the <wait_for_data_flag>"() method.
					* Measure mode has to be set to interrupt to activate this kind of notification
					* and data access.
					*/
					void start_interrupt_thread() noexcept;

					//! Stops the interrupt mode thread if it is running.
					/*!
					* Stops the interrupt mode thread if it is running.
					*/
					void stop_interrupt_thread() noexcept;

					//! Function that continuously checks the state of the nINT GPIO pin.
					/*!
					* Function that continuously checks the state of the nINT GPIO pin. If the pin goes
					* LOW it means that new data is available on the sensor. As a result <new_data_ready>"()"
					* will be called and this method finishes. This method should be executed inside a thread.
					* Measure mode has to be set to interrupt to activate this kind of notification and data
					* access.
					*/
					void wait_for_data_flag() const noexcept;

					//! Thread function that controls the inner interrupt check thread.
					/*!
					* The function checks if the int check thread finished. If this is the case, it reads
					* data from the sensor and restarts the thread.
					* \throws HALException if reading result data failed.
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
					void mode_dependent_sleep() const noexcept;

					bool m_use_power_safe_mode{};
					bool m_use_interrupt_mode{};
					int m_wake_gpio_pin{};
					int m_int_gpio_pin_nr{};
					int m_file_handle{};
					uint8_t m_dev_id{};
					std::thread* m_interrupt_thread{};
					std::thread* m_int_check_thread{};
					OperationMode m_current_mode = OperationMode::SLEEP;
				};
			}
		}
	}
}
