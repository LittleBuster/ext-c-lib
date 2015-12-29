#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <extc/json-cfg.h>


int main(int argc, char const *argv[]) {
    int ret_val;
    struct param params[2];

    puts("\nStarting test");
    puts("-----------------------\n");

    ret_val = json_configs_load("my.json");
    if (ret_val == -1) {
        puts("[FAIL] Loading configs file");
        assert(ret_val == 0);
    } else
        puts("[PASSED] Loading configs file");

    params[0].type = J_STR;
    strcpy(params[0].name, "Name");

    params[1].type = J_INT;
    strcpy(params[1].name, "Delay");

    json_configs_get(0, "Timer", params, 2);

    if (strcmp((char *)params[0].param, "System")) {
        puts("[FAIL] Name string param read");
        assert(ret_val == 0);
    } else
        puts("[PASSED] Name string param read");

    if (*(int *)params[1].param != 22) {
        puts("[FAIL] Delay integer param read");
        assert(ret_val == 0);
    } else
        puts("[PASSED] Delay integer param read");

    free(params[0].param);
    free(params[1].param);
    json_configs_free();

    puts("\n-----------------------");
	puts("Test complete. [OK]");

    return 0;
}
