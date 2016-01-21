/* EXTC JSON-configs loader
 *
 * Extended C-library
 *
 * Copyright (C) 2015-2016 Sergey Denisov.
 * Written by Sergey Denisov aka LittleBuster (DenisovS21@gmail.com)
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public Licence
 * as published by the Free Software Foundation; either version 3
 * of the Licence, or (at your option) any later version.
 */

#ifndef __JSON_CFG_H__
#define __JSON_CFG_H__


#include <stdio.h>

enum {
    J_STR,
    J_INT
};

struct param {
    /* param type: char* or int */
    char type;

    /* param name */
    char name[150];

    /**
     * char* or int*,
     * after using need to be freed
     */
    void *param;
};

/**
 * Loading configs from file to RAM
 * @filename: name of json configs file
 *
 * returns -1: if fail loading
 * returns 0: if succeful loading
 */
int json_configs_load(const char *filename);

/**
 * Get params from configs
 * @section: section number in mass
 * @subsection: subsection name in configs
 * @params: in/out params mass for reading
 * @sz_p: size of params mass
 *
 * returns -1: if fail reading param
 * returns 0: if succeful reading
 */
int json_configs_get(const size_t section, const char *subsection, struct param *restrict params, const size_t sz_p);

/*
 * Free memory
 */
void json_configs_free(void);


#endif
