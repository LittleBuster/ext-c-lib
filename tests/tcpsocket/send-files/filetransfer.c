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


int file_transfer_send(struct tcp_socket *sock, const char *fname, struct transf_sig *restrict sig)
{
    FILE *file;
    char *last_block;
    char data[512];
    int ret_val;
    size_t ret_byte;
    register unsigned long i;
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
    /* if file < 512bytes */
    if (finfo.size < 512) {
        finfo.last_block = finfo.size;
        finfo.blocks = 0;
    } else {
        finfo.last_block = finfo_buff.st_size % 512;
        finfo.blocks = (finfo_buff.st_size - finfo.last_block) / 512;
    }

    if (sig->start_transfer != NULL) {
        if (finfo.blocks > 1)
            sig->start_transfer(finfo.blocks, sig->data);
        else
            sig->start_transfer(1, sig->data);
    }

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
    if (finfo.blocks != 0) {
        for (i = 0; i < finfo.blocks; i++) {
            ret_byte = fread(data, 512, 1, file);
            if (ret_byte != 1) {
                fclose(file);
                return ERR_FILE_READ;
            }

            ret_val = tcp_socket_send(sock, (void *)data, 512);
            if (ret_val != 0) {
                fclose(file);
                return ERR_SEND_BLOCK;
            }

            if (sig->progress != NULL)
                sig->progress(sig->data);
        }
    }

    /*
     * Sending last block of file
     */
    if (finfo.last_block != 0) {
        last_block = (char *)malloc(finfo.last_block);

        ret_byte = fread(last_block, finfo.last_block, 1, file);
        if (ret_byte != 1) {
            free(last_block);
            fclose(file);
            return ERR_FILE_WRITE;
        }
        fclose(file);

        ret_val = tcp_socket_send(sock, (void *)last_block, finfo.last_block);
        if (ret_val != 0) {
            free(last_block);
            return ERR_SEND_LBLOCK;
        }
        if (sig->progress != NULL)
            sig->progress(sig->data);
        free(last_block);
    } else
        fclose(file);

    /*
     * Recv answ
     */
    ret_val = tcp_socket_recv(sock, (void *)&answ, sizeof(answ));
    if (ret_val != 0)
        return ERR_SEND_FILE;

    if (answ.code != ANSW_OK)
        return ERR_SEND_FILE;

    if (sig->end_transfer != NULL)
        sig->end_transfer(sig->data);
    return 0;
}

int file_transfer_recv(struct tcp_socket *sock, const char *path, struct transf_sig *restrict sig)
{
    FILE *file;
    char *last_block;
    char data[512];
    char file_path[512];
    int ret_val;
    size_t ret_byte;
    register unsigned long i;
    struct sock_answ answ;
    struct file_info finfo;

    if (strlen(path) > 255)
        return ERR_LONG_PATH;

    ret_val = tcp_socket_recv(sock, (void *)&finfo, sizeof(finfo));
    if (ret_val == SOCKET_ERROR)
        return ERR_RECV_INFO;

    if (sig->start_transfer != NULL) {
        if (finfo.blocks > 1)
            sig->start_transfer(finfo.blocks, sig->data);
        else
            sig->start_transfer(1, sig->data);
    }

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

    if (finfo.blocks != 0) {
        for (i = 0; i < finfo.blocks; i++) {
            ret_val = tcp_socket_recv(sock, (void *)&data, sizeof(data));
            if (ret_val == SOCKET_ERROR) {
                fclose(file);
                return ERR_RECV_BLOCK;
            }

            ret_byte = fwrite(data, 512, 1, file);
            if (ret_byte != 1) {
                fclose(file);
                return ERR_FILE_WRITE;
            }

            if (sig->progress != NULL)
                sig->progress(sig->data);
        }
    }

    if (finfo.last_block != 0) {
        last_block = (char *)malloc(finfo.last_block);

        ret_val = tcp_socket_recv(sock, (void *)last_block, finfo.last_block);
        if (ret_val == SOCKET_ERROR) {
            fclose(file);
            free(last_block);
            return ERR_RECV_LBLOCK;
        }
        ret_byte = fwrite(last_block, finfo.last_block, 1, file);
        if (ret_byte != 1) {
            free(last_block);
            fclose(file);
            return ERR_FILE_WRITE;
        }

        if (sig->progress != NULL)
            sig->progress(sig->data);

        fsync(fileno(file));
        fclose(file);
        free(last_block);
    } else {
        fsync(fileno(file));
        fclose(file);
    }

    answ.code = ANSW_OK;
    ret_val = tcp_socket_send(sock, (void *)&answ, sizeof(answ));
    if (ret_val == SOCKET_ERROR)
        return ERR_RECV_FILE;

    if (sig->end_transfer != NULL)
        sig->end_transfer(sig->data);

    return 0;
}
