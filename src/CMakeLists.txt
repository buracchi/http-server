cmake_minimum_required (VERSION 3.8)

add_subdirectory(lib)

add_executable (
	http-server
	"main.c"
	)

target_link_libraries(http-server PRIVATE server)
