//
// Created by wangzhanzhi on 2020/7/9.
//

#ifndef DISCJVM_BOOTSTRAP_H
#define DISCJVM_BOOTSTRAP_H

#include "../share/gc/serial/serial_heap.h"
#include "class_loader.h"
#include "opcode.h"

void init_lib(Thread *thread, SerialHeap *heap);

void start_vm(char *class_path);

#endif //DISCJVM_BOOTSTRAP_H
