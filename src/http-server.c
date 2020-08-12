// http-server.c: definisce il punto di ingresso dell'applicazione.
//

#include "http-server.h"
#include "fib.h"

int main() {
	printf("Hello CMake\n");
	printf("%d\n", fib(24));
	return 0;
}
