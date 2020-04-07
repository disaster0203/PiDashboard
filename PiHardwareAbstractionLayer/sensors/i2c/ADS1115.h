#pragma once

#include <memory>
#include <map>

#include "ADS1115Definitions.h"
#include "ADS1115Constants.h"
#include "../../enums/SensorSetting.h"
#include "../../interfaces/IConverter.h"
#include "../../utils/EnumConverter.h"

using namespace hal::utils;

namespace hal
{
	namespace sensors
	{
		namespace i2c
		{
			namespace ads1115
			{
				//! Class that communicates with the ADS1115 analog-digital-converter via i2c.
				/*!
				* This class implements various functions to configure the converter and receive the converted data.
				*/
				class ADS1115 final : public interfaces::IConverter
				{
				public:
					//! Default constructor.
					/*!
					* Default constructor.
					*/
					ADS1115() = default;

					/*!
					* Tells the hardware to perform a new measurement. The result will be sent with a callback function.
					* If no callback is registered the measurement cannot be obtained.
					* \param[in] type: The type of measurement that has to do be done.
					* \throws HALException if triggering a conversion fails.
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
					* If changing COMPARATOR_LATCHING setting: Configuration has to be the value of a ComparatorMode enum as string.
					* If changing COMPARATOR_MODE setting: Configuration has to be the value of a ComparatorQueue enum as string.
					* If changing DATA_RATE setting: Configuration has to be the value of a DataRate enum as string.
					* If changing GAIN_AMPLIFIER setting: Configuration has to be the value of a GainAmplifier enum as string.
					* If changing THRESHOLD setting: Configuration has to contain two uint16_t (first: lower threshold, 
					* second: upper threshold) values as string.
					* If changing MULTIPLEXER setting: Configuration has to be the value of a Multiplexer enum as string.
					* \throws HALException if setting new comparator latching value fails.
					* \throws HALException if setting new comparator mode value fails.
					* \throws HALException if setting new comparator queue value fails.
					* \throws HALException if setting new pin polarity value fails.
					* \throws HALException if setting new data rate value fails.
					* \throws HALException if setting new gain amplifier value fails.
					* \throws HALException if setting new threshold values fails.
					* \throws HALException if setting new multiplexer value fails.
					*/
					void configure(SensorSetting setting, const std::string& configuration) override;

					/*!
					* Returns one specific setting of a sensor.
					* \param[in] setting: The type of setting to return. For this sensor only OVERSAMPLING and FILTER settings can be returned.
					* \returns the current value of the given setting as string.
					* \throws HALException if getting comparator queue value fails.
					* \throws HALException if getting comparator latching value fails.
					* \throws HALException if getting pin polarity value fails.
					* \throws HALException if getting comparator mode value fails.
					* \throws HALException if getting data rate value fails.
					* \throws HALException if getting gain amplifier value fails.
					* \throws HALException if getting multiplexer value fails.
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
					* \param[in] device_reg: The address of the device to open. The default value is 48.
					* Supported values are:
					* 48 - address pin is connected to nothing or ground.
					* 49 - address pin is connected to power (VDD).
					* 50 - address pin is connected to SDA.
					* 51 - address pin is connected to SCL.
					* \throws HALException if opening a connection to the device fails (e.g. the device was not found).
					*/
					void init(uint8_t device_reg = CONVERTER_ADDR_IS_GND_I2C_REG);

					//! Checks whether the device connection is correctly setup.
					/*!
					* Checks whether the device connection is correctly setup.
					* \returns True if the device is initialized, false otherwise.
					*/
					bool is_initialized() const noexcept;

					//! Performs a soft reset on the device.
					/*!
					* Performs a soft reset on the device.
					* \throws I2CException if writing the reset command fails.
					*/
					void soft_reset();

					//! Triggers the device to start a single conversion.
					/*!
					* Triggers the device to start a single conversion.
					* \returns 0 if starting a conversion was successful, a warning value if the device is in CONTINUOUS mode.
					* \throws I2CException if reading the device settings fails.
					* \throws I2CException if writing the device settings fails.
					*/
					int8_t start_single_conversion();

					//! Checks whether the device is currently converting an analog value.
					/*!
					* Checks whether the device is currently converting an analog value.
					* \returns true if the device is currently converting, false otherwise.
					* \throws I2CException if reading the device settings fails.
					* \throws HALException if checking whether the convert bit of the config byte is set fails.
					*/
					bool is_converting();

					//! Returns the current multiplexer setting.
					/*!
					* Returns the current multiplexer setting.
					* \returns The current multiplexer setting.
					* \throws I2CException if reading the device settings fails.
					*/
					Multiplexer get_multiplexer_setting();

					//! Returns the current gain amplifier setting.
					/*!
					* Returns the current gain amplifier setting.
					* \returns The current gain amplifier setting.
					* \throws I2CException if reading the device settings fails.
					*/
					GainAmplifier get_gain_amplifier_setting();

					//! Returns the current operation mode setting.
					/*!
					* Returns the current operation mode setting.
					* \returns The current operation mode setting.
					* \throws I2CException if reading the device settings fails.
					*/
					OperationMode get_operation_mode_setting();

					//! Returns the current data rate setting.
					/*!
					* Returns the current data rate setting.
					* \returns The current data rate setting.
					* \throws I2CException if reading the device settings fails.
					*/
					DataRate get_data_rate_setting();

					//! Returns the current comparator mode setting.
					/*!
					* Returns the current comparator mode setting.
					* \returns The current comparator mode setting.
					* \throws I2CException if reading the device settings fails.
					*/
					ComparatorMode get_comparator_mode_setting();

					//! Returns the current comparator polarity setting.
					/*!
					* Returns the current comparator polarity setting.
					* \returns The current comparator polarity setting.
					* \throws I2CException if reading the device settings fails.
					*/
					AlertPolarity get_comparator_polarity_setting();

					//! Returns the current comparator latching setting.
					/*!
					* Returns the current comparator latching setting.
					* \returns The current comparator latching setting.
					* \throws I2CException if reading the device settings fails.
					*/
					AlertLatching get_comparator_latching_setting();

					//! Returns the current comparator queue setting.
					/*!
					* Returns the current comparator queue setting.
					* \returns The current comparator queue setting.
					* \throws I2CException if reading the device settings fails.
					*/
					AlertQueueing get_comparator_queue_setting();

					//! Returns the current device configuration.
					/*!
					* Returns the current device configuration.
					* \returns The current device configuration.
					* \throws I2CException if reading the device settings fails.
					*/
					Configuration get_settings();

					//! Sets a new multiplexer setting.
					/*!
					* Sets a new multiplexer setting.
					* \param[in] new_multiplexer_setting: The new multiplexer setting.
					* \throws I2CException if reading the device settings fails.
					* \throws HALException if setting multiplexer bits in config byte fails.
					* \throws I2CException if writing the device settings fails.
					*/
					void set_multiplexer_setting(Multiplexer new_multiplexer_setting);

					//! Sets a new gain amplifier setting.
					/*!
					* Sets a new gain amplifier setting.
					* \param[in] new_gain_amplifier_setting: The new gain amplifier setting.
					* \throws I2CException if reading the device settings fails.
					* \throws HALException if setting gain amplifier bits in config byte fails.
					* \throws I2CException if writing the device settings fails.
					*/
					void set_gain_amplifier_setting(GainAmplifier new_gain_amplifier_setting);

					//! Sets a new operation mode setting.
					/*!
					* Sets a new operation mode setting.
					* \param[in] new_operation_mode_setting: The new operation mode setting.
					* \throws I2CException if reading the device settings fails.
					* \throws HALException if setting operation mode bits in config byte fails.
					* \throws I2CException if writing the device settings fails.
					*/
					void set_operation_mode_setting(OperationMode new_operation_mode_setting);

					//! Sets a new data rate setting.
					/*!
					* Sets a new data rate setting.
					* \param[in] new_data_rate_setting: The new data rate setting.
					* \throws I2CException if reading the device settings fails.
					* \throws HALException if setting data rate bits in config byte fails.
					* \throws I2CException if writing the device settings fails.
					*/
					void set_data_rate_setting(DataRate new_data_rate_setting);

					//! Sets a new comparator mode setting.
					/*!
					* Sets a new comparator mode setting.
					* \param[in] new_comparator_mode_setting: The new comparator mode setting.
					* \throws I2CException if reading the device settings fails.
					* \throws HALException if setting comparator mode bits in config byte fails.
					* \throws I2CException if writing the device settings fails.
					*/
					void set_comparator_mode_setting(ComparatorMode new_comparator_mode_setting);

					//! Sets a new comparator polarity setting.
					/*!
					* Sets a new comparator polarity setting.
					* \param[in] new_comparator_polarity_setting: The new comparator polarity setting.
					* \throws I2CException if reading the device settings fails.
					* \throws HALException if setting pin polarity bits in config byte fails.
					* \throws I2CException if writing the device settings fails.
					*/
					void set_comparator_polarity_setting(AlertPolarity new_comparator_polarity_setting);

					//! Sets a new comparator latching setting.
					/*!
					* Sets a new comparator latching setting.
					* \param[in] new_comparator_latching_setting: The new comparator latching setting.
					* \throws I2CException if reading the device settings fails.
					* \throws HALException if setting comparator latching bits in config byte fails.
					* \throws I2CException if writing the device settings fails.
					*/
					void set_comparator_latching_setting(AlertLatching new_comparator_latching_setting);

					//! Sets a new comparator queue setting.
					/*!
					* Sets a new comparator queue setting.
					* \param[in] new_comparator_queue_setting: The new comparator queue setting.
					* \throws I2CException if reading the device settings fails.
					* \throws HALException if setting comparator queue bits in config byte fails.
					* \throws I2CException if writing the device settings fails.
					*/
					void set_comparator_queue_setting(AlertQueueing new_comparator_queue_setting);

					//! Sets all settings at once.
					/*!
					* Sets all settings at once.
					* \param[in] new_settings: The new settings.
					* \throws I2CException if reading the device settings fails.
					* \throws HALException if changing setting bits in config byte fails.
					* \throws I2CException if writing the device settings fails.
					*/
					void set_settings(struct Configuration new_settings);

					//! Sets all settings back to their default values.
					/*!
					* Sets all settings back to their default values.
					* \throws I2CException if writing the device settings fails.
					*/
					void restore_default_settings();

					//! Returns the last converted data.
					/*!
					* Returns the last converted data.
					* \returns The converted data.
					* \throws I2CException if reading converted data from the device fails.
					*/
					double get_converted_data();

					//! Returns the upper (high) threshold.
					/*!
					* Returns the upper (high) threshold.
					* \returns The upper (high) threshold.
					* \throws I2CException if reading the upper threshold fails.
					*/
					uint16_t get_upper_threshold();

					//! Returns the lower (low) threshold.
					/*!
					* Returns the lower (low) threshold.
					* \returns The lower (low) threshold.
					* \throws I2CException if reading the lower threshold fails.
					*/
					uint16_t get_lower_threshold();

					//! Returns both thresholds.
					/*!
					* Returns both (upper & lower) thresholds.
					* \param[out] lower_threshold: The lower (low) threshold.
					* \param[out] upper_threshold: The upper (high) threshold.
					* \throws I2CException if reading the thresholds fails.
					*/
					void get_thresholds(uint16_t& lower_threshold, uint16_t& upper_threshold);

					//! Sets the upper (high) threshold.
					/*!
					* Sets the upper (high) threshold.
					* \param[in] upper_threshold: The upper (high) threshold.
					* \throws I2CException if writing the upper threshold fails.
					*/
					void set_upper_threshold(uint16_t upper_threshold);

					//! Sets the lower (low) threshold.
					/*!
					* Sets the lower (low) threshold.
					* \param[in] lower_threshold: The lower (low) threshold.
					* \throws I2CException if writing the lower threshold fails.
					*/
					void set_lower_threshold(uint16_t lower_threshold);

					//! Sets both thresholds.
					/*!
					* Sets both (upper & lower) thresholds.
					* \param[in] lower_threshold: The lower (low) threshold.
					* \param[in] upper_threshold: The upper (high) threshold.
					* \throws I2CException if writing the thresholds fails.
					*/
					void set_thresholds(uint16_t lower_threshold, uint16_t upper_threshold);

					//! Sets the upper threshold back to its default value.
					/*!
					* Sets the upper threshold back to its default value.
					* \throws I2CException if writing the default upper thresholds fails.
					*/
					void restore_default_upper_thresholds();

					//! Sets the lower threshold back to its default value.
					/*!
					* Sets the lower threshold back to its default value.
					* \throws I2CException if writing the default lower thresholds fails.
					*/
					void restore_default_lower_thresholds();

					//! Sets both thresholds back to their default values.
					/*!
					* Sets both thresholds back to their default values.
					* \throws I2CException if writing the default thresholds fails.
					*/
					void restore_default_thresholds();

				protected:
					//! Extracts the multiplexer bits from the given byte and parses them into the resulting enum.
					/*!
					*  Extracts the multiplexer bits from the given byte and parses them into the resulting enum.
					* \param[in] raw_data: A setting byte that was read from the device.
					* \returns The parsed multiplexer value as Multiplexer enum.
					* \throws HALException if reading the multiplexer bits fails.
					*/
					static Multiplexer parse_multiplexer_value(uint8_t raw_data);

					//! Extracts the gain amplifier bits from the given byte and parses them into the resulting enum.
					/*!
					*  Extracts the gain amplifier bits from the given byte and parses them into the resulting enum.
					* \param[in] raw_data: A setting byte that was read from the device.
					* \returns The parsed gain amplifier value as GainAmplifier enum.
					* \throws HALException if reading the gain amplifier bits fails.
					*/
					static GainAmplifier parse_gain_amplifier_value(uint8_t raw_data);

					//! Extracts the operation mode bit from the given byte and parses it into the resulting enum.
					/*!
					*  Extracts the operation mode bit from the given byte and parses it into the resulting enum.
					* \param[in] raw_data: A setting byte that was read from the device.
					* \returns The parsed operation mode value as OperationMode enum.
					* \throws HALException if reading the operation mode bits fails.
					*/
					static OperationMode parse_operation_mode_value(uint8_t raw_data);

					//! Extracts the data rate bits from the given byte and parses them into the resulting enum.
					/*!
					*  Extracts the data rate bits from the given byte and parses them into the resulting enum.
					* \param[in] raw_data: A setting byte that was read from the device.
					* \returns The parsed data rate value as DataRate enum.
					* \throws HALException if reading the data rate bits fails.
					*/
					static DataRate parse_data_rate_value(uint8_t raw_data);

					//! Extracts the comparator mode bit from the given byte and parses it into the resulting enum.
					/*!
					*  Extracts the comparator mode bit from the given byte and parses it into the resulting enum.
					* \param[in] raw_data: A setting byte that was read from the device.
					* \returns The parsed comparator mode value as ComparatorMode enum.
					* \throws HALException if reading the comparator mode bits fails.
					*/
					static ComparatorMode parse_comparator_mode_value(uint8_t raw_data);

					//! Extracts the comparator polarity bit from the given byte and parses it into the resulting enum.
					/*!
					*  Extracts the comparator polarity bit from the given byte and parses it into the resulting enum.
					* \param[in] raw_data: A setting byte that was read from the device.
					* \returns The parsed comparator polarity value as AlertPolarity enum.
					* \throws HALException if reading the pin polarity bits fails.
					*/
					static AlertPolarity parse_comparator_polarity_value(uint8_t raw_data);

					//! Extracts the comparator latching bit from the given byte and parses it into the resulting enum.
					/*!
					*  Extracts the comparator latching bit from the given byte and parses it into the resulting enum.
					* \param[in] raw_data: A setting byte that was read from the device.
					* \returns The parsed comparator latching value as AlertLatching enum.
					* \throws HALException if reading the comparator latching bits fails.
					*/
					static AlertLatching parse_comparator_latching_value(uint8_t raw_data);

					//! Extracts the comparator queuing bits from the given byte and parses them into the resulting enum.
					/*!
					*  Extracts the comparator queuing bits from the given byte and parses them into the resulting enum.
					* \param[in] raw_data: A setting byte that was read from the device.
					* \returns The parsed comparator queuing value as AlertQueueing enum.
					* \throws HALException if reading the comparator queue bits fails.
					*/
					static AlertQueueing parse_comparator_queueing_value(uint8_t raw_data);

					//! Converts the bit value read via i2c based on the current gain amplifier to voltage.
					/*!
					*  Converts the bit value read via i2c based on the current gain amplifier to voltage.
					* \param[in] raw_data: The bit data read via i2c.
					* \returns The raw data converted to voltage.
					* \throws HALException if reading the current gain amplifier setting fails.
					*/
					double convert_to_voltage(uint16_t raw_data);

					//! Fall-back i2c write function that is used if m_write_function is nullptr.
					/*!
					*  Fall-back i2c write function that is used if m_write_function is nullptr.
					* \param[in] handle: The handle that will be used to communicate over the i2c bus.
					* \param[in] address: The file address to write to.
					* \param[in] buffer: The buffer containing the content to write.
					* \param[in] length: The number of bytes to write. Default is 2.
					* \returns 0 if writing was successful, a negative error value otherwise.
					* \throws I2CException if writing to the device fails.
					*/
					int8_t write_operation(int handle, uint8_t address, const uint8_t* buffer, uint16_t length = 2);

					//! Fall-back i2c read function that is used if m_read_function is nullptr.
					/*!
					*  Fall-back i2c write function that is used if m_read_function is nullptr.
					* \param[in] handle: The handle that will be used to communicate over the i2c bus.
					* \param[in] address: The file address to write to.
					* \param[in] buffer: The buffer containing the content to write.
					* \param[in] length: The number of bytes to write.
					* \returns 0 if reading was successful, a negative error value otherwise.
					* \throws I2CException if switching to the desired register fails.
					* \throws I2CException if reading from the device fails.
					*/
					int8_t read_operation(int handle, uint8_t address, uint8_t* buffer, uint16_t length = 2);

					int m_file_handle{};
					uint8_t m_dev_id{};
					uint8_t m_chip_id{};
				};
			}
		}
	}
}
