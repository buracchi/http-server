#include "fib.h"

int fib(unsigned n) {
	return n > 1 ? fib(n - 1) + fib (n - 2) : 1;
}
