#include "MICS6814.h"

void hal::sensors::analog::mics6814::MICS6814::trigger_measurement(const SensorType type)
{
	for (auto i = m_callbacks[type].begin(); i != m_callbacks[type].end(); ++i)
	{
		if (type == SensorType::CARBON_MONOXIDE_CO)
		{
			try
			{
				(*i)->callback(std::to_string(get_carbon_monoxide_co()));
			}
			catch (exception::HALException & ex)
			{
				throw exception::HALException("MICS6814", "trigger_measurement",
					std::string("Could not trigger CO measurement:\n").append(ex.to_string()));
			}
		}
		if (type == SensorType::NITROGEN_DIOXIDE_NO2)
		{
			try
			{
				(*i)->callback(std::to_string(get_nitrogen_dioxide_no2()));
			}
			catch (exception::HALException & ex)
			{
				throw exception::HALException("MICS6814", "trigger_measurement",
					std::string("Could not trigger NO2 measurement:\n").append(ex.to_string()));
			}
		}
		if (type == SensorType::AMMONIAC_NH3)
		{
			try
			{
				(*i)->callback(std::to_string(get_ammoniac_nh3()));
			}
			catch (exception::HALException & ex)
			{
				throw exception::HALException("MICS6814", "trigger_measurement",
					std::string("Could not trigger NH3 measurement:\n").append(ex.to_string()));
			}
		}
		if (type == SensorType::PROPANE_C3H8)
		{
			try
			{
				(*i)->callback(std::to_string(get_propane_c3h8()));
			}
			catch (exception::HALException & ex)
			{
				throw exception::HALException("MICS6814", "trigger_measurement",
					std::string("Could not trigger NO2 measurement:\n").append(ex.to_string()));
			}
		}
		if (type == SensorType::BUTANE_C4H10)
		{
			try
			{
				(*i)->callback(std::to_string(get_butane_c4h10()));
			}
			catch (exception::HALException & ex)
			{
				throw exception::HALException("MICS6814", "trigger_measurement",
					std::string("Could not trigger NO2 measurement:\n").append(ex.to_string()));
			}
		}
		if (type == SensorType::METHANE_CH4)
		{
			try
			{
				(*i)->callback(std::to_string(get_methane_ch4()));
			}
			catch (exception::HALException & ex)
			{
				throw exception::HALException("MICS6814", "trigger_measurement",
					std::string("Could not trigger NO2 measurement:\n").append(ex.to_string()));
			}
		}
		if (type == SensorType::HYDROGEN_H2)
		{
			try
			{
				(*i)->callback(std::to_string(get_hydrogen_h2()));
			}
			catch (exception::HALException & ex)
			{
				throw exception::HALException("MICS6814", "trigger_measurement",
					std::string("Could not trigger NO2 measurement:\n").append(ex.to_string()));
			}
		}
		if (type == SensorType::ETHANOL_C2H5OH)
		{
			try
			{
				(*i)->callback(std::to_string(get_ethanol_c2h5oh()));
			}
			catch (exception::HALException & ex)
			{
				throw exception::HALException("MICS6814", "trigger_measurement",
					std::string("Could not trigger NO2 measurement:\n").append(ex.to_string()));
			}
		}
		else
		{
			throw exception::HALException("MICS6814", "trigger_measurement", "Invalid sensor type.");
		}
	}
}

void hal::sensors::analog::mics6814::MICS6814::configure(const SensorSetting setting, const std::string& configuration)
{
	try
	{
		if (dynamic_cast<sensors::i2c::ads1115::ADS1115*>(m_converter))
		{
			if (setting == SensorSetting::COMPARATOR_LATCHING)
			{
				dynamic_cast<sensors::i2c::ads1115::ADS1115*>(m_converter)->set_comparator_latching_setting(EnumConverter::string_to_alert_latching(configuration));
			}
			else if (setting == SensorSetting::COMPARATOR_MODE)
			{
				dynamic_cast<sensors::i2c::ads1115::ADS1115*>(m_converter)->set_comparator_mode_setting(EnumConverter::string_to_comparator_mode(configuration));
			}
			else if (setting == SensorSetting::COMPARATOR_QUEUE)
			{
				dynamic_cast<sensors::i2c::ads1115::ADS1115*>(m_converter)->set_comparator_queue_setting(EnumConverter::string_to_alert_queueing(configuration));
			}
			else if (setting == SensorSetting::DATA_RATE)
			{
				dynamic_cast<sensors::i2c::ads1115::ADS1115*>(m_converter)->set_data_rate_setting(EnumConverter::string_to_data_rate(configuration));
			}
			else if (setting == SensorSetting::GAIN_AMPLIFIER)
			{
				dynamic_cast<sensors::i2c::ads1115::ADS1115*>(m_converter)->set_gain_amplifier_setting(EnumConverter::string_to_gain_amplifier(configuration));
			}
			else if (setting == SensorSetting::THRESHOLD)
			{
				if (Helper::string_contains_separator(configuration))
				{
					std::vector<uint16_t> thresholds;
					Helper::string_to_array(thresholds, configuration);
					if (thresholds.size() == 2)
					{
						dynamic_cast<sensors::i2c::ads1115::ADS1115*>(m_converter)->set_thresholds(thresholds[0], thresholds[1]);
					}
				}
			}
			else if (setting == SensorSetting::MULTIPLEXER)
			{
				dynamic_cast<sensors::i2c::ads1115::ADS1115*>(m_converter)->set_multiplexer_setting(EnumConverter::string_to_multiplexer(configuration));
			}
		}
		// if (std::is_same<Converter, converter_XYZ>::value) { ... }
		else
		{
			throw exception::HALException("MICS6814", "configure", "Unsupported converter type.");
		}
	}
	catch (exception::HALException & ex)
	{
		throw exception::HALException("MICS6814", "configure",
			std::string("Could not change a setting of the devices AD-converter:\n").append(
				ex.to_string()));
	}
}

std::string hal::sensors::analog::mics6814::MICS6814::get_configuration(SensorSetting setting)
{
	try
	{
		return m_converter->get_configuration(setting);
	}
	catch (exception::HALException & ex)
	{
		throw exception::HALException("MICS6814", "get_configuration",
			std::string("Could not get a setting from the devices AD-converter:\n").append(
				ex.to_string()));
	}
}

std::vector<hal::SensorSetting> hal::sensors::analog::mics6814::MICS6814::available_configurations() noexcept
{
	return m_converter->available_configurations();
}

void hal::sensors::analog::mics6814::MICS6814::close()
{
	try
	{
		m_converter->close();
	}
	catch (exception::HALException & ex)
	{
		throw exception::HALException("MICS6814", "close",
			std::string("Could not close the devices AD-converter:\n").append(ex.to_string()));
	}
}

void hal::sensors::analog::mics6814::MICS6814::init(interfaces::IConverter* converter, uint8_t analog_pin)
{
	m_converter = converter;
	m_analog_pin = analog_pin;

	// If the converter device is not yet fully setup, initialize it
	uint8_t try_count = 0;
	m_mutex.lock();
	if (dynamic_cast<sensors::i2c::ads1115::ADS1115*>(m_converter))
	{
		while (!dynamic_cast<sensors::i2c::ads1115::ADS1115*>(m_converter)->is_initialized())
		{
			dynamic_cast<sensors::i2c::ads1115::ADS1115*>(m_converter)->init();
			try_count++;
			if (try_count == 5)
			{
				m_mutex.unlock();
				throw exception::HALException("MICS6814", "init", "Could not initialize analog digital converter.");
			}
		}
	}
	m_mutex.unlock();
}

double hal::sensors::analog::mics6814::MICS6814::get_voltage()
{
	try
	{
		if (dynamic_cast<sensors::i2c::ads1115::ADS1115*>(m_converter))
		{
			m_mutex.lock(); // Lock the shared ADS1115 pointer to avoid conflicts (we need to change multiplexer and gain)
			auto multiplexer = sensors::i2c::ads1115::Multiplexer::POSITIVE_0_AND_NEGATIVE_GND;
			switch (m_analog_pin)
			{
			case 0:
				multiplexer = sensors::i2c::ads1115::Multiplexer::POSITIVE_0_AND_NEGATIVE_GND;
			case 1:
				multiplexer = sensors::i2c::ads1115::Multiplexer::POSITIVE_1_AND_NEGATIVE_GND;
			case 2:
				multiplexer = sensors::i2c::ads1115::Multiplexer::POSITIVE_2_AND_NEGATIVE_GND;
			case 3:
				multiplexer = sensors::i2c::ads1115::Multiplexer::POSITIVE_3_AND_NEGATIVE_GND;
			case 4:
				multiplexer = sensors::i2c::ads1115::Multiplexer::POSITIVE_0_AND_NEGATIVE_1;
			case 5:
				multiplexer = sensors::i2c::ads1115::Multiplexer::POSITIVE_0_AND_NEGATIVE_3;
			case 6:
				multiplexer = sensors::i2c::ads1115::Multiplexer::POSITIVE_1_AND_NEGATIVE_3;
			case 7:
				multiplexer = sensors::i2c::ads1115::Multiplexer::POSITIVE_2_AND_NEGATIVE_3;
			default:
				break;
			}
			// Set multiplexer
			dynamic_cast<sensors::i2c::ads1115::ADS1115*>(m_converter)->set_multiplexer_setting(multiplexer);
			// For simplicity set gain amplifier always to 2048mV
			dynamic_cast<sensors::i2c::ads1115::ADS1115*>(m_converter)->set_gain_amplifier_setting(sensors::i2c::ads1115::GainAmplifier::GAIN_2048_mV);
			// Trigger new conversion
			dynamic_cast<sensors::i2c::ads1115::ADS1115*>(m_converter)->start_single_conversion();
			// Receive the new voltage data from the ADS1115
			auto voltage = dynamic_cast<sensors::i2c::ads1115::ADS1115*>(m_converter)->get_converted_data();
			// Unlock ADS1115 pointer
			m_mutex.unlock();

			// Clamp voltage
			return std::fmaxl(std::fminl(m_max_voltage, voltage), m_min_voltage);
		}
		// if (std::is_same<Converter, converter_XYZ>::value) { ... }
		else
		{
			throw exception::HALException("MICS6814", "get_voltage", "Unsupported converter type.");
		}
	}
	catch (exception::HALException & ex)
	{
		throw exception::HALException("MICS6814", "get_voltage",
			std::string("Could not get a voltage value from the devices AD-converter:\n").append(
				ex.to_string()));
	}
}

double hal::sensors::analog::mics6814::MICS6814::get_resistance()
{
	try
	{
		const auto voltage = get_voltage();
		return 47.0 * voltage / (m_max_voltage - voltage);
	}
	catch (exception::HALException & ex)
	{
		throw exception::HALException("MICS6814", "get_resistance",
			std::string("Could not get a voltage value from the devices AD-converter:\n").append(
				ex.to_string()));
	}
}

double hal::sensors::analog::mics6814::MICS6814::get_carbon_monoxide_co()
{
	try
	{
		auto ratio = get_resistance() / m_co_clean_air;
		if (ratio > 4.0 || ratio < 0.01)
		{
			return 0;
		}
		else
		{
			auto co = powf32x(ratio, -1.177) * 4.4638;
			return (co < 1.0 || co > 1000) ? 0 : co;
		}
	}
	catch (exception::HALException & ex)
	{
		throw exception::HALException("MICS6814", "get_carbon_monoxide_co",
			std::string("Could not get a resistance value from the devices AD-converter:\n").append(
				ex.to_string()));
	}
}

double hal::sensors::analog::mics6814::MICS6814::get_nitrogen_dioxide_no2()
{
	try
	{
		auto ratio = get_resistance() / m_no2_clean_air;
		if (ratio > 40.0 || ratio < 0.06)
		{
			return 0;
		}
		else
		{
			auto no2 = powf32x(ratio, 0.9979) * 0.1516;
			return (no2 < 0.01 || no2 > 7) ? 0 : no2;
		}
	}
	catch (exception::HALException & ex)
	{
		throw exception::HALException("MICS6814", "get_nitrogen_dioxide_no2",
			std::string("Could not get a resistance value from the devices AD-converter:\n").append(
				ex.to_string()));
	}
}

double hal::sensors::analog::mics6814::MICS6814::get_ammoniac_nh3()
{
	try
	{
		auto ratio = get_resistance() / m_nh3_clean_air;
		if (ratio > 0.9 || ratio < 0.05)
		{
			return 0;
		}
		else
		{
			auto nh3 = powf32x(ratio, -1.903) * 0.6151;
			return (nh3 < 1 || nh3 > 160) ? 0 : nh3;
		}
	}
	catch (exception::HALException & ex)
	{
		throw exception::HALException("MICS6814", "get_ammoniac_nh3",
			std::string("Could not get a resistance value from the devices AD-converter:\n").append(
				ex.to_string()));
	}
}

double hal::sensors::analog::mics6814::MICS6814::get_propane_c3h8()
{
	try
	{
		auto ratio = get_resistance() / m_nh3_clean_air;
		if (ratio > 0.9 || ratio < 0.2)
		{
			return 0;
		}
		else
		{
			auto c3h8 = powf32x(ratio, -2.492) * 569.56;
			return (c3h8 < 1000 || c3h8 > 30000) ? 0 : c3h8;
		}
	}
	catch (exception::HALException & ex)
	{
		throw exception::HALException("MICS6814", "get_propane_c3h8",
			std::string("Could not get a resistance value from the devices AD-converter:\n").append(
				ex.to_string()));
	}
}

double hal::sensors::analog::mics6814::MICS6814::get_butane_c4h10()
{
	try
	{
		auto ratio = get_resistance() / m_nh3_clean_air;
		if (ratio > 0.8 || ratio < 0.1)
		{
			return 0;
		}
		else
		{
			auto c4h10 = powf32x(ratio, -1.888) * 503.2;
			return (c4h10 < 1000 || c4h10 > 30000) ? 0 : c4h10;
		}
	}
	catch (exception::HALException & ex)
	{
		throw exception::HALException("MICS6814", "get_butane_c4h10",
			std::string("Could not get a resistance value from the devices AD-converter:\n").append(
				ex.to_string()));
	}
}

double hal::sensors::analog::mics6814::MICS6814::get_methane_ch4()
{
	try
	{
		auto ratio = get_resistance() / m_co_clean_air;
		if (ratio > 0.8 || ratio < 0.45)
		{
			return 0;
		}
		else
		{
			auto ch4 = powf32x(ratio, -4.093) * 837.38;
			return (ch4 < 3000 || ch4 > 10500) ? 0 : ch4;
		}
	}
	catch (exception::HALException & ex)
	{
		throw exception::HALException("MICS6814", "get_methane_ch4",
			std::string("Could not get a resistance value from the devices AD-converter:\n").append(
				ex.to_string()));
	}
}

double hal::sensors::analog::mics6814::MICS6814::get_hydrogen_h2()
{
	try
	{
		auto ratio = get_resistance() / m_co_clean_air;
		if (ratio > 1 || ratio < 0.035)
		{
			return 0;
		}
		else
		{
			auto h2 = powf32x(ratio, -1.781) * 0.828;
			return (h2 < 1 || h2 > 250) ? 0 : h2;
		}
	}
	catch (exception::HALException & ex)
	{
		throw exception::HALException("MICS6814", "get_hydrogen_h2",
			std::string("Could not get a resistance value from the devices AD-converter:\n").append(
				ex.to_string()));
	}
}

double hal::sensors::analog::mics6814::MICS6814::get_ethanol_c2h5oh()
{
	try
	{
		auto ratio = get_resistance() / m_co_clean_air;
		if (ratio > 1.05 || ratio < 0.03)
		{
			return 0;
		}
		else
		{
			auto c2h5oh = powf32x(ratio, -1.58) * 1.363;
			return (c2h5oh < 1.5 || c2h5oh > 250) ? 0 : c2h5oh;
		}
	}
	catch (exception::HALException & ex)
	{
		throw exception::HALException("MICS6814", "get_ethanol_c2h5oh",
			std::string("Could not get a resistance value from the devices AD-converter:\n").append(
				ex.to_string()));
	}
}
