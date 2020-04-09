#pragma once

namespace hal
{
	/*! Represents the various supported hardware devices. */
	enum class SensorName
	{
		/*!< BME280 barometer from Bosch that measures temperature, air pressure and air humidity. */
		BME280,
		/*!< CCS811 sensor from ams AG that measures CO2 concentration and total volatile organic compound (TVOC). */
		CCS811,
		/*!< CCS811 sensor from SGX Sensortech that measures CO, NO2, NH3, C3H8, C4H10, CH4, H2 and C2H5OH concentration. */
		MICS6814,
		/*!< KY_018 photo sensor from AZ-Delivery GmbH that measures lightness. */
		KY_018,
		/*!< ADS1115 analog digital converter (16 bit) from Texas Instruments with 4 analog inputs and i2c output. */
		ADS1115,
		/*!< AM312 pir sensor from NANYANG SENBA OPTICAL AND ELECTRONIC CO.,LTD. that detects motion. */
		AM312,
		/*!< DS3231 real time clock from Maxim Integrated Products, Inc. */
		DS3231
	};
}
