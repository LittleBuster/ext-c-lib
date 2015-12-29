/* EXTC JSON-configs loader
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

#include "json-cfg.h"

#include <sys/stat.h>
#include <stdlib.h>
#include <string.h>
#include <jansson.h>


static struct {
    /* configs file body */
    char *data;

    /* configs tree */
    json_t *root;

} json_cfg = {
    .data = NULL,
    .root = NULL,
};

int json_configs_load(const char *filename)
{
    FILE *file;
    struct stat buff;
    json_error_t error;

    /* reading configs file */
    file = fopen(filename, "r");
    if (file == NULL)
        return -1;
    /* get file size */
    fstat(fileno(file), &buff);
    json_cfg.data = (char *)malloc(buff.st_size);

    if (fread(json_cfg.data, buff.st_size, 1, file)) {
    }
    fclose(file);

    /* load configs in parser */
    json_cfg.root = json_loads(json_cfg.data, 0, &error);
    if (!json_is_array(json_cfg.root)) {
        json_decref(json_cfg.root);
        return -1;
    }
    return 0;
}

int json_configs_get(size_t section, const char *subsection, struct param *params, size_t sz_p)
{
    json_t *jdata, *jobj;

    jdata = json_array_get(json_cfg.root, section);
    jobj = json_object_get(jdata, subsection);

    for (size_t i = 0; i < sz_p; i++) {
        json_t *jsub_obj = json_object_get(jobj, params[i].name);

        /* reding strig param from configs */
        if (params[i].type == J_STR) {
            char *str = (char *)malloc(255);
            strcpy(str, json_string_value(jsub_obj));
            if (str == NULL)
                return -1;
            params[i].param = (void *)str;
        }

        /* reding integer param from configs */
        if (params[i].type == J_INT) {
            int *num = (int *)malloc(sizeof(int));
            *num = json_integer_value(jsub_obj);
            if (num == NULL)
                return -1;
            params[i].param = (void *)num;
        }

        json_decref(jsub_obj);
    }
    json_decref(jobj);
    json_decref(jdata);
    return 0;
}

void json_configs_free(void)
{
    json_decref(json_cfg.root);
    free(json_cfg.data);
}
