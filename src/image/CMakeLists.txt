cmake_minimum_required (VERSION 3.8)

add_library(
	image
	"image.c"
	"image.h"
	)

target_include_directories(image PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(image PRIVATE ${JPEG_LIBRARIES})
target_include_directories(image PRIVATE ${JPEG_INCLUDE_DIR})
target_compile_options(image PUBLIC -Wall -pedantic)
target_link_libraries(image PUBLIC coverage_config)
