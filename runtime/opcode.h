//
// Created by wangzhanzhi on 2020/6/25.
//

#ifndef DISCJVM_OPCODE_H
#define DISCJVM_OPCODE_H

#include "../model/stack.h"
#include "../model/thread.h"
#include "../runtime/class_loader.h"
#include "../share/gc/serial/serial_heap.h"

typedef void (*Operator)(SerialHeap *heap, Thread *, Frame *);

void init_instructions();

void invoke_method(Thread thread, SerialHeap *heap);

#endif //DISCJVM_OPCODE_H
