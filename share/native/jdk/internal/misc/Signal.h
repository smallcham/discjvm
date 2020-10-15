//
// Created by wangzhanzhi on 2020/9/25.
//

#ifndef DISCJVM_SIGNAL_H
#define DISCJVM_SIGNAL_H

#include "../../../../../model/thread.h"
#include "../../../../../runtime/jvm.h"

void jdk_internal_misc_Signal_findSignal0_9Ljava_lang_String10I(Thread *thread, SerialHeap *heap, Frame *frame);

void jdk_internal_misc_Signal_handle0_9IJ0J(Thread *thread, SerialHeap *heap, Frame *frame);

#endif //DISCJVM_SIGNAL_H
