//
// Created by wangzhanzhi on 2020/8/13.
//

#ifndef DISCJVM_UNSAFE_H
#define DISCJVM_UNSAFE_H

#include "stddef.h"
#include "../../../../../model/thread.h"
#include "../../../../../runtime/class_loader.h"

void jdk_internal_misc_Unsafe_registerNatives_90V(Thread *thread, SerialHeap *heap, Frame *frame);

void jdk_internal_misc_Unsafe_arrayBaseOffset0_9java_lang_Class10I(Thread *thread, SerialHeap *heap, Frame *frame);

void jdk_internal_misc_Unsafe_arrayIndexScale0_9Ljava_lang_Class10I(Thread *thread, SerialHeap *heap, Frame *frame);

void jdk_internal_misc_Unsafe_addressSize0_90I(Thread *thread, SerialHeap *heap, Frame *frame);

void jdk_internal_misc_Unsafe_isBigEndian0_90Z(Thread *thread, SerialHeap *heap, Frame *frame);

void jdk_internal_misc_Unsafe_unalignedAccess0_90Z(Thread *thread, SerialHeap *heap, Frame *frame);

void jdk_internal_misc_Unsafe_objectFieldOffset1_9Ljava_lang_Class1Ljava_lang_String10J(Thread *thread, SerialHeap *heap, Frame *frame);

void jdk_internal_misc_Unsafe_storeFence_90V(Thread *thread, SerialHeap *heap, Frame *frame);

void jdk_internal_misc_Unsafe_compareAndSetInt_9Ljava_lang_Object1JII0Z(Thread *thread, SerialHeap *heap, Frame *frame);

void jdk_internal_misc_Unsafe_compareAndSetObject_9Ljava_lang_Object1JLjava_lang_Object1Ljava_lang_Object10Z(Thread *thread, SerialHeap *heap, Frame *frame);

void jdk_internal_misc_Unsafe_compareAndSetLong_9Ljava_lang_Object1JJJ0Z(Thread *thread, SerialHeap *heap, Frame *frame);

void jdk_internal_misc_Unsafe_getObjectVolatile_9Ljava_lang_Object1J0Ljava_lang_Object1(Thread *thread, SerialHeap *heap, Frame *frame);

void jdk_internal_misc_Unsafe_putObjectVolatile_9Ljava_lang_Object1JLjava_lang_Object10V(Thread *thread, SerialHeap *heap, Frame *frame);

void jdk_internal_misc_Unsafe_getIntVolatile_9Ljava_lang_Object1J0I(Thread *thread, SerialHeap *heap, Frame *frame);

void jdk_internal_misc_Unsafe_ensureClassInitialized0_9Ljava_lang_Class10V(Thread *thread, SerialHeap *heap, Frame *frame);

void jdk_internal_misc_Unsafe_allocateMemory0_9J0J(Thread *thread, SerialHeap *heap, Frame *frame);

void jdk_internal_misc_Unsafe_getObject_9Ljava_lang_Object1J0Ljava_lang_Object1(Thread *thread, SerialHeap *heap, Frame *frame);

void jdk_internal_misc_Unsafe_putObject_9Ljava_lang_Object1JLjava_lang_Object10V(Thread *thread, SerialHeap *heap, Frame *frame);

void jdk_internal_misc_Unsafe_copyMemory0_9Ljava_lang_Object1JLjava_lang_Object1JJ0V(Thread *thread, SerialHeap *heap, Frame *frame);

void jdk_internal_misc_Unsafe_putByte_9Ljava_lang_Object1JB0V(Thread *thread, SerialHeap *heap, Frame *frame);

void jdk_internal_misc_Unsafe_getInt_9Ljava_lang_Object1J0I(Thread *thread, SerialHeap *heap, Frame *frame);

void jdk_internal_misc_Unsafe_getByte_9Ljava_lang_Object1J0B(Thread *thread, SerialHeap *heap, Frame *frame);

#endif //DISCJVM_UNSAFE_H
