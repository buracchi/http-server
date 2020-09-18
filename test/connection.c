#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include "unistd.h"
#include "connection.h"

#include <stdio.h>

#define assert_neq(p,q) ((p) != (q)) ? ((void)0) : exit(EXIT_FAILURE);

int server();
int client();

int main() {
	int child_retval;
	pid_t pid;
	pid = fork();
	if (pid == -1) {
		return EXIT_FAILURE;
	}
	if (!pid) {
		return client();
	}
	server();
	assert_neq(wait(&child_retval), -1);
	return EXIT_SUCCESS;
}


int server() {
	connection_t connection;
	connection_t accepted_connection;
	char* buff;
	assert_neq(connection = connection_init("127.0.0.1", (uint16_t)1234), NULL);
	assert_neq(connection_listen(connection), -1);
	assert_neq(accepted_connection = connection_accepted(connection), NULL);
	assert_neq(connection_recv(accepted_connection, &buff), -1);
	assert_neq(connection_close(accepted_connection), -1);
	assert_neq(connection_close(connection), -1);
	connection_destroy(accepted_connection);
	connection_destroy(connection);
	free(buff);
	return EXIT_SUCCESS;
}

int client() {
	connection_t connection;
	assert_neq(connection = connection_init("127.0.0.1", (uint16_t)1234), NULL);
	assert_neq(connection_connect(connection), -1);
	assert_neq(connection_send(connection, "Message\n"), -1);
	assert_neq(connection_close(connection), -1);
	connection_destroy(connection);
	return EXIT_SUCCESS;
}
