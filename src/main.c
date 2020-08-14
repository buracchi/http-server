#include <stdio.h>
#include "server.h"

static int print_usage(const char* prog) {
	return fprintf(stderr,
		"Usage:  %s [option ...]\n" \
		"\n" \
		"The following options are recognized:\n" \
		"\t--help\n", prog);
}

int main(int argc, char** argv) {
	print_hello_world();
	return 0;
}
