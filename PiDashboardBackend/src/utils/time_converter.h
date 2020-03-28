#pragma once

#include <chrono>
#include <ctime>
#include <iomanip>
#include <sstream>


namespace utils
{
	class time_converter
	{
	public:
		static std::string timepoint_to_string(std::chrono::time_point<std::chrono::system_clock> timepoint)
		{
			return timepoint_to_string(timepoint, default_time_format);
		}

		static std::string timepoint_to_string(std::chrono::time_point<std::chrono::system_clock> timepoint, std::string time_format)
		{
			auto time = std::chrono::system_clock::to_time_t(timepoint);
			std::tm tm = *std::localtime(&time);
			std::stringstream ss;
			ss << std::put_time(&tm, time_format.c_str());
			return ss.str();
		}

		static std::chrono::time_point<std::chrono::system_clock> string_to_timepoint(std::string timepoint)
		{
			return string_to_timepoint(timepoint, default_time_format);
		}

		static std::chrono::time_point<std::chrono::system_clock> string_to_timepoint(std::string timepoint, std::string time_format)
		{
			if (timepoint == "")
			{
				return std::chrono::system_clock::now();
			}
			else
			{
				if (time_format == "")
				{
					time_format = default_time_format;
				}

				std::tm tm = {};
				std::stringstream ss(timepoint);
				ss >> std::get_time(&tm, time_format.c_str());
				return std::chrono::system_clock::from_time_t(std::mktime(&tm));
			}
		}

		static constexpr char* default_time_format = "%Y-%m-%d %T";
	};
}