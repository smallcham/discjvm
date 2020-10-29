//
// Created by wangzhanzhi on 2020/10/4.
//

#include "monitor.h"

int do_monitor_enter(Monitor *monitor, void *thread);

Monitor *create_monitor(void *owner)
{
    Monitor *monitor = malloc(sizeof(Monitor));
    pthread_mutex_t *lock = malloc(sizeof(pthread_mutex_t));
    pthread_cond_t *cond = malloc(sizeof(pthread_cond_t));
    pthread_mutex_init(lock, NULL);
    pthread_cond_init(cond, NULL);
    monitor->count = 0;
    monitor->owner = owner;
    monitor->cond = cond;
    monitor->lock = lock;
    return monitor;
}

int do_monitor_enter(Monitor *monitor, void *thread)
{
    if (monitor->count == 0) {
        if (pthread_mutex_trylock(monitor->lock) == 0) {
            if (monitor->count == 0) {
                monitor->owner = thread;
                monitor->count ++;
            }
            pthread_mutex_unlock(monitor->lock);
            return 1;
        } else {
            return 0;
        }
    }
    if (monitor->owner == thread) {
        monitor->count ++;
        return 1;
    }
    if (monitor->owner != thread) {
        return 0;
    }
    return 0;
}

void monitor_enter(Monitor *monitor, void *thread)
{
    int res = do_monitor_enter(monitor, thread);
    if (!res) {
        while (!res) {
            pthread_mutex_lock(monitor->lock);
            pthread_cond_wait(monitor->cond, monitor->lock);
            pthread_mutex_unlock(monitor->lock);
            res = do_monitor_enter(monitor, thread);
        }
    }
}

void monitor_exit(Monitor *monitor, void *thread)
{
    if (monitor->owner == thread) {
        if (--monitor->count == 0) {
            monitor->owner = NULL;
            pthread_cond_signal(monitor->cond);
        }
    }
}