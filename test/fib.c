#include <stdlib.h>
#include "fib.h"

int main() {
	if (
		fib(0) == 1 &&
		fib(1) == 1 &&
		fib(2) == 2 &&
		fib(3) == 3 &&
		fib(4) == 5 &&
		fib(5) == 8
		) {
		return EXIT_SUCCESS;
	}
	return EXIT_FAILURE;
}
