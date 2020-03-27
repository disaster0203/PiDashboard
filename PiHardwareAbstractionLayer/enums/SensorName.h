#pragma once

namespace hal
{
	/*! Represents the various supported hardware devices. */
	enum class SensorName
	{
		BME280,
		/*!< BME280 barometer from Bosch that measures temperature, air pressure and air humidity. */
		CCS811,
		/*!< CCS811 sensor from ams AG that measures CO2 concentration and total volatile organic compound (TVOC). */
		KY_018,
		/*!< KY_018 photo sensor from AZ-Delivery GmbH that measures lightness. */
		ADS1115,
		/*!< ADS1115 analog digital converter (16 bit) from Texas Instruments with 4 analog inputs and i2c output. */
		AM312,
		/*!< AM312 pir sensor from NANYANG SENBA OPTICAL AND ELECTRONIC CO.,LTD. that detects motion. */
		DS3231 /*!< DS3231 real time clock from Maxim Integrated Products, Inc. */
	};
}
