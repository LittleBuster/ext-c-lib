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

#include "filetransfer.h"
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>


struct file_info {
    char filename[255];
    long unsigned int size;
    long unsigned int blocks;
    unsigned last_block;
};

struct sock_answ {
    uint8_t code;
};


void file_transfer_init(struct transf_sig *sig)
{
    sig->data = NULL;
    sig->start_transfer = NULL;
    sig->end_transfer = NULL;
    sig->progress = NULL;
    sig->error = NULL;
}

int file_transfer_send(struct tcp_socket *sock, const char *fname, struct transf_sig *sig)
{
    FILE *file;
    char *last_block;
    char data[512];
    int ret_val;
    unsigned long int i;
    struct stat finfo_buff;
    struct file_info finfo;
    struct sock_answ answ;

    if (strlen(fname) > 255)
        return ERR_LONG_NAME;
    strncpy(finfo.filename, fname, 255);

    file = fopen(fname, "rb");
    if (file == NULL)
        return ERR_EXISTS_FILE;
    fstat(fileno(file), &finfo_buff);
    finfo.size = finfo_buff.st_size;
    finfo.last_block = finfo_buff.st_size % 512;
    finfo.blocks = (finfo_buff.st_size - finfo.last_block) / 512;

    if (sig != NULL)
        if (sig->start_transfer != NULL)
            sig->start_transfer(finfo.blocks, sig->data);

    /*
     * Sending file info to server and checking answ
     */
    ret_val = tcp_socket_send(sock, (void *)&finfo, sizeof(finfo));
    if (ret_val == SOCKET_ERROR) {
        fclose(file);
        return ERR_SEND_INFO;
    }

    ret_val = tcp_socket_recv(sock, (void *)&answ, sizeof(answ));
    if (ret_val == SOCKET_ERROR) {
        fclose(file);
        return ERR_SEND_INFO;
    }

    if (answ.code != ANSW_OK) {
        fclose(file);
        return ERR_SEND_INFO;
    }

    /*
     * Sending each block of file
     */
    for (i = 0; i < finfo.blocks; i++) {
        fread(data, 512, 1, file);

        ret_val = tcp_socket_send(sock, (void *)data, 512);
        if (ret_val != 0) {
            fclose(file);
            return ERR_SEND_BLOCK;
        }

        if (sig != NULL)
            if (sig->progress != NULL)
                sig->progress(sig->data);
    }

    /*
     * Sending last block of file
     */
    last_block = (char *)malloc(finfo.last_block);
    fread(last_block, finfo.last_block, 1, file);
    fclose(file);

    ret_val = tcp_socket_send(sock, (void *)last_block, finfo.last_block);
    if (ret_val != 0) {
        free(last_block);
        return ERR_SEND_LBLOCK;
    }
    free(last_block);

    /*
     * Recv answ
     */
    ret_val = tcp_socket_recv(sock, (void *)&answ, sizeof(answ));
    if (ret_val != 0)
        return ERR_SEND_FILE;

    if (answ.code != ANSW_OK)
        return ERR_SEND_FILE;

    if (sig != NULL)
        if (sig->end_transfer != NULL)
            sig->end_transfer(sig->data);
    return 0;
}

int file_transfer_recv(struct tcp_socket *sock, const char *path, struct transf_sig *sig)
{
    FILE *file;
    char *last_block;
    char data[512];
    char file_path[512];
    int ret_val;
    unsigned long int i;
    struct sock_answ answ;
    struct file_info finfo;

    if (strlen(path) > 255)
        return ERR_LONG_PATH;

    ret_val = tcp_socket_recv(sock, (void *)&finfo, sizeof(finfo));
    if (ret_val == SOCKET_ERROR)
        return ERR_RECV_INFO;

    if (sig != NULL)
        if (sig->start_transfer != NULL)
            sig->start_transfer(finfo.blocks, sig->data);

    strcpy(file_path, path);
    strcat(file_path, finfo.filename);

    file = fopen(file_path, "wb");
    if (file == NULL)
        return ERR_OPEN_FILE;

    answ.code = ANSW_OK;
    ret_val = tcp_socket_send(sock, (void *)&answ, sizeof(answ));
    if (ret_val == SOCKET_ERROR) {
        fclose(file);
        return ERR_RECV_INFO;
    }

    for (i = 0; i < finfo.blocks; i++) {
        ret_val = tcp_socket_recv(sock, (void *)&data, sizeof(data));
        if (ret_val == SOCKET_ERROR) {
            fclose(file);
            return ERR_RECV_BLOCK;
        }

        fwrite(data, 512, 1, file);

        if (sig != NULL)
            if (sig->progress != NULL)
                sig->progress(sig->data);
    }

    if (finfo.last_block == 0) {
        fclose(file);

        answ.code = ANSW_OK;
        ret_val = tcp_socket_send(sock, (void *)&answ, sizeof(answ));
        if (ret_val == SOCKET_ERROR)
            return ERR_RECV_FILE;
        else
            return 0;
    }

    last_block = (char *)malloc(finfo.last_block);

    ret_val = tcp_socket_recv(sock, (void *)last_block, finfo.last_block);
    if (ret_val == SOCKET_ERROR) {
        fclose(file);
        free(last_block);
        return ERR_RECV_LBLOCK;
    }
    fclose(file);
    free(last_block);

    answ.code = ANSW_OK;
    ret_val = tcp_socket_send(sock, (void *)&answ, sizeof(answ));
    if (ret_val == SOCKET_ERROR)
        return ERR_RECV_FILE;

    if (sig != NULL)
        if (sig->end_transfer != NULL)
            sig->end_transfer(sig->data);

    return 0;
}
