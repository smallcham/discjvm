//
// Created by wangzhanzhi on 2020/6/26.
//

#ifndef DISCJVM_THREAD_H
#define DISCJVM_THREAD_H

#include "stack.h"
#include "class.h"

typedef struct {
    Stack operand_stack;
    ConstantPool *constant_pool;
    u4 local_variables[];
} Frame;

typedef struct {
    u4 pc;
    Stack *vm_stack;
    Stack *c_stack;
} Thread;

Frame *create_vm_frame(Thread* thread, ConstantPool *constant_pool, int local_variables_size, int operand_stack_size);

Thread create_thread(int vm_stack_size, int c_stack_size);

#endif //DISCJVM_THREAD_H
