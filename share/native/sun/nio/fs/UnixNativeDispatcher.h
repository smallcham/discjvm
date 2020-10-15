//
// Created by wangzhanzhi on 2020/10/2.
//

#ifndef DISCJVM_UNIXNATIVEDISPATCHER_H
#define DISCJVM_UNIXNATIVEDISPATCHER_H

#include "../../../../../model/thread.h"
#include "../../../../../runtime/jvm.h"
#include <sys/stat.h>

void sun_nio_fs_UnixNativeDispatcher_init_90I(Thread *thread, SerialHeap *heap, Frame *frame);

void sun_nio_fs_UnixNativeDispatcher_getcwd_90Bs(Thread *thread, SerialHeap *heap, Frame *frame);

void sun_nio_fs_UnixNativeDispatcher_stat1_9J0I(Thread *thread, SerialHeap *heap, Frame *frame);

void sun_nio_fs_UnixNativeDispatcher_open0_9JII0I(Thread *thread, SerialHeap *heap, Frame *frame);

void sun_nio_fs_UnixNativeDispatcher_stat0_9JLsun_nio_fs_UnixFileAttributes10V(Thread *thread, SerialHeap *heap, Frame *frame);

#endif //DISCJVM_UNIXNATIVEDISPATCHER_H
