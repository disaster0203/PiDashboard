#include "bme280_barometer.h"

int8_t driver::sensors::bme280::barometer::init(uint8_t device_address,
	std::function<int8_t(int, uint8_t, std::unique_ptr<uint8_t[]>&, uint16_t)> read_function,
	std::function<int8_t(int, uint8_t, const std::unique_ptr<uint8_t[]>&, uint16_t)> write_function,
	std::function<int8_t(const std::string, uint8_t, int&)> open_device_function,
	std::function<int8_t(int&)> close_device_function)
{
	m_device = bme280_device();
	m_device.dev_id = device_address;
	m_read_function = read_function;
	m_write_function = write_function;
	m_open_device_function = open_device_function;
	m_close_device_function = close_device_function;

	if (m_open_device_function(manager::i2c_manager::DEFAULT_PI_I2C_ADDRESS, device_address, m_file_handle) != OK)
	{
		std::cerr << "BME280 [init] Error: Could not establish connection with device via WiringPi" << std::endl;
		return DEVICE_NOT_FOUND;
	}

	uint8_t try_count = 5;
	std::unique_ptr<uint8_t[]> chip_id(new uint8_t[1]);
	while (try_count)
	{
		if (m_read_function(m_file_handle, CHIP_ID_ADDR, chip_id, 1) == OK)
		{
			m_device.chip_id = *chip_id.get();
			if (soft_reset() == OK)
			{
				get_calibration_data(m_device.calibration_data);
				break;
			}
		}
		usleep(1000);
		--try_count;
	}

	if (!try_count)
	{
		std::cerr << "BME280 [init] Error: Could not find device" << std::endl;
		return DEVICE_NOT_FOUND;
	}

	return OK;
}

int8_t driver::sensors::bme280::barometer::close()
{
	m_close_device_function(m_file_handle);
	return int8_t();
}

int8_t driver::sensors::bme280::barometer::set_pressure_and_temperature_oversampling(uint8_t desired_settings, struct settings_data settings)
{
	int8_t rslt;
	uint8_t reg_addr = MEASUREMENT_OVERSAMPLING_ADDR;
	std::unique_ptr<uint8_t[]> reg_data(new uint8_t[1]);

	if (m_read_function(m_file_handle, reg_addr, reg_data, 1) != OK)
	{
		std::cerr << "BME280 [set_pressure_and_temperature_oversampling] Error: Could not read pressure and temperature oversampling setting from device" << std::endl;
		return COMMUNICATION_FAIL;
	}

	if (desired_settings & PRESSURE_SETTING_SELECTION)
	{
		reg_data.get()[0] = ((reg_data.get()[0] & ~((PRESSURE_MASK))) | ((settings.pressure_oversampling << (PRESSURE_POS)) & (PRESSURE_MASK)));
	}
	if (desired_settings & TEMPERATURE_SETTING_SELECTION)
	{
		reg_data.get()[0] = ((reg_data.get()[0] & ~((TEMPERATURE_MASK))) | ((settings.temperature_oversampling << (TEMPERATURE_POS)) & (TEMPERATURE_MASK)));
	}

	/* Write the oversampling settings in the register */
	if (m_write_function(m_file_handle, reg_addr, std::move(reg_data), 1) != OK)
	{
		std::cerr << "BME280 [set_pressure_and_temperature_oversampling] Error: Could not write pressure and temperature oversampling settings to device" << std::endl;
		return COMMUNICATION_FAIL;
	}

	return OK;
}

int8_t driver::sensors::bme280::barometer::set_humidity_oversampling(struct settings_data settings)
{
	int8_t rslt;

	/* Humidity related changes will be only effective after a
	 * write operation to ctrl_meas register
	 */
	uint8_t reg_addr = HUMIDITY_OVERSAMPLING_ADDR;
	std::unique_ptr<uint8_t[]> ctrl_hum(new uint8_t[1]{ settings.humidity_oversampling & HUMIDITY_MASK });
	if (m_write_function(m_file_handle, reg_addr, ctrl_hum, 1) != OK)
	{
		std::cerr << "BME280 [set_humidity_oversampling] Error: Could not write humidity setting to device" << std::endl;
		return COMMUNICATION_FAIL;
	}

	reg_addr = MEASUREMENT_OVERSAMPLING_ADDR;
	std::unique_ptr<uint8_t[]> ctrl_meas(new uint8_t[1]);
	if (m_read_function(m_file_handle, reg_addr, ctrl_meas, 1) != OK)
	{
		std::cerr << "BME280 [set_humidity_oversampling] Error: Could not read settings from device" << std::endl;
		return COMMUNICATION_FAIL;
	}

	if (m_write_function(m_file_handle, reg_addr, ctrl_meas, 1) != OK)
	{
		std::cerr << "BME280 [set_humidity_oversampling] Error: Could not write settings to device" << std::endl;
		return COMMUNICATION_FAIL;
	}

	return OK;
}

int8_t driver::sensors::bme280::barometer::set_filter_and_standby_settings(uint8_t desired_settings, settings_data settings)
{
	uint8_t reg_addr = CONFIG_ADDR;
	std::unique_ptr<uint8_t[]> reg_data(new uint8_t[1]);

	if (m_read_function(m_file_handle, reg_addr, reg_data, 1) != OK)
	{
		std::cerr << "BME280 [set_filter] Error: Could not read filter and standby settings from device" << std::endl;
		return COMMUNICATION_FAIL;
	}

	if (desired_settings & FILTER_SETTING_SELECTION)
	{
		reg_data.get()[0] = ((reg_data.get()[0] & ~((FILTER_MASK))) | ((settings.filter << (FILTER_POS)) & (FILTER_MASK)));
	}
	if (desired_settings & STANDBY_SETTING_SELECTION)
	{
		reg_data.get()[0] = ((reg_data.get()[0] & ~((STANDBY_MASK))) | ((settings.standby_time << (STANDBY_POS)) & (STANDBY_MASK)));

	}

	if (m_write_function(m_file_handle, reg_addr, reg_data, 1) != OK)
	{
		std::cerr << "BME280 [set_filter] Error: Could not write filter and standby settings to device" << std::endl;
		return COMMUNICATION_FAIL;
	}

	return OK;
}

int8_t driver::sensors::bme280::barometer::set_sensor_mode(enum bme280_mode mode)
{
	enum bme280_mode last_mode;
	if (get_sensor_mode(last_mode) < 0)
	{
		std::cerr << "BME280 [set_sensor_mode] Error: Could not read current sensor mode" << std::endl;
		return COMMUNICATION_FAIL;
	}

	if (mode != last_mode)
	{
		std::unique_ptr<uint8_t[]> reg_data(new uint8_t[1]);

		if (m_read_function(m_file_handle, MODE_ADDR, reg_data, 1) != OK)
		{
			std::cerr << "BME280 [set_sensor_mode] Error: Could not read settings from device" << std::endl;
			return COMMUNICATION_FAIL;
		}

		reg_data.get()[0] = ((reg_data.get()[0] & ~((SENSOR_MODE_MASK))) | ((uint8_t)mode & (SENSOR_MODE_MASK)));
		if (m_write_function(m_file_handle, MODE_ADDR, reg_data, 1) != OK)
		{
			std::cerr << "BME280 [set_sensor_mode] Error: Could not write new sensor mode" << std::endl;
			return COMMUNICATION_FAIL;
		}
	}

	return OK;
}

int8_t driver::sensors::bme280::barometer::get_sensor_mode(enum bme280_mode& mode)
{
	std::unique_ptr<uint8_t[]> result(new uint8_t[1]{ 0 });

	/* Read the power mode register */
	if (m_read_function(m_file_handle, MODE_ADDR, result, 1) != OK)
	{
		std::cerr << "BME280 [get_sensor_mode] Error: Could not read device mode" << std::endl;
		return COMMUNICATION_FAIL;
	}

	result.get()[0] = (result.get()[0] & (((SENSOR_MODE_MASK))));
	if (result.get()[0] == 0) mode = bme280_mode::SLEEP;
	else if (result.get()[0] == 1 || result.get()[0] == 2) mode = bme280_mode::FORCED;
	else if (result.get()[0] == 3) mode = bme280_mode::NORMAL;

	return OK;
}

int8_t driver::sensors::bme280::barometer::set_settings(enum bme280_oversampling temperature, enum bme280_oversampling pressure, enum bme280_oversampling humidity, enum bme280_filter filter, enum bme280_standby_time standby)
{
	m_device.settings.temperature_oversampling = (uint8_t)temperature;
	m_device.settings.pressure_oversampling = (uint8_t)pressure;
	m_device.settings.humidity_oversampling = (uint8_t)humidity;
	m_device.settings.filter = (uint8_t)filter;
	m_device.settings.standby_time = (uint8_t)standby;

	uint8_t settings_sel = PRESSURE_SETTING_SELECTION | TEMPERATURE_SETTING_SELECTION | HUMIDITY_SETTING_SELECTION | FILTER_SETTING_SELECTION | STANDBY_SETTING_SELECTION;
	uint8_t reg_data[4];
	std::unique_ptr<struct settings_data> settings = std::make_unique<struct settings_data>();
	enum bme280_mode sensor_mode;

	if (get_sensor_mode(sensor_mode) != OK)
	{
		std::cerr << "BME280 [set_settings] Error: Could not read current device mode" << std::endl;
		return COMMUNICATION_FAIL;
	}

	if (get_settings(settings) != OK)
	{
		std::cerr << "BME280 [set_settings] Error: Could not read current settings from device" << std::endl;
		return COMMUNICATION_FAIL;
	}

	// Sleep mode and reset
	if (sensor_mode != bme280_mode::SLEEP)
	{
		if (soft_reset() != OK)
		{
			std::cerr << "BME280 [set_settings] Error: Could not soft reset device" << std::endl;
			return COMMUNICATION_FAIL;
		}
		if (reload_device_settings(*settings.get()) != OK)
		{
			std::cerr << "BME280 [set_settings] Error: Could not reload device settings" << std::endl;
			return COMMUNICATION_FAIL;
		}
	}

	// Apply new settings
	if (are_settings_changed(OVERSAMPLING_SETTINGS, settings_sel))
	{
		if (settings_sel & HUMIDITY_SETTING_SELECTION)
		{
			set_humidity_oversampling(m_device.settings);
		}
		if (settings_sel & (PRESSURE_SETTING_SELECTION | TEMPERATURE_SETTING_SELECTION))
		{
			set_pressure_and_temperature_oversampling(settings_sel, m_device.settings);
		}

		if (calculate_wait_time(m_device.wait_time) != OK)
		{
			std::cerr << "BME280 [set_settings] Error: Could not calculate wait time" << std::endl;
			return COMMUNICATION_FAIL;
		}
	}

	if (are_settings_changed(FILTER_STANDBY_SETTINGS, settings_sel))
	{
		set_filter_and_standby_settings(settings_sel, m_device.settings);
	}

	double t, p, h;
	get_all_data(t, p, h);
	return OK;
}

int8_t driver::sensors::bme280::barometer::get_settings(std::unique_ptr<struct settings_data>& settings)
{
	std::unique_ptr<uint8_t[]> reg_data(new uint8_t[4]);

	if (null_check(settings.get()) != OK)
	{
		std::cerr << "BME280 [get_settings] Error: Settings input struct is null" << std::endl;
		return NULL_PTR;
	}

	if (m_read_function(m_file_handle, HUMIDITY_OVERSAMPLING_ADDR, reg_data, 4) != OK)
	{
		std::cerr << "BME280 [get_settings] Error: Could not read settings data from device" << std::endl;
		return COMMUNICATION_FAIL;
	}

	parse_settings(reg_data, settings);
	return OK;

}

int8_t driver::sensors::bme280::barometer::soft_reset()
{
	std::unique_ptr<uint8_t[]> data(new uint8_t[1]{ SOFT_RESET_VALUE });
	if (m_write_function(m_file_handle, SOFT_RESET_ADDR, data, 1) != OK)
	{
		std::cerr << "BME280 [soft_reset] Error: Could not write soft reset command to device" << std::endl;
		return COMMUNICATION_FAIL;
	}

	std::unique_ptr<uint8_t[]> status_reg(new uint8_t[1]{ 0 });
	uint8_t try_run = 5;
	int8_t result;
	do
	{
		usleep(2000);
		result = m_read_function(m_file_handle, STATUS_ADDR, status_reg, 1);
	} while ((result == OK) && (try_run--) && (status_reg.get()[0] & STATUS_DURING_UPDATE));

	if (status_reg.get()[0] & STATUS_DURING_UPDATE)
	{
		std::cerr << "BME280 [soft_reset] Error: NVM copy failed" << std::endl;
		return NVM_COPY_FAILED;
	}

	if (result != OK)
	{
		std::cerr << "BME280 [soft_reset] Error: Could not reset device" << std::endl;
		return COMMUNICATION_FAIL;
	}

	return OK;
}

int8_t driver::sensors::bme280::barometer::get_temperature_data(double& temperature)
{
	if (set_sensor_mode(bme280_mode::FORCED) != OK)
	{
		std::cerr << "BME280 [get_all_data] Error: Could not switch to forced mode" << std::endl;
		return COMMUNICATION_FAIL;
	}

	sleep_until_ready();

	std::unique_ptr<uint8_t[]> reg_data(new uint8_t[ALL_DATA_LENGTH]{ 0 });
	std::unique_ptr<struct raw_data> raw = std::make_unique<struct raw_data>();
	if (m_read_function(m_file_handle, DATA_ADDR, reg_data, ALL_DATA_LENGTH) != OK)
	{
		std::cerr << "BME280 [get_temperature_data] Error: Could not read raw data" << std::endl;
		return COMMUNICATION_FAIL;
	}

	if (parse_raw_data(reg_data, raw) != OK)
	{
		std::cerr << "BME280 [get_temperature_data] Error: Could not read raw sensor data from device" << std::endl;
		return COMMUNICATION_FAIL;
	}
	temperature = compensate_temperature(m_device.calibration_data, raw.get()->temperature);
	return OK;
}

int8_t driver::sensors::bme280::barometer::get_pressure_data(double& pressure)
{
	if (set_sensor_mode(bme280_mode::FORCED) != OK)
	{
		std::cerr << "BME280 [get_all_data] Error: Could not switch to forced mode" << std::endl;
		return COMMUNICATION_FAIL;
	}

	sleep_until_ready();

	std::unique_ptr<uint8_t[]> reg_data(new uint8_t[ALL_DATA_LENGTH]{ 0 });
	std::unique_ptr<struct raw_data> raw = std::make_unique<struct raw_data>();
	if (m_read_function(m_file_handle, DATA_ADDR, reg_data, ALL_DATA_LENGTH) != OK)
	{
		std::cerr << "BME280 [get_pressure_data] Error: Could not read raw data" << std::endl;
		return COMMUNICATION_FAIL;
	}

	if (parse_raw_data(reg_data, raw) != OK)
	{
		std::cerr << "BME280 [get_pressure_data] Error: Could not read raw sensor data from device" << std::endl;
		return COMMUNICATION_FAIL;
	}
	pressure = compensate_pressure(m_device.calibration_data, raw.get()->pressure);
	return OK;
}

int8_t driver::sensors::bme280::barometer::get_humidity_data(double& humidity)
{
	if (set_sensor_mode(bme280_mode::FORCED) != OK)
	{
		std::cerr << "BME280 [get_all_data] Error: Could not switch to forced mode" << std::endl;
		return COMMUNICATION_FAIL;
	}

	sleep_until_ready();

	std::unique_ptr<uint8_t[]> reg_data(new uint8_t[ALL_DATA_LENGTH]{ 0 });
	std::unique_ptr<struct raw_data> raw = std::make_unique<struct raw_data>();
	if (m_read_function(m_file_handle, DATA_ADDR, reg_data, ALL_DATA_LENGTH) != OK)
	{
		std::cerr << "BME280 [get_humidity_data] Error: Could not read raw data" << std::endl;
		return COMMUNICATION_FAIL;
	}

	if (parse_raw_data(reg_data, raw) != OK)
	{
		std::cerr << "BME280 [get_humidity_data] Error: Could not read raw sensor data from device" << std::endl;
		return COMMUNICATION_FAIL;
	}
	humidity = compensate_humidity(m_device.calibration_data, raw.get()->humidity);
	return OK;
}

int8_t driver::sensors::bme280::barometer::get_all_data(double& temperature, double& pressure, double& humidity)
{
	if (set_sensor_mode(bme280_mode::FORCED) != OK)
	{
		std::cerr << "BME280 [get_all_data] Error: Could not switch to forced mode" << std::endl;
		return COMMUNICATION_FAIL;
	}

	sleep_until_ready();

	std::unique_ptr<uint8_t[]> reg_data(new uint8_t[ALL_DATA_LENGTH]{ 0 });
	std::unique_ptr<struct raw_data> raw = std::make_unique<struct raw_data>();
	if (m_read_function(m_file_handle, DATA_ADDR, reg_data, ALL_DATA_LENGTH) != OK)
	{
		std::cerr << "BME280 [get_all_data] Error: Could not read raw data" << std::endl;
		return COMMUNICATION_FAIL;
	}

	if (parse_raw_data(reg_data, raw) != OK)
	{
		std::cerr << "BME280 [get_all_data] Error: Could not read raw sensor data from device" << std::endl;
		return COMMUNICATION_FAIL;
	}

	temperature = get_temperature_data(*raw.get());
	pressure = get_pressure_data(*raw.get());
	humidity = get_humidity_data(*raw.get());
	return OK;
}

double driver::sensors::bme280::barometer::get_temperature_data(struct raw_data raw_data)
{
	return compensate_temperature(m_device.calibration_data, raw_data.temperature);
}

double driver::sensors::bme280::barometer::get_pressure_data(struct raw_data raw_data)
{
	return compensate_pressure(m_device.calibration_data, raw_data.pressure);
}

double driver::sensors::bme280::barometer::get_humidity_data(struct raw_data raw_data)
{
	return compensate_humidity(m_device.calibration_data, raw_data.humidity);
}

int8_t driver::sensors::bme280::barometer::get_calibration_data(struct calibration_data& calibration_data)
{
	std::unique_ptr<uint8_t[]> calib_data(new uint8_t[TEMPERATURE_PRESSURE_CALIB_DATA_LENGTH]{ 0 });

	if (m_read_function(m_file_handle, TEMPERATURE_CALIBRATION_ADDR_1, calib_data, TEMPERATURE_PRESSURE_CALIB_DATA_LENGTH) != OK)
	{
		std::cerr << "BME280 [get_calibration_data] Error: Could not read temperature and pressure calibration data" << std::endl;
		return COMMUNICATION_FAIL;
	}

	calibration_data.temperature_calibration_addr_1 = (((uint16_t)calib_data[1] << 8) | (uint16_t)calib_data[0]);
	calibration_data.temperature_calibration_addr_2 = (int16_t)(((uint16_t)calib_data[3] << 8) | (uint16_t)calib_data[2]);
	calibration_data.temperature_calibration_addr_3 = (int16_t)(((uint16_t)calib_data[5] << 8) | (uint16_t)calib_data[4]);

	calibration_data.pressure_calibration_addr_1 = (((uint16_t)calib_data[7] << 8) | (uint16_t)calib_data[6]);
	calibration_data.pressure_calibration_addr_2 = (int16_t)(((uint16_t)calib_data[9] << 8) | (uint16_t)calib_data[8]);
	calibration_data.pressure_calibration_addr_3 = (int16_t)(((uint16_t)calib_data[11] << 8) | (uint16_t)calib_data[10]);
	calibration_data.pressure_calibration_addr_4 = (int16_t)(((uint16_t)calib_data[13] << 8) | (uint16_t)calib_data[12]);
	calibration_data.pressure_calibration_addr_5 = (int16_t)(((uint16_t)calib_data[15] << 8) | (uint16_t)calib_data[14]);
	calibration_data.pressure_calibration_addr_6 = (int16_t)(((uint16_t)calib_data[17] << 8) | (uint16_t)calib_data[16]);
	calibration_data.pressure_calibration_addr_7 = (int16_t)(((uint16_t)calib_data[19] << 8) | (uint16_t)calib_data[18]);
	calibration_data.pressure_calibration_addr_8 = (int16_t)(((uint16_t)calib_data[21] << 8) | (uint16_t)calib_data[20]);
	calibration_data.pressure_calibration_addr_9 = (int16_t)(((uint16_t)calib_data[23] << 8) | (uint16_t)calib_data[22]);
	//calib_data[24] (0xA0) is not needed
	calibration_data.humidity_calibration_addr_1 = calib_data[25];

	if (m_read_function(m_file_handle, HUMIDITY_CALIBRATION_ADDR_2, calib_data, HUMIDITY_CALIB_DATA_LENGTH) != OK)
	{
		std::cerr << "BME280 [get_calibration_data] Error: Could not read humidity calibration data" << std::endl;
		return COMMUNICATION_FAIL;
	}

	int16_t dig_h4_lsb;
	int16_t dig_h4_msb;
	int16_t dig_h5_lsb;
	int16_t dig_h5_msb;

	calibration_data.humidity_calibration_addr_2 = (int16_t)(((uint16_t)calib_data[1] << 8) | (uint16_t)calib_data[0]);
	calibration_data.humidity_calibration_addr_3 = calib_data[2];
	dig_h4_msb = (int16_t)(int8_t)calib_data[3] * 16;
	dig_h4_lsb = (int16_t)(calib_data[4] & 0x0F);
	calibration_data.humidity_calibration_addr_4 = dig_h4_msb | dig_h4_lsb;
	dig_h5_msb = (int16_t)(int8_t)calib_data[5] * 16;
	dig_h5_lsb = (int16_t)(calib_data[4] >> 4);
	calibration_data.humidity_calibration_addr_5 = dig_h5_msb | dig_h5_lsb;
	calibration_data.humidity_calibration_addr_6 = (int8_t)calib_data[6];

	return OK;
}

int8_t driver::sensors::bme280::barometer::parse_raw_data(std::unique_ptr<uint8_t[]>& read_data, std::unique_ptr<struct raw_data>& raw_data)
{
	uint32_t data_xlsb = 0;
	uint32_t data_lsb = 0;
	uint32_t data_msb = 0;

	data_msb = (uint32_t)read_data[0] << 12;
	data_lsb = (uint32_t)read_data[1] << 4;
	data_xlsb = (uint32_t)read_data[2] >> 4;
	raw_data->pressure = data_msb | data_lsb | data_xlsb;

	data_msb = (uint32_t)read_data[3] << 12;
	data_lsb = (uint32_t)read_data[4] << 4;
	data_xlsb = (uint32_t)read_data[5] >> 4;
	raw_data->temperature = data_msb | data_lsb | data_xlsb;

	data_msb = (uint32_t)read_data[6] << 8;
	data_lsb = (uint32_t)read_data[7];
	raw_data->humidity = data_msb | data_lsb;

	return OK;
}

int8_t driver::sensors::bme280::barometer::get_all_raw_data(std::unique_ptr<uint8_t[]>& all_data)
{
	std::unique_ptr<uint8_t[]>reg_data(new uint8_t[COMPLETE_FILE_LENGTH]{ 0 });
	if (m_read_function(m_file_handle, FILE_BEGIN, reg_data, COMPLETE_FILE_LENGTH) != OK)
	{
		std::cerr << "BME280 [get_all_raw_data] Error: Could not read all file data" << std::endl;
		return COMMUNICATION_FAIL;
	}
	all_data = std::move(reg_data);

	return OK;
}

double driver::sensors::bme280::barometer::compensate_temperature(struct calibration_data calibration, int32_t raw_temperature)
{
	double var1;
	double var2;
	double temperature;

	var1 = ((double)raw_temperature) / 16384.0 - ((double)calibration.temperature_calibration_addr_1) / 1024.0;
	var1 = var1 * ((double)calibration.temperature_calibration_addr_2);
	var2 = (((double)raw_temperature) / 131072.0 - ((double)calibration.temperature_calibration_addr_1) / 8192.0);
	var2 = (var2 * var2) * ((double)calibration.temperature_calibration_addr_3);
	calibration.fine_temperature = (int32_t)(var1 + var2);
	temperature = (var1 + var2) / 5120.0;
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

double driver::sensors::bme280::barometer::compensate_pressure(struct calibration_data calibration, int32_t raw_pressure)
{
	double var1;
	double var2;
	double var3;
	double pressure;

	var1 = ((double)calibration.fine_temperature / 2.0) - 64000.0;
	var2 = var1 * var1 * (double)calibration.pressure_calibration_addr_6 / 32768.0;
	var2 = var2 + var1 * (double)calibration.pressure_calibration_addr_5 * 2.0;
	var2 = var2 / 4.0 + (double)calibration.pressure_calibration_addr_4 * 65536.0;
	var3 = ((double)calibration.pressure_calibration_addr_3 * var1 * var1) / 524288.0;
	var1 = (var3 + (double)calibration.pressure_calibration_addr_2 * var1) / 524288.0;
	var1 = (1.0 + var1 / 32768.0) * (double)calibration.pressure_calibration_addr_1;

	/* avoid exception caused by division by zero */
	if (var1 > (0.0))
	{
		pressure = 1048576.0 - (double)raw_pressure;
		pressure = (pressure - var2 / 4096.0) * 6250.0 / var1;
		var1 = (double)calibration.pressure_calibration_addr_9 * pressure * pressure / 2147483648.0;
		var2 = pressure * (double)calibration.pressure_calibration_addr_8 / 32768.0;
		pressure = pressure + (var1 + var2 + (double)calibration.pressure_calibration_addr_7) / 16.0;
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

double driver::sensors::bme280::barometer::compensate_humidity(struct calibration_data calibration, int32_t raw_humidity)
{
	double humidity;
	double var1;
	double var2;
	double var3;
	double var4;
	double var5;
	double var6;

	var1 = ((double)calibration.fine_temperature) - 76800.0;
	var2 = (((double)calibration.humidity_calibration_addr_4) * 64.0 + (((double)calibration.humidity_calibration_addr_5) / 16384.0) * var1);
	var3 = raw_humidity - var2;
	var4 = ((double)calibration.humidity_calibration_addr_2) / 65536.0;
	var5 = (1.0 + (((double)calibration.humidity_calibration_addr_3) / 67108864.0) * var1);
	var6 = 1.0 + (((double)calibration.humidity_calibration_addr_6) / 67108864.0) * var1 * var5;
	var6 = var3 * var4 * (var5 * var6);
	humidity = var6 * (1.0 - ((double)calibration.humidity_calibration_addr_1) * var6 / 524288.0);

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

int8_t driver::sensors::bme280::barometer::calculate_wait_time(double& time)
{
	std::unique_ptr<struct settings_data> settings = std::make_unique<struct settings_data>(m_device.settings);
	if (get_settings(settings) != OK)
	{
		std::cerr << "BME280 [calculate_wait_time] Error: Could not read device settings" << std::endl;
		return COMMUNICATION_FAIL;
	}
	time = 1.25 + (2.3 * m_device.settings.temperature_oversampling) + ((2.3 * m_device.settings.pressure_oversampling) + 0.575) + ((2.3 * m_device.settings.humidity_oversampling) + 0.575);
	return OK;
}

void driver::sensors::bme280::barometer::sleep_until_ready()
{
	usleep(m_device.wait_time * 1000);
}

void driver::sensors::bme280::barometer::parse_settings(std::unique_ptr<uint8_t[]>& read_data, std::unique_ptr<struct settings_data>& settings)
{
	settings->humidity_oversampling = (read_data[0] & ((HUMIDITY_MASK)));
	settings->pressure_oversampling = ((read_data[2] & ((PRESSURE_MASK))) >> ((PRESSURE_POS)));
	settings->temperature_oversampling = ((read_data[2] & ((TEMPERATURE_MASK))) >> ((TEMPERATURE_POS)));
	settings->filter = ((read_data[3] & ((FILTER_MASK))) >> ((FILTER_POS)));
	settings->standby_time = ((read_data[3] & ((STANDBY_MASK))) >> ((STANDBY_POS)));
}

int8_t driver::sensors::bme280::barometer::reload_device_settings(struct settings_data settings)
{
	if (set_humidity_oversampling(settings) != OK || set_filter_and_standby_settings(ALL_SETTING_SELECTION, settings) != OK)
	{
		std::cerr << "BME280 [reload_device_settings] Error: Could not rewrite device settings" << std::endl;
		return COMMUNICATION_FAIL;
	}

	return OK;
}

bool driver::sensors::bme280::barometer::are_settings_changed(uint8_t old_settings, uint8_t desired_settings)
{
	if (old_settings & desired_settings)
	{
		return true;
	}
	else
	{
		return false;
	}
}

int8_t driver::sensors::bme280::barometer::null_check(void* pointer)
{
	if (pointer)
	{
		return OK;
	}

	return NULL_PTR;
}
