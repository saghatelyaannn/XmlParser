## Xml Parser

This project provides a C++ application to parse XML files and import the data into a MySQL database. 
The application creates a table in the database based on the XML structure and inserts the parsed data into that table.


## Features

- Parse XML files and extract data into a structured format.
- Dynamically create a MySQL table based on the XML data.
- Insert parsed XML data into the MySQL table.
- Handle unique elements in XML data for table columns.

## Requirements

- MySQL server
- MySQL Connector/C++ library
- TinyXML2 library for XML parsing

## Installation

1. Install MySQL Connector/C++:

	sudo apt install libmysqlcppconn-dev

2. Install TinyXML2:

	sudo apt install libtinyxml2-dev


3. Build the Project:

   Make sure you have a C++ compiler, make and CMake installed. Navigate to the project directory and run the following commands:

   mkdir build
   cd build
   cmake ..
   make


4. Usage

	./XmlParser /path/to/xml/file host user password database-name table-name


XmlParser
Excellent center project N1 
