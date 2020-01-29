#pragma once

#include <string>
#include <vector>

namespace dto
{
	struct column
	{
		column(std::string name, std::string type)
		{
			this->name = name;
			this->type = type;
		}

		std::string name = "";
		std::string type = "";
	};

	class query_object
	{
	public:
		query_object(std::string table, std::vector<column*> columns, std::string create) : m_table(table), m_columns(columns), m_create(create) { }

		const char* get_create_statement() const { return m_create.c_str(); }
		const char* get_table_name() const { return m_table.c_str(); }
		const std::vector<column*> get_columns() { return m_columns; }
		const column* get_column(uint32_t index)
		{
			if (index >= 0 && index < m_columns.size())
			{
				return m_columns[index];
			}
			else
			{
				return new column("", "");
			}
		}

	protected:
		std::string m_table = "";
		std::vector<column*> m_columns;
		std::string m_create = "";
	};
}