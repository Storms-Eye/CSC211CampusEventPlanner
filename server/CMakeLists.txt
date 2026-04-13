cmake_minimum_required(VERSION 3.10)
project(finalProject)

set (CMAKE_CXX_STANDARD 20)

#include directories
include_directories(../crow/include)

find_package(cpr REQUIRED)
find_package(nlohmann_json REQUIRED)

#add executables
add_executable(final-server src/main.cpp src/json-repository.cpp src/event.cpp)

#link libraries
target_link_libraries(final-server pthread nlohmann_json::nlohmann_json cpr::cpr)

#set target database
add_custom_command(TARGET final-server POST_BUILD
	COMMAND ${CMAKE_COMMAND} -E copy
			${CMAKE_SOURCE_DIR}/data.json
			$<TARGET_FILE_DIR:final-server>/data.json
			)
