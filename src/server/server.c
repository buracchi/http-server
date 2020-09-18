#include "server.h"

#include <stdio.h>

#include "image.h"
#include "connection.h"

int print_hello_world() {
	print_image();
	return printf("Hello CMake!\n");
}
