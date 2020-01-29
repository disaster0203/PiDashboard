#include "db_manager.h"

int8_t manager::db_manager::add_extremum(std::shared_ptr<dto::extremas_dto> new_value)
{
	std::string insert = "INSERT INTO " + std::string(tables["extremas"]->get_table_name()) + "(sensor_type_name, individual_name, count, sum, max, min)"
		+ " values('" + new_value->get_sensor_type_name() + "', "
		+ new_value->get_individual_name() + ", "
		+ std::to_string(1) + ", "
		+ std::to_string(new_value->get_sum()) + ", "
		+ std::to_string(new_value->get_max()) + ", "
		+ std::to_string(new_value->get_min()) + ");";

	if (mysql_query(db_connection, insert.c_str()) != 0)
	{
		handle_error("add_extremum", tables["extremas"]->get_table_name(), insert.c_str(), mysql_error(db_connection));
		return QUERY_ERROR;
	}
	return TRUE;
}

int8_t manager::db_manager::delete_extremum(std::string sensor_type_name, std::string individual_name)
{
	std::string statement = "DELETE FROM " + std::string(tables["extremas"]->get_table_name()) +
		" WHERE sensor_type_name='" + sensor_type_name + "' AND individual_name='" + individual_name + "';";

	if (mysql_query(db_connection, statement.c_str()) != 0)
	{
		handle_error("delete_extremum [by type and name]", tables["extremas"]->get_table_name(), statement.c_str(), mysql_error(db_connection));
		return QUERY_ERROR;
	}
	return TRUE;
}

int8_t manager::db_manager::get_extremum(std::shared_ptr<dto::extremas_dto>& result, std::string sensor_type_name, std::string individual_name)
{
	std::string select = "SELECT * FROM " + std::string(tables["extremas"]->get_table_name()) +
		" WHERE sensor_name='" + sensor_type_name + "' AND individual_name='" + individual_name + "' LIMIT 1;";

	if (mysql_query(db_connection, select.c_str()) != 0)
	{
		handle_error("get_extremum", tables["extremas"]->get_table_name(), select.c_str(), mysql_error(db_connection));
		return QUERY_ERROR;
	}

	MYSQL_RES* res = mysql_use_result(db_connection);
	MYSQL_ROW row = mysql_fetch_row(res);
	result = std::make_shared<dto::extremas_dto>();

	if (row != NULL)
	{
		result->set_sensor_type_name(row[1]);
		result->set_individual_name(row[2]);
		result->set_count(atof(row[3]));
		result->set_sum(atof(row[4]));
		result->set_max(atof(row[5]));
		result->set_min(atof(row[6]));
	}

	mysql_free_result(res);
	return TRUE;
}

int8_t manager::db_manager::update_extremum(std::shared_ptr<dto::sensor_dto> new_value)
{
	std::shared_ptr<dto::extremas_dto> extremum = std::make_shared<dto::extremas_dto>();
	if (get_extremum(extremum, new_value->get_sensor_type_name(), new_value->get_individual_name()) != TRUE)
	{
		handle_error("update_extremum", tables["extremas"]->get_table_name(), "Get extremum", mysql_error(db_connection));
		return QUERY_ERROR;
	}

	if (extremum->get_count() > 0) // Row already exists -> update it
	{
		// row[0] = id
		std::string update = "UPDATE " + std::string(tables["extremas"]->get_table_name()) + " SET " +
			"count='" + std::to_string(extremum->get_count() + 1) + "', " +
			"sum='" + std::to_string(extremum->get_sum() + new_value->get_value()) + "', " +
			"max='" + std::to_string(new_value->get_value() >= extremum->get_max() ? new_value->get_value() : extremum->get_max()) + "', " +
			"min='" + std::to_string(new_value->get_value() < extremum->get_min() ? new_value->get_value() : extremum->get_min()) + "' " +
			"WHERE sensor_type_name='" + extremum->get_sensor_type_name() + "' AND individual_name='" + extremum->get_individual_name() + "' LIMIT 1;";

		if (mysql_query(db_connection, update.c_str()) != 0)
		{
			handle_error("update_extremum", tables["extremas"]->get_table_name(), update.c_str(), mysql_error(db_connection));
			return QUERY_ERROR;
		}
	}
	else // Row does not exist -> add new one
	{
		auto new_entry = std::make_shared<dto::extremas_dto>(dto::extremas_dto(new_value->get_sensor_type_name(),
			new_value->get_individual_name(),
			1,
			new_value->get_value(),
			new_value->get_value(),
			new_value->get_value()));
		if (add_extremum(new_entry) != TRUE)
		{
			handle_error("update_extremum", tables["extremas"]->get_table_name(), "Add new entry", mysql_error(db_connection));
			return QUERY_ERROR;
		}
	}
	return TRUE;
}

int8_t manager::db_manager::update_extremum(std::string sensor_type_name, std::string individual_name, double count, double sum, double max, double min)
{
	std::shared_ptr<dto::extremas_dto> extremum = std::make_shared<dto::extremas_dto>();
	if (get_extremum(extremum, sensor_type_name, individual_name) != TRUE)
	{
		handle_error("update_extremum", tables["extremas"]->get_table_name(), "Get extremum", mysql_error(db_connection));
		return QUERY_ERROR;
	}

	if (extremum->get_count() > 0) // Row already exists -> update it
	{
		// row[0] = id
		std::string update = "UPDATE " + std::string(tables["extremas"]->get_table_name()) + " SET " +
			"count='" + std::to_string(count) + "', " +
			"sum='" + std::to_string(sum) + "', " +
			"max='" + std::to_string(max) + "', " +
			"min='" + std::to_string(min) + "' " +
			"WHERE sensor_type_name='" + sensor_type_name + "' AND individual_name='" + individual_name + "' LIMIT 1;";

		if (mysql_query(db_connection, update.c_str()) != 0)
		{
			handle_error("update_extremum", tables["extremas"]->get_table_name(), update.c_str(), mysql_error(db_connection));
			return QUERY_ERROR;
		}
	}
	else // Row does not exist -> add new one
	{
		if (add_extremum(std::make_shared<dto::extremas_dto>(dto::extremas_dto(sensor_type_name, individual_name, count, sum, max, min))) != TRUE)
		{
			handle_error("update_extremum", tables["extremas"]->get_table_name(), "Add new entry", mysql_error(db_connection));
			return QUERY_ERROR;
		}
	}
	return TRUE;
}

int8_t manager::db_manager::recalculate_extremum(std::string sensor_type_name, std::string individual_name)
{
	std::vector<std::shared_ptr<dto::sensor_dto>> entries;
	if (get_all_sensor_entries(entries, sensor_type_name, individual_name) != TRUE)
	{
		handle_error("recalculate_extremum", tables["extremas"]->get_table_name(), "Get all sensor entries", mysql_error(db_connection));
		return QUERY_ERROR;
	}

	if (entries.size() == 0)
	{
		std::cout << "No entries with sensor_type_name " << sensor_type_name << "and individual_name " << individual_name << " found. Cannot recalculate extremas..." << std::endl;
		return FALSE;
	}

	double sum = 0;
	double max = std::numeric_limits<double>::min();
	double min = std::numeric_limits<double>::max();
	for (auto entry : entries)
	{
		sum += entry->get_value();
		max = (entry->get_value() >= max) ? entry->get_value() : max;
		min = (entry->get_value() < min) ? entry->get_value() : min;
	}

	return update_extremum(sensor_type_name, individual_name, entries.size(), sum, max, min);
}

