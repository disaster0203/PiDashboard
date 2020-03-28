#pragma once

namespace hal
{
	/*! Defines the properties that can be set in order to configure hardware sensors. Note 
	* that not all sensors allow all properties to be set. Use \sa {ISensor::available_configurations()} 
	* to check which properties are supported by a specific sensor. */
	enum class SensorSetting
	{
		OVERSAMPLING,
		/*!< Allows to change the oversampling factor. */
		FILTER,
		/*!< Allows to set the filter size. This reduces outliers due to short time environmental disturbances. */
		BASELINE,
		/*!< Allows to read or set a baseline that will be used to correct the sensors output. The correction is needed due to environmental impacts. */
		ENVIRONMENT_DATA,
		/*!< Allows to pass additional environmental data (e.g. temperature) to a sensor in order to get more accurate measurement results. */
		THRESHOLD,
		/*!< Allows to get or set a threshold value that new sensor measurements need to pass in order to result in a new sensor result. */
		MULTIPLEXER,
		/*!< Allows to specify differential or single ended input. */
		GAIN_AMPLIFIER,
		/*!< Allows to set a gain value that is used to increase the power of an input signal. */
		DATA_RATE,
		/*!< Allows to set the data rate. */
		COMPARATOR_MODE,
		/*!< Allows to switch comparator modes. */
		COMPARATOR_LATCHING,
		/*!< Allows to switch latching mode of the comparator. */
		COMPARATOR_QUEUE,
		/*!< Allows to set the size of the comparator queue. */
		PIN_POLARITY /*!< Allows to set the state a pin has when being asserted as active (HIGH or LOW). */
	};
}
