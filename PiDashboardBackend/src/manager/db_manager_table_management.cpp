#include "db_manager.h"

db_manager::db_manager(const std::string host, const std::string user, const std::string password, const std::string database)
{
	// 1. Check if basic connection to MySQL works
	db_connection = mysql_init(NULL);
	if (db_connection == NULL)
	{
		std::printf(mysql_error(db_connection));
		mysql_close(db_connection);
		throw new std::runtime_error("Error establishing simple MySQL connection");
	}

	// 2. Try to open a connection to the database
	if (mysql_real_connect(db_connection, host.c_str(), user.c_str(), password.c_str(), NULL, 0, NULL, 0) == NULL)
	{
		std::printf("In database %s: %s\n", database, mysql_error(db_connection));
		mysql_close(db_connection);
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

db_manager::~db_manager()
{
	mysql_close(db_connection);
}

void db_manager::create_table(std::string statement)
{
	if (mysql_query(db_connection, statement.c_str()) != 0)
	{
		std::printf(mysql_error(db_connection));
		mysql_close(db_connection);
		throw new std::runtime_error("Error creating table");
	}
}

void db_manager::create_table(std::string table_name, std::vector<std::string> column_definitions)
{
	std::string statement = "CREATE TABLE IF NOT EXISTS " + table_name + "(";
	for (auto i = 0; i < column_definitions.size(); ++i)
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

void db_manager::create_database(std::string database_name)
{
	std::string statement = "CREATE DATABASE IF NOT EXISTS " + database_name + ";";
	if (mysql_query(db_connection, statement.c_str()) != 0)
	{
		std::printf("In database %s: %s\n", database_name, mysql_error(db_connection));
		mysql_close(db_connection);
		throw new std::runtime_error("Error creating database");
	}
}

void db_manager::use_database(std::string database_name)
{
	std::string statement = "USE " + database_name + ";";
	if (mysql_query(db_connection, statement.c_str()) != 0)
	{
		std::printf("In database %s: %s\n", database_name, mysql_error(db_connection));
		mysql_close(db_connection);
		throw new std::runtime_error("Error calling USE on database");
	}
}

void db_manager::delete_table(std::string table_name)
{
	std::string statement = "DROP TABLE IF EXISTS " + table_name + ";";

	if (mysql_query(db_connection, statement.c_str()) != 0)
	{
		handle_error("delete_table", table_name.c_str(), statement.c_str(), mysql_error(db_connection));
	}
}

void db_manager::delete_database(std::string database_name)
{
	std::string statement = "DROP DATABASE IF EXISTS " + database_name + ";";

	if (mysql_query(db_connection, statement.c_str()) != 0)
	{
		handle_error("delete_database", database_name.c_str(), statement.c_str(), mysql_error(db_connection));
	}
}

bool db_manager::check_if_table_exists(std::string database, std::string table_name)
{
	// Lookup tablename
	std::string statement = "SELECT * FROM information_schema.tables WHERE table_schema = '" + database + "' AND table_name = '" + table_name + "' LIMIT 1;";
	if (mysql_query(db_connection, statement.c_str()) != 0)
	{
		handle_error("check_if_table_exists", database.c_str(), statement.c_str(), mysql_error(db_connection));
	}

	// Retrieve query result
	MYSQL_RES* result = mysql_use_result(db_connection);
	if (result == NULL)
	{
		std::printf("In Table %s: %s\n", table_name, mysql_error(db_connection));
		mysql_close(db_connection);
		throw new std::runtime_error("Error retriving query result");
	}

	// Check if rows were found
	if (mysql_fetch_row(result) == NULL)
	{
		mysql_free_result(result);
		return false;
	}
	else
	{
		mysql_free_result(result);
		return true;
	}
}

bool db_manager::check_if_database_exists(std::string database_name)
{
	// Lookup tablename
	std::string statement = "SELECT SCHEMA_NAME FROM information_schema.schemata WHERE schema_name = '" + database_name + "' LIMIT 1;";
	if (mysql_query(db_connection, statement.c_str()) != 0)
	{
		handle_error("check_if_database_exists", database_name.c_str(), statement.c_str(), mysql_error(db_connection));
	}

	// Retrieve query result
	MYSQL_RES* result = mysql_use_result(db_connection);
	if (result == NULL)
	{
		std::printf(mysql_error(db_connection));
		mysql_close(db_connection);
		throw new std::runtime_error("Error retriving query result");
	}

	// Check if rows were found
	if (mysql_fetch_row(result) == NULL)
	{
		mysql_free_result(result);
		return false;
	}
	else
	{
		mysql_free_result(result);
		return true;
	}
}

void db_manager::handle_error(const char* method, const char* table, const char* statement, const char* error)
{
	std::printf("In table %s: %s\n", table, error);
	mysql_close(db_connection);
	throw new std::runtime_error(("Error during sql query with statement '%s', in method '%s()'", statement, method));
}
