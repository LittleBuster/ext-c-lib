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

#ifndef __SINGLE_LIST_H__
#define __SINGLE_LIST_H__

#include <stdio.h>


struct slist {
    /* user's data */
    void *data;

    /* next element */
    struct slist *next;
};

/**
 * Add new element in end of list
 * @list: single-linked list struct
 * @data: user's data
 *
 * returns single-linked list with added element
 */
struct slist *slist_append(struct slist *list, void *data);

/**
 * Add new element in start of list
 * @list: single-linked list struct
 * @data: user's data
 *
 * returns single-linked list with added element
 */
struct slist *slist_prepend(struct slist *list, void *data);

/*
 * Get size of list
 */
size_t slist_len(struct slist *restrict list);

/**
 * Get element from list by number
 * @list: single-linked list
 * @n: number of element
 *
 * returns single-linked list structure
 */
struct slist *slist_nth(struct slist *restrict list, size_t n);

/**
 * Get user data from list by number
 * @list: single-linked list
 * @n: number of element
 *
 * returns user data
 */
const void *slist_nth_data(struct slist *list, size_t n);

/*
 * Get last element from list
 */
struct slist *slist_last(struct slist *restrict list);

/**
 * Remove element from list by data
 * @list: single-linked list
 * @data: user data
 *
 * returns single-linked list without element
 */
struct slist *slist_remove(struct slist *list, const void *data);

/*
 * Free list elements
 */
void slist_free_all(struct slist *list);

/*
 * Free memory
 */
void slist_free(struct slist *list);


#endif
