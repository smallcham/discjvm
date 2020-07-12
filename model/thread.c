//
// Created by wangzhanzhi on 2020/6/26.
//

#include "thread.h"

Frame *create_vm_frame_by_method(Thread* thread, ConstantPool *constant_pool, MethodInfo *method, CodeAttribute *code)
{
    Frame *frame = (Frame*)malloc(sizeof(Frame) + (sizeof(u4) * code->max_locals));
    frame->operand_stack = create_stack(code->max_stack);
    frame->constant_pool = constant_pool;
    frame->method = method;
    frame->code_info = code;
    frame->pc = 0;
    push_stack(thread->vm_stack, frame);
    return frame;
}

Thread create_thread(int vm_stack_size, int c_stack_size)
{
    int len = sizeof(Stack);
    Thread thread = { malloc(len), malloc(len) };
    thread.vm_stack = create_pstack(vm_stack_size);
    thread.c_stack = create_pstack(c_stack_size);
    return thread;
}
