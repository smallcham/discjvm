//
// Created by wangzhanzhi on 2020/8/6.
//

#ifndef DISCJVM_SYSTEM_H
#define DISCJVM_SYSTEM_H

#include "../../../../model/thread.h"
#include "../../../../runtime/class_loader.h"

void java_lang_System_registerNatives_90V(Thread *thread, SerialHeap *heap, Frame *frame);

void java_lang_System_initProperties_9Ljava_util_Properties10Ljava_util_Properties1(Thread *thread, SerialHeap *heap, Frame *frame);

void java_lang_System_arraycopy_9Ljava_lang_Object1ILjava_lang_Object1II0V(Thread *thread, SerialHeap *heap, Frame *frame);

void java_lang_System_nanoTime_90J(Thread *thread, SerialHeap *heap, Frame *frame);

void java_lang_System_setIn0_9Ljava_io_InputStream10V(Thread *thread, SerialHeap *heap, Frame *frame);

void java_lang_System_setOut0_9Ljava_io_PrintStream10V(Thread *thread, SerialHeap *heap, Frame *frame);

void java_lang_System_setErr0_9Ljava_io_PrintStream10V(Thread *thread, SerialHeap *heap, Frame *frame);

void java_lang_System_mapLibraryName_9Ljava_lang_String10Ljava_lang_String1(Thread *thread, SerialHeap *heap, Frame *frame);

#endif //DISCJVM_CLASS_H
