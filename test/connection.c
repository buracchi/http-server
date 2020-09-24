#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

#include "connection.h"

#define assert_neq(p,q) ((p) != (q)) ? ((void)0) : exit(EXIT_FAILURE);

int server();
int client();

int main() {
	int cstatus = 0;
	pid_t pid;
	pid = fork();
	if (pid == -1) {
		return EXIT_FAILURE;
	}
	if (!pid) {
		return client();
	}
	server();
	assert_neq(wait(&cstatus), -1);
	if (WIFEXITED(cstatus)) {
		assert_neq(WEXITSTATUS(cstatus), EXIT_FAILURE);
	}
	else {
		return EXIT_FAILURE;
	}
	return EXIT_SUCCESS;
}

int server() {
	connection_t list_con;
	connection_t acpt_con;
	char* buff;
	assert_neq(list_con = connection_init("127.0.0.1", 1234), NULL);
	assert_neq(connection_listen(list_con), -1);
	assert_neq(acpt_con = connection_accepted(list_con), NULL);
	assert_neq(connection_recv(acpt_con, &buff), -1);
	assert_neq(connection_close(acpt_con), -1);
	assert_neq(connection_close(list_con), -1);
	connection_destroy(acpt_con);
	connection_destroy(list_con);
	free(buff);
	return EXIT_SUCCESS;
}

int client() {
	connection_t con;
	assert_neq(con = connection_init("127.0.0.1", 1234), NULL);
	assert_neq(connection_connect(con), -1);
	assert_neq(connection_send(con, "Message\n"), -1);
	assert_neq(connection_close(con), -1);
	connection_destroy(con);
	return EXIT_SUCCESS;
}
