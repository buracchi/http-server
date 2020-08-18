#include <stdio.h>
#include "server.h"

static void usage(const char* prog) {
	fprintf(stderr,
		"Usage:  %s [option ...]\n" \
		"\n" \
		"The following options are recognized:\n" \
		"\t--help\n", prog);
}

int main(int argc, char** argv) {
	print_hello_world();
	return 0;
}
