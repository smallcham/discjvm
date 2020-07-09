//
// Created by wangzhanzhi on 2020/6/26.
//

#include "thread.h"

Frame *create_vm_frame(Thread* thread, ConstantPool *constant_pool, int local_variables_size, int operand_stack_size)
{
    Frame *frame = (Frame*)malloc(sizeof(Frame) + (sizeof(u4) * local_variables_size));
    frame->operand_stack = create_stack(operand_stack_size);
    frame->constant_pool = constant_pool;
    push_stack(thread->vm_stack, frame);
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
