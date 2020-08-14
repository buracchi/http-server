add_executable(test_server server.c)
target_link_libraries(test_server PRIVATE server)

add_test(NAME "Hello_Test" COMMAND "test_server")
