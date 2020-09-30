//
// Created by wangzhanzhi on 2020/8/13.
//

#include "ioutil.h"

void printf_debug(const char *format, ...)
{
    if (LOG_DEBUG < LOG_LEVEL) return;
    va_list fs;
    va_start(fs, format);
    vfprintf(stdout, format, fs);
    va_end(fs);
}

void printf_err(const char *format, ...)
{
    if (LOG_ERROR < LOG_LEVEL) return;
    va_list fs;
    fprintf(stdout, "\033[;31m");
    va_start(fs, format);
    vfprintf(stdout, format, fs);
    va_end(fs);
    fprintf(stdout, "\033[;0m\n");
}

void printf_warn(const char *format, ...)
{
    if (LOG_WARN < LOG_LEVEL) return;
    va_list fs;
    fprintf(stdout, "\033[;33m");
    va_start(fs, format);
    vfprintf(stdout, format, fs);
    va_end(fs);
    fprintf(stdout, "\033[;0m\n");
}

void printf_succ(const char *format, ...)
{
    if (LOG_SUCCESS < LOG_LEVEL) return;
    va_list fs;
    fprintf(stdout, "\033[;32m");
    va_start(fs, format);
    vfprintf(stdout, format, fs);
    va_end(fs);
    fprintf(stdout, "\033[;0m\n");
}