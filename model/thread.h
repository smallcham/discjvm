//
// Created by wangzhanzhi on 2020/6/26.
//

#ifndef DISCJVM_THREAD_H
#define DISCJVM_THREAD_H

#include "stack.h"
#include "class.h"
#include "../util/endian.h"

typedef void (*PopHook)(void *, void *, void *);

typedef struct {
    u4 pc;
    Stack *operand_stack;
    ClassFile *class;
    ConstantPool *constant_pool;
    MethodInfo *method;
    void *native_method;
    CodeAttribute *code_info;
    PopHook pop_hook;
    Slot *local_variables[];
} Frame;

typedef struct {
    Stack *vm_stack;
    Stack *c_stack;
} Thread;

Frame *create_vm_frame_by_method(Thread* thread, ClassFile *class, MethodInfo *method, CodeAttribute *code);

Frame *create_vm_frame_by_method_add_params(Thread* thread, ClassFile *class, Frame *frame, MethodInfo *method, CodeAttribute *code);

Frame *create_vm_frame_by_method_add_params_and_this(Thread* thread, ClassFile *class, Frame *frame, MethodInfo *method, CodeAttribute *code);

Frame *create_vm_frame_by_method_add_hook(Thread* thread, ClassFile *class, MethodInfo *method, CodeAttribute *code, PopHook hook);

Thread create_thread(int vm_stack_size, int c_stack_size);

void free_frame(Frame **frame);

void print_local_variables(Frame *frame);

#endif //DISCJVM_THREAD_H
