#include <stdlib.h>
#include "server.h"

int main() {
	if (print_hello_world() == 13) {
		return EXIT_SUCCESS;
	}
	return EXIT_FAILURE;
}
