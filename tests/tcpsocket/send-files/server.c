#include <extc/tcpsocket.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include "filetransfer.h"


struct tcp_socket server;


void start_transfer(unsigned long blocks, void *data)
{
    puts("[PASSED] Start file transfer");
}

void progress(void *data)
{
    printf("[PASSED] Progress (%s)", (char *)data);
}

void end_transfer(void *data)
{
    puts("[PASSED] End file transfer");
}

static void fail_quit(struct tcp_socket *client, int ret_val)
{
    tcp_socket_close(client);
    tcp_socket_quit();
    assert(ret_val == 0);
}

void new_session(struct tcp_socket *s_client, void *data)
{
    int ret_val;
    char sdata[255];
    struct transf_sig ts;

    strcpy(sdata, "SomeData");
    ts.data = (void *)sdata;
    ts.start_transfer = &start_transfer;
    ts.progress = &progress;
    ts.end_transfer = &end_transfer;

    ret_val = file_transfer_recv(s_client, "./out/", &ts);
    switch (ret_val) {
        case 0: {
            puts("[PASSED] File sended.");
            break;
        }
        case ERR_LONG_PATH: {
            puts("[FAIL] File receiving");
            puts("error: very long file path (szie: 255)");
            fail_quit(s_client, ret_val);
            break;
        }
        case ERR_OPEN_FILE: {
            puts("[FAIL] File receiving");
            puts("error: file can not create");
            fail_quit(s_client, ret_val);
            break;
        }
        case ERR_RECV_INFO: {
            puts("[FAIL] File receiving");
            puts("error: fail receiving file information");
            fail_quit(s_client, ret_val);
            break;
        }
        case ERR_RECV_BLOCK: {
            puts("[FAIL] File receiving");
            puts("error: fail receiving block of file");
            fail_quit(s_client, ret_val);
            break;
        }
        case ERR_RECV_LBLOCK: {
            puts("[FAIL] File receiving");
            puts("error: fail receiving last block of file");
            fail_quit(s_client, ret_val);
            break;
        }
        case ERR_SEND_FILE: {
            puts("[FAIL] File receiving");
            puts("error: fail receiving file");
            fail_quit(s_client, ret_val);
            break;
        }
    }

    puts("\n-----------------------");
    puts("Test complete. [OK]");

    tcp_socket_close(s_client);
    tcp_socket_close(&server);
    tcp_socket_quit();
    exit(0);
}

int main()
{
    int ret_val;

    puts("\nStarting test");
    puts("-----------------------\n");

    ret_val = tcp_socket_init(&server);
    if (ret_val != 0) {
        puts("[FAIL] Socket initialization");
        assert(ret_val == 0);
    } else
        puts("[PASSED] Socket initialization");

    server.new_session = &new_session;
    ret_val = tcp_socket_bind(&server, 5000, 10, NULL);
    if (ret_val != 0) {
        puts("[FAIL] Bind server");
        tcp_socket_quit();
        assert(ret_val == 0);
    } else
        puts("[PASSED] Bind server");

    tcp_socket_quit();
}
