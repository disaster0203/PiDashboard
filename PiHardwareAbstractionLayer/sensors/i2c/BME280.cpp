#include "BME280.h"
#include "../../exceptions/HALException.h"
#include "../../exceptions/I2CException.h"
#include "../../utils/BitManipulation.h"
#include "../../utils/Helper.h"
#include "../../utils/I2CManager.h"
#include <unistd.h>

void hal::sensors::i2c::bme280::BME280::trigger_measurement(const SensorType type)
{
	double val;
	for (auto i = m_callbacks[type].begin(); i != m_callbacks[type].end(); ++i)
	{
		switch (type)
		{
		case SensorType::TEMPERATURE:
			try
			{
				val = get_temperature_data();
			}
			catch (exception::HALException* ex)
			{
				throw exception::HALException("BME280", "trigger_measurement",
														std::string("Could not trigger temperature measurement:\n").append(ex->to_string()));
			}
			break;
		case SensorType::AIR_PRESSURE:
			try
			{
				val = get_pressure_data();
			}
			catch (exception::HALException* ex)
			{
				throw exception::HALException("BME280", "trigger_measurement",
														std::string("Could not trigger air pressure measurement:\n").append(ex->to_string()));
			}
			break;
		case SensorType::AIR_HUMIDITY:
			try
			{
				val = get_humidity_data();
			}
			catch (exception::HALException* ex)
			{
				throw exception::HALException("BME280", "trigger_measurement",
														std::string("Could not trigger air humidity measurement:\n").append(ex->to_string()));
			}
			break;
		default:
			throw exception::HALException("BME280", "trigger_measurement", "Invalid sensor type.");
		}
		(*i)->callback(std::to_string(val));
	}
}

void hal::sensors::i2c::bme280::BME280::configure(const SensorSetting setting, const std::string& configuration)
{
	if (setting == SensorSetting::OVERSAMPLING)
	{
		std::vector<uint8_t> oversampling;
		Helper::string_to_array(oversampling, configuration);
		auto os = SettingsData();
		if (oversampling.size() == 3)
		{
			os.temperature_oversampling = oversampling[0];
			os.pressure_oversampling = oversampling[1];
			os.humidity_oversampling = oversampling[2];
			try
			{
				set_pressure_and_temperature_oversampling(OVERSAMPLING_SETTINGS, os);
				set_humidity_oversampling(os);
			}
			catch (exception::HALException* ex)
			{
				throw exception::HALException("BME280", "configure",
														std::string("Could not change oversampling settings:\n").append(ex->to_string()));
			}
		}
	}
	else if (setting == SensorSetting::FILTER)
	{
		auto os = SettingsData();
		os.filter = Helper::string_to_uint8_t(configuration);
		try
		{
			set_filter_and_standby_settings(FILTER_SETTING_SELECTION, os);
		}
		catch (exception::HALException* ex)
		{
			throw exception::HALException("BME280", "configure", std::string("Could not change filter settings:\n").append(ex->to_string()));
		}
	}
}

std::string hal::sensors::i2c::bme280::BME280::get_configuration(const SensorSetting setting)
{
	try
	{
		const auto settings = get_settings();
		if (setting == SensorSetting::OVERSAMPLING)
		{
			const std::vector<uint8_t> oversampling = {
				settings->temperature_oversampling,
				settings->pressure_oversampling,
				settings->humidity_oversampling
			};
			return Helper::array_to_string(oversampling);
		}

		if (setting == SensorSetting::FILTER)
		{
			return std::to_string(settings->filter);
		}
	}
	catch (exception::HALException* ex)
	{
		throw exception::HALException("BME280", "get_configuration",
												std::string("Could not read settings from the device:\n").append(ex->to_string()));
	}

	return "";
}

std::vector<hal::SensorSetting> hal::sensors::i2c::bme280::BME280::available_configurations() noexcept
{
	return {SensorSetting::OVERSAMPLING, SensorSetting::FILTER};
}

void hal::sensors::i2c::bme280::BME280::close()
{
	try
	{
		I2CManager::close_device(m_file_handle);
	}
	catch (exception::HALException* ex)
	{
		throw exception::HALException("BME280", "close", std::string("Could not close device connection:\n").append(ex->to_string()));
	}
}

uint8_t hal::sensors::i2c::bme280::BME280::init(const uint8_t device_reg)
{
	m_dev_id = device_reg;
	m_device = Device();

	try
	{
		I2CManager::open_device(I2CManager::DEFAULT_PI_I2C_PATH, device_reg, m_file_handle);
	}
	catch (exception::HALException* ex)
	{
		throw exception::HALException("BME280", "init", std::string("Could not establish connection with device:\n").append(ex->to_string()));
	}

	uint8_t try_count = 5;
	while (try_count)
	{
		try
		{
			I2CManager::read_from_device(m_file_handle, CHIP_ID_REG, &m_chip_id, 1);
			soft_reset();
			m_device.calibration_data = get_calibration_data();
			break;
		}
		catch (...)
		{
			usleep(1000);
			--try_count;
		}
	}

	if (!try_count)
	{
		throw exception::HALException("BME280", "init", "Could not read chip id from the device.");
	}

	return m_chip_id;
}

void hal::sensors::i2c::bme280::BME280::set_pressure_and_temperature_oversampling(
	const uint8_t desired_settings,
	const SettingsData settings) const
{
	const auto reg_REG = MEASUREMENT_OVERSAMPLING_REG;
	uint8_t reg_data[1];

	try
	{
		I2CManager::read_from_device(m_file_handle, reg_REG, reg_data, 1);
	}
	catch (exception::HALException* ex)
	{
		throw exception::I2CException("BME280", "set_pressure_and_temperature_oversampling", m_dev_id, reg_REG,
												std::string("Could not read pressure and temperature oversampling setting from device:\n").append(
													ex->to_string()));
	}

	try
	{
		if (desired_settings & PRESSURE_SETTING_SELECTION)
		{
			BitManipulation::set_bits(reg_data[0],
									  BitManipulation::multiply_by_2_power_n(settings.pressure_oversampling, BitManipulation::mask_out(PRESSURE_POS, PRESSURE_MASK), uint8_t()),
									  PRESSURE_MASK);
		}
		if (desired_settings & TEMPERATURE_SETTING_SELECTION)
		{
			BitManipulation::set_bits(reg_data[0],
									  BitManipulation::multiply_by_2_power_n(settings.temperature_oversampling, BitManipulation::mask_out(TEMPERATURE_POS, TEMPERATURE_MASK), uint8_t()),
									  TEMPERATURE_MASK);
		}
	}
	catch (exception::HALException* ex)
	{
		throw exception::HALException("BME280", "set_pressure_and_temperature_oversampling",
												std::string("Could not set pressure/temperature bits:\n").append(ex->to_string()));
	}

	/* Write the oversampling settings in the register */
	try
	{
		I2CManager::write_to_device(m_file_handle, reg_REG, std::move(reg_data), 1);
	}
	catch (exception::HALException* ex)
	{
		throw exception::I2CException("BME280", "set_pressure_and_temperature_oversampling", m_dev_id, reg_REG,
												std::string("Could not write pressure and temperature oversampling settings to device:\n").append(
													ex->to_string()));
	}
}

void hal::sensors::i2c::bme280::BME280::set_humidity_oversampling(const SettingsData settings) const
{
	/* Humidity related changes will be only effective after a
	 * write operation to ctrl_meas register
	 */
	auto reg_REG = HUMIDITY_OVERSAMPLING_REG;
	uint8_t ctrl_hum[1] = {static_cast<uint8_t>(settings.humidity_oversampling & HUMIDITY_MASK)};
	try
	{
		I2CManager::write_to_device(m_file_handle, reg_REG, ctrl_hum, 1);
	}
	catch (exception::HALException* ex)
	{
		throw exception::I2CException("BME280", "set_humidity_oversampling", m_dev_id, reg_REG,
												std::string("Could not write humidity setting to device:\n").append(ex->to_string()));
	}

	reg_REG = MEASUREMENT_OVERSAMPLING_REG;
	uint8_t ctrl_meas[1];
	try
	{
		I2CManager::read_from_device(m_file_handle, reg_REG, ctrl_meas, 1);
	}
	catch (exception::HALException* ex)
	{
		throw exception::I2CException("BME280", "set_humidity_oversampling", m_dev_id, reg_REG,
												std::string("Could not read settings from device:\n").append(ex->to_string()));
	}

	try
	{
		I2CManager::write_to_device(m_file_handle, reg_REG, ctrl_meas, 1);
	}
	catch (exception::HALException* ex)
	{
		throw exception::I2CException("BME280", "set_humidity_oversampling", m_dev_id, reg_REG,
												std::string("Could not write settings to device (to force the new oversampling take effect):\n").append(
													ex->to_string()));
	}
}

void hal::sensors::i2c::bme280::BME280::set_filter_and_standby_settings(const uint8_t desired_settings, const SettingsData settings) const
{
	const auto reg_REG = CONFIG_REG;
	uint8_t reg_data[1];

	try
	{
		I2CManager::read_from_device(m_file_handle, reg_REG, reg_data, 1);
	}
	catch (exception::HALException* ex)
	{
		throw exception::I2CException("BME280", "set_filter_and_standby_settings", m_dev_id, reg_REG,
												std::string("Could not read filter and standby settings from device:\n").append(ex->to_string()));
	}

	try
	{
		if (desired_settings & FILTER_SETTING_SELECTION)
		{
			BitManipulation::set_bits(reg_data[0],
									  BitManipulation::multiply_by_2_power_n(settings.filter, BitManipulation::mask_out(FILTER_POS, FILTER_MASK), uint8_t()),
									  FILTER_MASK);
		}
		if (desired_settings & STANDBY_SETTING_SELECTION)
		{
			BitManipulation::set_bits(reg_data[0],
									  BitManipulation::multiply_by_2_power_n(settings.standby_time, BitManipulation::mask_out(STANDBY_POS, STANDBY_MASK), uint8_t()),
									  STANDBY_MASK);
		}
	}
	catch (exception::HALException* ex)
	{
		throw exception::HALException("BME280", "set_filter_and_standby_settings",
												std::string("Could not set filter/standby bits:\n").append(ex->to_string()));
	}

	try
	{
		I2CManager::write_to_device(m_file_handle, reg_REG, reg_data, 1);
	}
	catch (exception::HALException* ex)
	{
		throw exception::I2CException("BME280", "set_filter_and_standby_settings", m_dev_id, reg_REG,
												std::string("Could not write filter and standby settings to device:\n").append(ex->to_string()));
	}
}

void hal::sensors::i2c::bme280::BME280::set_sensor_mode(OperationMode mode) const
{
	if (mode != get_sensor_mode())
	{
		uint8_t reg_data[1];

		try
		{
			I2CManager::read_from_device(m_file_handle, MODE_REG, reg_data, 1);
		}
		catch (exception::HALException* ex)
		{
			throw exception::I2CException("BME280", "set_sensor_mode", m_dev_id, MODE_REG,
													std::string("Could not read settings from device:\n").append(ex->to_string()));
		}

		BitManipulation::set_bits(reg_data[0], BitManipulation::mask_out(static_cast<uint8_t>(mode), SENSOR_MODE_MASK), SENSOR_MODE_MASK);
		try
		{
			I2CManager::write_to_device(m_file_handle, MODE_REG, reg_data, 1);
		}
		catch (exception::HALException* ex)
		{
			throw exception::I2CException("BME280", "set_sensor_mode", m_dev_id, MODE_REG,
													std::string("Could not write new sensor mode:\n").append(ex->to_string()));
		}
	}
}

hal::sensors::i2c::bme280::OperationMode hal::sensors::i2c::bme280::BME280::get_sensor_mode() const
{
	uint8_t result[1] = {0};
	/* Read the power mode register */
	try
	{
		I2CManager::read_from_device(m_file_handle, MODE_REG, result, 1);
	}
	catch (exception::HALException* ex)
	{
		throw exception::I2CException("BME280", "get_sensor_mode", m_dev_id, MODE_REG,
												std::string("Could not read device mode:\n").append(ex->to_string()));
	}

	result[0] = BitManipulation::mask_out(result[0], SENSOR_MODE_MASK);
	if (result[0] == 0) return OperationMode::SLEEP;
	if (result[0] == 1 || result[0] == 2) return OperationMode::FORCED;
	return OperationMode::NORMAL;
}

void hal::sensors::i2c::bme280::BME280::set_settings(
	Oversampling temperature,
	Oversampling pressure,
	Oversampling humidity,
	Filter filter,
	StandbyTime standby)
{
	m_device.settings.temperature_oversampling = static_cast<uint8_t>(temperature);
	m_device.settings.pressure_oversampling = static_cast<uint8_t>(pressure);
	m_device.settings.humidity_oversampling = static_cast<uint8_t>(humidity);
	m_device.settings.filter = static_cast<uint8_t>(filter);
	m_device.settings.standby_time = static_cast<uint8_t>(standby);

	const auto settings_sel = BitManipulation::combine(PRESSURE_SETTING_SELECTION,
																		BitManipulation::combine(TEMPERATURE_SETTING_SELECTION,
																										BitManipulation::combine(HUMIDITY_SETTING_SELECTION,
																																		BitManipulation::combine(
																																			FILTER_SETTING_SELECTION,
																																			STANDBY_SETTING_SELECTION))));

	auto sensor_mode = OperationMode::SLEEP;
	try
	{
		sensor_mode = get_sensor_mode();
	}
	catch (exception::HALException* ex)
	{
		throw exception::HALException("BME280", "set_settings",
												std::string("Could not read sensor mode:\n").append(ex->to_string()));
	}
	std::shared_ptr<SettingsData> settings;
	try
	{
		settings = get_settings();
	}
	catch (exception::HALException* ex)
	{
		throw exception::HALException("BME280", "set_settings",
												std::string("Could not read sensor settings:\n").append(ex->to_string()));
	}

	// Sleep mode and reset
	if (sensor_mode != OperationMode::SLEEP)
	{
		try
		{
			soft_reset();
			reload_device_settings(*settings.get());
		}
		catch (exception::HALException* ex)
		{
			throw exception::HALException("BME280", "set_settings",
													std::string("Could not perform soft reset on device:\n").append(ex->to_string()));
		}
	}

	// Apply new settings
	try
	{
		if (are_settings_changed(OVERSAMPLING_SETTINGS, settings_sel))
		{
			if (BitManipulation::mask_out(settings_sel, HUMIDITY_SETTING_SELECTION))
			{
				set_humidity_oversampling(m_device.settings);
			}
			if (BitManipulation::mask_out(settings_sel, BitManipulation::combine(PRESSURE_SETTING_SELECTION, TEMPERATURE_SETTING_SELECTION)))
			{
				set_pressure_and_temperature_oversampling(settings_sel, m_device.settings);
			}

			m_device.wait_time = calculate_wait_time();
		}

		if (are_settings_changed(FILTER_STANDBY_SETTINGS, settings_sel))
		{
			set_filter_and_standby_settings(settings_sel, m_device.settings);
		}
	}
	catch (exception::HALException* ex)
	{
		throw exception::HALException("BME280", "set_settings",
												std::string("Could not apply new settings to the device:\n").append(ex->to_string()));
	}
}

std::shared_ptr<hal::sensors::i2c::bme280::SettingsData> hal::sensors::i2c::bme280::BME280::get_settings() const
{
	uint8_t reg_data[4];
	try
	{
		I2CManager::read_from_device(m_file_handle, HUMIDITY_OVERSAMPLING_REG, reg_data, 4);
	}
	catch (exception::HALException* ex)
	{
		throw exception::I2CException("BME280", "get_settings", m_dev_id, HUMIDITY_OVERSAMPLING_REG,
												std::string("Could not read settings data from device:\n").append(ex->to_string()));
	}

	return parse_settings(reg_data);
}

void hal::sensors::i2c::bme280::BME280::soft_reset() const
{
	uint8_t data[1] = {SOFT_RESET_VALUE};
	try
	{
		I2CManager::write_to_device(m_file_handle, SOFT_RESET_REG, data, 1);
	}
	catch (exception::HALException* ex)
	{
		throw exception::I2CException("BME280", "soft_reset", m_dev_id, SOFT_RESET_REG,
												std::string("Could not write soft reset command to device:\n").append(ex->to_string()));
	}

	uint8_t status_reg[1] = {0};
	uint8_t try_run = 5;
	do
	{
		usleep(2000);
		try
		{
			I2CManager::read_from_device(m_file_handle, STATUS_REG, status_reg, 1);
		}
		catch (exception::HALException* ex)
		{
			throw exception::I2CException("BME280", "soft_reset", m_dev_id, STATUS_REG,
													std::string("Could not read device status:\n").append(ex->to_string()));
		}
	}
	while (try_run-- && BitManipulation::mask_out(status_reg[0], STATUS_DURING_UPDATE));

	if (status_reg[0] & STATUS_DURING_UPDATE)
	{
		throw exception::I2CException("BME280", "soft_reset", m_dev_id, STATUS_REG, "NVM copy failed.");
	}
}

double hal::sensors::i2c::bme280::BME280::get_temperature_data()
{
	try
	{
		set_sensor_mode(OperationMode::FORCED);
		sleep_until_ready();
	}
	catch (exception::HALException* ex)
	{
		throw exception::HALException("BME280", "get_temperature_data",
												std::string("Could not set device mode to FORCED:\n").append(ex->to_string()));
	}

	uint8_t reg_data[ALL_DATA_LENGTH] = {0};
	try
	{
		I2CManager::read_from_device(m_file_handle, DATA_REG, reg_data, ALL_DATA_LENGTH);
	}
	catch (exception::HALException* ex)
	{
		throw exception::I2CException("BME280", "get_temperature_data", m_dev_id, DATA_REG,
												std::string("Could not read raw data:\n").append(ex->to_string()));
	}

	return compensate_temperature(m_device.calibration_data, parse_raw_data(reg_data)->temperature);
}

double hal::sensors::i2c::bme280::BME280::get_pressure_data() const
{
	try
	{
		set_sensor_mode(OperationMode::FORCED);
		sleep_until_ready();
	}
	catch (exception::HALException* ex)
	{
		throw exception::HALException("BME280", "get_pressure_data",
												std::string("Could not set device mode to FORCED:\n").append(ex->to_string()));
	}

	uint8_t reg_data[ALL_DATA_LENGTH] = {0};
	try
	{
		I2CManager::read_from_device(m_file_handle, DATA_REG, reg_data, ALL_DATA_LENGTH);
	}
	catch (exception::HALException* ex)
	{
		throw exception::I2CException("BME280", "get_pressure_data", m_dev_id, DATA_REG,
												std::string("Could not read raw data:\n").append(ex->to_string()));
	}

	return compensate_pressure(m_device.calibration_data, parse_raw_data(reg_data)->pressure);
}

double hal::sensors::i2c::bme280::BME280::get_humidity_data() const
{
	try
	{
		set_sensor_mode(OperationMode::FORCED);
		sleep_until_ready();
	}
	catch (exception::HALException* ex)
	{
		throw exception::HALException("BME280", "get_humidity_data",
												std::string("Could not set device mode to FORCED:\n").append(ex->to_string()));
	}

	uint8_t reg_data[ALL_DATA_LENGTH] = {0};
	try
	{
		I2CManager::read_from_device(m_file_handle, DATA_REG, reg_data, ALL_DATA_LENGTH);
	}
	catch (exception::HALException* ex)
	{
		throw exception::I2CException("BME280", "get_humidity_data", m_dev_id, DATA_REG,
												std::string("Could not read raw data:\n").append(ex->to_string()));
	}

	return compensate_humidity(m_device.calibration_data, parse_raw_data(reg_data)->humidity);
}

void hal::sensors::i2c::bme280::BME280::get_all_data(double& temperature, double& pressure, double& humidity)
{
	try
	{
		set_sensor_mode(OperationMode::FORCED);
		sleep_until_ready();
	}
	catch (exception::HALException* ex)
	{
		throw exception::HALException("BME280", "get_all_data",
												std::string("Could not set device mode to FORCED:\n").append(ex->to_string()));
	}

	uint8_t reg_data[ALL_DATA_LENGTH] = {0};
	try
	{
		I2CManager::read_from_device(m_file_handle, DATA_REG, reg_data, ALL_DATA_LENGTH);
	}
	catch (exception::HALException* ex)
	{
		throw exception::I2CException("BME280", "get_all_data", m_dev_id, DATA_REG,
												std::string("Could not read raw data:\n").append(ex->to_string()));
	}

	const auto raw = parse_raw_data(reg_data);
	temperature = compensate_temperature(m_device.calibration_data, raw->temperature);
	pressure = compensate_pressure(m_device.calibration_data, raw->pressure);
	humidity = compensate_humidity(m_device.calibration_data, raw->humidity);
}

hal::sensors::i2c::bme280::CalibrationData hal::sensors::i2c::bme280::BME280::get_calibration_data() const
{
	uint8_t calibration_data[TEMPERATURE_PRESSURE_CALIB_DATA_LENGTH] = {0};
	try
	{
		I2CManager::read_from_device(m_file_handle, TEMPERATURE_CALIBRATION_REG_1, calibration_data, TEMPERATURE_PRESSURE_CALIB_DATA_LENGTH);
	}
	catch (exception::HALException* ex)
	{
		throw exception::I2CException("BME280", "get_calibration_data", m_dev_id, DATA_REG,
												std::string("Could not read temperature and pressure calibration data:\n").append(ex->to_string()));
	}

	auto calibration = CalibrationData();
	calibration.temperature_calibration_reg_1 = static_cast<int16_t>(BitManipulation::combine_bytes(calibration_data[1], calibration_data[0])
	);
	calibration.temperature_calibration_reg_2 = static_cast<int16_t>(BitManipulation::combine_bytes(calibration_data[3], calibration_data[2])
	);
	calibration.temperature_calibration_reg_3 = static_cast<int16_t>(BitManipulation::combine_bytes(calibration_data[5], calibration_data[4])
	);

	calibration.pressure_calibration_reg_1 = BitManipulation::combine_bytes(calibration_data[7], calibration_data[6]);
	calibration.pressure_calibration_reg_2 = static_cast<int16_t>(BitManipulation::combine_bytes(calibration_data[9], calibration_data[8]));
	calibration.pressure_calibration_reg_3 = static_cast<int16_t>(BitManipulation::combine_bytes(calibration_data[11], calibration_data[10])
	);
	calibration.pressure_calibration_reg_4 = static_cast<int16_t>(BitManipulation::combine_bytes(calibration_data[13], calibration_data[12])
	);
	calibration.pressure_calibration_reg_5 = static_cast<int16_t>(BitManipulation::combine_bytes(calibration_data[15], calibration_data[14])
	);
	calibration.pressure_calibration_reg_6 = static_cast<int16_t>(BitManipulation::combine_bytes(calibration_data[17], calibration_data[16])
	);
	calibration.pressure_calibration_reg_7 = static_cast<int16_t>(BitManipulation::combine_bytes(calibration_data[19], calibration_data[18])
	);
	calibration.pressure_calibration_reg_8 = static_cast<int16_t>(BitManipulation::combine_bytes(calibration_data[21], calibration_data[20])
	);
	calibration.pressure_calibration_reg_9 = static_cast<int16_t>(BitManipulation::combine_bytes(calibration_data[23], calibration_data[22])
	);
	//calibration_data[24] (0xA0) is not needed
	calibration.humidity_calibration_reg_1 = calibration_data[25];

	try
	{
		I2CManager::read_from_device(m_file_handle, HUMIDITY_CALIBRATION_REG_2, calibration_data, HUMIDITY_CALIB_DATA_LENGTH);
	}
	catch (exception::HALException* ex)
	{
		throw exception::I2CException("BME280", "get_calibration_data", m_dev_id, DATA_REG,
												std::string("Could not read humidity calibration data:\n").append(ex->to_string()));
	}

	calibration.humidity_calibration_reg_2 = static_cast<int16_t>(BitManipulation::combine_bytes(calibration_data[1], calibration_data[0]));
	calibration.humidity_calibration_reg_3 = calibration_data[2];
	const auto dig_h4_msb = static_cast<int16_t>(calibration_data[3] * 16);
	const auto dig_h4_lsb = static_cast<int16_t>(BitManipulation::mask_out(calibration_data[4], 0x0F));
	calibration.humidity_calibration_reg_4 = BitManipulation::combine(dig_h4_msb, dig_h4_lsb);
	const auto dig_h5_msb = static_cast<int16_t>(calibration_data[5] * 16);
	const auto dig_h5_lsb = BitManipulation::divide_by_2_power_n(calibration_data[4], static_cast<uint8_t>(4), int16_t());
	calibration.humidity_calibration_reg_5 = BitManipulation::combine(dig_h5_msb, dig_h5_lsb);
	calibration.humidity_calibration_reg_6 = static_cast<int8_t>(calibration_data[6]);

	return calibration;
}

std::shared_ptr<hal::sensors::i2c::bme280::RawData> hal::sensors::i2c::bme280::BME280::parse_raw_data(uint8_t* read_data) const noexcept
{
	auto raw_data = std::make_shared<RawData>();

	auto data_msb = BitManipulation::multiply_by_2_power_n(read_data[0], 12, uint32_t());
	auto data_lsb = BitManipulation::multiply_by_2_power_n(read_data[1], 4, uint32_t());
	auto data_xlsb = BitManipulation::divide_by_2_power_n(read_data[2], 4, uint32_t());
	raw_data->pressure = BitManipulation::combine(data_msb, BitManipulation::combine(data_lsb, data_xlsb));

	data_msb = BitManipulation::multiply_by_2_power_n(read_data[3], 12, uint32_t());
	data_lsb = BitManipulation::multiply_by_2_power_n(read_data[4], 4, uint32_t());
	data_xlsb = BitManipulation::divide_by_2_power_n(read_data[5], 4, uint32_t());
	raw_data->temperature = BitManipulation::combine(data_msb, BitManipulation::combine(data_lsb, data_xlsb));

	data_msb = BitManipulation::multiply_by_2_power_n(read_data[6], 8, uint32_t());
	data_lsb = static_cast<uint32_t>(read_data[7]);
	raw_data->humidity = BitManipulation::combine(data_msb, data_lsb);

	return raw_data;
}

std::shared_ptr<hal::sensors::i2c::bme280::SettingsData> hal::sensors::i2c::bme280::BME280::parse_settings(uint8_t* read_data) const
{
	try
	{
		auto settings = std::make_shared<SettingsData>();
		settings->humidity_oversampling = BitManipulation::mask_out(read_data[0], HUMIDITY_MASK);
		settings->pressure_oversampling = BitManipulation::value_of_bits(read_data[2], PRESSURE_POS, 4);
		settings->temperature_oversampling = BitManipulation::value_of_bits(read_data[2], TEMPERATURE_POS, 7);
		settings->filter = BitManipulation::value_of_bits(read_data[3], FILTER_POS, 4);
		settings->standby_time = BitManipulation::value_of_bits(read_data[3], STANDBY_POS, 7);
		return settings;
	}
	catch (exception::HALException* ex)
	{
		throw exception::HALException("BME280", "parse_settings",
												std::string("Could not read value of certain bits from byte:\n").append(ex->to_string()));
	}
}

void hal::sensors::i2c::bme280::BME280::get_all_raw_data(uint8_t all_data[COMPLETE_FILE_LENGTH]) const
{
	try { I2CManager::read_from_device(m_file_handle, FILE_BEGIN, all_data, COMPLETE_FILE_LENGTH); }
	catch (exception::HALException* ex)
	{
		throw exception::I2CException("BME280", "get_all_RawData", m_dev_id, DATA_REG,
												std::string("Could not read all file data:\n").append(ex->to_string()));
	}
}

double hal::sensors::i2c::bme280::BME280::compensate_temperature(CalibrationData& calibration, const int32_t raw_temperature) noexcept
{
	auto var1 = static_cast<double>(raw_temperature) / 16384.0 - static_cast<double>(calibration.temperature_calibration_reg_1) / 1024.0;
	var1 = var1 * static_cast<double>(calibration.temperature_calibration_reg_2);
	auto var2 = (static_cast<double>(raw_temperature) / 131072.0 - static_cast<double>(calibration.temperature_calibration_reg_1) / 8192.0);
	var2 = (var2 * var2) * static_cast<double>(calibration.temperature_calibration_reg_3);
	calibration.fine_temperature = static_cast<int32_t>(var1 + var2);
	auto temperature = (var1 + var2) / 5120.0;
	if (temperature < TEMPERATURE_MIN)
	{
		temperature = TEMPERATURE_MIN;
	}
	else if (temperature > TEMPERATURE_MAX)
	{
		temperature = TEMPERATURE_MAX;
	}

	return temperature;
}

double hal::sensors::i2c::bme280::BME280::compensate_pressure(const CalibrationData calibration, const int32_t raw_pressure) noexcept
{
	double pressure;

	auto var1 = (static_cast<double>(calibration.fine_temperature) / 2.0) - 64000.0;
	auto var2 = var1 * var1 * static_cast<double>(calibration.pressure_calibration_reg_6) / 32768.0;
	var2 = var2 + var1 * static_cast<double>(calibration.pressure_calibration_reg_5) * 2.0;
	var2 = var2 / 4.0 + static_cast<double>(calibration.pressure_calibration_reg_4) * 65536.0;
	const auto var3 = (static_cast<double>(calibration.pressure_calibration_reg_3) * var1 * var1) / 524288.0;
	var1 = (var3 + static_cast<double>(calibration.pressure_calibration_reg_2) * var1) / 524288.0;
	var1 = (1.0 + var1 / 32768.0) * static_cast<double>(calibration.pressure_calibration_reg_1);

	/* avoid exception caused by division by zero */
	if (var1 > (0.0))
	{
		pressure = 1048576.0 - static_cast<double>(raw_pressure);
		pressure = (pressure - var2 / 4096.0) * 6250.0 / var1;
		var1 = static_cast<double>(calibration.pressure_calibration_reg_9) * pressure * pressure / 2147483648.0;
		var2 = pressure * static_cast<double>(calibration.pressure_calibration_reg_8) / 32768.0;
		pressure = pressure + (var1 + var2 + static_cast<double>(calibration.pressure_calibration_reg_7)) / 16.0;
		if (pressure < PRESSURE_MIN)
		{
			pressure = PRESSURE_MIN;
		}
		else if (pressure > PRESSURE_MAX)
		{
			pressure = PRESSURE_MAX;
		}
	}
	else /* Invalid case */
	{
		pressure = PRESSURE_MIN;
	}

	return pressure / 100;
}

double hal::sensors::i2c::bme280::BME280::compensate_humidity(const CalibrationData calibration, const int32_t raw_humidity) noexcept
{
	const auto var1 = static_cast<double>(calibration.fine_temperature) - 76800.0;
	const auto var2 = (static_cast<double>(calibration.humidity_calibration_reg_4) * 64.0 + (static_cast<double>(calibration.
		humidity_calibration_reg_5) / 16384.0) * var1);
	const auto var3 = raw_humidity - var2;
	const auto var4 = static_cast<double>(calibration.humidity_calibration_reg_2) / 65536.0;
	const auto var5 = (1.0 + (static_cast<double>(calibration.humidity_calibration_reg_3) / 67108864.0) * var1);
	auto var6 = 1.0 + (static_cast<double>(calibration.humidity_calibration_reg_6) / 67108864.0) * var1 * var5;
	var6 = var3 * var4 * (var5 * var6);
	auto humidity = var6 * (1.0 - static_cast<double>(calibration.humidity_calibration_reg_1) * var6 / 524288.0);

	if (humidity > HUMIDITY_MAX)
	{
		humidity = HUMIDITY_MAX;
	}
	else if (humidity < HUMIDITY_MIN)
	{
		humidity = HUMIDITY_MIN;
	}

	return humidity;
}

double hal::sensors::i2c::bme280::BME280::calculate_wait_time() const
{
	try
	{
		auto settings = get_settings();
		return 1.25 + (2.3 * m_device.settings.temperature_oversampling) + ((2.3 * m_device.settings.pressure_oversampling) + 0.575) + ((2.3 *
			m_device.settings.humidity_oversampling) + 0.575);
	}
	catch (exception::HALException* ex)
	{
		throw exception::HALException("BME280", "calculate_wait_time",
												std::string("Could not read settings from the device:\n").append(ex->to_string()));
	}
}

void hal::sensors::i2c::bme280::BME280::sleep_until_ready() const noexcept
{
	usleep(static_cast<__useconds_t>(m_device.wait_time * 1000));
}

void hal::sensors::i2c::bme280::BME280::reload_device_settings(const SettingsData settings) const
{
	try
	{
		set_humidity_oversampling(settings);
	}
	catch (exception::HALException* ex)
	{
		throw exception::HALException("BME280", "reload_device_settings",
												std::string("Could not reset humidity oversampling setting back to default:\n").append(
													ex->to_string()));
	}
	try
	{
		set_filter_and_standby_settings(ALL_SETTING_SELECTION, settings);
	}
	catch (exception::HALException* ex)
	{
		throw exception::HALException("BME280", "reload_device_settings",
												std::string("Could not reset filter and standby settings back to default:\n").append(ex->to_string()));
	}
}

bool hal::sensors::i2c::bme280::BME280::are_settings_changed(const uint8_t old_settings, const uint8_t desired_settings) noexcept
{
	return BitManipulation::mask_out(old_settings, desired_settings) != 0;
}
