//
// Created by wangzhanzhi on 2020/6/26.
//

#ifndef DISCJVM_THREAD_H
#define DISCJVM_THREAD_H

#include "stack.h"
#include "class.h"
#include "../util/endian.h"

typedef void (*PopHook)(void *, void *, void *, void *);

typedef struct {
    u4 pc;
    long count;
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
    Object *jthread;
} Thread;

Frame *create_vm_frame_by_method(Thread* thread, ClassFile *class, MethodInfo *method, CodeAttribute *code);

Frame *create_vm_frame_by_method_with_push(Thread* thread, ClassFile *class, MethodInfo *method, CodeAttribute *code);

Frame *create_vm_frame_by_method_add_params(Thread* thread, ClassFile *class, Frame *frame, MethodInfo *method, CodeAttribute *code);

Frame *create_vm_frame_by_method_add_params_plus1(Thread* thread, ClassFile *class, Frame *frame, MethodInfo *method, CodeAttribute *code);

Frame *create_vm_frame_by_method_add_hook(Thread* thread, ClassFile *class, MethodInfo *method, CodeAttribute *code, PopHook hook);

Thread create_thread(int vm_stack_size, int c_stack_size);

void free_frame(Frame **frame);

void print_local_variables(Frame *frame);

u4 get_localvar(Frame *frame, int index);

Slot *get_slot_localvar(Frame *frame, int index);

void set_long_localvar(Frame *frame, int index, u4 higher, u4 lower);

void set_localvar_with_slot(Frame *frame, int index, Slot *value);

void set_long_localvar_with_slot(Frame *frame, int index, Slot *higher, Slot *lower);

void set_localvar(Frame *frame, int index, u4 value);

u8 get_long_localvar(Frame *frame, int index);

void *get_ref_localvar(Frame *frame, int index);

void **get_ref_addr_localvar(Frame *frame, int index);

void *get_localvar_this(Frame *frame);

void *set_ref_localvar(Frame *frame, int index, void *object_value);

void add_params(Frame *frame, Frame *new_frame, MethodInfo *method);

void add_params_and_plus1(Frame *frame, Frame *new_frame, MethodInfo *method);

#endif //DISCJVM_THREAD_H
