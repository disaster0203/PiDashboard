#pragma once

#include "ISensor.h"
#include "../exceptions/HALException.h"

namespace hal
{
	namespace interfaces
	{
		/*!
		* Interface each sensor implements to offer a basic set of functionality.
		*/
		class IConverter : public ISensor
		{
		public:
			IConverter() = default;

			IConverter(const IConverter& rhs) 
			{
				m_callbacks = rhs.m_callbacks; 
				m_analog_pins = rhs.m_analog_pins;
			}

			IConverter(IConverter&&) = delete;
			virtual ~IConverter() = default;
			IConverter& operator=(const IConverter& ex) = delete;
			IConverter& operator=(IConverter&&) = delete;

			//! Registers a new analog sensor to the given analog input pin of the converter.
			/*!
			* Registers a new analog sensor to the given analog input pin of the converter.
			* \throws HALException if the pin is already occupied.
			* \throws HALException if the pin number is out of range.
			*/
			void register_analog_device(uint8_t pin)
			{
				if (m_analog_pins.find(pin) == m_analog_pins.end())
				{
					throw exception::HALException("IConverter", "register_analog_device", std::string("Pin ").append(std::to_string(pin)
						.append("is out of range. This converter has ").append(std::to_string(get_number_of_analog_pins())).append(" analog pins.")));
				}

				if (m_analog_pins[pin])
				{
					throw exception::HALException("IConverter", "register_analog_device", std::string("Pin ").append(std::to_string(pin)
						.append("is already registered to another analog sensor.")));
				}

				m_analog_pins[pin] = true;
			}

			//! Returns whether the given pin is already occupied by an analog sensor or not.
			/*!
			* Returns whether the given pin is already occupied by an analog sensor or not.
			* \returns True if the pin is still free, false if it is already occupied.
			* \throws HALException if the pin number is out of range.
			*/
			bool is_analog_pin_free(uint8_t pin)
			{
				if (m_analog_pins.find(pin) == m_analog_pins.end())
				{
					throw exception::HALException("IConverter", "is_analog_pin_free", std::string("Pin ").append(std::to_string(pin)
						.append("is out of range. This converter has ").append(std::to_string(get_number_of_analog_pins())).append(" analog pins.")));
				}

				return !m_analog_pins[pin]; // false means "no sensor" -> invert the value
			}

			//! Returns whether all pins are free.
			/*!
			* Returns whether all pins are free which means that this converter is not used
			* by any analog sensor at the moment.
			* \returns True if all pins are free, false if minimum one analog sensor is using
			* this converter.
			*/
			bool are_analog_pins_free() noexcept
			{
				for (auto const& pin : m_analog_pins)
				{
					if (pin.second)
					{
						return false;
					}
				}
				return true;
			}

			//! Returns the analog pin map of this converter.
			/*!
			* Returns the analog pin map of this converter. The map contains information about all
			* available pins and their current status (e.g. if an analog sensor is currently using it).
			* \returns The pin map of the converter.
			*/
			std::map<uint8_t, bool> get_analog_pins_map() noexcept
			{
				return m_analog_pins;
			}

			//! Returns how many analog pins the converter has.
			/*!
			* Returns how many analog pins the converter has.
			* \returns The number of analog pins.
			*/
			unsigned int get_number_of_analog_pins() noexcept
			{
				return m_analog_pins.size();
			}

			//! Returns how many analog pins are currently unused.
			/*!
			* Returns how many analog pins are currently unused.
			* \returns The number of unused analog pins.
			*/
			unsigned int get_number_of_free_analog_pins() noexcept
			{
				uint8_t number = 0;
				for (auto const& pin : m_analog_pins)
				{
					if (!pin.second)
					{
						number++;
					}
				}
				return number;
			}

			//! Returns how many analog pins are currently used.
			/*!
			* Returns how many analog pins are currently used.
			* \returns The number of used analog pins.
			*/
			unsigned int get_number_of_occupied_analog_pins() noexcept
			{
				return get_number_of_analog_pins() - get_number_of_free_analog_pins();
			}

		protected:
			/*! A map storing the analog input pins. */
			std::map<uint8_t, bool> m_analog_pins;
		};
	}
}