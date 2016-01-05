#include <extc/tcpsocket.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>


struct user_data {
    char name[20];
    unsigned age;
};


int main()
{
    int ret_val;
    struct tcp_socket client;
    struct user_data udata;

    puts("\nStarting test");
    puts("-----------------------\n");

    strcpy(udata.name, "Serg");
    udata.age = 1;

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

    ret_val = tcp_socket_send(&client, (void *)&udata, sizeof(udata));
    if (ret_val != 0) {
        puts("[FAIL] Sending data to server.");
        tcp_socket_close(&client);
        tcp_socket_quit();
        assert(ret_val == 0);
    } else
        puts("[PASSED] Sending data to server.");

    tcp_socket_close(&client);
    tcp_socket_quit();

    puts("\n-----------------------");
    puts("Test complete. [OK]");
}
