/* Single-linked list
 *
 * Copyright (C) 2015 Sergey Denisov.
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


struct slist *slist_append(struct slist *slist, void *data)
{
    struct slist *new_list;
    struct slist *last;

    new_list = (struct slist *)malloc(sizeof(struct slist));
    new_list->data = data;
    new_list->next = NULL;

    if (slist) {
        last = slist_last(slist);
        last->next = new_list;
        return slist;
    }
    else
        return new_list;
}

struct slist *slist_prepend(struct slist *slist, void *data)
{
    struct slist *new_list;

    new_list = (struct slist *)malloc(sizeof(struct slist));
    new_list->data = data;
    new_list->next = slist;

    return new_list;
}

struct slist *slist_last(struct slist *slist)
{
    if (slist)
        while (slist->next)
            slist = slist->next;
    return slist;
}

unsigned slist_len(struct slist *slist)
{
    unsigned len;

    len = 0;
    while (slist) {
        len++;
        slist = slist->next;
    }
    return len;
}

struct slist *slist_nth(struct slist *slist, unsigned n)
{
    while (n-- > 0 && slist)
        slist = slist->next;

    return slist;
}

struct slist *slist_nth_data(struct slist *slist, unsigned n)
{
    while (n-- > 0 && slist)
        slist = slist->next;

    return slist ? slist->data : NULL;
}

struct slist *slist_remove(struct slist *slist, const void *data)
{
    struct slist *tmp, *prev = NULL;

    tmp = slist;
    while (tmp) {
        if (tmp->data == data) {
            if (prev)
                prev->next = tmp->next;
            else
                slist = tmp->next;
            free(tmp);
            break;
        }
        prev = tmp;
        tmp = prev->next;
    }
    return slist;
}

void slist_free(struct slist *slist)
{
    free(slist);
}

void slist_free_all(struct slist *slist)
{
    struct slist *tmp;

    if (!slist)
        return;

    while (slist) {
        tmp = slist;
        slist = slist->next;
        free(tmp);
    }
    free(slist);
}
