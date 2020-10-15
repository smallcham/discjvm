//
// Created by wangzhanzhi on 2020/9/25.
//

#ifndef DISCJVM_UNIXFILESYSTEM_H
#define DISCJVM_UNIXFILESYSTEM_H

#include "../../../../model/thread.h"
#include "../../../../runtime/jvm.h"

void java_io_UnixFileSystem_initIDs_90V(Thread *thread, SerialHeap *heap, Frame *frame);

void java_io_UnixFileSystem_getBooleanAttributes0_9Ljava_io_File10I(Thread *thread, SerialHeap *heap, Frame *frame);

void java_io_UnixFileSystem_canonicalize0_9Ljava_lang_String10Ljava_lang_String1(Thread *thread, SerialHeap *heap, Frame *frame);

#endif //DISCJVM_UNIXFILESYSTEM_H
