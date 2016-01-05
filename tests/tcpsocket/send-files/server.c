#include <extc/tcpsocket.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>


struct user_data {
    char name[20];
    unsigned age;
};


struct tcp_socket server;


void new_session(struct tcp_socket *s_client, void *data)
{
    int ret_val;
    struct user_data udata;

    ret_val = tcp_socket_recv(s_client, &udata, sizeof(udata));
    if (ret_val != 0) {
        puts("[FAIL] Receiving data");
        tcp_socket_close(&server);
        tcp_socket_quit();
        assert(ret_val == 0);
    } else
        puts("[PASSED] Receiving data");

    if ((!strcmp(udata.name, "Serg")) && (udata.age == 1)) {
        puts("[PASSED] Veryfing data");
    } else {
        puts("[FAIL] Veryfing data");
        tcp_socket_close(&server);
        tcp_socket_quit();
        exit(0);
    }

    puts("\n-----------------------");
    puts("Test complete. [OK]");

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
