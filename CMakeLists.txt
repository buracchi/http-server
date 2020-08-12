cmake_minimum_required (VERSION 3.8)

project (
	"http-server"
	VERSION 0.1
	LANGUAGES C
	)

# Use C 11
set(CMAKE_C_STANDARD 11)
# Require (at least) it
set(CMAKE_C_STANDARD_REQUIRED ON)
# Use GNU extension
set(CMAKE_C_EXTENSIONS ON)

# Guards

if(PROJECT_SOURCE_DIR STREQUAL PROJECT_BINARY_DIR)
    message(
    FATAL_ERROR
    "In-source builds not allowed. Please make a new directory (called a build directory) and run CMake from there."
    )
endif()

# Code Coverage Configuration

add_library(coverage_config INTERFACE)

option(CODE_COVERAGE "Enable coverage reporting" OFF)

if(CODE_COVERAGE AND CMAKE_C_COMPILER_ID MATCHES "GNU|Clang")
    # Add required flags (GCC & LLVM/Clang)
    target_compile_options(coverage_config INTERFACE
        -O0        # no optimization
        -g         # generate debug info
        --coverage # sets all required flags
    )
    if(CMAKE_VERSION VERSION_GREATER_EQUAL 3.13)
        target_link_options(coverage_config INTERFACE --coverage)
    else()
        target_link_libraries(coverage_config INTERFACE --coverage)
    endif()
endif()

# Source

add_subdirectory("src")

# Library

# Test

option (BUILD_TESTING "Build the testing tree." ON)

if (BUILD_TESTING AND (PROJECT_SOURCE_DIR STREQUAL CMAKE_SOURCE_DIR))
    enable_testing()
    add_subdirectory("test")
endif()
