//
// Created by wangzhanzhi on 2020/8/6.
//

#ifndef DISCJVM_JCLASS_H
#define DISCJVM_JCLASS_H

#include "../../../../model/thread.h"
#include "../../../../runtime/class_loader.h"

void java_lang_Class_registerNatives_90V(Thread *thread, SerialHeap *heap, Frame *frame);

void java_lang_Class_getPrimitiveClass_9Ljava_lang_String10Ljava_lang_Class(Thread *thread, SerialHeap *heap, Frame *frame);

#endif //DISCJVM_CLASS_H
