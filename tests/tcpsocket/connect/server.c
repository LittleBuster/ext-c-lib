#include <extc/tcpsocket.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>


struct tcp_socket server;


void new_session(struct tcp_socket *s_client, void *data)
{
    puts("[PASSED] New client connected.");
    puts("\n-----------------------");
    puts("Test complete. [OK]");

    tcp_socket_close(s_client);
    tcp_socket_close(&server);
    tcp_socket_quit();
    exit(0);
}

int main() {
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
    // For 1 client
    ret_val = tcp_socket_bind(&server, 5000, 1, NULL);
    if (ret_val != 0) {
        puts("[FAIL] Bind server");
        assert(ret_val == 0);
    } else
        puts("[PASSED] Bind server");

    tcp_socket_quit();
}
