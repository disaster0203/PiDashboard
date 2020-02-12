#pragma once
#include <cstdint>
#include <functional>
#include <memory>
#include <string>
#include <wiringPi.h>
#include <thread>
#include <vector>

#include "sensor_base.h"
#include "ads1115_converter_constants.h"
#include "ads1115_converter_definitions.h"
#include "../manager/i2c_manager.h"

namespace driver
{
	namespace sensors
	{
		namespace ads1115
		{
			//! Class that communicates with the ADS1115 analog-digital-converter via I2C.
			/*!
			* This class implements various functions to configure the converter and receive the converted data.
			*/
			class converter : sensor_base
			{
			public:
				//! Default constructor.
				/*!
				* Default constructor.
				*/
				converter() {}

				//! Default destructor.
				/*!
				* Default destructor.
				*/
				~converter() {  }

				//! Opens a device connection and performs basic setup.
				/*!
				* Tries to open the device at the given i2c address in O_RDWR and I2C_SLAVE mode.
				* \param[in] device_reg: The address of the device to open. The default value is 48 (address pin is connected to nothing or ground).
				* \param[in] read_function: Function pointer to the function that does i2c read operations.
				* \param[in] write_function: Function pointer to the function that does i2c write operations.
				* \param[in] open_device_function: Function pointer to the function that opens an i2c connection.
				* \param[in] close_device_function: Function pointer to the function that closes an i2c connection.
				* \returns 0 if initializing the device was successful, a negative error value otherwise.
				*/
				virtual int8_t init(uint8_t device_reg = CONVERTER_ADDR_IS_GND_I2C_REG,
					std::function<int8_t(int, uint8_t, uint8_t*, uint16_t)> read_function = nullptr,
					std::function<int8_t(int, uint8_t, const uint8_t*, uint16_t)> write_function = nullptr,
					std::function<int8_t(const std::string, uint8_t, int&)> open_device_function = manager::i2c_manager::open_device,
					std::function<int8_t(int&)> close_device_function = manager::i2c_manager::close_device) override;
				
				//! Closes a device connection and performs some cleanup.
				/*!
				*  Closes a device connection and performs some cleanup.
				* \returns 0 if closing the device was successful, a negative error value otherwise.
				*/
				virtual int8_t close() override;

				//! Performs a soft reset on the device.
				/*!
				* Performs a soft reset on the device.
				* \returns 0 if resetting the device was successful, a negative error value otherwise.
				*/
				virtual int8_t soft_reset() override;

				//! Triggers the device to start a single conversion.
				/*!
				* Triggers the device to start a single conversion.
				* \returns 0 if starting a conversion was successful, a negative error value otherwise.
				*/
				int8_t start_single_conversion();

				//! Checks whether the device is currently converting an analog value.
				/*!
				* Checks whether the device is currently converting an analog value.
				* \param[out] is_converting: Whether the device is currently converting or not.
				* \returns 0 if getting the conversion state was successful, a negative error value otherwise.
				*/
				int8_t is_converting(bool& is_converting);

				//! Returns the current multiplexer setting.
				/*!
				* Returns the current multiplexer setting.
				* \param[out] current_multiplexer_setting: The current multiplexer setting.
				* \returns 0 if getting the multiplexer setting was successful, a negative error value otherwise.
				*/
				int8_t get_multiplexer_setting(ads1115_multiplexer& current_multiplexer_setting);

				//! Returns the current gain amplifier setting.
				/*!
				* Returns the current gain amplifier setting.
				* \param[out] current_gain_amplifier_setting: The current gain amplifier setting.
				* \returns 0 if getting the gain amplifier setting was successful, a negative error value otherwise.
				*/
				int8_t get_gain_amplifier_setting(ads1115_gain_amplifier& current_gain_amplifier_setting);

				//! Returns the current operation mode setting.
				/*!
				* Returns the current operation mode setting.
				* \param[out] current_operation_mode_setting: The current operation mode setting.
				* \returns 0 if getting the operation mode setting was successful, a negative error value otherwise.
				*/
				int8_t get_operation_mode_setting(ads1115_operation_mode& current_operation_mode_setting);

				//! Returns the current data rate setting.
				/*!
				* Returns the current data rate setting.
				* \param[out] current_data_rate_setting: The current data rate setting.
				* \returns 0 if getting the data rate setting was successful, a negative error value otherwise.
				*/
				int8_t get_data_rate_setting(ads1115_data_rate& current_data_rate_setting);

				//! Returns the current comparator mode setting.
				/*!
				* Returns the current comparator mode setting.
				* \param[out] current_comparator_mode_setting: The current comparator mode setting.
				* \returns 0 if getting the comparator mode setting was successful, a negative error value otherwise.
				*/
				int8_t get_comparator_mode_setting(ads1115_comparator_mode& current_comparator_mode_setting);

				//! Returns the current comparator polarity setting.
				/*!
				* Returns the current comparator polarity setting.
				* \param[out] current_comparator_polarity_setting: The current comparator polarity setting.
				* \returns 0 if getting the comparator polarity setting was successful, a negative error value otherwise.
				*/
				int8_t get_comparator_polarity_setting(ads1115_alert_polarity& current_comparator_polarity_setting);

				//! Returns the current comparator latching setting.
				/*!
				* Returns the current comparator latching setting.
				* \param[out] current_comparator_latching_setting: The current comparator latching setting.
				* \returns 0 if getting the comparator latching setting was successful, a negative error value otherwise.
				*/
				int8_t get_comparator_latching_setting(ads1115_alert_latching& current_comparator_latching_setting);

				//! Returns the current comparator queue setting.
				/*!
				* Returns the current comparator queue setting.
				* \param[out] current_comparator_queue_setting: The current comparator queue setting.
				* \returns 0 if getting the comparator queue setting was successful, a negative error value otherwise.
				*/
				int8_t get_comparator_queue_setting(ads1115_alert_queueing& current_comparator_queue_setting);

				//! Returns the current device configuration.
				/*!
				* Returns the current device configuration.
				* \param[out] current_settings: The current device configuration.
				* \returns 0 if getting the device configuration was successful, a negative error value otherwise.
				*/
				int8_t get_settings(ads1115_configuration& current_settings);

				//! Sets a new multiplexer setting.
				/*!
				* Sets a new multiplexer setting.
				* \param[in] new_multiplexer_setting: The new multiplexer setting.
				* \returns 0 if setting the multiplexer setting was successful, a negative error value otherwise.
				*/
				int8_t set_multiplexer_setting(ads1115_multiplexer new_multiplexer_setting);

				//! Sets a new gain amplifier setting.
				/*!
				* Sets a new gain amplifier setting.
				* \param[in] new_gain_amplifier_setting: The new gain amplifier setting.
				* \returns 0 if setting the gain amplifier setting was successful, a negative error value otherwise.
				*/
				int8_t set_gain_amplifier_setting(ads1115_gain_amplifier new_gain_amplifier_setting);

				//! Sets a new operation mode setting.
				/*!
				* Sets a new operation mode setting.
				* \param[in] new_operation_mode_setting: The new operation mode setting.
				* \returns 0 if setting the operation mode setting was successful, a negative error value otherwise.
				*/
				int8_t set_operation_mode_setting(ads1115_operation_mode new_operation_mode_setting);

				//! Sets a new data rate setting.
				/*!
				* Sets a new data rate setting.
				* \param[in] new_data_rate_setting: The new data rate setting.
				* \returns 0 if setting the data rate setting was successful, a negative error value otherwise.
				*/
				int8_t set_data_rate_setting(ads1115_data_rate new_data_rate_setting);

				//! Sets a new comparator mode setting.
				/*!
				* Sets a new comparator mode setting.
				* \param[in] new_comparator_mode_setting: The new comparator mode setting.
				* \returns 0 if setting the comparator mode setting was successful, a negative error value otherwise.
				*/
				int8_t set_comparator_mode_setting(ads1115_comparator_mode new_comparator_mode_setting);

				//! Sets a new comparator polarity setting.
				/*!
				* Sets a new comparator polarity setting.
				* \param[in] new_comparator_polarity_setting: The new comparator polarity setting.
				* \returns 0 if setting the comparator polarity setting was successful, a negative error value otherwise.
				*/
				int8_t set_comparator_polarity_setting(ads1115_alert_polarity new_comparator_polarity_setting);

				//! Sets a new comparator latching setting.
				/*!
				* Sets a new comparator latching setting.
				* \param[in] new_comparator_latching_setting: The new comparator latching setting.
				* \returns 0 if setting the comparator latching setting was successful, a negative error value otherwise.
				*/
				int8_t set_comparator_latching_setting(ads1115_alert_latching new_comparator_latching_setting);

				//! Sets a new comparator queue setting.
				/*!
				* Sets a new comparator queue setting.
				* \param[in] new_comparator_queue_setting: The new comparator queue setting.
				* \returns 0 if setting the comparator queue setting was successful, a negative error value otherwise.
				*/
				int8_t set_comparator_queue_setting(ads1115_alert_queueing new_comparator_queue_setting);

				//! Sets all settings at once.
				/*!
				* Sets all settings at once.
				* \param[in] new_settings: The new settings.
				* \returns 0 if setting the settings was successful, a negative error value otherwise.
				*/
				int8_t set_settings(struct ads1115_configuration new_settings);

				//! Sets all settings back to their default values.
				/*!
				* Sets all settings back to their default values.
				* \returns 0 if setting the settings was successful, a negative error value otherwise.
				*/
				int8_t restore_default_settings();

				//! Returns the last converted data.
				/*!
				* Returns the last converted data.
				* \param[out] converted_data: The converted data.
				* \returns 0 if getting the converted data was successful, a negative error value otherwise.
				*/
				int8_t get_converted_data(double& converted_data);

				//! Returns the upper (high) threshold.
				/*!
				* Returns the upper (high) threshold.
				* \param[out] upper_threshold: The upper (high) threshold.
				* \returns 0 if getting the upper threshold was successful, a negative error value otherwise.
				*/
				int8_t get_upper_threshold(uint16_t& upper_threshold);

				//! Returns the lower (low) threshold.
				/*!
				* Returns the lower (low) threshold.
				* \param[out] lower_threshold: The lower (low) threshold.
				* \returns 0 if getting the lower threshold was successful, a negative error value otherwise.
				*/
				int8_t get_lower_threshold(uint16_t& lower_threshold);

				//! Returns both thresholds.
				/*!
				* Returns both (upper & lower) thresholds.
				* \param[out] lower_threshold: The lower (low) threshold.
				* \param[out] upper_threshold: The upper (high) threshold.
				* \returns 0 if getting the thresholds was successful, a negative error value otherwise.
				*/
				int8_t get_thresholds(uint16_t& lower_threshold, uint16_t& upper_threshold);

				//! Sets the upper (high) threshold.
				/*!
				* Sets the upper (high) threshold.
				* \param[in] upper_threshold: The upper (high) threshold.
				* \returns 0 if setting the upper threshold was successful, a negative error value otherwise.
				*/
				int8_t set_upper_threshold(uint16_t upper_threshold);

				//! Sets the lower (low) threshold.
				/*!
				* Sets the lower (low) threshold.
				* \param[in] lower_threshold: The lower (low) threshold.
				* \returns 0 if setting the lower threshold was successful, a negative error value otherwise.
				*/
				int8_t set_lower_threshold(uint16_t lower_threshold);

				//! Sets both thresholds.
				/*!
				* Sets both (upper & lower) thresholds.
				* \param[in] lower_threshold: The lower (low) threshold.
				* \param[in] upper_threshold: The upper (high) threshold.
				* \returns 0 if setting the thresholds was successful, a negative error value otherwise.
				*/
				int8_t set_thresholds(uint16_t lower_threshold, uint16_t upper_threshold);

				//! Sets the upper threshold back to its default value.
				/*!
				* Sets the upper threshold back to its default value.
				* \returns 0 if setting the thresholds was successful, a negative error value otherwise.
				*/
				int8_t restore_default_upper_thresholds();

				//! Sets the lower threshold back to its default value.
				/*!
				* Sets the lower threshold back to its default value.
				* \returns 0 if setting the thresholds was successful, a negative error value otherwise.
				*/
				int8_t restore_default_lower_thresholds();

				//! Sets both thresholds back to their default values.
				/*!
				* Sets both thresholds back to their default values.
				* \returns 0 if setting the thresholds was successful, a negative error value otherwise.
				*/
				int8_t restore_default_thresholds();

			protected:
				//! Simply reads all content from the device at once.
				/*!
				*  Simply reads all content from the device at once. The function should only be used for
				*  debug purposes.
				* \param[out] all_data: A buffer to store the content.
				* \returns 0 if reading all data was successful, a negative error value otherwise.
				*/
				virtual int8_t get_all_raw_data(uint8_t* all_data) override;

			private:
				//! Extracts the multiplexer bits from the given byte and parses them into the resulting enum.
				/*!
				*  Extracts the multiplexer bits from the given byte and parses them into the resulting enum.
				* \param[in] raw_data: A setting byte that was read from the device.
				* \returns The parsed multiplexer value as ads1115_multiplexer enum.
				*/
				ads1115_multiplexer parse_multiplexer_value(uint8_t raw_data);

				//! Extracts the gain amplifier bits from the given byte and parses them into the resulting enum.
				/*!
				*  Extracts the gain amplifier bits from the given byte and parses them into the resulting enum.
				* \param[in] raw_data: A setting byte that was read from the device.
				* \returns The parsed gain amplifier value as ads1115_gain_amplifier enum.
				*/
				ads1115_gain_amplifier parse_gain_amplifier_value(uint8_t raw_data);

				//! Extracts the operation mode bit from the given byte and parses it into the resulting enum.
				/*!
				*  Extracts the operation mode bit from the given byte and parses it into the resulting enum.
				* \param[in] raw_data: A setting byte that was read from the device.
				* \returns The parsed operation mode value as ads1115_operation_mode enum.
				*/
				ads1115_operation_mode parse_operation_mode_value(uint8_t raw_data);

				//! Extracts the data rate bits from the given byte and parses them into the resulting enum.
				/*!
				*  Extracts the data rate bits from the given byte and parses them into the resulting enum.
				* \param[in] raw_data: A setting byte that was read from the device.
				* \returns The parsed data rate value as ads1115_data_rate enum.
				*/
				ads1115_data_rate parse_data_rate_value(uint8_t raw_data);

				//! Extracts the comparator mode bit from the given byte and parses it into the resulting enum.
				/*!
				*  Extracts the comparator mode bit from the given byte and parses it into the resulting enum.
				* \param[in] raw_data: A setting byte that was read from the device.
				* \returns The parsed comparator mode value as ads1115_comparator_mode enum.
				*/
				ads1115_comparator_mode parse_comparator_mode_value(uint8_t raw_data);

				//! Extracts the comparator polarity bit from the given byte and parses it into the resulting enum.
				/*!
				*  Extracts the comparator polarity bit from the given byte and parses it into the resulting enum.
				* \param[in] raw_data: A setting byte that was read from the device.
				* \returns The parsed comparator polarity value as ads1115_alert_polarity enum.
				*/
				ads1115_alert_polarity parse_comparator_polarity_value(uint8_t raw_data);

				//! Extracts the comparator latching bit from the given byte and parses it into the resulting enum.
				/*!
				*  Extracts the comparator latching bit from the given byte and parses it into the resulting enum.
				* \param[in] raw_data: A setting byte that was read from the device.
				* \returns The parsed comparator latching value as ads1115_alert_latching enum.
				*/
				ads1115_alert_latching parse_comparator_latching_value(uint8_t raw_data);

				//! Extracts the comparator queueing bits from the given byte and parses them into the resulting enum.
				/*!
				*  Extracts the comparator queueing bits from the given byte and parses them into the resulting enum.
				* \param[in] raw_data: A setting byte that was read from the device.
				* \returns The parsed comparator queueing value as ads1115_alert_queueing enum.
				*/
				ads1115_alert_queueing parse_comparator_queueing_value(uint8_t raw_data);

				//! Fallback i2c write function that is used if m_write_function is nullptr.
				/*!
				*  Fallback i2c write function that is used if m_write_function is nullptr.
				* \param[in] handle: The handle that will be used to communicate over the i2c bus.
				* \param[in] address: The file address to write to.
				* \param[in] data: The buffer containing the content to write.
				* \param[in] length: The number of bytes to write. Default is 2.
				* \returns 0 if writing was successful, a negative error value otherwise.
				*/
				int8_t write_operation(int handle, uint8_t address, const uint8_t* buffer, uint16_t length = 2);

				//! Fallback i2c read function that is used if m_read_function is nullptr.
				/*!
				*  Fallback i2c write function that is used if m_read_function is nullptr.
				* \param[in] handle: The handle that will be used to communicate over the i2c bus.
				* \param[in] address: The file address to write to.
				* \param[in] data: The buffer containing the content to write.
				* \param[in] length: The number of bytes to write.
				* \returns 0 if reading was successful, a negative error value otherwise.
				*/
				int8_t read_operation(int handle, uint8_t address, uint8_t* buffer, uint16_t length = 2);
			};
		}
	}
}