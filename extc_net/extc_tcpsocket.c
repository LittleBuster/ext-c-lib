/* EXTC Network library
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


#include "extc_tcpsocket.h"
#include <stdlib.h>


static void* tcp_socket_srv_thread(void *data)
{
    SOCKET s_client;
    struct tcp_socket *server;

    server = (struct tcp_socket *)data;

    for (;;) {
        s_client = accept(server->s, NULL, NULL);
        if (s_client == SOCKET_ERROR) {
            if (server->accept_error != NULL)
                server->accept_error();
            continue;
        }

        if (server->new_session == NULL)
            continue;

        pthread_t cl_th;
        struct tcp_socket *client = (struct tcp_socket *)malloc(sizeof(client));

        /* New session thread */
        client->s = s_client;
        pthread_create(&cl_th, NULL, server->new_session, (void *)client);
        pthread_detach(cl_th);
    }
    return NULL;
}


struct tcp_socket* tcp_socket_init(void)
{
#ifdef WIN32
    WSADATA wsaData;
    WORD version_wanted = MAKEWORD(1, 1);

    if (WSAStartup(version_wanted, &wsaData) != 0)
        return NULL;
#endif
    struct tcp_socket *sock = NULL;
    sock = (struct tcp_socket *)malloc(sizeof(sock));
    /* Init signals */
    sock->accept_error = NULL;
    sock->new_session = NULL;
    return sock;
}

int tcp_socket_connect(struct tcp_socket *sock, const char *ip, unsigned port)
{
    int ret_val;
    struct sockaddr_in sock_addr;

    memset(&sock_addr, 0x00, sizeof(sock_addr));
    sock_addr.sin_family = AF_INET;
    sock_addr.sin_addr.s_addr = inet_addr(ip);
    sock_addr.sin_port = htons(port);

    sock->s = socket(AF_INET, SOCK_STREAM, 0);
    if (sock->s == INVALID_SOCKET)
        return SOCK_ERR;

    ret_val = connect(sock->s, (struct sockaddr *)&sock_addr, sizeof(sock_addr));
    if (ret_val == SOCKET_ERROR)
        return SOCK_ERR;
    return 0;
}

int tcp_socket_send(struct tcp_socket *sock, void *data, size_t len)
{
    int ret_val = 0;

    for (;;) {
        ret_val = send(sock->s, data, len, 0);
        if (ret_val == SOCKET_ERROR)
            return SOCK_ERR;

        if (ret_val == (int)len)
            break;
    }
    return 0;
}

int tcp_socket_recv(struct tcp_socket *sock, void *data, size_t len)
{
    int ret_val;

    for (;;) {
        ret_val = recv(sock->s, data, len, 0);
        if (ret_val == SOCKET_ERROR)
            return SOCK_ERR;

        if (ret_val == (int)len)
            break;
    }
    return 0;
}

int tcp_socket_bind(struct tcp_socket *sock, unsigned port)
{
    int ret_val;
    struct sockaddr_in sock_addr;

#ifdef WIN32
    tcp_socket_init_win32();
#endif

    sock->s = socket(AF_INET, SOCK_STREAM, 0);
    if (sock->s == INVALID_SOCKET)
        return SOCK_ERR;

    memset(&sock_addr, 0, sizeof(sock_addr));
    sock_addr.sin_family = AF_INET;
    sock_addr.sin_addr.s_addr = INADDR_ANY;
    sock_addr.sin_port = htons(port);

#ifndef WIN32
    int yes = 1;
    setsockopt(sock->s, SOL_SOCKET, SO_REUSEADDR, (char*)&yes, sizeof(yes));
#endif

    ret_val = bind(sock->s, (struct sockaddr *)&sock_addr, sizeof(sock_addr));
    if (ret_val == SOCKET_ERROR)
        return SOCK_ERR;

    ret_val = listen(sock->s, 5);
    if (ret_val == SOCKET_ERROR)
        return SOCK_ERR;

    pthread_create(&sock->srv_th, NULL, &tcp_socket_srv_thread, (void *)sock);
    pthread_detach(sock->srv_th);
    return 0;
}

void tcp_socket_close(struct tcp_socket *sock)
{
    if (sock->s != INVALID_SOCKET) {
        shutdown(sock->s, 1);
#ifdef WIN32
        closesocket(sock->s);
#else
        close(sock->s);
#endif
    }
}

void tcp_socket_quit(struct tcp_socket *sock)
{
#ifdef WIN32
    if (WSACleanup() == SOCKET_ERROR) {
        if (WSAGetLastError() == WSAEINPROGRESS) {
#ifndef _WIN32_WCE
            WSACancelBlockingCall();
#endif
            WSACleanup();
        }
    }
#endif
    free(sock);
}
