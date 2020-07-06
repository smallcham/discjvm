//
// Created by wangzhanzhi on 2020/7/6.
//

#ifndef DISCJVM_ZIP_ENTRY_H
#define DISCJVM_ZIP_ENTRY_H

#include "class.h"

typedef struct {
    u4 crc_32;
    u4 compressed_size;
    u4 uncompress_size;
    u2 file_name_len;
    u2 extra_len;
    u1 *file_name;
} ZipEntry;

typedef struct {
    u4 head;
    u4 magic;
    u2 version_limit;
    u2 bit_flag;
    u2 compress_method;
    u2 last_m_time;
    u2 last_m_date;
    ZipEntry entry;
} ZipFile;

#endif //DISCJVM_ZIP_ENTRY_H
