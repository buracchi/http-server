#pragma once

#include <stdint.h>

/*
* TCP/IP socket wrapper
*/
typedef void* connection_t;

/**
* Return an handle to an initialized TCP connection object.
* 
* @param	address	
* @param	port	
* @return	the handle to the connection object if successfull or a NULL pointer otherwise.
*/
extern connection_t connection_init(const char* address, const uint16_t port);

/**
* 
* @param	handle
* @return	
*/
extern int connection_destroy(const connection_t handle);

/*
* Close connection
* 
* @param	handle	
* @return	1 and set properly errno on error
*/
extern int connection_close(const connection_t handle);

/*
* 
* @param	handle
* @return	
*/
extern int connection_connect(const connection_t handle);

/*
* Get a malloc'd buffer wich contain a received message
* 
* @param	handle	
* @param	buff	
* @return	number of byte read or -1 on error
*/
extern int connection_recv(const connection_t handle, char** buff);

/*
* 
* 
* @param	handle	
* @param	buff
* @return	number of bytes sended
*/
extern int connection_send(const connection_t handle, const char* buff);

/*
* Initiazlize connection
* 
* @param	handle
* @return	1 and set properly errno on error
*/
extern int connection_listen(const connection_t handle);

/*
* Get an accepted connection
* 
* @param	handle
* @return	NULL and set properly errno on error
*/
extern connection_t connection_accepted(const connection_t handle);
