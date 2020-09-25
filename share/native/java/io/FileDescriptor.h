//
// Created by wangzhanzhi on 2020/9/25.
//

#ifndef DISCJVM_FILEDESCRIPTOR_H
#define DISCJVM_FILEDESCRIPTOR_H

#include "../../../../model/thread.h"
#include "../../../../runtime/class_loader.h"
#include <fcntl.h>
#include <bits/fcntl-linux.h>

void java_io_FileDescriptor_initIDs_90V(Thread *thread, SerialHeap *heap, Frame *frame);

void java_io_FileDescriptor_getHandle_9I0J(Thread *thread, SerialHeap *heap, Frame *frame);

void java_io_FileDescriptor_getAppend_9I0Z(Thread *thread, SerialHeap *heap, Frame *frame);

#endif //DISCJVM_FILEDESCRIPTOR_H
