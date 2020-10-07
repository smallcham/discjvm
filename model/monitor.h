//
// Created by wangzhanzhi on 2020/10/4.
//

#ifndef DISCJVM_MONITOR_H
#define DISCJVM_MONITOR_H

#include "class.h"
#include <pthread.h>
#include "../util/ioutil.h"

Monitor *create_monitor(void *owner);
void monitor_enter(Monitor *monitor, void *thread);
void monitor_exit(Monitor *monitor, void *thread);

#endif //DISCJVM_MONITOR_H
