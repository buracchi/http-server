cmake_minimum_required (VERSION 3.8)

add_library(
	server
	"server.c"
	"server.h"
	)

target_include_directories(server PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_compile_options(server PUBLIC -Wall -pedantic)
target_link_libraries(server PUBLIC coverage_config)
