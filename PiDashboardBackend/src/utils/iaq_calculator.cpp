#include "iaq_calculator.h"

void utils::iaq_calculator::add_temperature(double new_temperature)
{
	m_iaq_components[iaq_component::TEMPERATURE].points = new_temperature;
	rate_temperature(m_iaq_components[iaq_component::TEMPERATURE]);
	calculate_overall_iaq();
}

void utils::iaq_calculator::add_co(uint16_t new_co)
{
	m_iaq_components[iaq_component::CO].points = new_co;
	rate_co(m_iaq_components[iaq_component::CO]);
	calculate_overall_iaq();
}

void utils::iaq_calculator::add_co2(uint16_t new_co2)
{
	m_iaq_components[iaq_component::CO2].points = new_co2;
	rate_co2(m_iaq_components[iaq_component::CO2]);
	calculate_overall_iaq();
}

void utils::iaq_calculator::add_tvoc(uint16_t new_tvco)
{
	m_iaq_components[iaq_component::TVOC].points = new_tvco;
	rate_tvoc(m_iaq_components[iaq_component::TVOC]);
	calculate_overall_iaq();
}

void utils::iaq_calculator::add_humidity(double new_humidity)
{
	m_iaq_components[iaq_component::HUMIDITY].points = new_humidity;
	rate_humidity(m_iaq_components[iaq_component::HUMIDITY]);
	calculate_overall_iaq();
}

void utils::iaq_calculator::add_no2(double new_no2)
{
	m_iaq_components[iaq_component::NO2].points = new_no2;
	rate_no2(m_iaq_components[iaq_component::NO2]);
	calculate_overall_iaq();
}

void utils::iaq_calculator::add(double new_temperature, uint16_t new_co, uint16_t new_co2, uint16_t new_tvco, double new_humidity, double new_no2)
{
	add_temperature(new_temperature);
	add_co(new_co);
	add_co2(new_co2);
	add_tvoc(new_tvco);
	add_humidity(new_humidity);
	add_no2(new_no2);
}

utils::iaq_rating utils::iaq_calculator::get_rating(iaq_component component)
{
	return m_iaq_components[component].rating;
}

utils::iaq_rating utils::iaq_calculator::get_overall_rating()
{
	return m_overall_rating;
}

std::tuple<utils::iaq_component, utils::iaq_rating> utils::iaq_calculator::get_best_rating()
{
	uint8_t max = 0;
	iaq_component max_comp;
	iaq_rating max_rating;
	for (auto iter = m_iaq_components.begin(); iter != m_iaq_components.end(); ++iter)
	{
		if (iter->second.points >= max)
		{
			max = iter->second.points;
			max_rating = iter->second.rating;
			max_comp = iter->first;
		}
	}
	return std::make_tuple(max_comp, max_rating);
}

std::tuple<utils::iaq_component, utils::iaq_rating> utils::iaq_calculator::get_worst_rating()
{
	uint8_t min = m_iaq_components.size() * EXCELLENT_POINTS;
	iaq_component min_comp;
	iaq_rating min_rating;
	for (auto iter = m_iaq_components.begin(); iter != m_iaq_components.end(); ++iter)
	{
		if (iter->second.points <= min)
		{
			min = iter->second.points;
			min_rating = iter->second.rating;
			min_comp = iter->first;
		}
	}
	return std::make_tuple(min_comp, min_rating);
}

std::map<utils::iaq_component, utils::iaq_rating> utils::iaq_calculator::get_component_ratings()
{
	std::map<iaq_component, iaq_rating> result;
	for (auto iter = m_iaq_components.begin(); iter != m_iaq_components.end(); ++iter)
	{
		result[iter->first] = iter->second.rating;
	}
	return result;
}

uint8_t utils::iaq_calculator::get_points(iaq_component component)
{
	return m_iaq_components[component].points;
}

uint8_t utils::iaq_calculator::get_overall_points()
{
	return m_overall_points;
}

std::tuple<utils::iaq_component, uint8_t> utils::iaq_calculator::get_best_points()
{
	uint8_t max = 0;
	iaq_component max_comp;
	for (auto iter = m_iaq_components.begin(); iter != m_iaq_components.end(); ++iter)
	{
		if (iter->second.points >= max)
		{
			max = iter->second.points;
			max_comp = iter->first;
		}
	}
	return std::make_tuple(max_comp, max);
}

std::tuple<utils::iaq_component, uint8_t> utils::iaq_calculator::get_worst_points()
{
	uint8_t min = m_iaq_components.size() * EXCELLENT_POINTS;
	iaq_component min_comp;
	for (auto iter = m_iaq_components.begin(); iter != m_iaq_components.end(); ++iter)
	{
		if (iter->second.points <= min)
		{
			min = iter->second.points;
			min_comp = iter->first;
		}
	}
	return std::make_tuple(min_comp, min);
}

std::map<utils::iaq_component, uint8_t> utils::iaq_calculator::get_component_points()
{
	std::map<iaq_component, uint8_t> result;
	for (auto iter = m_iaq_components.begin(); iter != m_iaq_components.end(); ++iter)
	{
		result[iter->first] = iter->second.points;
	}
	return result;
}

utils::iaq_rating utils::iaq_calculator::get_best_history_rating()
{
	return m_history_best_overall_iaq_rating;
}

utils::iaq_rating utils::iaq_calculator::get_worst_history_rating()
{
	return m_history_worst_overall_iaq_rating;
}

uint8_t utils::iaq_calculator::get_best_history_points()
{
	return m_history_best_overall_iaq_points;
}

uint8_t utils::iaq_calculator::get_worst_history_points()
{
	return m_history_worst_overall_iaq_points;
}

void utils::iaq_calculator::reset()
{
	m_overall_rating = iaq_rating::INADEQUATE;
	m_history_best_overall_iaq_rating = iaq_rating::INADEQUATE;
	m_history_worst_overall_iaq_rating = iaq_rating::INADEQUATE;
	m_overall_points = 0;
	m_history_best_overall_iaq_points = 0;
	m_history_worst_overall_iaq_points = 0;

	for (auto iter = m_iaq_components.begin(); iter != m_iaq_components.end(); ++iter)
	{
		iter->second.points = 0;
		iter->second.rating = iaq_rating::INADEQUATE;
		iter->second.value = 0;
	}
}

void utils::iaq_calculator::rate_temperature(component_container& component)
{
	if (component.value >= 18.0 && component.value <= 21.0)
	{
		component.points = EXCELLENT_POINTS;
		component.rating = iaq_rating::EXCELLENT;
	}
	else if (component.value < 18.0 && component.value >= 17.0 || component.value > 21.0 && component.value <= 22.0)
	{
		component.points = GOOD_POINTS;
		component.rating = iaq_rating::GOOD;
	}
	else if (component.value < 17.0 && component.value >= 16.0 || component.value > 22.0 && component.value <= 23.0)
	{
		component.points = FAIR_POINTS;
		component.rating = iaq_rating::FAIR;
	}
	else if (component.value < 16.0 && component.value >= 15.0 || component.value > 23.0 && component.value <= 24.0)
	{
		component.points = POOR_POINTS;
		component.rating = iaq_rating::POOR;
	}
	else
	{
		component.points = INADEQUATE_POINTS;
		component.rating = iaq_rating::INADEQUATE;
	}
}

void utils::iaq_calculator::rate_co(component_container& component)
{
	if (component.value == 0.0)
	{
		component.points = EXCELLENT_POINTS;
		component.rating = iaq_rating::EXCELLENT;
	}
	else if (component.value >= 1.0 && component.value <= 7.0)
	{
		component.points = FAIR_POINTS;
		component.rating = iaq_rating::FAIR;
	}
	else
	{
		component.points = INADEQUATE_POINTS;
		component.rating = iaq_rating::INADEQUATE;
	}
}

void utils::iaq_calculator::rate_co2(component_container& component)
{
	if (component.value <= 600.0)
	{
		component.points = EXCELLENT_POINTS;
		component.rating = iaq_rating::EXCELLENT;
	}
	else if (component.value > 600.0 && component.value <= 800.0)
	{
		component.points = GOOD_POINTS;
		component.rating = iaq_rating::GOOD;
	}
	else if (component.value > 800.0 && component.value <= 1500.0)
	{
		component.points = FAIR_POINTS;
		component.rating = iaq_rating::FAIR;
	}
	else if (component.value > 1500.0 && component.value <= 1800.0)
	{
		component.points = POOR_POINTS;
		component.rating = iaq_rating::POOR;
	}
	else
	{
		component.points = INADEQUATE_POINTS;
		component.rating = iaq_rating::INADEQUATE;
	}
}

void utils::iaq_calculator::rate_tvoc(component_container& component)
{
	if (component.value <= 0.1)
	{
		component.points = EXCELLENT_POINTS;
		component.rating = iaq_rating::EXCELLENT;
	}
	else if (component.value > 0.1 && component.value <= 0.3)
	{
		component.points = GOOD_POINTS;
		component.rating = iaq_rating::GOOD;
	}
	else if (component.value > 0.3 && component.value <= 0.5)
	{
		component.points = FAIR_POINTS;
		component.rating = iaq_rating::FAIR;
	}
	else if (component.value > 0.5 && component.value <= 1.0)
	{
		component.points = POOR_POINTS;
		component.rating = iaq_rating::POOR;
	}
	else
	{
		component.points = INADEQUATE_POINTS;
		component.rating = iaq_rating::INADEQUATE;
	}
}

void utils::iaq_calculator::rate_humidity(component_container& component)
{
	if (component.value >= 40.0 && component.value <= 60.0)
	{
		component.points = EXCELLENT_POINTS;
		component.rating = iaq_rating::EXCELLENT;
	}
	else if (component.value < 40.0 && component.value >= 30.0 || component.value > 60.0 && component.value <= 70.0)
	{
		component.points = GOOD_POINTS;
		component.rating = iaq_rating::GOOD;
	}
	else if (component.value < 30.0 && component.value >= 20.0 || component.value > 70.0 && component.value <= 80.0)
	{
		component.points = FAIR_POINTS;
		component.rating = iaq_rating::FAIR;
	}
	else if (component.value < 20.0 && component.value >= 10.0 || component.value > 80.0 && component.value <= 90.0)
	{
		component.points = POOR_POINTS;
		component.rating = iaq_rating::POOR;
	}
	else
	{
		component.points = INADEQUATE_POINTS;
		component.rating = iaq_rating::INADEQUATE;
	}
}

void utils::iaq_calculator::rate_no2(component_container& component)
{
	if (component.value < 0.2)
	{
		component.points = EXCELLENT_POINTS;
		component.rating = iaq_rating::EXCELLENT;
	}
	else if (component.value >= 0.2 && component.value <= 0.4)
	{
		component.points = FAIR_POINTS;
		component.rating = iaq_rating::FAIR;
	}
	else
	{
		component.points = INADEQUATE_POINTS;
		component.rating = iaq_rating::INADEQUATE;
	}
}

void utils::iaq_calculator::calculate_overall_iaq()
{
	// Sum up points of components
	m_overall_points = 0;
	for (auto& component : m_iaq_components)
	{
		m_overall_points += component.second.points;
	}

	// Find out the rating
	if (m_overall_points >= 28) // max available points = 30  -> Range = 2 (Original: 65-61 -> R=4)
	{
		m_overall_rating = iaq_rating::EXCELLENT;
	}
	else if (m_overall_points < 28 && m_overall_points >= 24) // -> Range = 4 (Original: 60-52 -> R=8)
	{
		m_overall_rating = iaq_rating::GOOD;
	}
	else if (m_overall_points < 24 && m_overall_points >= 18) // -> Range = 6 (Original: 51-39 -> R=12)
	{
		m_overall_rating = iaq_rating::FAIR;
	}
	else if (m_overall_points < 18 && m_overall_points >= 12) // -> Range = 6 (Original: 38-26 -> R=12)
	{
		m_overall_rating = iaq_rating::POOR;
	}
	else
	{
		m_overall_rating = iaq_rating::INADEQUATE;
	}

	// Update history if neccessary
	if (m_overall_points <= m_history_worst_overall_iaq_points)
	{
		m_history_worst_overall_iaq_points = m_overall_points;
		m_history_worst_overall_iaq_rating = m_overall_rating;
	}
	if (m_overall_points >= m_history_best_overall_iaq_points)
	{
		m_history_best_overall_iaq_points = m_overall_points;
		m_history_best_overall_iaq_rating = m_overall_rating;
	}
}
