#include <extc/slist.h>
#include <extc/dlist.h>
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>


int main(int argc, char const *argv[])
{
    struct slist *list;
    struct slist *s;

    puts("\nStarting test");
    puts("-----------------------\n");

    list = slist_append(list, "Serg");
    list = slist_append(list, "Andrew");

    if (list == NULL) {
        puts("[FAIL] Add elements.");
        assert(list != NULL);
    } else
        puts("[PASSED] Add elements.");

    puts("List:");
    for (s = list; s != NULL; s = s->next) {
        puts(s->data);
        if (!strcmp(s->data, "Andrew"))
            list = slist_remove(list, s->data);
    }

    puts("\nNew list:");
    for (s = list; s != NULL; s = s->next)
        puts(s->data);

    slist_free_all(list);

    puts("\n-----------------------");
	puts("Test complete. [OK]");
}
