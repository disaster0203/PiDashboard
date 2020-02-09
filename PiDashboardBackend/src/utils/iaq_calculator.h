#pragma once
#include <cstdint>
#include <map>
#include <tuple>

namespace utils
{
	static constexpr const uint8_t EXCELLENT_POINTS = 5;
	static constexpr const uint8_t GOOD_POINTS = 4;
	static constexpr const uint8_t FAIR_POINTS = 3;
	static constexpr const uint8_t POOR_POINTS = 2;
	static constexpr const uint8_t INADEQUATE_POINTS = 1;

	//! Enum defining the various components.
	/*!
	* Enum defining the various components:
	* - TEMPERATURE
	* - CO
	* - CO2
	* - TVOC
	* - HUMIDITY
	* - NO2
	*/
	enum class iaq_component : uint8_t
	{
		TEMPERATURE = 0,
		CO = 1,
		CO2 = 2,
		TVOC = 3,
		HUMIDITY = 4,
		NO2 = 5
	};

	//! Enum defining the various iaq ratings.
	/*!
	* Enum defining the various iaq ratings:
	* - EXCELLENT
	* - GOOD
	* - FAIR
	* - POOR
	* - INADEQUATE
	*/
	enum class iaq_rating : uint8_t
	{
		EXCELLENT = 0,
		GOOD = 1,
		FAIR = 2,
		POOR = 3,
		INADEQUATE = 4
	};

	//! Container class representing one component.
	/*!
	* Container class representing one component. It contains the 
	* current component value, its points and iaq rating.
	*/
	struct component_container
	{
		double value;
		uint8_t points;
		iaq_rating rating;
	};

	//! Class that calculates the indoor air quality.
	/*!
	* Class that calculates the indoor air quality based on temperature, carbon monoxide,
	* carbon dioxide, total volatile organic components, humidity and no3. 
	*/
	class iaq_calculator
	{
	public:
		//! Adds a new temperature value to the iaq calculation.
		/*!
		* Adds a new temperature value to the iaq calculation. This will update the current
		* iaq value.
		* \param[in] new_temperature: the temperature value to add.
		*/
		void add_temperature(double new_temperature);

		//! Adds a new carbon monoxide value to the iaq calculation.
		/*!
		* Adds a new carbon monoxide value to the iaq calculation. This will update the current
		* iaq value.
		* \param[in] new_co: the carbon monoxide value to add.
		*/
		void add_co(uint16_t new_co);

		//! Adds a new carbon dioxide value to the iaq calculation.
		/*!
		* Adds a new carbon dioxide value to the iaq calculation. This will update the current
		* iaq value.
		* \param[in] new_co2: the carbon dioxide value to add.
		*/
		void add_co2(uint16_t new_co2);

		//! Adds a new TVOC value to the iaq calculation.
		/*!
		* Adds a new TVOC value to the iaq calculation. This will update the current
		* iaq value.
		* \param[in] new_tvco: the TVOC value to add.
		*/
		void add_tvoc(uint16_t new_tvco);

		//! Adds a new humidity value to the iaq calculation.
		/*!
		* Adds a new humidity value to the iaq calculation. This will update the current
		* iaq value.
		* \param[in] new_humidity: the humidity value to add.
		*/
		void add_humidity(double new_humidity);

		//! Adds a new NO2 value to the iaq calculation.
		/*!
		* Adds a new NO2 value to the iaq calculation. This will update the current
		* iaq value.
		* \param[in] new_no2: the NO2 value to add.
		*/
		void add_no2(double new_no2);

		//! Adds a new values of all components together to the iaq calculation.
		/*!
		* Adds a new values of all components together to the iaq calculation. This will update
		* the current iaq value.
		* \param[in] new_temperature: the temperature value to add.
		* \param[in] new_co: the carbon monoxide value to add.
		* \param[in] new_co2: the carbon dioxide value to add.
		* \param[in] new_tvco: the TVOC value to add.
		* \param[in] new_humidity: the humidity value to add.
		* \param[in] new_no2: the NO2 value to add.
		*/
		void add(double new_temperature, uint16_t new_co, uint16_t new_co2, uint16_t new_tvco, double new_humidity, double new_no2);

		//! Gets the current iaq rating of one specific component.
		/*!
		* Gets the current iaq rating of one specific component.
		* \param[in] component: the desired component.
		* \returns the current iaq rating of the given component.
		*/
		iaq_rating get_rating(iaq_component component);

		//! Gets the overall iaq rating.
		/*!
		* Gets the overall iaq rating.
		* \returns the current iaq rating all components together.
		*/
		iaq_rating get_overall_rating();

		//! Gets the component with the best rating together with its current component.
		/*!
		* Gets the component with the best rating together with its current component.
		* \returns the currently best iaq rating over all components together with the component.
		*/
		std::tuple<iaq_component, iaq_rating> get_best_rating();

		//! Gets the component with the worst rating together with its current component.
		/*!
		* Gets the component with the worst rating together with its current component.
		* \returns the currently worst iaq rating over all components together with the component.
		*/
		std::tuple<iaq_component, iaq_rating> get_worst_rating();

		//! Gets all single iaq ratings together with their components.
		/*!
		* Gets all single iaq ratings together with their components.
		* \returns the current iaq ratings all components.
		*/
		std::map<iaq_component, iaq_rating> get_component_ratings();

		//! Gets the current iaq points of one specific component.
		/*!
		* Gets the current iaq points of one specific component.
		* \param[in] component: the desired component.
		* \returns the current iaq points of the given component.
		*/
		uint8_t get_points(iaq_component component);

		//! Gets the overall iaq points.
		/*!
		* Gets the overall iaq points.
		* \returns the current iaq points all components together.
		*/
		uint8_t get_overall_points();

		//! Gets the component with the best points together with its current component.
		/*!
		* Gets the component with the best points together with its current component.
		* \returns the currently best iaq points over all components together with the component.
		*/
		std::tuple <iaq_component, uint8_t> get_best_points();

		//! Gets the component with the worst points together with its current component.
		/*!
		* Gets the component with the worst points together with its current component.
		* \returns the currently worst iaq points over all components together with the component.
		*/
		std::tuple <iaq_component, uint8_t> get_worst_points();

		//! Gets all single iaq points together with their components.
		/*!
		* Gets all single iaq points together with their components.
		* \returns the current iaq points all components.
		*/
		std::map <iaq_component, uint8_t> get_component_points();

		//! Gets the best overall iaq rating since the last reset.
		/*!
		* Gets the best overall iaq rating since the last reset.
		* \returns the best overall iaq rating since the last reset.
		*/
		iaq_rating get_best_history_rating();

		//! Gets the worst overall iaq rating since the last reset.
		/*!
		* Gets the worst overall iaq rating since the last reset.
		* \returns the worst overall iaq rating since the last reset.
		*/
		iaq_rating get_worst_history_rating();

		//! Gets the best overall points since the last reset.
		/*!
		* Gets the best overall points since the last reset.
		* \returns the best overall points since the last reset.
		*/
		uint8_t get_best_history_points();

		//! Gets the worst overall points since the last reset.
		/*!
		* Gets the best overall worst since the last reset.
		* \returns the best overall worst since the last reset.
		*/
		uint8_t get_worst_history_points();

		//! Resets all components to 0 points and INADEQUATE rating.
		/*!
		* Resets all components to 0 points and INADEQUATE rating.
		*/
		void reset();

	private:
		//! Calculates a new temperature iaq rating and points.
		/*!
		* Calculates a new temperature iaq rating and points.
		* \param[out] component: the temperature component to rate.
		*/
		void rate_temperature(struct component_container& component);

		//! Calculates a new carbon monoxide iaq rating and points.
		/*!
		* Calculates a new carbon monoxide iaq rating and points.
		* \param[out] component: the carbon monoxide component to rate.
		*/
		void rate_co(struct component_container& component);

		//! Calculates a new carbon dioxide iaq rating and points.
		/*!
		* Calculates a new carbon dioxide iaq rating and points.
		* \param[out] component: the carbon dioxide component to rate.
		*/
		void rate_co2(struct component_container& component);

		//! Calculates a new TVOC iaq rating and points.
		/*!
		* Calculates a new TVOC iaq rating and points.
		* \param[out] component: the TVOC component to rate.
		*/
		void rate_tvoc(struct component_container& component);

		//! Calculates a new humidity iaq rating and points.
		/*!
		* Calculates a new humidity iaq rating and points.
		* \param[out] component: the humidity component to rate.
		*/
		void rate_humidity(struct component_container& component);

		//! Calculates a new NO2 iaq rating and points.
		/*!
		* Calculates a new NO2 iaq rating and points.
		* \param[out] component: the NO2 component to rate.
		*/
		void rate_no2(struct component_container& component);

		//! Calculates the new overall iaq rating and points.
		/*!
		* Calculates the new overall iaq rating and points.
		*/
		void calculate_overall_iaq();

		std::map<enum iaq_component, struct component_container> m_iaq_components = {
			{iaq_component::TEMPERATURE, component_container()},
			{iaq_component::CO, component_container()},
			{iaq_component::CO2, component_container()},
			{iaq_component::TVOC, component_container()},
			{iaq_component::HUMIDITY, component_container()},
			{iaq_component::NO2, component_container()},
		};

		uint8_t m_overall_points;
		uint8_t m_history_worst_overall_iaq_points;
		uint8_t m_history_best_overall_iaq_points;
		iaq_rating m_overall_rating;
		iaq_rating m_history_worst_overall_iaq_rating;
		iaq_rating m_history_best_overall_iaq_rating;
	};
}