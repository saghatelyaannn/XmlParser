#include <iostream>
#include "../lib/XmlParser.hpp"
#include "../lib/DatabaseManager.hpp"

int main(int argc, char *argv[]) {

    if (argc < 7) {
        std::cerr << "Error: not enough arguments." << std::endl;
        std::cerr << "Usage: " << argv[0] << " </path/to/the/xml/file> <host> <user> <password> <database-name> <table-name>" << std::endl;
        return -1;
    }

    XmlStructure structure = parseXML(argv[1]);

    const std::string hostname = argv[2];
    const std::string username = argv[3];
    const std::string password = argv[4];
    const std::string database = argv[5];
    const std::string table_name = argv[6];

    printXmlStructure(structure);

    sql::Connection *con = connectDatabase(username, password, hostname, database);
    
    if (con) {
        std::string creation_string = creationString(structure, table_name);

        std::cout << std::endl << "Generated SQL for table creation: " << creation_string << std::endl;

        createTable(con, creation_string, table_name);
			
		insertDataIntoTable(con, structure, table_name);

        delete con;
    }
    
    return 0;
}
