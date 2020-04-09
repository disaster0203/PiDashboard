#pragma once

namespace hal
{
	/*! Represents the various supported measurement types. */
	enum class SensorType
	{
		/*!< A analog digital converter. */
		CONVERTER,
		/*!< A sensor measuring temperatures. */
		TEMPERATURE,
		/*!< A sensor measuring air pressure. */
		AIR_PRESSURE,
		/*!< A sensor measuring air humidity. */
		AIR_HUMIDITY,
		/*!< A sensor measuring the total volatile organic compound. */
		TVOC,
		/*!< A sensor measuring the concentration of carbon dioxide (CO2). */
		CARBON_DIOXIDE_CO2,
		/*!< A sensor measuring the concentration of carbon monoxide (CO). */
		CARBON_MONOXIDE_CO,
		/*!< A sensor measuring the concentration of nitrogen dioxide (NO2). */
		NITROGEN_DIOXIDE_NO2,
		/*!< A sensor measuring the concentration of ammoniac (NH3). */
		AMMONIAC_NH3,
		/*!< A sensor measuring the concentration of propane (C3H8). */
		PROPANE_C3H8,
		/*!< A sensor measuring the concentration of butane (C4H10). */
		BUTANE_C4H10,
		/*!< A sensor measuring the concentration of methane (CH4). */
		METHANE_CH4,
		/*!< A sensor measuring the concentration of hydrogen (H2). */
		HYDROGEN_H2,
		/*!< A sensor measuring the concentration of ethanol (C2H5OH). */
		ETHANOL_C2H5OH,
		/*!< A real time clock measuring time and date. */
		CLOCK,
		/*!< A sensor detecting motion in its field of view. */
		MOTION,
		/*!< A sensor measuring the current lightness. */
		LIGHT
	};
}
