//
// Created by wangzhanzhi on 2020/8/13.
//

#include "ioutil.h"

pthread_mutex_t *lock;

void log_lock()
{
    if (NULL == lock) {
        lock = malloc(sizeof(pthread_mutex_t));
        pthread_mutex_init(lock, NULL);
    }
    pthread_mutex_lock(lock);
}

void log_unlock()
{
    pthread_mutex_unlock(lock);
}

void printf_debug(const char *format, ...)
{
    if (LOG_DEBUG < LOG_LEVEL) return;
    log_lock();
    va_list fs;
    va_start(fs, format);
    vfprintf(stdout, format, fs);
    va_end(fs);
    log_unlock();
}

void printf_err(const char *format, ...)
{
    if (LOG_ERROR < LOG_LEVEL) return;
    log_lock();
    va_list fs;
    fprintf(stdout, "\033[;31m");
    va_start(fs, format);
    vfprintf(stdout, format, fs);
    va_end(fs);
    fprintf(stdout, "\033[;0m\n");
    log_unlock();
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
    log_lock();
    va_list fs;
    fprintf(stdout, "\033[;32m");
    va_start(fs, format);
    vfprintf(stdout, format, fs);
    va_end(fs);
    fprintf(stdout, "\033[;0m\n");
    log_unlock();
}