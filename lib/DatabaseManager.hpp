#ifndef DATABASE_MANAGER_HPP
#define DATABASE_MANAGER_HPP

#include <string>
#include <vector>
#include <map>
#include <mysql_driver.h>
#include <mysql_connection.h>
#include <cppconn/statement.h>
#include <cppconn/prepared_statement.h>

using XmlMap = std::map<std::string, std::string>;
using XmlStructure = std::vector<XmlMap>;

void printXmlStructure(const XmlStructure& structure);
void dropTableIfExists(sql::Connection* con, const std::string& tableName);
sql::Connection* connectDatabase(const std::string& username, const std::string& password, const std::string& hostname, const std::string& database);
std::string creationString(const XmlStructure& structure, const std::string& tableName);
void createTable(sql::Connection* con, const std::string& creation_string, const std::string& table_name);
void insertDataIntoTable(sql::Connection* con, const XmlStructure& structure, const std::string& table_name);

#endif

