//
// Created by wangzhanzhi on 2020/8/13.
//

#include "ioutil.h"

void printf_err(const char *format, ...)
{
    va_list fs;
    fprintf(stdout, "\033[;31m");
    va_start(fs, format);
    vfprintf(stdout, format, fs);
    va_end(fs);
    fprintf(stdout, "\033[;0m\n");
}
