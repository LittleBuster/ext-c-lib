#include <extc/tcpsocket.h>
#include "filetransfer.h"
#include <stdio.h>
#include <string.h>
#include <assert.h>


struct tcp_socket client;

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

static void fail_quit(int ret_val)
{
    tcp_socket_close(&client);
    tcp_socket_quit();
    assert(ret_val == 0);
}

int main()
{
    int ret_val;
    char sdata[20];
    struct transf_sig ts;

    puts("\nStarting test");
    puts("-----------------------\n");

    ret_val = tcp_socket_init(&client);
    if (ret_val != 0) {
        puts("[FAIL] Socket initialization");
        tcp_socket_quit();
        assert(ret_val == 0);
    } else
        puts("[PASSED] Socket initialization");

    ret_val = tcp_socket_connect(&client, "127.0.0.1", 5000);
    if (ret_val != 0) {
        puts("[FAIL] Connection to server.");
        tcp_socket_quit();
        assert(ret_val == 0);
    } else
        puts("[PASSED] Connection to server.");

    strcpy(sdata, "SomeData");
    ts.data = (void *)sdata;
    ts.start_transfer = &start_transfer;
    ts.progress = &progress;
    ts.end_transfer = &end_transfer;

    ret_val = file_transfer_send(&client, "file.jpg", &ts);
    switch (ret_val) {
        case 0: {
            puts("[PASSED] File sended.");
            break;
        }
        case ERR_LONG_NAME: {
            puts("[FAIL] File sending");
            puts("error: very long file name (szie: 255)");
            fail_quit(ret_val);
            break;
        }
        case ERR_EXISTS_FILE: {
            puts("[FAIL] File sending");
            puts("error: file not found");
            fail_quit(ret_val);
            break;
        }
        case ERR_SEND_INFO: {
            puts("[FAIL] File sending");
            puts("error: fail sending file information");
            fail_quit(ret_val);
            break;
        }
        case ERR_SEND_BLOCK: {
            puts("[FAIL] File sending");
            puts("error: fail sending block of file");
            fail_quit(ret_val);
            break;
        }
        case ERR_SEND_LBLOCK: {
            puts("[FAIL] File sending");
            puts("error: fail sending last block of file");
            fail_quit(ret_val);
            break;
        }
        case ERR_SEND_FILE: {
            puts("[FAIL] File sending");
            puts("error: fail sending file");
            fail_quit(ret_val);
            break;
        }
    }

    tcp_socket_close(&client);
    tcp_socket_quit();

    puts("\n-----------------------");
    puts("Test complete. [OK]");
}
