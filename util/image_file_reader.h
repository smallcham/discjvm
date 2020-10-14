//
// Created by wangzhanzhi on 2020/10/10.
//

#ifndef DISCJVM_IMAGE_FILE_READER_H
#define DISCJVM_IMAGE_FILE_READER_H

#include <stdio.h>
#include <stdlib.h>
#include "../model/base_type.h"
#include "../model/hash_map.h"

typedef struct {
    u4 magic;
    u4 version;
    u4 flags;
    u4 res_count;
    u4 table_length;
    u4 location_size;
    u4 string_size;
} ImageHeader;

typedef struct {
    char *name;
    int _use;
    long _file_size;
    ImageHeader header;
    size_t _index_size;
    u1* _index_data;
    int* _redirect_table;
    u4* _offsets_table;
    u1* _location_bytes;
    u1* _string_bytes;
} ImageFile;

ImageFile* find_image(char *name);

#endif //DISCJVM_IMAGE_FILE_READER_H
