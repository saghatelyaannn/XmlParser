cmake_minimum_required(VERSION 3.22.1)
project(XmlParserProject)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(SOURCE_DIR ${CMAKE_SOURCE_DIR}/src)
set(LIB_DIR ${CMAKE_SOURCE_DIR}/lib)

file(GLOB LIB_SOURCES ${SOURCE_DIR}/*.cpp)
list(REMOVE_ITEM LIB_SOURCES ${SOURCE_DIR}/main.cpp)

add_library(parsing_and_db_lib SHARED ${LIB_SOURCES})

add_executable(XmlParser ${SOURCE_DIR}/main.cpp)

target_include_directories(XmlParser PRIVATE ${LIB_DIR})

target_link_libraries(XmlParser PRIVATE MyLib mysqlcppconn tinyxml2)

