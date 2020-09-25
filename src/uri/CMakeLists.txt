cmake_minimum_required (VERSION 3.8)

add_library(
	uri
	"uri.c"
	"uri.h"
	)

target_include_directories(uri PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_compile_options(uri PUBLIC -Wall -pedantic)
target_link_libraries(uri PUBLIC coverage_config)
