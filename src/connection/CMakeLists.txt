cmake_minimum_required (VERSION 3.8)

add_library(
	connection
	"connection.c"
	"connection.h"
	)

target_include_directories(connection PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_compile_options(connection PUBLIC -Wall -pedantic)
target_link_libraries(connection PUBLIC coverage_config)
