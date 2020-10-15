//
// Created by wangzhanzhi on 2020/8/13.
//

#ifndef DISCJVM_CLASSLOADER_H
#define DISCJVM_CLASSLOADER_H

#include "../../../../model/thread.h"
#include "../../../../runtime/jvm.h"
#include <dlfcn.h>

void java_lang_ClassLoader_registerNatives_90V(Thread *thread, SerialHeap *heap, Frame *frame);

void java_lang_ClassLoader_findBuiltinLib_9Ljava_lang_String10Ljava_lang_String1(Thread *thread, SerialHeap *heap, Frame *frame);

void java_lang_ClassLoader$NativeLibrary_load0_9Ljava_lang_String1Z0Z(Thread *thread, SerialHeap *heap, Frame *frame);

#endif //DISCJVM_CLASSLOADER_H
