/* Double linked list
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

#include "dlist.h"
#include <stdlib.h>


struct dlist *dlist_append(struct dlist *dlist, void *data)
{
    struct dlist *new_list;
    struct dlist *last;

    new_list = (struct dlist *)malloc(sizeof(struct dlist));
    new_list->data = data;
    new_list->next = NULL;

    if (dlist) {
        last = dlist_last(dlist);
        last->next = new_list;
        new_list->prev = last;
        return dlist;
    } else {
        new_list->prev = NULL;
        return new_list;
    }
}

struct dlist *dlist_prepend(struct dlist *dlist, void *data)
{
    struct dlist *new_list;

    new_list = (struct dlist *)malloc(sizeof(struct dlist));
    new_list->data = data;
    new_list->next = dlist;

    if (dlist) {
        new_list->prev = dlist->prev;
        if (dlist->prev)
            dlist->prev->next = new_list;
        dlist->prev = new_list;
    } else {
        new_list->prev = NULL;
    }
    return new_list;
}

unsigned dlist_len(struct dlist *dlist)
{
    unsigned len;

    len = 0;
    while (dlist) {
        len++;
        dlist = dlist->next;
    }
    return len;
}

struct dlist *dlist_nth(struct dlist *dlist, unsigned n)
{
    while ((n-- > 0) && dlist)
        dlist = dlist->next;
    return dlist;
}

struct dlist *dlist_nth_data(struct dlist *dlist, unsigned n)
{
    while ((n-- > 0) && dlist)
        dlist = dlist->next;
    return dlist ? dlist->data : NULL;
}

struct dlist *dlist_first(struct dlist *dlist)
{
    if (dlist)
        while (dlist->prev)
            dlist = dlist->prev;
    return dlist;
}

struct dlist *dlist_last(struct dlist *dlist)
{
    if (dlist)
        while (dlist->next)
            dlist = dlist->next;
    return dlist;
}

static inline struct dlist *_dlist_remove_link(struct dlist *dlist,
                                                            struct dlist *link)
{
    if (link == NULL)
        return dlist;

    if (link->prev) {
        if (link->prev->next == link)
            link->prev->next = link->next;
        else
            puts("Corrupted double-linked list");
    }

    if (link->next) {
        if (link->next->prev == link)
            link->next->prev = link->prev;
        else
            puts("Corrupted double-linked list");
    }

    if (link == dlist)
        dlist = dlist->next;

    link->next = NULL;
    link->prev = NULL;

    return dlist;
}

struct dlist *dlist_remove(struct dlist *dlist, const void *data)
{
    struct dlist *tmp;

    tmp = dlist;
    while (dlist)
        if (tmp->data != data)
            tmp = tmp->next;
        else {
            dlist = _dlist_remove_link(dlist, tmp);
            free(tmp);
            break;
        }
    return dlist;
}

void dlist_free(struct dlist *dlist)
{
    free(dlist);
}

void dlist_free_all(struct dlist *dlist)
{
    struct dlist *tmp;

    if (!dlist)
        return;

    while (dlist) {
        tmp = dlist;
        dlist = dlist->next;
        free(tmp);
    }
    free(dlist);
}
