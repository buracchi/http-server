cmake_minimum_required (VERSION 3.8)

add_library(
	http
	"http.c"
	"http.h"
	)

target_include_directories(http PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_compile_options(http PUBLIC -Wall -pedantic)
target_link_libraries(http PUBLIC coverage_config)
