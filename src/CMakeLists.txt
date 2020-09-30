cmake_minimum_required (VERSION 3.8)

add_subdirectory(server)
add_subdirectory(image)
add_subdirectory(connection)
add_subdirectory(abnf)
add_subdirectory(uri)
add_subdirectory(http)

add_executable (
	http-server
	"main.c"
	)

target_link_libraries(http-server PRIVATE server)
