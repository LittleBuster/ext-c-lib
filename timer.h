/* EXTC Timer module
 *
 * Extended C-library
 *
 * Copyright (C) 2015 Sergey Denisov.
 * Written by Sergey Denisov aka LittleBuster (DenisovS21@gmail.com)
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public Licence
 * as published by the Free Software Foundation; either version 3
 * of the Licence, or (at your option) any later version.
 */

struct timer {
    /* time settings */
    unsigned is_work;
    unsigned interval;

    /* data for timer handle */
    void *data;

    /* timer's callback */
    void (*timer_handle)(void *);
};


/*
 * Timer initialization
 */
void timer_init(struct timer *tmr);

/**
 * Start timer
 * @tmr: timer struct
 * @interval: interval in seconds
 * @tmr_handle: callback function pointer
 * @data: user data for callbasck function
 *
 * returns -1: if interval == 0 or timer handle == NULL
 */
int timer_create(struct timer *tmr, unsigned interval, void (*tmr_handle)(void*), void *data);

/*
 * Stop timer cycle
 */
void timer_stop(struct timer *tmr);