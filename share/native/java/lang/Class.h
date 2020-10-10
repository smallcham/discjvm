//
// Created by wangzhanzhi on 2020/8/6.
//

#ifndef DISCJVM_JCLASS_H
#define DISCJVM_JCLASS_H

#include "../../../../model/thread.h"
#include "../../../../runtime/class_loader.h"

void java_lang_Class_registerNatives_90V(Thread *thread, SerialHeap *heap, Frame *frame);

void java_lang_Class_getPrimitiveClass_9Ljava_lang_String10Ljava_lang_Class(Thread *thread, SerialHeap *heap, Frame *frame);

void java_lang_Class_desiredAssertionStatus0_9Ljava_lang_Class10Z(Thread *thread, SerialHeap *heap, Frame *frame);

void java_lang_Class_isArray_90Z(Thread *thread, SerialHeap *heap, Frame *frame);

void java_lang_Class_initClassName_90Ljava_lang_String1(Thread *thread, SerialHeap *heap, Frame *frame);

void java_lang_Class_forName0_9Ljava_lang_String1ZLjava_lang_ClassLoader1Ljava_lang_Class10Ljava_lang_Class1(Thread *thread, SerialHeap *heap, Frame *frame);

void java_lang_Class_isPrimitive_90Z(Thread *thread, SerialHeap *heap, Frame *frame);

#endif //DISCJVM_CLASS_H
