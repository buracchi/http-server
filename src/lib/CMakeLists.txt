cmake_minimum_required (VERSION 3.8)

add_library(
	server
	"server.c"
	)

target_include_directories(server PUBLIC "include")
target_compile_options(server PUBLIC -Wall -pedantic)
target_link_libraries(server PUBLIC coverage_config)
