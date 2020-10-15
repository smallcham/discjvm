//
// Created by wangzhanzhi on 2020/8/14.
//

#ifndef DISCJVM_RUNTIME_H
#define DISCJVM_RUNTIME_H

#include "../../../../model/thread.h"
#include "../../../../runtime/jvm.h"
#include <sys/sysinfo.h>

void java_lang_Runtime_registerNatives_90V(Thread *thread, SerialHeap *heap, Frame *frame);

void java_lang_Runtime_availableProcessors_90I(Thread *thread, SerialHeap *heap, Frame *frame);

#endif //DISCJVM_RUNTIME_H
