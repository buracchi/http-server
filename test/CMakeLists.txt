add_executable(test_fib fib.c)

target_link_libraries(test_fib PRIVATE fib)

add_test(NAME "Fib_Test" COMMAND "test_fib")
