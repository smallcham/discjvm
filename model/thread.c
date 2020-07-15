//
// Created by wangzhanzhi on 2020/6/26.
//

#include "thread.h"

Frame *create_vm_frame_by_method(Thread* thread, ClassFile *class, MethodInfo *method, CodeAttribute *code)
{
    Frame *frame = (Frame*)malloc(sizeof(Frame) + (sizeof(u4) * code->max_locals));
    frame->operand_stack = create_stack(code->max_stack);
    frame->constant_pool = class->constant_pool;
    frame->method = method;
    frame->code_info = code;
    frame->pop_hook = NULL;
    frame->class = class;
    frame->pc = 0;
    push_stack(thread->vm_stack, frame);
    return frame;
}

Frame *create_vm_frame_by_method_add_hook(Thread* thread, ClassFile *class, MethodInfo *method, CodeAttribute *code, PopHook hook)
{
    Frame *frame = create_vm_frame_by_method(thread, class, method, code);
    frame->pop_hook = hook;
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
