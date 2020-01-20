#pragma once

#include "../dto/sensor_dto.h"
#include "../dto/extremas_dto.h"
#include "../dto/query_object.h"
#include "../utils/time_converter.h"

#include <limits>
#include <map>
#include <mysql/mysql.h>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>

//! Class that manages all database operations.
/*!
* This class implements various functions manipulate the underlying MySQL database.
*/
class db_manager
{
public:
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// db_manager_table_management.cpp
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	//! Default constructor.
	/*!
	* Initializes the database connection by performing the following steps:
	* - Check if a anonymous connection can be established.
	* - Try to connect to the projects database.
	* - Create the database if it does not exist yet and use it afterwards.
	* - Check if the tables are existing and create them if needed.
	* 
	* \param host: ip (or localhost) of the pc where the database is located.
	* \param user: the database user to use for all operations (needs select, insert, update, delete, create, drop rights).
	* \param password: the password of the user account.
	* \param database: the name of the database where all tables are located in.
	*/
	db_manager(const std::string host, const std::string user, const std::string password, const std::string database);

	//! Default destructor.
	~db_manager();

	//! Creates a new table.
	/*!
	* Creates a new table by executing the given create table statement.
	*
	* \param statement: the create table statement that is used to create the new table.
	*/
	void create_table(std::string statement);

	//! Creates a new table.
	/*!
	* Creates a new table by building a create table statement from the given parameters.
	*
	* \param table_name: the name of the new table.
	* \param column_definitions: a list of column definitions (name + data type + special settings (e.g. autoincrement, primary key, ...)).
	*/
	void create_table(std::string table_name, std::vector<std::string> column_definitions);

	//! Creates a new database.
	/*!
	* Creates a new database with the given name.
	*
	* \param database_name: the name of the new database.
	*/
	void create_database(std::string database_name);

	//! Calls the use statement on the given database.
	/*!
	* Calls the use statement on the given database.
	*
	* \param database_name: the name of the database to use.
	*/
	void use_database(std::string database_name);

	//! Deletes a table.
	/*!
	* Deletes the table with the given name.
	*
	* \param table_name: the name of the table to delete.
	*/
	void delete_table(std::string table_name);

	//! Deletes a database.
	/*!
	* Deletes the database with the given name.
	*
	* \param database_name: the name of the database to delete.
	*/
	void delete_database(std::string database_name);

	//! Checks if a table exists.
	/*!
	* Checks if the table with the given name exists inside the given database.
	*
	* \param database_name: the name of the database in which the table should be found.
	* \param table_name: the name of the table to lookup.
	* \return true if the table exists, false otherwise.
	*/
	bool check_if_table_exists(std::string database_name, std::string table_name);

	//! Checks if a database exists.
	/*!
	* Checks if the database with the given name exists.
	*
	* \param database_name: the name of the database to lookup.
	* \return true if the database exists, false otherwise.
	*/
	bool check_if_database_exists(std::string database_name);


	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// db_manager_sensors.cpp
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	//! Adds a new entry to the sensor database.
	/*!
	* Adds a new entry to the sensor database.
	*
	* \param new_value: a dto object with the values to add.
	*/
	void add_sensor_entry(dto::sensor_dto* new_value);

	//! Deletes a entry from the sensor database.
	/*!
	* Deletes the entry the given dto represents from the sensor database.
	*
	* \param value: the entry to delete.
	*/
	void delete_sensor_entry(dto::sensor_dto* value);

	//! Deletes a entry from the sensor database.
	/*!
	* Deletes the entry that matches the given names and timestamp from the sensor database.
	*
	* \param sensor_type_name: the type name in the row to delete.
	* \param individual_name: the individual name in the row to delete.
	* \param timestamp: the timestamp name in the row to delete.
	*/
	void delete_sensor_entry(std::string sensor_type_name, std::string individual_name, std::chrono::time_point<std::chrono::system_clock> timestamp);

	//! Deletes multiple entries from the sensor database.
	/*!
	* Deletes all entries that match the given names from the sensor database.
	*
	* \param sensor_type_name: the type name in the rows to delete.
	* \param individual_name: the individual name in the rows to delete.
	*/
	void delete_sensor_entries(std::string sensor_type_name, std::string individual_name);

	//! Deletes multiple entries from the sensor database.
	/*!
	* Deletes all entries that match the given names from the sensor database.
	*
	* \param sensor_type_name: the type name in the rows to delete.
	* \param individual_name: the individual name in the rows to delete.
	* \param timestamp: the timestamp threshold.
	* \param delete_older: true to delete values older than timestamp, false to delete newer ones.
	*/
	void delete_sensor_entries(std::string sensor_type_name, std::string individual_name, std::chrono::time_point<std::chrono::system_clock> timestamp, bool delete_older = true);

	//! Updates an entry.
	/*!
	* Updates an entry that matches the given names and value.
	*
	* \param sensor_type_name: the type name in the row to update.
	* \param individual_name: the individual name in the rows to update.
	* \param column: the name of the column to update.
	* \param old_value: the current value that should be replaced by the new one.
	* \param new_value: the new value to insert into the row.
	*/
	void update_entry(std::string sensor_type_name, std::string individual_name, std::string column, std::string old_value, std::string new_value);

	//! Updates an entry.
	/*!
	* Updates an entry that matches the given names and value.
	*
	* \param sensor_type_name: the type name in the row to update.
	* \param individual_name: the individual name in the rows to update.
	* \param column: the name of the column to update.
	* \param old_value: the current value that should be replaced by the new one.
	* \param new_value: the new value to insert into the row.
	*/
	void update_entry(std::string sensor_type_name, std::string individual_name, std::string column, int old_value, int new_value);

	//! Updates an entry.
	/*!
	* Updates an entry that matches the given names and value.
	*
	* \param sensor_type_name: the type name in the row to update.
	* \param individual_name: the individual name in the rows to update.
	* \param column: the name of the column to update.
	* \param old_value: the current value that should be replaced by the new one.
	* \param new_value: the new value to insert into the row.
	*/
	void update_entry(std::string sensor_type_name, std::string individual_name, std::string column, float old_value, float new_value);

	//! Updates an entry.
	/*!
	* Updates an entry that matches the given names and value.
	*
	* \param sensor_type_name: the type name in the row to update.
	* \param individual_name: the individual name in the rows to update.
	* \param column: the name of the column to update.
	* \param old_value: the current value that should be replaced by the new one.
	* \param new_value: the new value to insert into the row.
	*/
	void update_entry(std::string sensor_type_name, std::string individual_name, std::string column, double old_value, double new_value);

	//! Updates an entry.
	/*!
	* Updates an entry that matches the given names and value.
	*
	* \param sensor_type_name: the type name in the row to update.
	* \param individual_name: the individual name in the rows to update.
	* \param column: the name of the column to update.
	* \param old_value: the current value that should be replaced by the new one.
	* \param new_value: the new value to insert into the row.
	*/
	void update_entry(std::string sensor_type_name, std::string individual_name, std::string column, bool old_value, bool new_value);

	//! Returns a single sensor entry.
	/*!
	* Returns the sensor entry that matches the names and timestamp in the given dto.
	*
	* \param value: the dto used to find the desired sensor row.
	* \return the desired row or an empty dto if the input param did not match any row (check if names are "")
	*/
	dto::sensor_dto* get_sensor_entry(dto::sensor_dto* value);

	//! Returns a single sensor entry.
	/*!
	* Returns the sensor entry that matches the given names and timestamp.
	*
	* \param sensor_type_name: the type name in the row to return.
	* \param individual_name: the individual name in the rows to return.
	* \param timestamp: the timestamp in the rows to return.
	* \return the desired row or an empty dto if the input params did not match any row (check if names are "")
	*/
	dto::sensor_dto* get_sensor_entry(std::string sensor_type_name, std::string individual_name, std::chrono::time_point<std::chrono::system_clock> timestamp);

	//! Returns multiple sensor entries.
	/*!
	* Returns all entries from the sensor table.
	*
	* \return a list of all values in the sensor table.
	*/
	std::vector<dto::sensor_dto*> get_all_sensor_entries();

	//! Returns multiple sensor entries.
	/*!
	* Returns all entries that match the given name.
	*
	* \param sensor_type_name: the type name in the rows to return.
	* \return a list of all values in the sensor table that match the input params.
	*/
	std::vector<dto::sensor_dto*> get_all_sensor_entries(std::string sensor_type_name);

	//! Returns multiple sensor entries.
	/*!
	* Returns all entries that match the given names.
	*
	* \param sensor_type_name: the type name in the rows to return.
	* \param individual_name: the individual name in the rows to return.
	* \return a list of all values in the sensor table that match the input params.
	*/
	std::vector<dto::sensor_dto*> get_all_sensor_entries(std::string sensor_type_name, std::string individual_name);

	//! Returns multiple sensor entries.
	/*!
	* Returns all entries that are older or newer than the given timestamp.
	*
	* \param timestamp: the timestamp threshold.
	* \param older_entries: true to return all values older than the given timestamp, false to return newer values.
	* \return a list of all values in the sensor table that match the input params.
	*/
	std::vector<dto::sensor_dto*> get_all_sensor_entries(std::chrono::time_point<std::chrono::system_clock> timestamp, bool older_entries = false);

	//! Returns multiple sensor entries.
	/*!
	* Returns all entries that are located between both input timestamps.
	*
	* \param start_timestamp: the earliest timestamp to return.
	* \param end_timestamp: the latest timestamp to return.
	* \return a list of all values in the sensor table that match the input params.
	*/
	std::vector<dto::sensor_dto*> get_all_sensor_entries(std::chrono::time_point<std::chrono::system_clock> start_timestamp, std::chrono::time_point<std::chrono::system_clock> end_timestamp);

	//! Returns multiple sensor entries.
	/*!
	* Returns all entries that match the given name and timestamp.
	*
	* \param sensor_type_name: the type name in the rows to return.
	* \param timestamp: the timestamp threshold.
	* \param older_entries: true to return all values older than the given timestamp, false to return newer values.
	* \return a list of all values in the sensor table that match the input params.
	*/
	std::vector<dto::sensor_dto*> get_all_sensor_entries(std::string sensor_type_name, std::chrono::time_point<std::chrono::system_clock> timestamp, bool older_entries = false);

	//! Returns multiple sensor entries.
	/*!
	* Returns all entries that match the given name and are located between both input timestamps.
	*
	* \param sensor_type_name: the type name in the rows to return.
	* \param start_timestamp: the earliest timestamp to return.
	* \param end_timestamp: the latest timestamp to return.
	* \return a list of all values in the sensor table that match the input params.
	*/
	std::vector<dto::sensor_dto*> get_all_sensor_entries(std::string sensor_type_name, std::chrono::time_point<std::chrono::system_clock> start_timestamp, std::chrono::time_point<std::chrono::system_clock> end_timestamp);

	//! Returns multiple sensor entries.
	/*!
	* Returns all entries that match the given names and timestamp.
	*
	* \param sensor_type_name: the type name in the rows to return.
	* \param individual_name: the individual name in the rows to return.
	* \param timestamp: the timestamp threshold.
	* \param older_entries: true to return all values older than the given timestamp, false to return newer values.
	* \return a list of all values in the sensor table that match the input params.
	*/
	std::vector<dto::sensor_dto*> get_all_sensor_entries(std::string sensor_type_name, std::string individual_name, std::chrono::time_point<std::chrono::system_clock> timestamp, bool older_entries = false);

	//! Returns multiple sensor entries.
	/*!
	* Returns all entries that match the given names and are located between both input timestamps.
	*
	* \param sensor_type_name: the type name in the rows to return.
	* \param individual_name: the individual name in the rows to return.
	* \param start_timestamp: the earliest timestamp to return.
	* \param end_timestamp: the latest timestamp to return.
	* \return a list of all values in the sensor table that match the input params.
	*/
	std::vector<dto::sensor_dto*> get_all_sensor_entries(std::string sensor_type_name, std::string individual_name, std::chrono::time_point<std::chrono::system_clock> start_timestamp, std::chrono::time_point<std::chrono::system_clock> end_timestamp);
	
	//! Returns the first entry from the sensor table.
	/*!
	* Returns the first entry from the sensor table.
	*
	* \return the first entry from the sensor table.
	*/
	dto::sensor_dto* get_first_sensor_entry();

	//! Returns the last entry from the sensor table.
	/*!
	* Returns the last entry from the sensor table.
	*
	* \return the last entry from the sensor table.
	*/
	dto::sensor_dto* get_last_sensor_entry();


	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// db_manager_extremas.cpp
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	//! Adds a new extremum to the extremas table.
	/*!
	* Adds a new extremum to the extremas table.
	*
	* \param new_value: a dto containing the values to add to the table.
	*/
	void add_extremum(dto::extremas_dto* new_value);

	//! Deletes a extremum from the extremas table.
	/*!
	* Deletes the extremum with the given names from the extremas table.
	*
	* \param sensor_type_name: the type name in the row to delete.
	* \param individual_name: the individual name in the row to delete.
	*/
	void delete_extremum(std::string sensor_type_name, std::string individual_name);

	//! Returns a single extremum from the extremas table.
	/*!
	* Returns a single extremum that matches the given names.
	*
	* \param sensor_type_name: the type name in the row to return.
	* \param individual_name: the individual name in the row to return.
	*/
	dto::extremas_dto* get_extremum(std::string sensor_type_name, std::string individual_name);

	//! Updates an existing extremum in the extremas table.
	/*!
	* Updates an existing extremum in the extremas table with the given sensor dto object.
	*
	* \param new_value: dto containing the values that should be added to the table.
	*/
	void update_extremum(dto::sensor_dto* new_value);

	//! Updates an existing extremum in the extremas table.
	/*!
	* Updates an existing extremum in the extremas table with the given params.
	*
	* \param sensor_type_name: the type name in the row to update.
	* \param individual_name: the individual name in the row to update.
	* \param count: the new count to add to the row.
	* \param sum: the new sum to add to the row.
	* \param max: the new max to add to the row.
	* \param min: the new min to add to the row.
	*/
	void update_extremum(std::string sensor_type_name, std::string individual_name, double count, double sum, double max, double min);

	//! Recalculates the sum, count, max and min values of one row.
	/*!
	* Recalculates the sum, count, max and min values of one row in the extremas table by getting all
	* sensor values from the sensors table.
	*
	* \param sensor_type_name: the type name in the row to update.
	* \param individual_name: the individual name in the row to update.
	*/
	void recalculate_extremum(std::string sensor_type_name, std::string individual_name);

private:
	dto::sensor_dto* get_single_sensor_query_result(const char* statement);
	std::vector<dto::sensor_dto*> get_multiple_sensor_query_results(const char* statement);

	void handle_error(const char* method, const char* table, const char* statement, const char* error);

	MYSQL* db_connection;

	std::map<std::string, dto::query_object*> tables = {
		{"extremas", new dto::query_object("extremas",
							  "CREATE TABLE IF NOT EXISTS extremas(id INT UNSIGNED AUTO_INCREMENT PRIMARY KEY, sensor_type_name TEXT NOT NULL, individual_name TEXT NOT NULL, count DOUBLE, sum DOUBLE, max DOUBLE, min DOUBLE);",
							  std::vector<dto::column*>{ new dto::column("id", "INT"),
														 new dto::column("sensor_type_name", "TEXT"),
														 new dto::column("individual_name", "TEXT"),
														 new dto::column("count", "DOUBLE"),
														 new dto::column("sum", "DOUBLE"),
														 new dto::column("max", "DOUBLE"),
														 new dto::column("min", "DOUBLE")})},
		{"sensors", new dto::query_object("sensors",
							  "CREATE TABLE IF NOT EXISTS sensors(id INT UNSIGNED AUTO_INCREMENT PRIMARY KEY, sensor_type_name TEXT NOT NULL, individual_name TEXT NOT NULL, timestamp TIMESTAMP DEFAULT CURRENT_TIMESTAMP ON UPDATE CURRENT_TIMESTAMP, value DOUBLE);",
							  std::vector<dto::column*>{ new dto::column("id", "INT"),
														 new dto::column("sensor_type_name", "TEXT"),
														 new dto::column("individual_name", "TEXT"),
														 new dto::column("timestamp", "TIMESTAMP"),
														 new dto::column("value", "DOUBLE")})}

	};
};

