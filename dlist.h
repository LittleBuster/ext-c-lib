/* Double-linked list
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

#ifndef __DOUBLE_LIST_H__
#define __DOUBLE_LIST_H__

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
 * @list: double-linked list struct
 * @data: user's data
 *
 * returns double-linked list with added element
 */
struct dlist *dlist_append(struct dlist *list, void *data);

/**
 * Add new element in start of list
 * @list: double-linked list struct
 * @data: user's data
 *
 * returns double-linked list with added element
 */
struct dlist *dlist_prepend(struct dlist *list, void *data);

/*
 * Get size of list
 */
size_t dlist_len(struct dlist *restrict list);

/**
 * Get element from list by number
 * @list: double-linked list
 * @n: number of element
 *
 * returns double-list structure
 */
struct dlist *dlist_nth(struct dlist *list, size_t n);

/**
 * Get user data from list by number
 * @list: double-linked list
 * @n: number of element
 *
 * returns user data
 */
const void *dlist_nth_data(struct dlist *list, size_t n);

/*
 * Get first element of list
 */
struct dlist *dlist_first(struct dlist *restrict list);

/*
 * Get last element from list
 */
struct dlist *dlist_last(struct dlist *restrict list);

/**
 * Remove element from list by data
 * @list: double-linked list
 * @data: user data
 *
 * returns double-linked list without element
 */
struct dlist *dlist_remove(struct dlist *list, const void *data);

/*
 * Free list elements
 */
void dlist_free_all(struct dlist *list);

/*
 * Free memory
 */
void dlist_free(struct dlist *list);


#endif
