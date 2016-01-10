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

#ifndef __GET_TIME_H__
#define __GET_TIME_H__

/*
 * Get now time string
 */
void get_time_str(char *time_str);

/*
 * Get now date string
 */
void get_date_str(char *date_str);

/*
 * Get now date + time string (Database format)
 */
void get_datetime_str(char *date_time_str);


#endif
