/* EXTC Network module
 *
 * Extended C-library
 *
 * Copyright (C) 2015 Sergey Denisov.
 * Written by Sergey Denisov aka LittleBuster (DenisovS21@gmail.com)
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public Licence
 * as published by the Free Software Foundation; either version 3
 * of the Licence, or (at your option) any later version.
 */

#ifndef __TCP_SOCKET_H__
#define __TCP_SOCKET_H__

#include <pthread.h>

#ifdef WIN32
    #include <Windows.h>
    #include <Winsock2.h>
#else
    #include <sys/types.h>
    #include <sys/socket.h>
    #include <netinet/in.h>
    #include <arpa/inet.h>
    #include <unistd.h>
    #include <string.h>

    #define INVALID_SOCKET (SOCKET)(~0)
    #define SOCKET_ERROR (-1)
    #define SOCKET int
#endif


struct tcp_socket {
    /* Socket id */
    SOCKET s;

    /* User data */
    void *data;

    /**
     * Client accept error signal
     * @data: user data
     */
    void (*accept_error)(void *data);

    /*
     * New client session
     */
    void (*new_session)(struct tcp_socket *s_client, void *data);
};


/*
 * Socket initialization
 */
int tcp_socket_init(struct tcp_socket *restrict sock);

/**
 * Connect to other socket
 * @sock: socket struct
 * @ip: ip address of other socket
 * @port: tcp port of other socket
 *
 * Returns 0 if succeful connection
 * Returns SOCKET_ERROR if fail connection
 */
int tcp_socket_connect(struct tcp_socket *restrict sock, const char *ip, const unsigned port);

/**
 * Send data to other socket
 * @socket: socket struct
 * @data: sending data
 * @len: size of sendign data
 *
 * Returns 0 if succeful sending
 * Returns SOCKET_ERROR if fail sending
 */
int tcp_socket_send(struct tcp_socket *restrict sock, const void *data, const size_t len);

/**
 * Receive data from other socket
 * @socket: socket struct
 * @data: sending data
 * @len: size of receiving data
 *
 * Returns 0 if succeful receiving
 * Returns SOCKET_ERROR if fail receiving
 */
int tcp_socket_recv(struct tcp_socket *restrict sock, void *data, size_t len);

/**
 * Bind ip address and starting socket server
 * @sock: socket struct
 * @ip: ip address of server
 * @port: tcp port of server
 * @max_clients: maximum connected clients
 * @data: user data
 *
 * Returns 0 if succeful starting
 * Returns SOCKET_ERROR if fail binding ip address or port
 */
int tcp_socket_bind(struct tcp_socket *sock, const unsigned short port, const unsigned max_clients, void *data);

/*
 * Close connection
 */
void tcp_socket_close(struct tcp_socket *restrict sock);

/*
 * Free win32 memory
 */
void tcp_socket_quit(void);


#endif
