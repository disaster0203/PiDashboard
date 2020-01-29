#include "manager/db_manager.h"
#include "drivers/bme280_barometer.h"
#include "dto/sensor_dto.h"
#include "utils/time_converter.h"

#include <cstdio>
#include <iostream>
#include <iomanip>
#include <chrono>
#include <ctime>
#include <mysql/mysql.h>

driver::sensors::bme280::barometer* bme280;

void print_menu()
{
	std::cout << "0: Add entry\n";
	std::cout << "1: All entries\n";
	std::cout << "2: First entry\n";
	std::cout << "3: Last entry\n";
	std::cout << "4: Timestamp entry\n";
	std::cout << "5: Delete entry\n";
	std::cout << "6: Delete older entries\n";
	std::cout << "7: Table exists\n";
	std::cout << "8: Database exists\n";
	std::cout << "9: Delete table\n";
	std::cout << "10: Delete database\n";
	std::cout << "11: Create table\n";
	std::cout << "12: Create database\n";
	std::cout << "------------------------\n";
	std::cout << "13: Get All\n";
	std::cout << "14: Get Temperature\n";
	std::cout << "15: Get Pressure\n";
	std::cout << "16: Get Humidity\n";
}

void print(std::shared_ptr<dto::sensor_dto> entry)
{
	std::cout << entry->get_sensor_type_name() << ", "
		<< entry->get_individual_name() << ", "
		<< entry->get_timestamp_as_string() << ", "
		<< entry->get_value() << "\n";
}

int main()
{
	printf("hello from PiSensorBackend!\n");
	printf("MySQL version: %s\n", mysql_get_client_info());

	srand((int)time(0));

	auto mng = std::make_shared<manager::db_manager>(manager::db_manager("localhost", "test", "password123", "pi_sensor_db"));
	auto bme280 = std::make_shared<driver::sensors::bme280::barometer>();
	bme280->init();
	bme280->set_settings(driver::sensors::bme280::bme280_oversampling::OVERSAMPLING_2X,
		driver::sensors::bme280::bme280_oversampling::OVERSAMPLING_16X,
		driver::sensors::bme280::bme280_oversampling::OVERSAMPLING_1X,
		driver::sensors::bme280::bme280_filter::FILTER_16X,
		driver::sensors::bme280::bme280_standby_time::STANDBY_250_MS);

	int choose;
	while (true)
	{
		print_menu();
		std::string timestamp;
		std::cin >> choose;
		switch (choose)
		{
		case 0:
			mng->add_sensor_entry(std::make_shared<dto::sensor_dto>(dto::sensor_dto("barometer_gy_bme280_temperature", "Wohnzimmer", std::chrono::system_clock::now(), rand())));
			mng->add_sensor_entry(std::make_shared<dto::sensor_dto>(dto::sensor_dto("barometer_gy_bme280_air_humidity", "Wohnzimmer", std::chrono::system_clock::now(), rand())));
			mng->add_sensor_entry(std::make_shared<dto::sensor_dto>(dto::sensor_dto("barometer_gy_bme280_air_pressure", "Wohnzimmer", std::chrono::system_clock::now(), rand())));
			break;
		case 1:
		{
			std::vector<std::shared_ptr<dto::sensor_dto>> entries;
			if (mng->get_all_sensor_entries(entries) == 1)
			{
				for (auto entry : entries)
					print(entry);
			}
		}
		break;
		case 2:
		{
			auto entry = std::make_shared<dto::sensor_dto>();
			if (mng->get_first_sensor_entry(entry) == 1)
			{
				print(entry);
			}
		}
		break;
		case 3:
		{
			auto entry = std::make_shared<dto::sensor_dto>();
			if (mng->get_last_sensor_entry(entry) == 1)
			{
				print(entry);
			}
		}
		break;
		case 4:
		{
			auto entry = std::make_shared<dto::sensor_dto>();
			if (mng->get_sensor_entry(entry, "barometer_gy_bme280_temperature", "Wohnzimmer", utils::time_converter::string_to_timepoint("2020-01-15 19:14:00")) == 1)
			{
				print(entry);
			}
		}
		break;
		case 5:
			if (mng->delete_sensor_entry("barometer_gy_bme280", "Wohnzimmer", utils::time_converter::string_to_timepoint("2020-01-15 19:14:00")) == 1)
			{
				std::cout << "Deleted row with timestamp: " << "2020-01-15 19:14:00";
			}
			break;
		case 6:
			std::cout << "Enter timestamp (yyyy-mm-dd HH:MM:SS)";
			std::cin >> timestamp;
			if (mng->delete_sensor_entries("barometer_gy_bme280", "Wohnzimmer", utils::time_converter::string_to_timepoint(timestamp), true) == 1)
			{
				std::cout << "Deleted row with timestamp: " << "2020-01-15 19:14:00";
			}
			break;
		case 7:
			std::cout << "Table 'barometer_gy_bme280' " << ((mng->check_if_table_exists("pi_sensor_db", "barometer_gy_bme280") == 1) ? "exists" : "does not exist");
			break;
		case 8:
			std::cout << "Database 'pi_sensor_db' " << ((mng->check_if_database_exists("pi_sensor_db") == 1) ? "exists" : "does not exist");
			break;
		case 9:
			if (mng->delete_table("barometer_gy_bme280") == 1)
			{
				std::cout << "Deleted table 'barometer_gy_bme280'";
			}
			break;
		case 10:
			if (mng->delete_database("pi_sensor_db") == 1)
			{
				std::cout << "Deleted database 'pi_sensor_db'";
			}
			break;
		case 11:
			mng->create_table("CREATE TABLE IF NOT EXISTS barometer_gy_bme280(id INT UNSIGNED AUTO_INCREMENT PRIMARY KEY, sensor_name TEXT NOT NULL, timestamp TIMESTAMP DEFAULT CURRENT_TIMESTAMP ON UPDATE CURRENT_TIMESTAMP, temperature DOUBLE, air_humidity DOUBLE, air_pressure DOUBLE);");
			std::cout << "Created table 'barometer_gy_bme280'";
			break;
		case 12:
			mng->create_database("pi_sensor_db");
			mng->use_database("pi_sensor_db");
			std::cout << "Created database 'pi_sensor_db'";
			break;
		case 13:
		{
			double temp, press, hum;

			if (bme280->get_all_data(temp, press, hum) == 0)
			{
				std::cout << "Temperature: " << temp << "C  Pressure: " << press << "hPa  Humidity: " << hum << "%" << std::endl;
			}
		}
		break;
		case 14:
		{
			double temp;
			if (bme280->get_temperature_data(temp) == 0)
			{
				std::cout << "Temperature: " << temp << "C" << std::endl;
			}
		}
		break;
		case 15:
		{
			double press;
			if (bme280->get_pressure_data(press) == 0)
			{
				std::cout << "Pressure: " << press << "hPa" << std::endl;
			}
		}
		break;
		case 16:
		{
			double hum;
			if (bme280->get_humidity_data(hum) == 0)
			{
				std::cout << "Humidity: " << hum << "%" << std::endl;
			}
		}
		break;
		}
	}

	return 0;
}
