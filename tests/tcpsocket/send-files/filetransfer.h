/* File Transfer module
 *
 * Copyright (C) 2015-2016 Sergey Denisov.
 * Written by Sergey Denisov aka LittleBuster (DenisovS21@gmail.com)
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public Licence
 * as published by the Free Software Foundation; either version 3
 * of the Licence, or (at your option) any later version.
 */

#ifndef __FILE_TRANSFER_H__
#define __FILE_TRANSFER_H__

#include <extc/tcpsocket.h>

enum errors {
    ERR_LONG_NAME = 100,
    ERR_EXISTS_FILE = 101,
    ERR_SEND_INFO = 102,
    ERR_SEND_BLOCK = 103,
    ERR_SEND_LBLOCK = 104,
    ERR_SEND_FILE = 105
};

enum codes {
    ANSW_OK = 100,
    ANSW_FAIL = 200
};


struct transf_sig {
    /* User data */
    void *data;

    /**
     * Called after the start of transfer file
     * @blocks: file blocks count
     * @data: user data
     */
    void (*start_transfer)(unsigned long blocks, void *data);

    /**
     * Called after the end of transfer file
     * @data: user data
     */
    void (*end_transfer)(void *data);

    /**
     * Called in the process of transfer file
     * @data: user data
     */
    void (*progress)(void *data);

    /**
     * Called after error
     * @data: user data
     */
    void (*error)(void *data);
};


/*
 * Signals initialization
 */
void file_transfer_init(struct transf_sig *sig);

/**
 * Sending file to other tcp socket
 * @sock: tcp socket structure
 * @fname: filename of sending file
 *
 * returns :
 */
int file_transfer_send(struct tcp_socket *sock, const char *fname, struct transf_sig *sig);

/**
 * Receiving file from other tcp socket
 * @sock: tcp socket structure
 * @fname: filename of receiving file
 * @sig: signals structure
 *
 * returns :
 */
int file_transfer_recv(struct tcp_socket *sock, const char *fname, struct transf_sig *sig);


#endif
