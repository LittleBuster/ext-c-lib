/* Double linked list
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

#include "dlist.h"
#include <stdlib.h>


static inline struct dlist *_dlist_remove_link(struct dlist *list, struct dlist *link)
{
    if (link == NULL)
        return list;

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

    if (link == list)
        list = list->next;

    link->next = NULL;
    link->prev = NULL;

    return list;
}

struct dlist *dlist_append(struct dlist *list, void *data)
{
    struct dlist *new_list;
    struct dlist *last;

    new_list = (struct dlist *)malloc(sizeof(new_list));
    new_list->data = data;
    new_list->next = NULL;

    if (list) {
        last = dlist_last(list);
        last->next = new_list;
        new_list->prev = last;
        return list;
    } else {
        new_list->prev = NULL;
        return new_list;
    }
}

struct dlist *dlist_prepend(struct dlist *list, void *data)
{
    struct dlist *new_list;

    new_list = (struct dlist *)malloc(sizeof(new_list));
    new_list->data = data;
    new_list->next = list;

    if (list) {
        new_list->prev = list->prev;
        if (list->prev)
            list->prev->next = new_list;
        list->prev = new_list;
    } else
        new_list->prev = NULL;
    return new_list;
}

size_t dlist_len(struct dlist *restrict list)
{
    size_t len = 0;

    while (list) {
        len++;
        list = list->next;
    }
    return len;
}

struct dlist *dlist_nth(struct dlist *list, size_t n)
{
    while ((n-- > 0) && list)
        list = list->next;
    return list;
}

void *dlist_nth_data(struct dlist *list, size_t n)
{
    while ((n-- > 0) && list)
        list = list->next;
    return list ? list->data : NULL;
}

struct dlist *dlist_first(struct dlist *restrict list)
{
    if (list)
        while (list->prev)
            list = list->prev;
    return list;
}

struct dlist *dlist_last(struct dlist *restrict list)
{
    if (list)
        while (list->next)
            list = list->next;
    return list;
}

struct dlist *dlist_remove(struct dlist *list, const void *data)
{
    struct dlist *tmp;

    tmp = list;
    while (list)
        if (tmp->data != data)
            tmp = tmp->next;
        else {
            list = _dlist_remove_link(list, tmp);
            free(tmp);
            break;
        }
    return list;
}

void dlist_free_all(struct dlist *list)
{
    struct dlist *tmp;

    if (!list)
        return;

    while (list) {
        tmp = list;
        list = list->next;
        free(tmp);
    }
    free(list);
}

void dlist_free(struct dlist *list)
{
    free(list);
}
