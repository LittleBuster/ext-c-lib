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

#include <sys/time.h>
#include <sys/types.h>
#include <unistd.h>
#include <errno.h>
#include "stimer.h"


void stimer_init(struct stimer *tmr)
{
    tmr->is_work = 0;
    tmr->interval = 0;
    tmr->data = NULL;
    tmr->timer_handle = NULL;
}

int stimer_create(struct stimer *tmr, unsigned interval, void (*tmr_handle)(void*), void *data)
{
    if ((interval ==  0) || (tmr_handle == NULL))
        return -1;

    tmr->timer_handle = tmr_handle;
    tmr->interval = interval;
    tmr->data = data;
    tmr->is_work = 1;

    while(tmr->is_work) {
        struct timeval tv = {tmr->interval, 0};
        if (select(0, NULL, NULL, NULL, &tv) == -1)
            if (EINTR == errno)
                continue;
        tmr->timer_handle(tmr->data);
    }
    return 0;
}

void stimer_stop(struct stimer *tmr)
{
    tmr->is_work = 0;
}
