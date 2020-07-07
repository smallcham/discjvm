//
// Created by wangzhanzhi on 2020/7/5.
//

#ifndef DISCJVM_STRING_UTIL_H
#define DISCJVM_STRING_UTIL_H

#include "string.h"

int end_with(char *source, char *pattern)
{
    unsigned long source_len = strlen(source);
    unsigned long pattern_len = strlen(pattern);
    if (source_len < pattern_len) return 0;
    unsigned long k = source_len - 1;
    int count = 0;
    for (unsigned long i = (pattern_len - 1); i >= 0; i--, k-- )
    {
        if (source[k] != pattern[i]) return 0;
        count ++;
    }
    return count == pattern_len ? 1 : 0;
}

int start_with(char *source, char *pattern)
{
    unsigned long source_len = strlen(source);
    unsigned long pattern_len = strlen(pattern);
    if (source_len < pattern_len) return 0;
    int count = 0;
    for (unsigned long i = 0; i >= (pattern_len - 1); i++ )
    {
        if (source[i] != pattern[i]) return 0;
        count ++;
    }
    return count == pattern_len ? 1 : 0;
}

#endif //DISCJVM_STRING_UTIL_H
