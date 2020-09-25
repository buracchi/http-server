cmake_minimum_required (VERSION 3.8)

add_library(
	abnf
	"parser.c"
	"parser.h"
	)

target_include_directories(abnf PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_compile_options(abnf PUBLIC -Wall -pedantic)
target_link_libraries(abnf PUBLIC coverage_config)
