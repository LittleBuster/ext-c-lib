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


enum send_errors {
    ERR_LONG_NAME = -100,
    ERR_EXISTS_FILE = -101,
    ERR_SEND_INFO = -102,
    ERR_SEND_BLOCK = -103,
    ERR_SEND_LBLOCK = -104,
    ERR_FILE_READ = -105,
    ERR_SEND_FILE = -106
};

enum recv_errors {
    ERR_LONG_PATH = -200,
    ERR_RECV_INFO = -201,
    ERR_OPEN_FILE = -202,
    ERR_RECV_BLOCK = -203,
    ERR_RECV_LBLOCK = -204,
    ERR_FILE_WRITE = -205,
    ERR_RECV_FILE = -206
};

enum codes {
    ANSW_OK = 100,
    ANSW_FAIL = -200
};


struct transf_sig {
    /*
     * User data
     */
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
};


/**
 * Sending file to other tcp socket
 * @sock: tcp socket structure
 * @fname: filename of sending file
 * @sig: transfer signals structure (if needed)
 *
 * returns 0 if succeful sending
 * returns ERR_LONG_NAME if fname more then 255 chars
 * returns ERR_EXISTS_FILE if file not found
 * returns ERR_SEND_INFO if fail sending info about file to server
 * returns ERR_SEND_BLOCK if fail sending block of file
 * returns ERR_SEND_LBLOCK if fail sending last block of file
 * returns ERR_SEND_FILE if fail sending confirmation about sending file
 */
int file_transfer_send(struct tcp_socket *sock, const char *fname, struct transf_sig *restrict sig);

/**
 * Receiving file from other tcp socket
 * @sock: tcp socket structure
 * @path: filepath of receiving file
 * @sig: transfer signals structure (if needed)
 *
 * returns 0 if succeful receiving
 * returns ERR_LONG_PATH if filepath more then 255 chars
 * returns ERR_OPEN_FILE if file can not create
 * returns ERR_RECV_INFO if fail receiving info about file from client
 * returns ERR_RECV_BLOCK if fail receiving block of file
 * returns ERR_RECV_LBLOCK if fail receiving last block of file
 * returns ERR_RECV_FILE if fail sending confirmation about receiving file
 */
int file_transfer_recv(struct tcp_socket *sock, const char *path, struct transf_sig *restrict sig);


#endif
