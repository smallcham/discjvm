//
// Created by wangzhanzhi on 2020/7/6.
//

#ifndef DISCJVM_JMOD_H
#define DISCJVM_JMOD_H

#include <stdio.h>
#include <stdlib.h>
#include "../model/class.h"
#include "zip.h"

u1 *load_from_jmod(char *name)
{
    char *full_name = malloc(strlen(name) + 8);
    sprintf(full_name, "classes/%s", name);

    zip_error_t err;
    char *file_path = "/usr/lib/jvm/java-1.11.0-openjdk-amd64/jmods/java.base.jmod";
    FILE *fp = fopen(file_path, "rb");
    fseek(fp, 0, SEEK_END);
    long f_size = ftell(fp);
    fclose(fp);
    int offset = 4;
    zip_error_t error;
    zip_source_t *source = zip_source_file_create(file_path, offset, f_size - offset, &error);
    zip_t *z = zip_open_from_source(source, 0, &err);

    //Search for the file of given name
    struct zip_stat st;
    zip_stat_init(&st);
    zip_stat(z, full_name, 0, &st);

    //Alloc memory for its uncompressed contents
    u1 *contents = malloc(st.size);

    //Read the compressed file
    zip_file_t *f = zip_fopen(z, full_name, 0);
    zip_fread(f, contents, st.size);
    zip_fclose(f);

    //And close the archive
    zip_close(z);
    return contents;
}

#endif //DISCJVM_JMOD_H
