#include <extc/stimer.h>
#include <stdio.h>
#include <string.h>

void timer_callback(void *data)
{
    printf("[PASSED] Show some data: %s\n", (char *)data);
}

int main(int argc, char const *argv[]) {
    int ret_val;
    struct stimer tmr;
    char txt[22];

    puts("\nStarting test");
    puts("-----------------------\n");

    stimer_init(&tmr);
    strcpy(txt, "my some text");
    ret_val = stimer_create(&tmr, 1, &timer_callback, (void *)txt);
    if (ret_val == -1)
        puts("[FAIL] Timer creation");
    return 0;
}
