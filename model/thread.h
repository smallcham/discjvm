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
    frame->operand_stack = *(Stack*)malloc(sizeof(Stack));
    frame->method_name_index = method_name_index;
    frame->operand_stack.max_size = operand_stack_size;
    frame->operand_stack.size = 0;
    return frame;
}

Thread create_thread(int vm_stack_size, int c_stack_size)
{
    Thread thread = { 0, malloc(sizeof(Stack) * vm_stack_size), malloc(sizeof(Stack) * c_stack_size) };
    thread.vm_stack->size = 0;
    thread.vm_stack->max_size = vm_stack_size;
    thread.c_stack->size = 0;
    thread.c_stack->max_size = c_stack_size;
    return thread;
}

#endif //DISCJVM_THREAD_H
