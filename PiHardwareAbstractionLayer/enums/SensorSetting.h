#pragma once

namespace hal
{
	/*! Defines the properties that can be set in order to configure hardware sensors. Note 
	* that not all sensors allow all properties to be set. Use \sa {ISensor::available_configurations()} 
	* to check which properties are supported by a specific sensor. */
	enum class SensorSetting
	{
		/*!< Allows to change the oversampling factor. */
		OVERSAMPLING,
		/*!< Allows to set the filter size. This reduces outliers due to short time environmental disturbances. */
		FILTER,
		/*!< Allows to read or set a baseline that will be used to correct the sensors output. The correction is needed due to environmental impacts. */
		BASELINE,
		/*!< Allows to pass additional environmental data (e.g. temperature) to a sensor in order to get more accurate measurement results. */
		ENVIRONMENT_DATA,
		/*!< Allows to get or set a threshold value that new sensor measurements need to pass in order to result in a new sensor result. */
		THRESHOLD,
		/*!< Allows to specify differential or single ended input. */
		MULTIPLEXER,
		/*!< Allows to set a gain value that is used to increase the power of an input signal. */
		GAIN_AMPLIFIER,
		/*!< Allows to set the data rate. */
		DATA_RATE,
		/*!< Allows to switch comparator modes. */
		COMPARATOR_MODE,
		/*!< Allows to switch latching mode of the comparator. */
		COMPARATOR_LATCHING,
		/*!< Allows to set the size of the comparator queue. */
		COMPARATOR_QUEUE,
		/*!< Allows to set the state a pin has when being asserted as active (HIGH or LOW). */
		PIN_POLARITY,
		/*!< Allows to set the hour format of a clock to 12-hour or 24-hour format. */
		HOUR_FORMAT,
		/*!< Allows to start or stop an oscillator. */
		OSCILLATOR_STATE,
		/*!< Allows to enable or disable a square wave output. */
		SQUARE_WAVE_STATE,
		/*!< Allows to set the square waves rate in Herz. */
		SQUARE_WAVE_RATE,
		/*!< Allows to set the current timezone. */
		TIMEZONE,
		/*!< Allows to define the values and the format of a clock. */
		CLOCK_FORMAT,
		/*!< Allows to define whether a clock returns time as a formatted string or as a (stringified) int32. */
		OUTPUT_FORMAT,
		/*!< Allows to sync the time of a clock. */
		TIME_SYNC
	};
}
