#include <extc/tcpsocket.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>

int main()
{
    int ret_val;
	struct tcp_socket client;

    puts("\nStarting test");
    puts("-----------------------\n");

    ret_val = tcp_socket_init(&client);
    if (ret_val != 0) {
        puts("[FAIL] Socket initialization");
        assert(ret_val == 0);
    } else
        puts("[PASSED] Socket initialization");

    ret_val = tcp_socket_connect(&client, "127.0.0.1", 5000);
    if (ret_val != 0) {
        puts("[FAIL] Connection to server.");
        assert(ret_val == 0);
    } else
        puts("[PASSED] Connection to server.");

	tcp_socket_close(&client);
    tcp_socket_quit();

    puts("\n-----------------------");
	puts("Test complete. [OK]");
}
