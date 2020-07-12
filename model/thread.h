//
// Created by wangzhanzhi on 2020/6/26.
//

#ifndef DISCJVM_THREAD_H
#define DISCJVM_THREAD_H

#include "stack.h"
#include "class.h"

typedef struct {
    u4 pc;
    Stack operand_stack;
    ConstantPool *constant_pool;
    MethodInfo *method;
    CodeAttribute *code_info;
    u4 local_variables[];
} Frame;

typedef struct {
    Stack *vm_stack;
    Stack *c_stack;
} Thread;

Frame *create_vm_frame_by_method(Thread* thread, ConstantPool *constant_pool, MethodInfo *method, CodeAttribute *code);

Thread create_thread(int vm_stack_size, int c_stack_size);

#endif //DISCJVM_THREAD_H
