#include "manager/db_manager.h"
#include "dto/sensor_dto.h"
#include "utils/time_converter.h"

#include <cstdio>
#include <iostream>
#include <iomanip>
#include <chrono>
#include <ctime>
#include <mysql/mysql.h>

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
}

void print(dto::sensor_dto* entry)
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

	db_manager* mng = new db_manager("localhost", "test", "password123", "pi_sensor_db");

	int choose;
	while (true)
	{
		print_menu();
		std::string timestamp;
		std::cin >> choose;
		switch (choose)
		{
		case 0:
			mng->add_sensor_entry(new dto::sensor_dto("barometer_gy_bme280_temperature", "Wohnzimmer", std::chrono::system_clock::now(), rand()));
			mng->add_sensor_entry(new dto::sensor_dto("barometer_gy_bme280_air_humidity", "Wohnzimmer", std::chrono::system_clock::now(), rand()));
			mng->add_sensor_entry(new dto::sensor_dto("barometer_gy_bme280_air_pressure", "Wohnzimmer", std::chrono::system_clock::now(), rand()));
			break;
		case 1:
		{
			for (auto entry : mng->get_all_sensor_entries())
				print(entry);
		}
		break;
		case 2:
			print(mng->get_first_sensor_entry());
			break;
		case 3:
			print(mng->get_last_sensor_entry());
			break;
		case 4:
			print(mng->get_sensor_entry("barometer_gy_bme280_temperature", "Wohnzimmer", utils::time_converter::string_to_timepoint("2020-01-15 19:14:00")));
			break;
		case 5:
			mng->delete_sensor_entry("barometer_gy_bme280", "Wohnzimmer", utils::time_converter::string_to_timepoint("2020-01-15 19:14:00"));
			std::cout << "Deleted row with timestamp: " << "2020-01-15 19:14:00";
			break;
		case 6:
			std::cout << "Enter timestamp (yyyy-mm-dd HH:MM:SS)";
			std::cin >> timestamp;
			mng->delete_sensor_entries("barometer_gy_bme280", "Wohnzimmer", utils::time_converter::string_to_timepoint(timestamp), true);
			std::cout << "Deleted rows older then " << timestamp;
			break;
		case 7:
			std::cout << "Table 'barometer_gy_bme280' " << (mng->check_if_table_exists("pi_sensor_db", "barometer_gy_bme280") ? "exists" : "does not exist");
			break;
		case 8:
			std::cout << "Database 'pi_sensor_db' " << (mng->check_if_database_exists("pi_sensor_db") ? "exists" : "does not exist");
			break;
		case 9:
			mng->delete_table("barometer_gy_bme280");
			std::cout << "Deleted table 'barometer_gy_bme280'";
			break;
		case 10:
			mng->delete_database("pi_sensor_db");
			std::cout << "Deleted database 'pi_sensor_db'";
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
		}
	}

	return 0;
}