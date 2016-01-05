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


#include "tcpsocket.h"
#include <stdlib.h>


struct sock_data {
    struct tcp_socket *client;
    struct tcp_socket *server;
};


void *new_client(void *data)
{
    struct sock_data *sdata = (struct sock_data *)data;

    sdata->server->new_session(sdata->client, sdata->server->data);

    tcp_socket_close(sdata->client);
    free(sdata->client);
    free(sdata);
    return NULL;
}


int tcp_socket_init(struct tcp_socket *sock)
{
#ifdef WIN32
    WSADATA wsaData;
    WORD version_wanted = MAKEWORD(1, 1);

    if (WSAStartup(version_wanted, &wsaData) != 0)
        return SOCKET_ERROR;
#endif
    sock->accept_error = NULL;
    sock->new_session = NULL;
    return 0;
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
        return SOCKET_ERROR;

    ret_val = connect(sock->s, (struct sockaddr *)&sock_addr, sizeof(sock_addr));
    if (ret_val == SOCKET_ERROR)
        return SOCKET_ERROR;
    return 0;
}

int tcp_socket_send(struct tcp_socket *sock, void *data, size_t len)
{
    int ret_val = 0;

    for (;;) {
        ret_val = send(sock->s, data, len, MSG_NOSIGNAL);
        if (ret_val == SOCKET_ERROR)
            return SOCKET_ERROR;

        if (ret_val == (int)len)
            break;
    }
    return 0;
}

int tcp_socket_recv(struct tcp_socket *sock, void *data, size_t len)
{
    size_t bytes;

    while (len) {
        bytes = recv(sock->s, data, len, MSG_NOSIGNAL|MSG_WAITALL);
        if (bytes == len)
            break;

        if ((bytes == 0) || (bytes == SOCKET_ERROR))
            return SOCKET_ERROR;

        data += bytes;
        len -= bytes;
    }
    return 0;
}

int tcp_socket_bind(struct tcp_socket *sock, unsigned short port, unsigned max_clients, void *data)
{
    int ret_val;
    SOCKET s_client;
    struct sockaddr_in sock_addr;

    sock->data = data;
    sock->s = socket(AF_INET, SOCK_STREAM, 0);
    if (sock->s == INVALID_SOCKET)
        return SOCKET_ERROR;

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
        return SOCKET_ERROR;

    ret_val = listen(sock->s, max_clients);
    if (ret_val == SOCKET_ERROR)
        return SOCKET_ERROR;

    for (;;) {
        s_client = accept(sock->s, NULL, NULL);
        if (s_client == SOCKET_ERROR) {
            if (sock->accept_error != NULL)
                sock->accept_error(sock->data);
            continue;
        }

        if (sock->new_session == NULL)
            continue;

        /* New session thread */
        if (max_clients > 1) {
            pthread_t cl_th;
            struct tcp_socket *client = (struct tcp_socket *)malloc(sizeof(client));
            struct sock_data *sdata = (struct sock_data *)malloc(sizeof(sdata));
            sdata->client = client;
            sdata->server = sock;

            client->s = s_client;
            pthread_create(&cl_th, NULL, &new_client, (void *)sdata);
            pthread_detach(cl_th);
        } else {
            struct tcp_socket client;
            client.s = s_client;
            sock->new_session(&client, sock->data);
        }
    }
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

void tcp_socket_quit(void)
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
}
