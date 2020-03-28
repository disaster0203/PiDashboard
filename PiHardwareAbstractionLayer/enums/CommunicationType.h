#pragma once

namespace hal
{
	/*! Represents the various supported communication types. This enum is just 
	* for information purpose and cannot be set by the user. Each sensor has its
	* own predefined communication type that cannot be changed. However the com-type
	* does not need to bother the user.
	*/
	enum class CommunicationType
	{
		DIGITAL,
		/*!< The device is a digital sensor that sends binary data (0 and 1). */
		ANALOG_I2C,
		/*!< The device is a analog sensor that sends voltage data which is converted to binary data and sent via i2c by using an ADC. */
		I2C,
		/*!< The device is a i2c sensor that sends data that is already converted to the target unit. */
		UART,
		/*!< The device is a UART sensor. */
		SPI /*!< The device is a SPI sensor. */
	};
}
