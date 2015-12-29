/* Double-linked list
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

#ifndef __DLIST_H__
#define __DLIST_H__

#include <stdio.h>


struct dlist {
    /* user's data */
    void *data;

    /* next element */
    struct dlist *next;

    /* prev. element */
    struct dlist *prev;
};

/**
 * Add new element in end of list
 * @dlist: double-linked list struct
 * @data: user's data
 */
struct dlist *dlist_append(struct dlist *dlist, void *data);

/**
 * Add new element in start of list
 * @dlist: double-linked list struct
 * @data: user's data
 */
struct dlist *dlist_prepend(struct dlist *dlist, void *data);

/*
 * Get size of list
 */
unsigned dlist_len(struct dlist *dlist);

/*
 * Get element from list by number
 */
struct dlist *dlist_nth(struct dlist *dlist, unsigned n);

/*
 * Get data from list by number
 */
struct dlist *dlist_nth_data(struct dlist *dlist, unsigned n);

/*
 * First element from list
 */
struct dlist *dlist_first(struct dlist *dlist);

/*
 * Last element from list
 */
struct dlist *dlist_last(struct dlist *dlist);

/*
 * Remove element from list
 */
struct dlist *dlist_remove(struct dlist *dlist, const void *data);

/*
 * Free memory
 */
void dlist_free(struct dlist *dlist);

/*
 * Free all elements
 */
void dlist_free_all(struct dlist *dlist);


#endif
