#include <connection.h>

#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#include <unistd.h>
#include <stddef.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/un.h> 
#include <errno.h>

#define INVALID_SOCKET -1
#define SOCKET_ERROR  -1
#define BACKLOG 1024
#define MSG_LEN 1024

struct connection {
	int socket;
	struct sockaddr* addr;
	socklen_t addrlen;
};


connection_t connection_init(const char* address, const uint16_t port) {
	struct connection* connection;
	if ((connection = malloc(sizeof(struct connection))) == NULL) {
		// TODO: set errno
		return NULL;
	}
	struct sockaddr_in* paddr_in;
	struct in_addr host_addr;
	if ((connection->socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP)) == INVALID_SOCKET) {
		// TODO: set errno
		free(connection);
		return NULL;
	}
	if ((paddr_in = malloc(sizeof(struct sockaddr_in))) == NULL) {
		// TODO: set errno
		free(connection);
		return NULL;
	}
	if (!inet_aton(address, &host_addr)) {
		free(connection);
		free(paddr_in);
		errno = EINVAL;
		return NULL;
	}
	memset(&connection->addr, 0, sizeof(connection->addr));
	paddr_in->sin_family = AF_INET;
	paddr_in->sin_port = htons(port);
	paddr_in->sin_addr = host_addr;
	connection->addr = (struct sockaddr*)paddr_in;
	connection->addrlen = sizeof(struct sockaddr_in);
	return connection;
}

int connection_destroy(const connection_t handle) {
	struct connection* connection;
	connection = (struct connection*)handle;
	free(connection->addr);
	free(connection);
	return 0;
}

int connection_listen(const connection_t handle) {
	struct connection* connection;
	connection = (struct connection*)handle;
	if (bind(connection->socket, connection->addr, connection->addrlen) == -1) {
		return -1;
	}
	if (listen(connection->socket, BACKLOG) == -1) {
		return -1;
	}
	return 0;
}

int connection_connect(const connection_t handle) {
	struct connection* connection;
	connection = (struct connection*)handle;
	if (connect(connection->socket, connection->addr, connection->addrlen) == SOCKET_ERROR) {
		return -1;
	}
	return 0;
}

int connection_close(const connection_t handle) {
	struct connection* connection;
	connection = (struct connection*)handle;
	if (close(connection->socket) == -1) {
		return -1;
	}
	return 0;
}

int connection_recv(const connection_t handle, char** buff) {
	struct connection* connection;
	ssize_t len;
	connection = (struct connection*)handle;
	if ((*buff = malloc(sizeof(char) * (MSG_LEN + 1))) == NULL) {
		return -1;
	}
	memset(*buff, 0, sizeof(char) * (MSG_LEN + 1));
	len = recv(connection->socket, *buff, MSG_LEN, 0);
	if (len == -1 || len > MSG_LEN) {
		free(*buff);
		*buff = NULL;
		return -1;
	}
	return (int)len;
}

int connection_send(const connection_t handle, const char* buff) {
	struct connection* connection;
	int len;
	connection = (struct connection*)handle;
	if ((len = (int)send(connection->socket, buff, strlen(buff), 0)) == -1) {
		return -1;
	}
	return len;
}

connection_t connection_accepted(const connection_t handle) {
	struct connection* listener;
	struct connection* accepted;
	listener = (struct connection*)handle;
	if ((accepted = malloc(sizeof(struct connection))) == NULL) {
		return NULL;
	}
	memset(&accepted->addrlen, 0, sizeof(socklen_t));
	accepted->addr = malloc(sizeof(accepted->addrlen));
	while ((accepted->socket = accept(listener->socket, accepted->addr, &accepted->addrlen)) == -1) {
		if (errno != EMFILE) {
			free(accepted);
			return NULL;
		}
		sleep(1);
	}
	return accepted;
}
