#include "db_manager.h"

int8_t manager::db_manager::add_sensor_entry(std::shared_ptr<dto::sensor_dto> new_value)
{
	if (new_value == nullptr)
	{
		handle_error("add_sensor_entry", tables["sensors"]->get_table_name(), "Input param is NULL", "Null Pointer Exception: Param 'value' is NULL", false);
		return NULL_PTR;
	}

	std::string add_sensors_value = "INSERT INTO " + std::string(tables["sensors"]->get_table_name()) + "(sensor_type_name, individual_name, timestamp, value)"
		+ " values('" + new_value->get_sensor_type_name() + "', "
		+ "'" + new_value->get_individual_name() + "', "
		+ "STR_TO_DATE('" + new_value->get_timestamp_as_string() + "', '" + utils::time_converter::default_time_format + "'), "
		+ std::to_string(new_value->get_value()) + ");";

	if (mysql_query(db_connection, add_sensors_value.c_str()) != 0)
	{
		handle_error("add_sensor_entry", tables["sensors"]->get_table_name(), add_sensors_value.c_str(), mysql_error(db_connection), false);
		return QUERY_ERROR;
	}

	return TRUE;
}

int8_t manager::db_manager::delete_sensor_entry(std::shared_ptr<dto::sensor_dto> value)
{
	if (value == nullptr)
	{
		handle_error("delete_sensor_entry", tables["sensors"]->get_table_name(), "Input param is NULL", "Null Pointer Exception: Param 'value' is NULL");
		return NULL_PTR;
	}

	std::string statement = "DELETE FROM " + std::string(tables["sensors"]->get_table_name()) +
		" WHERE sensor_type_name='" + value->get_sensor_type_name() + "' AND individual_name='" + value->get_individual_name() +
		"' AND timestamp = STR_TO_DATE('" + value->get_timestamp_as_string() + "', '" + utils::time_converter::default_time_format + "');";

	if (mysql_query(db_connection, statement.c_str()) != 0)
	{
		handle_error("delete_sensor_entry [by dto]", tables["sensors"]->get_table_name(), statement.c_str(), mysql_error(db_connection));
		return QUERY_ERROR;
	}

	return TRUE;
}

int8_t manager::db_manager::delete_sensor_entry(std::string sensor_type_name, std::string individual_name, std::chrono::time_point<std::chrono::system_clock> timestamp)
{
	std::string statement = "DELETE FROM " + std::string(tables["sensors"]->get_table_name()) +
		" WHERE sensor_type_name='" + sensor_type_name + "' AND individual_name='" + individual_name +
		"' AND timestamp = STR_TO_DATE('" + utils::time_converter::timepoint_to_string(timestamp) + "', '" + utils::time_converter::default_time_format + "');";

	if (mysql_query(db_connection, statement.c_str()) != 0)
	{
		handle_error("delete_sensor_entry [by type, name and timestamp]", tables["sensors"]->get_table_name(), statement.c_str(), mysql_error(db_connection));
		return QUERY_ERROR;
	}

	return TRUE;
}

int8_t manager::db_manager::delete_sensor_entries(std::string sensor_type_name, std::string individual_name)
{
	std::string statement = "DELETE FROM " + std::string(tables["sensors"]->get_table_name()) +
		" WHERE sensor_type_name='" + sensor_type_name + "' AND individual_name='" + individual_name + "';";

	if (mysql_query(db_connection, statement.c_str()) != 0)
	{
		handle_error("delete_sensor_entries [by type and name]", tables["sensors"]->get_table_name(), statement.c_str(), mysql_error(db_connection));
		return QUERY_ERROR;
	}

	return TRUE;
}

int8_t manager::db_manager::delete_sensor_entries(std::string sensor_type_name, std::string individual_name, std::chrono::time_point<std::chrono::system_clock> timestamp, bool delete_older)
{
	std::string statement = "DELETE FROM " + std::string(tables["sensors"]->get_table_name()) +
		" WHERE sensor_type_name='" + sensor_type_name + "' AND individual_name='" + individual_name +
		"' AND timestamp " + (delete_older ? "<" : ">") + " STR_TO_DATE('" + utils::time_converter::timepoint_to_string(timestamp) + "', '" + utils::time_converter::default_time_format + "');";

	if (mysql_query(db_connection, statement.c_str()) != 0)
	{
		handle_error("delete_sensor_entries [by type, name and timestamp threshold]", tables["sensors"]->get_table_name(), statement.c_str(), mysql_error(db_connection));
		return QUERY_ERROR;
	}

	return TRUE;
}

int8_t manager::db_manager::update_entry(std::string sensor_type_name, std::string individual_name, std::string column, std::string old_value, std::string new_value)
{
	std::string statement = "UPDATE " + std::string(tables["sensors"]->get_table_name()) + " SET " + column + "='" + new_value + "'" +
		" WHERE sensor_type_name='" + sensor_type_name + "' AND individual_name='" + individual_name + "' AND " + column + "='" + old_value + "';";
	if (mysql_query(db_connection, statement.c_str()) != 0)
	{
		handle_error("update_entry [string]", tables["sensors"]->get_table_name(), statement.c_str(), mysql_error(db_connection));
		return QUERY_ERROR;
	}

	return TRUE;
}

int8_t manager::db_manager::update_entry(std::string sensor_type_name, std::string individual_name, std::string column, int old_value, int new_value)
{
	std::string statement = "UPDATE " + std::string(tables["sensors"]->get_table_name()) + " SET " + column + "=" + std::to_string(new_value) + "" +
		" WHERE sensor_type_name='" + sensor_type_name + "' AND individual_name='" + individual_name + "' AND " + column + "='" + std::to_string(old_value) + "';";
	if (mysql_query(db_connection, statement.c_str()) != 0)
	{
		handle_error("update_entry [int]", tables["sensors"]->get_table_name(), statement.c_str(), mysql_error(db_connection));
		return QUERY_ERROR;
	}

	return TRUE;
}

int8_t manager::db_manager::update_entry(std::string sensor_type_name, std::string individual_name, std::string column, float old_value, float new_value)
{
	std::string statement = "UPDATE " + std::string(tables["sensors"]->get_table_name()) + " SET " + column + "=" + std::to_string(new_value) + "" +
		" WHERE sensor_type_name='" + sensor_type_name + "' AND individual_name='" + individual_name + "' AND " + column + "='" + std::to_string(old_value) + "';";
	if (mysql_query(db_connection, statement.c_str()) != 0)
	{
		handle_error("update_entry [float]", tables["sensors"]->get_table_name(), statement.c_str(), mysql_error(db_connection));
		return QUERY_ERROR;
	}

	return TRUE;
}

int8_t manager::db_manager::update_entry(std::string sensor_type_name, std::string individual_name, std::string column, double old_value, double new_value)
{
	std::string statement = "UPDATE " + std::string(tables["sensors"]->get_table_name()) + " SET " + column + "=" + std::to_string(new_value) + "" +
		" WHERE sensor_type_name='" + sensor_type_name + "' AND individual_name='" + individual_name + "' AND " + column + "='" + std::to_string(old_value) + "';";
	if (mysql_query(db_connection, statement.c_str()) != 0)
	{
		handle_error("update_entry [double]", tables["sensors"]->get_table_name(), statement.c_str(), mysql_error(db_connection));
		return QUERY_ERROR;
	}

	return TRUE;
}

int8_t manager::db_manager::update_entry(std::string sensor_type_name, std::string individual_name, std::string column, bool old_value, bool new_value)
{
	std::string statement = "UPDATE " + std::string(tables["sensors"]->get_table_name()) + " SET " + column + "=" + (new_value ? "TRUE" : "FALSE") + "" +
		" WHERE sensor_type_name='" + sensor_type_name + "' AND individual_name='" + individual_name + "' AND " + column + "='" + (old_value ? "TRUE" : "FALSE") + "';";
	if (mysql_query(db_connection, statement.c_str()) != 0)
	{
		handle_error("update_entry [bool]", tables["sensors"]->get_table_name(), statement.c_str(), mysql_error(db_connection));
		return QUERY_ERROR;
	}

	return TRUE;
}

int8_t manager::db_manager::get_sensor_entry(std::shared_ptr<dto::sensor_dto>& result, std::shared_ptr<dto::sensor_dto> value)
{
	if (value == nullptr)
	{
		handle_error("get_sensor_entry", tables["sensors"]->get_table_name(), "Input param is NULL", "Null Pointer Exception: Param 'value' is NULL");
		return NULL_PTR;
	}

	std::string statement = "SELECT * FROM " + std::string(tables["sensors"]->get_table_name()) +
		" WHERE sensor_type_name='" + value->get_sensor_type_name() + "' AND individual_name='" + value->get_individual_name() +
		"' AND timestamp=STR_TO_DATE('" + value->get_timestamp_as_string() + "', '" + utils::time_converter::default_time_format + "');";

	return get_single_sensor_query_result(result, statement);
}

int8_t manager::db_manager::get_sensor_entry(std::shared_ptr<dto::sensor_dto>& result, std::string sensor_type_name, std::string individual_name, std::chrono::time_point<std::chrono::system_clock> timestamp)
{
	std::string statement = "SELECT * FROM " + std::string(tables["sensors"]->get_table_name()) +
		" WHERE sensor_type_name='" + sensor_type_name + "' AND individual_name='" + individual_name +
		"' AND timestamp=STR_TO_DATE('" + utils::time_converter::timepoint_to_string(timestamp) + "', '" + utils::time_converter::default_time_format + "');";

	return get_single_sensor_query_result(result, statement);
}

int8_t manager::db_manager::get_all_sensor_entries(std::vector<std::shared_ptr<dto::sensor_dto>>& result)
{
	std::string statement = "SELECT * FROM " + std::string(tables["sensors"]->get_table_name());

	return get_multiple_sensor_query_results(result, statement);
}

int8_t manager::db_manager::get_all_sensor_entries(std::vector<std::shared_ptr<dto::sensor_dto>>& result, std::string sensor_type_name)
{
	std::string statement = "SELECT * FROM " + std::string(tables["sensors"]->get_table_name()) +
		" WHERE sensor_type_name='" + sensor_type_name + "';";

	return get_multiple_sensor_query_results(result, statement);
}

int8_t manager::db_manager::get_all_sensor_entries(std::vector<std::shared_ptr<dto::sensor_dto>>& result, std::string sensor_type_name, std::string individual_name)
{
	std::string statement = "SELECT * FROM " + std::string(tables["sensors"]->get_table_name()) +
		" WHERE sensor_type_name='" + sensor_type_name + "' AND individual_name='" + individual_name + "';";

	return get_multiple_sensor_query_results(result, statement);
}

int8_t manager::db_manager::get_all_sensor_entries(std::vector<std::shared_ptr<dto::sensor_dto>>& result, std::chrono::time_point<std::chrono::system_clock> timestamp, bool older_entries)
{
	std::string statement = "SELECT * FROM " + std::string(tables["sensors"]->get_table_name()) +
		" WHERE timestamp" + (older_entries ? "<" : ">") + "STR_TO_DATE('" + utils::time_converter::timepoint_to_string(timestamp) + "', '" + utils::time_converter::default_time_format + "');";

	return get_multiple_sensor_query_results(result, statement);
}

int8_t manager::db_manager::get_all_sensor_entries(std::vector<std::shared_ptr<dto::sensor_dto>>& result, std::chrono::time_point<std::chrono::system_clock> start_timestamp, std::chrono::time_point<std::chrono::system_clock> end_timestamp)
{
	std::string statement = "SELECT * FROM " + std::string(tables["sensors"]->get_table_name()) +
		" WHERE timestamp >= STR_TO_DATE('" + utils::time_converter::timepoint_to_string(start_timestamp) + "', '" + utils::time_converter::default_time_format + "') " +
		" AND timestamp <= STR_TO_DATE('" + utils::time_converter::timepoint_to_string(end_timestamp) + "', '" + utils::time_converter::default_time_format + "');";

	return get_multiple_sensor_query_results(result, statement);
}

int8_t manager::db_manager::get_all_sensor_entries(std::vector<std::shared_ptr<dto::sensor_dto>>& result, std::string sensor_type_name, std::chrono::time_point<std::chrono::system_clock> timestamp, bool older_entries)
{
	std::string statement = "SELECT * FROM " + std::string(tables["sensors"]->get_table_name()) +
		" WHERE sensor_type_name='" + sensor_type_name +
		"' AND timestamp" + (older_entries ? "<" : ">") + "STR_TO_DATE('" + utils::time_converter::timepoint_to_string(timestamp) + "', '" + utils::time_converter::default_time_format + "');";

	return get_multiple_sensor_query_results(result, statement);
}

int8_t manager::db_manager::get_all_sensor_entries(std::vector<std::shared_ptr<dto::sensor_dto>>& result, std::string sensor_type_name, std::chrono::time_point<std::chrono::system_clock> start_timestamp, std::chrono::time_point<std::chrono::system_clock> end_timestamp)
{
	std::string statement = "SELECT * FROM " + std::string(tables["sensors"]->get_table_name()) +
		" WHERE sensor_type_name='" + sensor_type_name +
		"' AND  timestamp >= STR_TO_DATE('" + utils::time_converter::timepoint_to_string(start_timestamp) + "', '" + utils::time_converter::default_time_format + "') " +
		" AND timestamp <= STR_TO_DATE('" + utils::time_converter::timepoint_to_string(end_timestamp) + "', '" + utils::time_converter::default_time_format + "');";

	return get_multiple_sensor_query_results(result, statement);
}

int8_t manager::db_manager::get_all_sensor_entries(std::vector<std::shared_ptr<dto::sensor_dto>>& result, std::string sensor_type_name, std::string individual_name, std::chrono::time_point<std::chrono::system_clock> timestamp, bool older_entries)
{
	std::string statement = "SELECT * FROM " + std::string(tables["sensors"]->get_table_name()) +
		" WHERE sensor_type_name='" + sensor_type_name +
		"' AND individual_name = '" + individual_name +
		"' AND timestamp" + (older_entries ? "<" : ">") + "STR_TO_DATE('" + utils::time_converter::timepoint_to_string(timestamp) + "', '" + utils::time_converter::default_time_format + "');";

	return get_multiple_sensor_query_results(result, statement);
}

int8_t manager::db_manager::get_all_sensor_entries(std::vector<std::shared_ptr<dto::sensor_dto>>& result, std::string sensor_type_name, std::string individual_name, std::chrono::time_point<std::chrono::system_clock> start_timestamp, std::chrono::time_point<std::chrono::system_clock> end_timestamp)
{
	std::string statement = "SELECT * FROM " + std::string(tables["sensors"]->get_table_name()) +
		" WHERE sensor_type_name='" + sensor_type_name +
		"' AND individual_name = '" + individual_name +
		"' AND  timestamp >= STR_TO_DATE('" + utils::time_converter::timepoint_to_string(start_timestamp) + "', '" + utils::time_converter::default_time_format + "') " +
		" AND timestamp <= STR_TO_DATE('" + utils::time_converter::timepoint_to_string(end_timestamp) + "', '" + utils::time_converter::default_time_format + "');";

	return get_multiple_sensor_query_results(result, statement);
}

int8_t manager::db_manager::get_first_sensor_entry(std::shared_ptr<dto::sensor_dto>& result)
{
	std::string statement = "SELECT * FROM " + std::string(tables["sensors"]->get_table_name()) +
		" LIMIT 1;";

	return get_single_sensor_query_result(result, statement);
}

int8_t manager::db_manager::get_last_sensor_entry(std::shared_ptr<dto::sensor_dto>& result)
{
	std::string statement = "SELECT * FROM " + std::string(tables["sensors"]->get_table_name()) +
		" ORDER BY ID DESC LIMIT 1;";

	return get_single_sensor_query_result(result, statement);
}

int8_t manager::db_manager::get_single_sensor_query_result(std::shared_ptr<dto::sensor_dto>& result, const std::string statement)
{
	if (mysql_query(db_connection, statement.c_str()) != 0)
	{
		handle_error("get_single_sensor_query_result", tables["sensors"]->get_table_name(), statement, mysql_error(db_connection));
		return QUERY_ERROR;
	}

	MYSQL_RES* res = mysql_use_result(db_connection);
	MYSQL_ROW row = mysql_fetch_row(res);
	result = std::make_shared<dto::sensor_dto>();
	// row[0] = id
	if (row != NULL)
	{
		result->set_sensor_type_name(row[1]);
		result->set_individual_name(row[2]);
		result->set_timestamp(row[3]);
		result->set_value(atof(row[4]));
	}

	mysql_free_result(res);
	return TRUE;
}

int8_t manager::db_manager::get_multiple_sensor_query_results(std::vector<std::shared_ptr<dto::sensor_dto>>& result, const std::string statement)
{
	if (mysql_query(db_connection, statement.c_str()) != 0)
	{
		handle_error("get_multiple_sensor_query_results", tables["sensors"]->get_table_name(), statement, mysql_error(db_connection));
		return QUERY_ERROR;
	}

	MYSQL_RES* res = mysql_use_result(db_connection);
	MYSQL_ROW row;

	if (res)
	{
		while ((row = mysql_fetch_row(res)))
		{
			// row[0] = id
			result.push_back(std::make_shared<dto::sensor_dto>(dto::sensor_dto(row[1], row[2], row[2], utils::time_converter::default_time_format, atof(row[3]))));
		}
	}

	mysql_free_result(res);
	return TRUE;
}