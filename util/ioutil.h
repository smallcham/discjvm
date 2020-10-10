//
// Created by wangzhanzhi on 2020/8/13.
//

#ifndef DISCJVM_IOUTIL_H
#define DISCJVM_IOUTIL_H

#include <stdio.h>
#include <zconf.h>
#include <pthread.h>
#include <stdlib.h>

#define LOG_DEBUG   0
#define LOG_SUCCESS 0
#define LOG_WARN    1
#define LOG_INFO    2
#define LOG_ERROR   4

int LOG_LEVEL;

void printf_debug(const char *format, ...);

void printf_err(const char *format, ...);

void printf_warn(const char *format, ...);

void printf_succ(const char *format, ...);

#endif //DISCJVM_IOUTIL_H
