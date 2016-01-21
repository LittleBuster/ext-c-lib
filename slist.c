/* Single-linked list
 *
 * Extended C-library
 *
 * Copyright (C) 2015-2016 Sergey Denisov.
 * Written by Peter Mattis, Spencer Kimball and Josh MacDonald Copyright (C) 1995-1997
 * Rewritten by Sergey Denisov aka LittleBuster (DenisovS21@gmail.com) 2015
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public Licence
 * as published by the Free Software Foundation; either version 3
 * of the Licence, or (at your option) any later version.
 */

#include "slist.h"
#include <stdlib.h>


struct slist *slist_append(struct slist *list, void *data)
{
    struct slist *new_list;
    struct slist *last;

    new_list = (struct slist *)malloc(sizeof(new_list));
    new_list->data = data;
    new_list->next = NULL;

    if (list) {
        last = slist_last(list);
        last->next = new_list;
        return list;
    }
    else
        return new_list;
}

struct slist *slist_prepend(struct slist *list, void *data)
{
    struct slist *new_list;

    new_list = (struct slist *)malloc(sizeof(new_list));
    new_list->data = data;
    new_list->next = list;

    return new_list;
}

struct slist *slist_last(struct slist *restrict list)
{
    if (list)
        while (list->next)
            list = list->next;
    return list;
}

size_t slist_len(struct slist *restrict list)
{
    size_t len = 0;

    while (list) {
        len++;
        list = list->next;
    }
    return len;
}

struct slist *slist_nth(struct slist *restrict list, size_t n)
{
    while (n-- > 0 && list)
        list = list->next;

    return list;
}

const void *slist_nth_data(struct slist *list, size_t n)
{
    while (n-- > 0 && list)
        list = list->next;

    return list ? list->data : NULL;
}

struct slist *slist_remove(struct slist *list, const void *data)
{
    struct slist *tmp, *prev = NULL;

    tmp = list;
    while (tmp) {
        if (tmp->data == data) {
            if (prev)
                prev->next = tmp->next;
            else
                list = tmp->next;
            free(tmp);
            break;
        }
        prev = tmp;
        tmp = prev->next;
    }
    return list;
}

void slist_free_all(struct slist *list)
{
    struct slist *tmp;

    if (!list)
        return;

    while (list) {
        tmp = list;
        list = list->next;
        free(tmp);
    }
}

void slist_free(struct slist *list)
{
    free(list);
}
