add_executable(test_server server.c)
target_link_libraries(test_server PRIVATE server)

add_executable(test_image image.c)
target_link_libraries(test_image PRIVATE image)

add_executable(test_connection connection.c)
target_link_libraries(test_connection PRIVATE connection)

add_test(NAME "Server_Test" COMMAND "test_server")
add_test(NAME "Image_Test" COMMAND "test_image")
add_test(NAME "Connection_Test" COMMAND "test_connection")
