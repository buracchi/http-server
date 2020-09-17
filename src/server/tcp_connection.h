#pragma once

#include <stdint.h>

/*
* TCP/IP socket wrapper
*/
typedef void* tcp_connection_t;

/**
* Return an handle to an initialized TCP connection object.
* 
* @param	address	
* @param	port	
* @return	the handle to the connection object if successfull or a NULL pointer otherwise.
*/
extern tcp_connection_t tcp_connection_init(const char* address, const uint16_t port);

/**
* 
* @param	handle
* @return	
*/
extern int tcp_connection_destroy(const tcp_connection_t handle);

/*
* Close connection
* 
* @param	handle	
* @return	1 and set properly errno on error
*/
extern int tcp_connection_close(const tcp_connection_t handle);

/*
* 
* @param	handle
* @return	
*/
extern int tcp_connetcion_connect(const tcp_connection_t handle);

/*
* Get a malloc'd buffer wich contain a received message
* 
* @param	handle	
* @param	buff	
* @return	number of byte read or -1 on error
*/
extern int tcp_connection_recv(const tcp_connection_t handle, char** buff);

/*
* 
* 
* @param	handle	
* @param	buff
* @return	number of bytes sended
*/
extern int tcp_connection_send(const tcp_connection_t handle, const char* buff);

/*
* Initiazlize connection
* 
* @param	handle
* @return	1 and set properly errno on error
*/
extern int tcp_connection_listen(const tcp_connection_t handle);

/*
* Get an accepted connection
* 
* @param	handle
* @return	1 and set properly errno on error
*/
extern tcp_connection_t tcp_connection_accepted(const tcp_connection_t handle);
