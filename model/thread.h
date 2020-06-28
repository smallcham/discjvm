//
// Created by wangzhanzhi on 2020/6/26.
//

#ifndef DISCJVM_THREAD_H
#define DISCJVM_THREAD_H

#include "base_type.h"
#include "data_struct.h"

typedef struct {
    u4 value;
} LocalVariable;

typedef struct {
    Stack operand_stack;
    u2 method_name_index;
    LocalVariable local_variables[];
} Frame;

typedef struct {
    u4 pc;
    Stack *vm_stack;
    Stack *c_stack;
} Thread;

void create_vm_frame(Thread *thread, u2 method_name_index, int local_variables_size, int operand_stack_size)
{
    Frame frame = *(Frame*)malloc(sizeof(Frame) + (sizeof(LocalVariable) * local_variables_size));
    frame.operand_stack = *(Stack*)malloc(sizeof(Stack));
    frame.method_name_index = method_name_index;
    frame.operand_stack.max_size = operand_stack_size;
    frame.operand_stack.size = 0;
    push(thread->vm_stack, &frame);
}

Thread create_thread(int vm_stack_size, int c_stack_size)
{
    Thread thread = { 0, malloc(sizeof(Stack) * vm_stack_size), malloc(sizeof(Stack) * c_stack_size) };
    return thread;
}

#endif //DISCJVM_THREAD_H
