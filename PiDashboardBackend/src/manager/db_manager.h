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
#include <iostream>
#include <memory>

namespace manager
{
	static constexpr const int8_t TRUE = 1;
	static constexpr const int8_t FALSE = 0;
	static constexpr const int8_t NULL_PTR = -2;
	static constexpr const int8_t QUERY_ERROR = -1;

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
		* Closes database connection in case of an error and throws an exception.
		*
		* \param host[in]: ip (or localhost) of the pc where the database is located.
		* \param user[in]: the database user to use for all operations (needs select, insert, update, delete, create, drop rights).
		* \param password[in]: the password of the user account.
		* \param database[in]: the name of the database where all tables are located in.
		*/
		db_manager(const std::string host, const std::string user, const std::string password, const std::string database);

		//! Default destructor.
		~db_manager();

		//! Creates a new table.
		/*!
		* Creates a new table by executing the given create table statement. Closes database connection in case of an error
		* and throws an exception.
		*
		* \param statement[in]: the create table statement that is used to create the new table.
		*/
		void create_table(std::string statement);

		//! Creates a new table.
		/*!
		* Creates a new table by building a create table statement from the given parameters. Closes database connection in case of an error
		* and throws an exception.
		*
		* \param table[in]: the name of the new table.
		* \param column_definitions[in]: a list of column definitions (name + data type + special settings (e.g. autoincrement, primary key, ...)).
		*/
		void create_table(std::string table, std::vector<std::string> column_definitions);

		//! Creates a new database.
		/*!
		* Creates a new database with the given name. Closes database connection in case of an error
		* and throws an exception.
		*
		* \param database[in]: the name of the new database.
		*/
		void create_database(std::string database);

		//! Calls the use statement on the given database.
		/*!
		* Calls the use statement on the given database. Closes database connection in case of an error
		* and throws an exception.
		*
		* \param database[in]: the name of the database to use.
		*/
		void use_database(std::string database);

		//! Deletes a table.
		/*!
		* Deletes the table with the given name. Does not close database connection in case of an error.
		*
		* \param table[in]: the name of the table to delete.
		* \return 1 (true) is deleting succeeded, -2 (query error) if an error occured.
		*/
		int8_t delete_table(std::string table);

		//! Deletes a database.
		/*!
		* Deletes the database with the given name. Does not close database connection in case of an error.
		*
		* \param database[in]: the name of the database to delete.
		* \return 1 (true) is deleting succeeded, -2 (query error) if an error occured.
		*/
		int8_t delete_database(std::string database);

		//! Checks if a table exists.
		/*!
		* Checks if the table with the given name exists inside the given database.
		* Does not close database connection in case of an error.
		*
		* \param database[in]: the name of the database in which the table should be found.
		* \param table[in]: the name of the table to lookup.
		* \return 1 (true) if the table exists, 0 if it doesn't and -2 (query error) if an error occured.
		*/
		int8_t check_if_table_exists(std::string database, std::string table);

		//! Checks if a database exists.
		/*!
		* Checks if the database with the given name exists. Does not close database connection
		* in case of an error.
		*
		* \param database[in]: the name of the database to lookup.
		* \return 1 (true) if the table exists, 0 if it doesn't and -2 (query error) if an error occured.
		*/
		int8_t check_if_database_exists(std::string database);


		//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		// db_manager_sensors.cpp
		//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

		//! Adds a new entry to the sensor database.
		/*!
		* Adds a new entry to the sensor database. Does not close database connection in case of an error.
		*
		* \param new_value[in]: a dto object with the values to add.
		* \return 1 (true) if adding the entry succeeded and -1 (null ptr error) or -2 (query error) if an error occured.
		*/
		int8_t add_sensor_entry(std::shared_ptr<dto::sensor_dto> new_value);

		//! Deletes a entry from the sensor database.
		/*!
		* Deletes the entry the given dto represents from the sensor database. Does not close database connection in case of an error.
		*
		* \param value[in]: the entry to delete.
		* \return 1 (true) if removing the entry succeeded and -1 (null ptr error) or -2 (query error) if an error occured.
		*/
		int8_t delete_sensor_entry(std::shared_ptr<dto::sensor_dto> value);

		//! Deletes a entry from the sensor database.
		/*!
		* Deletes the entry that matches the given names and timestamp from the sensor database.
		* Does not close database connection in case of an error.
		*
		* \param sensor_type_name[in]: the type name in the row to delete.
		* \param individual_name[in]: the individual name in the row to delete.
		* \param timestamp[in]: the timestamp name in the row to delete.
		* \return 1 (true) if removing the entry succeeded and -2 (query error) if an error occured.
		*/
		int8_t delete_sensor_entry(std::string sensor_type_name, std::string individual_name, std::chrono::time_point<std::chrono::system_clock> timestamp);

		//! Deletes multiple entries from the sensor database.
		/*!
		* Deletes all entries that match the given names from the sensor database. Does not close database connection in case of an error.
		*
		* \param sensor_type_name[in]: the type name in the rows to delete.
		* \param individual_name[in]: the individual name in the rows to delete.
		* \return 1 (true) if removing the entry succeeded and -2 (query error) if an error occured.
		*/
		int8_t delete_sensor_entries(std::string sensor_type_name, std::string individual_name);

		//! Deletes multiple entries from the sensor database.
		/*!
		* Deletes all entries that match the given names from the sensor database. Does not close database connection in case of an error.
		*
		* \param sensor_type_name[in]: the type name in the rows to delete.
		* \param individual_name[in]: the individual name in the rows to delete.
		* \param timestamp[in]: the timestamp threshold.
		* \param delete_older[in]: true to delete values older than timestamp, false to delete newer ones.
		* \return 1 (true) if removing the entry succeeded and -2 (query error) if an error occured.
		*/
		int8_t delete_sensor_entries(std::string sensor_type_name, std::string individual_name, std::chrono::time_point<std::chrono::system_clock> timestamp, bool delete_older = true);

		//! Updates an entry.
		/*!
		* Updates an entry that matches the given names and value. Does not close database connection in case of an error.
		*
		* \param sensor_type_name[in]: the type name in the row to update.
		* \param individual_name[in]: the individual name in the rows to update.
		* \param column[in]: the name of the column to update.
		* \param old_value[in]: the current value that should be replaced by the new one.
		* \param new_value[in]: the new value to insert into the row.
		* \return 1 (true) if updating the entry succeeded and -2 (query error) if an error occured.
		*/
		int8_t update_entry(std::string sensor_type_name, std::string individual_name, std::string column, std::string old_value, std::string new_value);

		//! Updates an entry.
		/*!
		* Updates an entry that matches the given names and value. Does not close database connection in case of an error.
		*
		* \param sensor_type_name[in]: the type name in the row to update.
		* \param individual_name[in]: the individual name in the rows to update.
		* \param column[in]: the name of the column to update.
		* \param old_value[in]: the current value that should be replaced by the new one.
		* \param new_value[in]: the new value to insert into the row.
		* \return 1 (true) if updating the entry succeeded and -2 (query error) if an error occured.
		*/
		int8_t update_entry(std::string sensor_type_name, std::string individual_name, std::string column, int old_value, int new_value);

		//! Updates an entry.
		/*!
		* Updates an entry that matches the given names and value. Does not close database connection in case of an error.
		*
		* \param sensor_type_name[in]: the type name in the row to update.
		* \param individual_name[in]: the individual name in the rows to update.
		* \param column[in]: the name of the column to update.
		* \param old_value[in]: the current value that should be replaced by the new one.
		* \param new_value[in]: the new value to insert into the row.
		* \return 1 (true) if updating the entry succeeded and -2 (query error) if an error occured.
		*/
		int8_t update_entry(std::string sensor_type_name, std::string individual_name, std::string column, float old_value, float new_value);

		//! Updates an entry.
		/*!
		* Updates an entry that matches the given names and value. Does not close database connection in case of an error.
		*
		* \param sensor_type_name[in]: the type name in the row to update.
		* \param individual_name[in]: the individual name in the rows to update.
		* \param column[in]: the name of the column to update.
		* \param old_value[in]: the current value that should be replaced by the new one.
		* \param new_value[in]: the new value to insert into the row.
		* \return 1 (true) if updating the entry succeeded and -2 (query error) if an error occured.
		*/
		int8_t update_entry(std::string sensor_type_name, std::string individual_name, std::string column, double old_value, double new_value);

		//! Updates an entry.
		/*!
		* Updates an entry that matches the given names and value. Does not close database connection in case of an error.
		*
		* \param sensor_type_name[in]: the type name in the row to update.
		* \param individual_name[in]: the individual name in the rows to update.
		* \param column[in]: the name of the column to update.
		* \param old_value[in]: the current value that should be replaced by the new one.
		* \param new_value[in]: the new value to insert into the row.
		* \return 1 (true) if updating the entry succeeded and -2 (query error) if an error occured.
		*/
		int8_t update_entry(std::string sensor_type_name, std::string individual_name, std::string column, bool old_value, bool new_value);

		//! Returns a single sensor entry.
		/*!
		* Returns the sensor entry that matches the names and timestamp in the given dto. Does not close database connection in case of an error.
		*
		* \param result[out]: the desired row or an empty dto if the input param did not match any row (check if names are "")
		* \param value[in]: the dto used to find the desired sensor row.
		* \return 1 (true) if getting the entry succeeded and -1 (null ptr error) or -2 (query error) if an error occured.
		*/
		int8_t get_sensor_entry(std::shared_ptr<dto::sensor_dto>& result, std::shared_ptr<dto::sensor_dto> value);

		//! Returns a single sensor entry.
		/*!
		* Returns the sensor entry that matches the given names and timestamp. Does not close database connection in case of an error.
		*
		* \param result[out]: the desired row or an empty dto if the input params did not match any row (check if names are "")
		* \param sensor_type_name[in]: the type name in the row to return.
		* \param individual_name[in]: the individual name in the rows to return.
		* \param timestamp[in]: the timestamp in the rows to return.
		* \return 1 (true) if getting the entry succeeded and -2 (query error) if an error occured.
		*/
		int8_t get_sensor_entry(std::shared_ptr<dto::sensor_dto>& result, std::string sensor_type_name, std::string individual_name, std::chrono::time_point<std::chrono::system_clock> timestamp);

		//! Returns multiple sensor entries.
		/*!
		* Returns all entries from the sensor table. Does not close database connection in case of an error.
		*
		* \param result[out]: a list of all values in the sensor table.
		* \return 1 (true) if getting the entries succeeded and -2 (query error) if an error occured.
		*/
		int8_t get_all_sensor_entries(std::vector<std::shared_ptr<dto::sensor_dto>>& result);

		//! Returns multiple sensor entries.
		/*!
		* Returns all entries that match the given name. Does not close database connection in case of an error.
		*
		* \param result[out]: a list of all values in the sensor table that match the input params.
		* \param sensor_type_name[in]: the type name in the rows to return.
		* \return 1 (true) if getting the entries succeeded and -2 (query error) if an error occured.
		*/
		int8_t get_all_sensor_entries(std::vector<std::shared_ptr<dto::sensor_dto>>& result, std::string sensor_type_name);

		//! Returns multiple sensor entries.
		/*!
		* Returns all entries that match the given names. Does not close database connection in case of an error.
		*
		* \param result[out]: a list of all values in the sensor table that match the input params.
		* \param sensor_type_name[in]: the type name in the rows to return.
		* \param individual_name[in]: the individual name in the rows to return.
		* \return 1 (true) if getting the entries succeeded and -2 (query error) if an error occured.
		*/
		int8_t get_all_sensor_entries(std::vector<std::shared_ptr<dto::sensor_dto>>& result, std::string sensor_type_name, std::string individual_name);

		//! Returns multiple sensor entries.
		/*!
		* Returns all entries that are older or newer than the given timestamp. Does not close database connection in case of an error.
		*
		* \param result[out]: a list of all values in the sensor table that match the input params.
		* \param timestamp[in]: the timestamp threshold.
		* \param older_entries[in]: true to return all values older than the given timestamp, false to return newer values.
		* \return 1 (true) if getting the entries succeeded and -2 (query error) if an error occured.
		*/
		int8_t get_all_sensor_entries(std::vector<std::shared_ptr<dto::sensor_dto>>& result, std::chrono::time_point<std::chrono::system_clock> timestamp, bool older_entries = false);

		//! Returns multiple sensor entries.
		/*!
		* Returns all entries that are located between both input timestamps. Does not close database connection in case of an error.
		*
		* \param result[out]: a list of all values in the sensor table that match the input params.
		* \param start_timestamp[in]: the earliest timestamp to return.
		* \param end_timestamp[in]: the latest timestamp to return.
		* \return 1 (true) if getting the entries succeeded and -2 (query error) if an error occured.
		*/
		int8_t get_all_sensor_entries(std::vector<std::shared_ptr<dto::sensor_dto>>& result, std::chrono::time_point<std::chrono::system_clock> start_timestamp, std::chrono::time_point<std::chrono::system_clock> end_timestamp);

		//! Returns multiple sensor entries.
		/*!
		* Returns all entries that match the given name and timestamp. Does not close database connection in case of an error.
		*
		* \param result[out]: a list of all values in the sensor table that match the input params.
		* \param sensor_type_name[in]: the type name in the rows to return.
		* \param timestamp[in]: the timestamp threshold.
		* \param older_entries[in]: true to return all values older than the given timestamp, false to return newer values.
		* \return 1 (true) if getting the entries succeeded and -2 (query error) if an error occured.
		*/
		int8_t get_all_sensor_entries(std::vector<std::shared_ptr<dto::sensor_dto>>& result, std::string sensor_type_name, std::chrono::time_point<std::chrono::system_clock> timestamp, bool older_entries = false);

		//! Returns multiple sensor entries.
		/*!
		* Returns all entries that match the given name and are located between both input timestamps. Does not close database 
		* connection in case of an error.
		*
		* \param result[out]: a list of all values in the sensor table that match the input params.
		* \param sensor_type_name[in]: the type name in the rows to return.
		* \param start_timestamp[in]: the earliest timestamp to return.
		* \param end_timestamp[in]: the latest timestamp to return.
		* \return 1 (true) if getting the entries succeeded and -2 (query error) if an error occured.
		*/
		int8_t get_all_sensor_entries(std::vector<std::shared_ptr<dto::sensor_dto>>& result, std::string sensor_type_name, std::chrono::time_point<std::chrono::system_clock> start_timestamp, std::chrono::time_point<std::chrono::system_clock> end_timestamp);

		//! Returns multiple sensor entries.
		/*!
		* Returns all entries that match the given names and timestamp. Does not close database connection in case of an error.
		*
		* \param result[out]: a list of all values in the sensor table that match the input params.
		* \param sensor_type_name[in]: the type name in the rows to return.
		* \param individual_name[in]: the individual name in the rows to return.
		* \param timestamp[in]: the timestamp threshold.
		* \param older_entries[in]: true to return all values older than the given timestamp, false to return newer values.
		* \return 1 (true) if getting the entries succeeded and -2 (query error) if an error occured.
		*/
		int8_t get_all_sensor_entries(std::vector<std::shared_ptr<dto::sensor_dto>>& result, std::string sensor_type_name, std::string individual_name, std::chrono::time_point<std::chrono::system_clock> timestamp, bool older_entries = false);

		//! Returns multiple sensor entries.
		/*!
		* Returns all entries that match the given names and are located between both input timestamps. Does not close database 
		* connection in case of an error.
		*
		* \param result[out]: a list of all values in the sensor table that match the input params.
		* \param sensor_type_name[in]: the type name in the rows to return.
		* \param individual_name[in]: the individual name in the rows to return.
		* \param start_timestamp[in]: the earliest timestamp to return.
		* \param end_timestamp[in]: the latest timestamp to return.
		* \return 1 (true) if getting the entries succeeded and -2 (query error) if an error occured.
		*/
		int8_t get_all_sensor_entries(std::vector<std::shared_ptr<dto::sensor_dto>>& result, std::string sensor_type_name, std::string individual_name, std::chrono::time_point<std::chrono::system_clock> start_timestamp, std::chrono::time_point<std::chrono::system_clock> end_timestamp);

		//! Returns the first entry from the sensor table.
		/*!
		* Returns the first entry from the sensor table. Does not close database connection in case of an error.
		*
		* \param result[out]: the first entry from the sensor table.
		* \return 1 (true) if getting the entry succeeded and -2 (query error) if an error occured.
		*/
		int8_t get_first_sensor_entry(std::shared_ptr<dto::sensor_dto>& result);

		//! Returns the last entry from the sensor table.
		/*!
		* Returns the last entry from the sensor table. Does not close database connection in case of an error.
		*
		* \param result[out] the last entry from the sensor table.
		* \return 1 (true) if getting the entry succeeded and -2 (query error) if an error occured.
		*/
		int8_t get_last_sensor_entry(std::shared_ptr<dto::sensor_dto>& result);


		//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		// db_manager_extremas.cpp
		//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

		//! Adds a new extremum to the extremas table.
		/*!
		* Adds a new extremum to the extremas table. Does not close database connection in case of an error.
		*
		* \param new_value[in]: a dto containing the values to add to the table.
		* \return 1 (true) if adding the entry succeeded and -1 (null ptr error) or -2 (query error) if an error occured.
		*/
		int8_t add_extremum(std::shared_ptr<dto::extremas_dto> new_value);

		//! Deletes a extremum from the extremas table.
		/*!
		* Deletes the extremum with the given names from the extremas table. Does not close database connection in case of an error.
		*
		* \param sensor_type_name[in]: the type name in the row to delete.
		* \param individual_name[in]: the individual name in the row to delete.
		* \return 1 (true) if deleting the entry succeeded and -2 (query error) if an error occured.
		*/
		int8_t delete_extremum(std::string sensor_type_name, std::string individual_name);

		//! Returns a single extremum from the extremas table.
		/*!
		* Returns a single extremum that matches the given names. Does not close database connection in case of an error.
		*
		* \param result[out] the entry from the table.
		* \param sensor_type_name[in]: the type name in the row to return.
		* \param individual_name[in]: the individual name in the row to return.
		* \return 1 (true) if getting the entry succeeded and -2 (query error) if an error occured.
		*/
		int8_t get_extremum(std::shared_ptr<dto::extremas_dto>& result, std::string sensor_type_name, std::string individual_name);

		//! Updates an existing extremum in the extremas table.
		/*!
		* Updates an existing extremum in the extremas table with the given sensor dto object. Does not close database 
		* connection in case of an error.
		*
		* \param new_value[in]: dto containing the values that should be added to the table.
		* \return 1 (true) if updating the entry succeeded and -1 (null ptr error) or -2 (query error) if an error occured.
		*/
		int8_t update_extremum(std::shared_ptr<dto::sensor_dto> new_value);

		//! Updates an existing extremum in the extremas table.
		/*!
		* Updates an existing extremum in the extremas table with the given params. Does not close database connection in 
		* case of an error.
		*
		* \param sensor_type_name[in]: the type name in the row to update.
		* \param individual_name[in]: the individual name in the row to update.
		* \param count[in]: the new count to add to the row.
		* \param sum[in]: the new sum to add to the row.
		* \param max[in]: the new max to add to the row.
		* \param min[in]: the new min to add to the row.
		* \return 1 (true) if updating the entry succeeded and -2 (query error) if an error occured.
		*/
		int8_t update_extremum(std::string sensor_type_name, std::string individual_name, double count, double sum, double max, double min);

		//! Recalculates the sum, count, max and min values of one row.
		/*!
		* Recalculates the sum, count, max and min values of one row in the extremas table by getting all
		* sensor values from the sensors table. Does not close database connection in case of an error.
		*
		* \param sensor_type_name[in]: the type name in the row to update.
		* \param individual_name[in]: the individual name in the row to update.
		* \return 1 (true) if recalculating the entry succeeded, 0 (false) if no sensor values are available and -2 (query error) if an error occured.
		*/
		int8_t recalculate_extremum(std::string sensor_type_name, std::string individual_name);

	private:
		int8_t get_single_sensor_query_result(std::shared_ptr<dto::sensor_dto>& result, const std::string statement);
		int8_t get_multiple_sensor_query_results(std::vector<std::shared_ptr<dto::sensor_dto>>& result, const std::string statement);

		void handle_error(const std::string method, const std::string table, const std::string statement, const std::string error, bool close = false);

		MYSQL* db_connection;

		std::map<std::string, dto::query_object*> tables = {
			{"extremas", new dto::query_object("extremas",
								  std::vector<dto::column*>{ new dto::column("id", "INT"),
															 new dto::column("sensor_type_name", "TEXT"),
															 new dto::column("individual_name", "TEXT"),
															 new dto::column("count", "DOUBLE"),
															 new dto::column("sum", "DOUBLE"),
															 new dto::column("max", "DOUBLE"),
															 new dto::column("min", "DOUBLE")},
								  "CREATE TABLE IF NOT EXISTS extremas(id INT UNSIGNED AUTO_INCREMENT PRIMARY KEY, sensor_type_name TEXT NOT NULL, individual_name TEXT NOT NULL, count DOUBLE, sum DOUBLE, max DOUBLE, min DOUBLE);")
			},
			{"sensors", new dto::query_object("sensors",
								  std::vector<dto::column*>{ new dto::column("id", "INT"),
															 new dto::column("sensor_type_name", "TEXT"),
															 new dto::column("individual_name", "TEXT"),
															 new dto::column("timestamp", "TIMESTAMP"),
															 new dto::column("value", "DOUBLE")},
								  "CREATE TABLE IF NOT EXISTS sensors(id INT UNSIGNED AUTO_INCREMENT PRIMARY KEY, sensor_type_name TEXT NOT NULL, individual_name TEXT NOT NULL, timestamp TIMESTAMP DEFAULT CURRENT_TIMESTAMP ON UPDATE CURRENT_TIMESTAMP, value DOUBLE);")
			}
		};
	};
}
