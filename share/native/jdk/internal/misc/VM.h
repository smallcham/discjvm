//
// Created by wangzhanzhi on 2020/8/30.
//

#ifndef DISCJVM_VM_H
#define DISCJVM_VM_H

#include "../../../../../model/thread.h"
#include "../../../../../runtime/class_loader.h"

void jdk_internal_misc_VM_initialize_90V(Thread *thread, SerialHeap *heap, Frame *frame);

void jdk_internal_misc_VM_initializeFromArchive_9Ljava_lang_Class10V(Thread *thread, SerialHeap *heap, Frame *frame);

#endif //DISCJVM_VM_H
