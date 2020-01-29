#include "db_manager.h"

manager::db_manager::db_manager(const std::string host, const std::string user, const std::string password, const std::string database)
{
	// 1. Check if basic connection to MySQL works
	db_connection = mysql_init(NULL);
	if (db_connection == NULL)
	{
		handle_error("constructor", database, "Basic connection to MySQL", mysql_error(db_connection), true);
		throw new std::runtime_error("Error establishing simple MySQL connection");
	}

	// 2. Try to open a connection to the database
	if (mysql_real_connect(db_connection, host.c_str(), user.c_str(), password.c_str(), NULL, 0, NULL, 0) == NULL)
	{
		handle_error("constructor", database, "Open database connection", mysql_error(db_connection), true);
		throw new std::runtime_error("Error connecting to database");
	}

	// 3. Create the project database if it does not exist and try to USE it
	create_database(database);
	use_database(database);

	// 4. Check if all tables exist and create them if needed
	for (auto table : tables)
	{
		create_table(table.second->get_create_statement());
	}
}

manager::db_manager::~db_manager()
{
	mysql_close(db_connection);
}

void manager::db_manager::create_table(std::string statement)
{
	if (mysql_query(db_connection, statement.c_str()) != 0)
	{
		handle_error("create_table", "", statement, mysql_error(db_connection), true);
		throw new std::runtime_error("Error creating table");
	}
}

void manager::db_manager::create_table(std::string table_name, std::vector<std::string> column_definitions)
{
	std::string statement = "CREATE TABLE IF NOT EXISTS " + table_name + "(";
	for (size_t i = 0; i < column_definitions.size(); ++i)
	{
		if (i == column_definitions.size() - 1) // last column -> add ');' instead of ','
		{
			statement += column_definitions[i] + ");";
		}
		else
		{
			statement += column_definitions[i] + ", ";
		}
	}
	create_table(statement);
}

void manager::db_manager::create_database(std::string database)
{
	std::string statement = "CREATE DATABASE IF NOT EXISTS " + database + ";";
	if (mysql_query(db_connection, statement.c_str()) != 0)
	{
		handle_error("create_database", database, statement, mysql_error(db_connection), true);
		throw new std::runtime_error("Error creating database");
	}
}

void manager::db_manager::use_database(std::string database)
{
	std::string statement = "USE " + database + ";";
	if (mysql_query(db_connection, statement.c_str()) != 0)
	{
		handle_error("use_database", database, statement, mysql_error(db_connection), true);
		throw new std::runtime_error("Error calling USE on database");
	}
}

int8_t manager::db_manager::delete_table(std::string table_name)
{
	std::string statement = "DROP TABLE IF EXISTS " + table_name + ";";

	if (mysql_query(db_connection, statement.c_str()) != 0)
	{
		handle_error("delete_table", table_name, statement, mysql_error(db_connection));
		return QUERY_ERROR;
	}
	return TRUE;
}

int8_t manager::db_manager::delete_database(std::string database_name)
{
	std::string statement = "DROP DATABASE IF EXISTS " + database_name + ";";

	if (mysql_query(db_connection, statement.c_str()) != 0)
	{
		handle_error("delete_database", database_name, statement, mysql_error(db_connection));
		return QUERY_ERROR;
	}
	return TRUE;
}

int8_t manager::db_manager::check_if_table_exists(std::string database, std::string table)
{
	// Lookup tablename
	std::string statement = "SELECT * FROM information_schema.tables WHERE table_schema = '" + database + "' AND table_name = '" + table + "' LIMIT 1;";
	if (mysql_query(db_connection, statement.c_str()) != 0)
	{
		handle_error("check_if_table_exists", database.c_str(), statement.c_str(), mysql_error(db_connection));
		return QUERY_ERROR;
	}

	// Retrieve query result
	MYSQL_RES* result = mysql_use_result(db_connection);
	if (result == NULL)
	{
		handle_error("check_if_table_exists", database.c_str(), "Receive query results", mysql_error(db_connection));
		return QUERY_ERROR;
	}

	// Check if rows were found
	if (mysql_fetch_row(result) == NULL)
	{
		mysql_free_result(result);
		return FALSE;
	}
	else
	{
		mysql_free_result(result);
		return TRUE;
	}
}

int8_t manager::db_manager::check_if_database_exists(std::string database)
{
	// Lookup tablename
	std::string statement = "SELECT SCHEMA_NAME FROM information_schema.schemata WHERE schema_name = '" + database + "' LIMIT 1;";
	if (mysql_query(db_connection, statement.c_str()) != 0)
	{
		handle_error("check_if_database_exists", database.c_str(), statement.c_str(), mysql_error(db_connection));
		return QUERY_ERROR;
	}

	// Retrieve query result
	MYSQL_RES* result = mysql_use_result(db_connection);
	if (result == NULL)
	{
		handle_error("check_if_database_exists", database.c_str(), "Receive query results", mysql_error(db_connection));
		return QUERY_ERROR;
	}

	// Check if rows were found
	if (mysql_fetch_row(result) == NULL)
	{
		mysql_free_result(result);
		return FALSE;
	}
	else
	{
		mysql_free_result(result);
		return TRUE;
	}
}

void manager::db_manager::handle_error(const std::string method, const std::string table, const std::string statement, const std::string error, bool close)
{
	std::cerr << "DBManager [" << method << "] Error in table " << table << " during execution of statement '" << statement << "'.\nError message: " << error << ".\nClosing database connection" << std::endl;
	if (close)
	{
		mysql_close(db_connection);
	}
}
