//
// Created by wangzhanzhi on 2020/8/6.
//

#ifndef DISCJVM_OBJECT_H
#define DISCJVM_OBJECT_H

#include "../../../../model/thread.h"
#include "../../../../runtime/jvm.h"

void java_lang_Object_registerNatives_90V(Thread *thread, SerialHeap *heap, Frame *frame);

void java_lang_Object_getClass_90Ljava_lang_Class(Thread *thread, SerialHeap *heap, Frame *frame);

void java_lang_Object_hashCode_90I(Thread *thread, SerialHeap *heap, Frame *frame);

void java_lang_Object_notifyAll_90V(Thread *thread, SerialHeap *heap, Frame *frame);

void java_lang_Object_clone_90Ljava_lang_Object1(Thread *thread, SerialHeap *heap, Frame *frame);

void java_lang_Object_wait_9J0V(Thread *thread, SerialHeap *heap, Frame *frame);

#endif //DISCJVM_OBJECT_H
