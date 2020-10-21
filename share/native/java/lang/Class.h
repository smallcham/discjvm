//
// Created by wangzhanzhi on 2020/8/6.
//

#ifndef DISCJVM_JCLASS_H
#define DISCJVM_JCLASS_H

#include "../../../../model/thread.h"
#include "../../../../runtime/jvm.h"

void java_lang_Class_registerNatives_90V(Thread *thread, SerialHeap *heap, Frame *frame);

void java_lang_Class_getPrimitiveClass_9Ljava_lang_String10Ljava_lang_Class(Thread *thread, SerialHeap *heap, Frame *frame);

void java_lang_Class_desiredAssertionStatus0_9Ljava_lang_Class10Z(Thread *thread, SerialHeap *heap, Frame *frame);

void java_lang_Class_isArray_90Z(Thread *thread, SerialHeap *heap, Frame *frame);

void java_lang_Class_initClassName_90Ljava_lang_String1(Thread *thread, SerialHeap *heap, Frame *frame);

void java_lang_Class_forName0_9Ljava_lang_String1ZLjava_lang_ClassLoader1Ljava_lang_Class10Ljava_lang_Class1(Thread *thread, SerialHeap *heap, Frame *frame);

void java_lang_Class_isPrimitive_90Z(Thread *thread, SerialHeap *heap, Frame *frame);

void java_lang_Class_getDeclaredMethods0_9Z0sLjava_lang_reflect_Method1(Thread *thread, SerialHeap *heap, Frame *frame);

void java_lang_Class_getSuperclass_90Ljava_lang_Class1(Thread *thread, SerialHeap *heap, Frame *frame);

void java_lang_Class_getInterfaces0_90sLjava_lang_Class1(Thread *thread, SerialHeap *heap, Frame *frame);

void java_lang_Class_getConstantPool_90Ljdk_internal_reflect_ConstantPool1(Thread *thread, SerialHeap *heap, Frame *frame);

void java_lang_Class_isAssignableFrom_9Ljava_lang_Class10Z(Thread *thread, SerialHeap *heap, Frame *frame);

void java_lang_Class_isInterface_90Z(Thread *thread, SerialHeap *heap, Frame *frame);

void java_lang_Class_getEnclosingMethod0_90sLjava_lang_Object1(Thread *thread, SerialHeap *heap, Frame *frame);

void java_lang_Class_getDeclaringClass0_90Ljava_lang_Class1(Thread *thread, SerialHeap *heap, Frame *frame);

#endif //DISCJVM_CLASS_H
