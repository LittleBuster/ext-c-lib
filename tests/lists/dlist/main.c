#include <extc/slist.h>
#include <extc/dlist.h>
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>


struct data_t {
    char name[100];
    char surname[100];
    int age;
};

int main(int argc, char const *argv[])
{
    struct dlist *list;
    struct dlist *k;

    puts("\nStarting test");
    puts("-----------------------\n");

    for (size_t i = 0; i < 3; i++) {
        struct data_t *data = (struct data_t *)malloc(sizeof(data));
        strcpy(data->name, "alex");
        strcpy(data->surname, "soll");
        data->age = i;
        list = dlist_append(list, data);
    }

    if (list == NULL) {
        puts("[FAIL] Elements added.");
        assert(list != NULL);
    }

    puts("List:");
    for (k = list; k != NULL; k = k->next) {
        struct data_t *sdata = k->data;
        printf("%d\n", sdata->age);

        if (sdata->age == 1) {
            list = dlist_remove(list, sdata);
            free(sdata);
            puts("[PASSED] Freed.");
        }
    }

    puts("\nNew list:");
    puts("List:");
    for (k = list; k != NULL; k = k->next) {
        struct data_t *sdata2 = k->data;
        printf("%d\n", sdata2->age);
    }

    for (k = list; k != NULL; k = k->next)
        free(k->data);

    dlist_free_all(list);

    puts("\n-----------------------");
	puts("Test complete. [OK]");
}
