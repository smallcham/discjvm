//
// Created by wangzhanzhi on 2020/7/5.
//

#ifndef DISCJVM_STRING_UTIL_H
#define DISCJVM_STRING_UTIL_H
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

int str_end_with(char *source, char *pattern);

int str_start_with(char *source, char *pattern);

char *str_replace(char *source, char *pattern, char *change);

#endif //DISCJVM_STRING_UTIL_H
