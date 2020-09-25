#pragma once

#include <stdint.h>

/*
* TCP/IP socket wrapper
*/
typedef void* connection_t;

/*
* Return an initialized TCP connection object.
* 
* @param	address	
* @param	port	
* @return	the connection object if successfull or a NULL pointer otherwise.
*/
extern connection_t connection_init(const char* address, const uint16_t port);

/*
* Destroy a connection object.
*
* @param	connection
* @return
*/
extern int connection_destroy(const connection_t connection);

/*
* Connect an initialized connection.
* 
* @param	connection
* @return	
*/
extern int connection_connect(const connection_t connection);

/*
* Listen from the initialized connection.
*
* @param	connection
* @return	1 and set properly errno on error
*/
extern int connection_listen(const connection_t connection);

/*
* Get an accepted connection
*
* @param	connection
* @return	NULL and set properly errno on error
*/
extern connection_t connection_accepted(const connection_t connection);

/*
* Get a malloc'd buffer containing the received message.
*
* @param	connection
* @param	buff
* @return	number of byte read or -1 on error
*/
extern int connection_recv(const connection_t connection, char** buff);

/*
* Send a string.
*
* @param	connection
* @param	buff
* @return	number of bytes sended
*/
extern int connection_send(const connection_t connection, const char* buff);

/*
* Close connection
*
* @param	connection
* @return	1 and set properly errno on error
*/
extern int connection_close(const connection_t connection);
