#pragma once

#include "../utils/time_converter.h"
#include <string>


namespace dto
{
	class sensor_dto
	{
	public:
		sensor_dto() : m_sensor_type_name(""), m_individual_name(""), m_timestamp(std::chrono::system_clock::now()), m_value(0) {	}

		sensor_dto(std::string sensor_type_name, std::string individual_name, std::chrono::time_point<std::chrono::system_clock> timestamp, double value) :
			m_sensor_type_name(sensor_type_name), m_individual_name(individual_name), m_timestamp(timestamp), m_value(value) {	}

		sensor_dto(std::string sensor_type_name, std::string individual_name, std::string timestamp, std::string time_format, double value) :
			m_sensor_type_name(sensor_type_name), m_individual_name(individual_name),
			m_timestamp(utils::time_converter::string_to_timepoint(timestamp, time_format)), m_value(value) { }

		sensor_dto(std::string sensor_type_name, std::string individual_name, std::string timestamp, double value) :
			m_sensor_type_name(sensor_type_name), m_individual_name(individual_name), m_timestamp(utils::time_converter::string_to_timepoint(timestamp)), m_value(value) { }

		~sensor_dto() { }

		inline void set_sensor_type_name(std::string new_sensor_type_name) { m_sensor_type_name = new_sensor_type_name; }
		inline void set_individual_name(std::string new_individual_name) { m_individual_name = new_individual_name; }
		inline void set_timestamp(std::chrono::time_point<std::chrono::system_clock> new_timestamp) { m_timestamp = new_timestamp; }
		inline void set_timestamp(std::string new_timestamp) { m_timestamp = utils::time_converter::string_to_timepoint(new_timestamp); }
		inline void set_timestamp(std::string new_timestamp, std::string time_format) { m_timestamp = utils::time_converter::string_to_timepoint(new_timestamp, time_format); }
		inline void set_value(double new_value) { m_value = new_value; }

		inline std::string get_sensor_type_name() const { return m_sensor_type_name; }
		inline std::string get_individual_name() const { return m_individual_name; }
		inline std::chrono::time_point<std::chrono::system_clock> get_timestamp_as_chrono() const { return m_timestamp; }
		inline std::string get_timestamp_as_string() const { return utils::time_converter::timepoint_to_string(m_timestamp); }
		inline double get_value() const { return m_value; }



	private:
		std::string m_sensor_type_name;
		std::string m_individual_name;
		std::chrono::time_point<std::chrono::system_clock> m_timestamp;
		double m_value;
	};
}

