//
// Created by wangzhanzhi on 2020/7/5.
//

#include "string_util.h"

int str_end_with(char *source, char *pattern)
{
    unsigned long source_len = strlen(source);
    unsigned long pattern_len = strlen(pattern);
    if (source_len < pattern_len) return 0;
    unsigned long k = source_len - 1;
    int count = 0;
    int idx = (int)(pattern_len - 1);
    for (int i = idx; i >= 0; i--, k-- )
    {
        if (source[k] != pattern[i]) return 0;
        count ++;
    }
    return count == pattern_len ? 1 : 0;
}

int str_start_with(char *source, char *pattern)
{
    unsigned long source_len = strlen(source);
    unsigned long pattern_len = strlen(pattern);
    if (source_len < pattern_len) return 0;
    int count = 0;
    for (unsigned long i = 0; i < (pattern_len); i++ )
    {
        if (source[i] != pattern[i]) return 0;
        count ++;
    }
    return count == pattern_len ? 1 : 0;
}

char *str_replace(char *source, char *pattern, char *change)
{
//    unsigned long source_len = strlen(source);
//    unsigned long pattern_len = strlen(pattern);
//    if (source_len < pattern_len) return source;
//
//    char *res = malloc(1);
//    res[0] = '\0';
//    unsigned long change_len = strlen(change);
//
//    for (int i = 0; i < source_len; i++) {
//        int matched = 1;
//        for (int j = i; j < pattern_len; j++) {
//            if (source[j] == pattern[j]) {
//                matched = j;
//                continue;
//            }
//            matched = 0;
//            break;
//        }
//        if (matched != 0) {
//            char *tmp = malloc(strlen(res) + strlen(change) + 1);
//            sprintf(tmp, "%s%s", res, change);
//            i = i + change_len;
//            free(res);
//            res = tmp;
//        } else {
//            char *tmp = malloc(strlen(res) + 1);
//            sprintf(tmp, "%s%c", res, source[i]);
//            free(res);
//            res = tmp;
//        }
//    }
//    return res;
}