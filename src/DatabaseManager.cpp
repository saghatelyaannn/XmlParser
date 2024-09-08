#include "../lib/DatabaseManager.hpp"
#include <iostream>
#include <set>


void printXmlStructure(const XmlStructure& structure) {
    for (const auto& map : structure) {
        for (const auto& pair : map) {
            std::cout << pair.first << ": " << pair.second << std::endl;
        }
		std::cout << std::endl;
    }
}

template <typename T>
class UniqueVector {
public:
    void push_back(const T& value) {
        if (uniqueSet.find(value) == uniqueSet.end()) {
            uniqueSet.insert(value);
            vec.push_back(value);
        }
    }
    const std::vector<T>& getElements() const {
        return vec;
    }
    void print() const {
        for (const T& elem : vec) {
            std::cout << elem << " ";
        }
        std::cout << std::endl;
    }

private:
    std::vector<T> vec;
    std::set<T> uniqueSet;
};

void dropTableIfExists(sql::Connection* con, const std::string& tableName) {
    try {
        sql::Statement* stmt = con->createStatement();
        std::string query = "DROP TABLE IF EXISTS " + tableName;
        stmt->execute(query);
        std::cout << "Table '" << tableName << "' dropped successfully (if it existed)." << std::endl;
        delete stmt;
    } catch (sql::SQLException &e) {
        std::cerr << "SQLException: " << e.what() << std::endl;
    }
}

sql::Connection* connectDatabase(const std::string& username, const std::string& password, const std::string& hostname, const std::string& database) {
    sql::mysql::MySQL_Driver *driver = nullptr;
    sql::Connection *con = nullptr;
    
    try {
        driver = sql::mysql::get_mysql_driver_instance();
        con = driver->connect(hostname, username, password);
        con->setSchema(database);
        std::cout << "Connected to the database successfully" << std::endl;
    } catch (sql::SQLException &e) {
        std::cerr << "SQLException: " << e.what() << std::endl;
    }

    return con;
}

std::string creationString(const XmlStructure& structure, const std::string& tableName) {
    std::string creation_string = "CREATE TABLE " + tableName + " (";

    UniqueVector<std::string> keys;
    
    for (const auto& xmlMap : structure) {
        for (const auto& [path, value] : xmlMap) {
            keys.push_back(path);
        }
    }
    
    for (const auto& key : keys.getElements()) {
        creation_string += key + " VARCHAR(100), ";
    }
    
    if (!structure.empty()) {
        creation_string.erase(creation_string.size() - 2);
    }
    
    creation_string += ")";
    return creation_string;
}

void createTable(sql::Connection* con, const std::string& creation_string, const std::string& table_name) {
    dropTableIfExists(con, table_name);
    try {
        sql::Statement *stmt = con->createStatement();
        stmt->execute(creation_string);
        std::cout << "Table created successfully." << std::endl;
        delete stmt;
    } catch (sql::SQLException &e) {
        std::cerr << "SQLException: " << e.what() << std::endl;
    }
}

void insertDataIntoTable(sql::Connection* con, const XmlStructure& structure, const std::string& table_name) {
    try {
        for (const auto& xmlMap : structure) {
            std::string columns = "(";
            std::string values = "(";

            for (const auto& [key, value] : xmlMap) {
                columns += key + ",";
                values += "'" + value + "',";
            }

            columns.pop_back();
            values.pop_back();
            columns += ")";
            values += ")";

            std::string query = "INSERT INTO " + table_name + " " + columns + " VALUES " + values;

            std::cout << "Executing query: " << query << std::endl;

            sql::Statement* stmt = con->createStatement();
            stmt->execute(query);
            delete stmt;
        }
        std::cout << "Data inserted successfully into table '" << table_name << "'." << std::endl;
    } catch (sql::SQLException &e) {
        std::cerr << "SQLException: " << e.what() << std::endl;
    }
}

