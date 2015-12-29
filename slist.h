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

#ifndef __SLIST_H__
#define __SLIST_H__

#include <stdio.h>


struct slist {
    /* user's data */
    void *data;

    /* next element */
    struct slist *next;
};

/**
 * Add new element in end of list
 * @dlist: single-linked list struct
 * @data: user's data
 */
struct slist *slist_append(struct slist *slist, void *data);

/**
 * Add new element in start of list
 * @dlist: single-linked list struct
 * @data: user's data
 */
struct slist *slist_prepend(struct slist *slist, void *data);

/*
 * Get size of list
 */
unsigned slist_len(struct slist *slist);

/*
 * Get element from list by number
 */
struct slist *slist_nth(struct slist *slist, unsigned n);

/*
 * Get data from list by number
 */
struct slist *slist_nth_data(struct slist *slist, unsigned n);

/*
 * Get last element from list
 */
struct slist *slist_last(struct slist *slist);

/*
 * Remove element from list
 */
struct slist *slist_remove(struct slist *slist, const void *data);

/*
 * Free memory
 */
void slist_free(struct slist *slist);

/*
 * Free list elements
 */
void slist_free_all(struct slist *slist);


#endif
