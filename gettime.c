/* Get Time
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

#include <time.h>
#include <stdio.h>
#include <string.h>
#include "gettime.h"


void get_time_str(char *time_str)
{
    time_t t = time(NULL);
    struct tm *timeinfo;

    timeinfo = localtime (&t);
    strftime(time_str, 15, "%T", timeinfo);
}

void get_date_str(char *date_str)
{
    time_t t = time(NULL);
    struct tm *timeinfo;

    timeinfo = localtime (&t);
    strftime(date_str, 15, "%F", timeinfo);
}

void get_datetime_str(char *date_time_str)
{
    char time_str[15];
    char date_str[15];

    time_t t = time(NULL);
    struct tm *timeinfo;

    timeinfo = localtime (&t);
    strftime(date_str, 15, "%F", timeinfo);
    strftime(time_str, 15, "%T", timeinfo);

    strcpy(date_time_str, date_str);
    strcat(date_time_str, " ");
    strcat(date_time_str, time_str);
}
