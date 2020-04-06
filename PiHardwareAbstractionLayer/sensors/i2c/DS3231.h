#pragma once

#include <vector>

#include "../../enums/SensorSetting.h"
#include "../../interfaces/ISensor.h"
#include "../../utils/Timezone.h"

#include "DS3231Constants.h"
#include "DS3231Definitions.h"

using namespace hal::utils;

namespace hal
{
	namespace sensors
	{
		namespace i2c
		{
			namespace ds3231
			{
				//! Class that communicates with the DS3231 rtc sensor (Maxim Integrated) via i2c.
				/*!
				* This class implements various functions to configure the rtc and receive the current time and date.
				*/
				class DS3231 final : public interfaces::ISensor
				{
				public:
					//! Default constructor.
					/*!
					* Default constructor.
					*/
					DS3231() = default;

					/*!
					* Tells the hardware to perform a new measurement. The result will be sent with a callback function.
					* If no callback is registered the measurement cannot be obtained.
					* \param[in] type: The type of measurement that has to do be done.
					* \throws HALException if triggering a time measurement fails.
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
					* \throws HALException if setting new hour format values fails.
					* \throws HALException if setting new oscillator state fails.
					* \throws HALException if setting new square wave state fails.
					* \throws HALException if setting new square wave rate fails.
					* \throws HALException if setting new timezone fails.
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

					//! Gets the current time and date.
					/*!
					* Gets the current time and date formatted with the currently set output format.
					* \returns the current time and date formatted with the currently set output format.
					* \throws I2CException if reading the current time and date from the device fails.
					*/
					std::string get_time_and_date();

					//! Tries to sync the RTCs time with the current system time.
					/*!
					* Tries to sync the RTCs time with the current system time. If the RTC sets the 
					* system time and no wifi connection is available this method will have no effect.
					* \throws I2CException if writing the corrected time and date to the device fails.
					*/
					void sync_time();

					//! Writes the hour format setting to the device.
					/*!
					* Writes the hour format setting to the device.
					* \param[in] format: The new hour format to set.
					* \throws I2CException if reading the current hour format setting from the device fails.
					* \throws HALException if manipulating the hour format bit fails.
					* \throws I2CException if writing the new hour format setting to the device fails.
					*/
					void set_hour_format(HourFormat format) const;

					//! Gets the current hour format.
					/*!
					* Gets the current hour format.
					* \returns the current hour format.
					* \throws I2CException if reading the current hour format from the device fails.
					* \throws HALException if checking the hour format bit fails.
					*/
					HourFormat get_hour_format() const;

					//! Changes the oscillator state of the device.
					/*!
					* Changes the oscillator state of the device.
					* \param[in] state: The new oscillator state to set.
					* \throws I2CException if reading the current oscillator state from the device fails.
					* \throws HALException if manipulating the oscillator state bit fails.
					* \throws I2CException if writing the new oscillator state to the device fails.
					*/
					void set_oscillator_state(OscillatorState state) const;

					//! Gets the current oscillator state.
					/*!
					* Gets the current oscillator state.
					* \returns the current oscillator state.
					* \throws I2CException if reading the current oscillator state from the device fails.
					* \throws HALException if checking the oscillator bit fails.
					*/
					OscillatorState get_oscillator_state() const;

					//! Changes the square wave state of the device.
					/*!
					* Changes the square wave state of the device.
					* \param[in] state: The new square wave state to set.
					* \throws I2CException if reading the current square wave state from the device fails.
					* \throws HALException if manipulating the square wave state bit fails.
					* \throws I2CException if writing the new square wave state to the device fails.
					*/
					void set_square_wave_state(SquareWaveState state) const;

					//! Gets the current square wave state.
					/*!
					* Gets the current square wave state.
					* \returns the current square wave state.
					* \throws I2CException if reading the current square wave state from the device fails.
					* \throws HALException if checking the square wave state bit fails.
					*/
					SquareWaveState get_square_wave_state() const;

					//! Changes the square wave rate of the device.
					/*!
					* Changes the square wave rate of the device.
					* \param[in] rate: The new square wave rate to set.
					* \throws I2CException if reading the current square wave rate from the device fails.
					* \throws HALException if manipulating the square wave rate bit fails.
					* \throws I2CException if writing the new square wave rate to the device fails.
					*/
					void set_square_wave_rate(SquareWaveRate rate) const;

					//! Gets the current square wave rate.
					/*!
					* Gets the current square wave rate.
					* \returns the current square wave rate.
					* \throws I2CException if reading the current square wave rate from the device fails.
					* \throws HALException if checking the square wave rate bit fails.
					*/
					SquareWaveRate get_square_wave_rate() const;

					//! Sets the timezone to use.
					/*!
					* Sets the timezone to use.
					* \param[in] timezone: The timezone to set.
					*/
					void set_timezone(WorldTimezones timezone) noexcept;

					//! Gets the current timezone.
					/*!
					* Gets the current timezone.
					* \returns the current timezone.
					*/
					WorldTimezones get_timezone() const noexcept;

					//! Sets the format to use for output of the current time and date.
					/*!
					* Sets the format to use for output of the current time and date.
					* \param[in] format: The new clock format to set.
					* See https://en.cppreference.com/w/cpp/io/manip/put_time for a list 
					* of supported variables.
					*/
					void set_clock_format(const std::string& format) noexcept;

					//! Gets the current clock format.
					/*!
					* Gets the current clock format.
					* \returns the current clock format.
					*/
					std::string get_clock_format() const noexcept;

					//! Sets the output format to use.
					/*!
					* Sets the output format to use.
					* \param[in] format: The output format to set.
					*/
					void set_output_format(OutputFormat format) noexcept;

					//! Gets the current output format.
					/*!
					* Gets the current output format.
					* \returns the current output format.
					*/
					OutputFormat get_output_format() const noexcept;

					//! Changes all device settings at once.
					/*!
					* Changes all device settings at once.
					* \param[in] settings: The new device settings.
					* \throws I2CException if reading the current settings from the device fails.
					* \throws HALException if manipulating the setting bits fails.
					* \throws I2CException if writing the new settings to the device fails.
					*/
					void set_settings(const SettingsData& settings);

					//! Gets all device settings at once.
					/*!
					* Gets all device settings at once.
					* \returns the current device settings.
					* \throws I2CException if reading the current settings from the device fails.
					*/
					SettingsData get_settings() const;

					//! Get the current seconds value.
					/*!
					* Get the current seconds value.
					* \returns The current seconds in the range 0 - 59.
					* \throws I2CException if reading the current seconds from the device fails.
					*/
					uint8_t get_seconds() const;

					//! Get the current minutes value.
					/*!
					* Get the current minutes value.
					* \returns The current minutes in the range 0 - 59.
					* \throws I2CException if reading the current minutes from the device fails.
					*/
					uint8_t get_minutes() const;

					//! Get the current hour value.
					/*!
					* Get the current hour value.
					* \returns The current hour in the range 1 - 12 / 0 - 23.
					* \throws I2CException if reading the current hour from the device fails.
					*/
					uint8_t get_hours() const;

					//! Whether it is currently AM or PM.
					/*!
					* Whether it is currently AM or PM.
					* \returns Whether it is currently AM or PM.
					* \throws I2CException if reading the AM/PM bit from the device fails.
					*/
					AmPm get_am_pm() const;

					//! Get the current day value.
					/*!
					* Get the current day value.
					* \returns The current day in the range 1 - 7.
					* \throws I2CException if reading the current day from the device fails.
					*/
					uint8_t get_day() const;

					//! Get the current date value.
					/*!
					* Get the current date value.
					* \returns The current date in the range 1 - 31.
					* \throws I2CException if reading the current date from the device fails.
					*/
					uint8_t get_date() const;

					//! Get the current month value.
					/*!
					* Get the current month value.
					* \returns The current month in the range 1 - 12.
					* \throws I2CException if reading the current month from the device fails.
					*/
					uint8_t get_month() const;

					//! Get the current year value.
					/*!
					* Get the current year value.
					* \returns The current year in the range 0 - 99.
					* \throws I2CException if reading the current year from the device fails.
					*/
					uint8_t get_year() const;

					//! Triggers a manual recalibration to the current device temperature.
					/*!
					* Triggers a manual recalibration to the current device temperature. Usually
					* this functionality is not needed under normal circumstances. The recalibration
					* is automatically done every 64 seconds and a manual adjustment may only be
					* necessary in extreme environmental setups or if extreme high accuracy is needed
					* for the time and date.
					* \throws I2CException if triggering a manual recalibration fails.
					*/
					void calibrate_to_current_temperature();

					//! Get the current device temperature (in Degree Celsius).
					/*!
					* Get the current device temperature (in Degree Celsius).
					* \returns the current device temperature (accuracy = 0.25 Degree Celsius).
					* \throws I2CException if reading the current device temperature from the device fails.
					*/
					double get_current_device_temperature() const;

				protected:
					//! Reads the control register.
					/*!
					* Reads the control register.
					* \returns the control register.
					* \throws I2CException if reading the control register from the device fails.
					*/
					uint8_t read_control_register() const;

					//! Reads the status register.
					/*!
					* Reads the status register.
					* \returns the status register.
					* \throws I2CException if reading the status register from the device fails.
					*/
					uint8_t read_status_register() const;

					Timezone m_timezone = Timezone(WorldTimezones::COORDINATED_UNIVERSAL_TIME__UTC__PLUS_H00M00);
					std::string m_clock_format = "%d.%m.%Y %H:%M:%S";
					OutputFormat m_output_format = OutputFormat::FORMATTED_STRING;
					bool m_synced_during_this_run = false;
					int m_file_handle{};
					uint8_t m_dev_id{};
				};
			}
		}
	}
}