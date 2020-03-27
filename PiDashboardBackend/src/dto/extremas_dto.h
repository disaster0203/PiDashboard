#pragma once

#include <string>

namespace dto
{
	class extremas_dto
	{
	public:
		extremas_dto(std::string sensor_type_name = "", std::string individual_name = "", double count = 0, double sum = 0, double max = 0, double min = 0) :
			m_sensor_type_name(sensor_type_name), m_individual_name(individual_name), m_count(count), m_sum(sum), m_max(max), m_min(min) {	}

		~extremas_dto() { }

		void set_sensor_type_name(std::string new_sensor_type_name) { m_sensor_type_name = new_sensor_type_name; }

		void set_individual_name(std::string new_individual_name) { m_individual_name = new_individual_name; }

		void set_count(double new_count) { m_count = new_count; }

		void set_sum(double new_sum) { m_sum = new_sum; }

		void set_max(double new_max) { m_max = new_max; }

		void set_min(double new_min) { m_min = new_min; }

		std::string get_sensor_type_name() const { return m_sensor_type_name; }

		std::string get_individual_name() const { return m_individual_name; }

		double get_count() const { return m_count; }

		double get_sum() const { return m_sum; }

		double get_max() const { return m_max; }

		double get_min() const { return m_min; }


	private:
		std::string m_sensor_type_name;
		std::string m_individual_name;
		double m_count;
		double m_sum;
		double m_max;
		double m_min;
	};
}

