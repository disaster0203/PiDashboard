#pragma once

namespace hal
{
	/*! Represents the various supported measurement types. */
	enum class SensorType
	{
		CONVERTER,
		/*!< A analog digital converter. */
		TEMPERATURE,
		/*!< A sensor measuring temperatures. */
		AIR_PRESSURE,
		/*!< A sensor measuring air pressure. */
		AIR_HUMIDITY,
		/*!< A sensor measuring air humidity. */
		CO2,
		/*!< A sensor measuring the concentration of CO2. */
		TVOC,
		/*!< A sensor measuring the total volatile organic compound. */
		CLOCK,
		/*!< A real time clock measuring time and date. */
		MOTION,
		/*!< A sensor detecting motion in its field of view. */
		LIGHT /*!< A sensor measuring the current lightness. */
	};
}
