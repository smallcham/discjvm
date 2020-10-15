//
// Created by wangzhanzhi on 2020/8/6.
//

#ifndef DISCJVM_JTHREAD_H
#define DISCJVM_JTHREAD_H

#include "../../../../model/thread.h"
#include "../../../../runtime/jvm.h"
#include <pthread.h>

void java_lang_Thread_registerNatives_90V(Thread *thread, SerialHeap *heap, Frame *frame);

void java_lang_Thread_currentThread_90Ljava_lang_Thread1(Thread *thread, SerialHeap *heap, Frame *frame);

void java_lang_Thread_setPriority0_9I0V(Thread *thread, SerialHeap *heap, Frame *frame);

void java_lang_Thread_isAlive_90Z(Thread *thread, SerialHeap *heap, Frame *frame);

void java_lang_Thread_start0_90V(Thread *thread, SerialHeap *heap, Frame *frame);

#endif //DISCJVM_CLASS_H
