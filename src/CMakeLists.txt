cmake_minimum_required (VERSION 3.8)

add_executable (
	http-server
	"http-server.c"
	"http-server.h"
	)

target_link_libraries(http-server PUBLIC coverage_config)
target_link_libraries(http-server PRIVATE fib)

add_library(fib
	"fib/fib.c"
	"fib/fib.h"
	)

target_include_directories(fib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/fib)
target_compile_options(fib PUBLIC -Wall -pedantic)
target_link_libraries(fib PUBLIC coverage_config)
