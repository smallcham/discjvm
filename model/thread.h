//
// Created by wangzhanzhi on 2020/6/26.
//

#ifndef DISCJVM_THREAD_H
#define DISCJVM_THREAD_H

#include "base_type.h"
#include "data_struct.h"

typedef struct {
    Stack operand_stack;
    u2 method_name_index;
    u4 local_variables[];
} Frame;

typedef struct {
    u4 pc;
    Stack *vm_stack;
    Stack *c_stack;
} Thread;

Frame *create_vm_frame(u2 method_name_index, int local_variables_size, int operand_stack_size)
{
    Frame *frame = (Frame*)malloc(sizeof(Frame) + (sizeof(u4) * local_variables_size));
    frame->operand_stack = create_stack(operand_stack_size);
    frame->method_name_index = method_name_index;
    return frame;
}

Thread create_thread(int vm_stack_size, int c_stack_size)
{
    int len = sizeof(Stack);
    Thread thread = { 0, malloc(len), malloc(len) };
    thread.vm_stack = create_pstack(vm_stack_size);
    thread.c_stack = create_pstack(c_stack_size);
    return thread;
}

#endif //DISCJVM_THREAD_H
