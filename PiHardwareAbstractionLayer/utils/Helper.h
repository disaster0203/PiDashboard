#pragma once

#include "../utils/Constants.h"
#include "../exceptions/HALException.h"

#include <type_traits>

namespace hal
{
	namespace utils
	{
		class Helper
		{
		public:
			//! Checks if the given pointer is null.
			/*!
			*  Checks if the given pointer is null.
			* \param[in] pointer: The pointer to check.
			* \returns 0 if the pointer is not null and -1 if the pointer is null.
			*/
			static int8_t null_check(void* pointer) noexcept
			{
				if (pointer != nullptr)
				{
					return OK;
				}

				return NULL_PTR;
			}

			//! Checks if the given shared pointer is null.
			/*!
			*  Checks if the given shared pointer is null.
			* \param[in] pointer: The shared pointer to check. T can be any type.
			* \returns 0 if the shared pointer is not null and -1 if the shared pointer is null.
			*/
			template <typename T>
			static int8_t null_check(std::shared_ptr<T> pointer) noexcept
			{
				if (pointer)
				{
					return OK;
				}

				return NULL_PTR;
			}

			//! Transforms a given array into a string.
			/*!
			*  Transforms a given array into a string where the single values are separated by the given separator.
			* \param[in] arr: The array to transform to a string. T must be convertible to string.
			* \param[in] separator: An string that will be placed between the values of the array. Can be "" if no separator is needed.
			* \returns The array transformed to a string.
			*/
			template <typename T>
			static std::string array_to_string(std::vector<T> arr, std::string separator = ",") noexcept
			{
				std::string result = "";
				for (const auto& i : arr)
				{
					result += std::to_string(i) + separator;
				}

				return result.substr(0, result.length() - separator.length());
			}

			//! Checks if a string contains the given separator.
			/*!
			*  Checks if a string contains the given separator.
			* \param[in] setting: The string that has to be checked.
			* \param[in] separator: The separator to search for.
			* \returns True if the string contains the separator, false otherwise.
			*/
			static bool string_contains_separator(const std::string setting, const std::string separator = ",") noexcept
			{
				return setting.find(separator) != std::string::npos;
			}

			//! Splits a given string into an array.
			/*!
			*  Splits a given string into an array by using the given separator.
			* \param[out] output: The array to fill with the string values.
			* T must be a number or boolean (boolean, uint8_t, int8_t, uint16_t, int16_t, int, float, double).
			* \param[in] setting: The string that has to be splitted.
			* \param[in] separator: An string that is placed between the single values and will be used to split the settings.
			* If the separator is "" no splitting will be done.
			*/
			template <typename T>
			static void string_to_array(std::vector<T>& output, std::string setting, const std::string separator = ",") noexcept
			{
				size_t pos;
				while ((pos = setting.find(separator)) != std::string::npos)
				{
					output.push_back(convert(setting.substr(0, pos), T()));
					setting.erase(0, pos + separator.length());
				}
				output.push_back(convert(setting, T()));
			}

			//! Converts the value of a given string to a boolean value.
			/*!
			*  Converts the value of a given string to a boolean value.
			* \param[in] str: the string to convert to boolean. 
			* Supported values are: '1', '0', 'true', 'false', 'TRUE' and 'FALSE'.
			* \returns a boolean with the value of the input string.
			*/
			static bool string_to_bool(const std::string& str) noexcept
			{
				if (str == "1" || str == "true" || str == "True" || str == "TRUE")
				{
					return true;
				}
				return false;
			}

			//! Converts the value of a given string to a uint8_t (unsigned char) value.
			/*!
			*  Converts the value of a given string to a uint8_t (unsigned char) value.
			* \param[in] str: the string to convert to uint8_t (unsigned char).
			* \returns a uint8_t (unsigned char) with the value of the input string.
			*/
			static uint8_t string_to_uint8_t(const std::string& str)
			{
				return static_cast<uint8_t>(std::stoi(str));
			}

			//! Converts the value of a given string to an int8_t (signed char) value.
			/*!
			*  Converts the value of a given string to an int8_t (signed char) value.
			* \param[in] str: the string to convert to int8_t (signed char).
			* \returns an int8_t (signed char) with the value of the input string.
			*/
			static int8_t string_to_int8_t(const std::string& str)
			{
				return static_cast<int8_t>(std::stoi(str));
			}

			//! Converts the value of a given string to a uint16_t (unsigned short) value.
			/*!
			*  Converts the value of a given string to a uint16_t (unsigned short) value.
			* \param[in] str: the string to convert to uint16_t (unsigned short).
			* \returns a uint16_t (unsigned short) with the value of the input string.
			*/
			static uint16_t string_to_uint16_t(const std::string& str)
			{
				return static_cast<uint16_t>(std::stoi(str));
			}

			//! Converts the value of a given string to an int16_t (signed short) value.
			/*!
			*  Converts the value of a given string to an int16_t (signed short) value.
			* \param[in] str: the string to convert to int16_t (signed short).
			* \returns an int16_t (signed short) with the value of the input string.
			*/
			static int16_t string_to_int16_t(const std::string& str)
			{
				return static_cast<int16_t>(std::stoi(str));
			}

			//! Converts the value of a given string to an int value.
			/*!
			*  Converts the value of a given string to an int value.
			* \param[in] str: the string to convert to int.
			* \returns an int with the value of the input string.
			*/
			static int string_to_int(const std::string& str)
			{
				return std::stoi(str);
			}

			//! Converts the value of a given string to a float value.
			/*!
			*  Converts the value of a given string to a float value.
			* \param[in] str: the string to convert to float.
			* \returns a float with the value of the input string.
			*/
			static float string_to_float(const std::string& str)
			{
				return std::stof(str);
			}

			//! Converts the value of a given string to a double value.
			/*!
			*  Converts the value of a given string to a double value.
			* \param[in] str: the string to convert to double.
			* \returns a double with the value of the input string.
			*/
			static double string_to_double(const std::string& str)
			{
				return std::stod(str);
			}

		protected:
			//! Converts a given string into the desired type.
			/*!
			*  Converts a given string into the desired type.
			* \param[in] str: The string that has to be converted.
			* \param[in] type: The desired result type
			* T must be a number or boolean (boolean, uint8_t, int8_t, uint16_t, int16_t, int, float, double).
			* \returns The value of the input string converted to the desired type T.
			* \throws HALException if the type to convert to is not supported.
			*/
			template <typename T>
			static T convert(const std::string str, T type)
			{
				if (std::is_same<T, bool>::value)
				{
					return string_to_bool(str);
				}
				if (std::is_same<T, uint8_t>::value)
				{
					return string_to_uint8_t(str);
				}
				if (std::is_same<T, int8_t>::value)
				{
					return string_to_int8_t(str);
				}
				if (std::is_same<T, uint16_t>::value)
				{
					return string_to_uint16_t(str);
				}
				if (std::is_same<T, int16_t>::value)
				{
					return string_to_int16_t(str);
				}
				if (std::is_same<T, int>::value)
				{
					return string_to_int(str);
				}
				if (std::is_same<T, float>::value)
				{
					return string_to_float(str);
				}
				if (std::is_same<T, double>::value)
				{
					return string_to_double(str);
				}
				throw exception::HALException("Helper", "convert",
														std::string("Could not convert string '").append(str).append(
															"' since the given input type is not supported."));
			}
		};
	}
}
