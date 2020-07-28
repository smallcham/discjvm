//
// Created by wangzhanzhi on 2020/6/26.
//

#include "thread.h"

void add_params(Frame *frame, Frame *new_frame, CodeAttribute *code);

Frame *create_vm_frame_by_method(Thread* thread, ClassFile *class, MethodInfo *method, CodeAttribute *code)
{
    if (NULL == code) return NULL;
    Frame *frame = (Frame*)malloc(sizeof(Frame) + (sizeof(Slot) * code->max_locals));
    for (int i = 0; i < code->max_locals; i++) {
        frame->local_variables[i] = malloc(sizeof(Slot));
        frame->local_variables[i]->value = 0;
        frame->local_variables[i]->object_value = NULL;
    }
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

Frame *create_vm_frame_by_method_add_params(Thread* thread, ClassFile *class, Frame *frame, MethodInfo *method, CONSTANT_Utf8_info method_desc_info, CodeAttribute *code)
{
    Frame *new_frame = create_vm_frame_by_method(thread, class, method, code);
    if (NULL != new_frame) {
        for (int i = 0; i < code->attributes_count; i++) {
            CONSTANT_Utf8_info info = *(CONSTANT_Utf8_info*)class->constant_pool[code->attributes[i].attribute_name_index].info;
            printf("%s**************\n", info.bytes);
        }
        add_params(frame, new_frame, code);
    }
    return new_frame;
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
    thread.vm_stack = create_stack(vm_stack_size);
    thread.c_stack = create_stack(c_stack_size);
    return thread;
}

void add_params(Frame *frame, Frame *new_frame, CodeAttribute *code)
{

//    for (int i = 0; i < code->attributes_count; i++) {
//        CONSTANT_Utf8_info info = *(CONSTANT_Utf8_info*)new_frame->constant_pool[code->attributes[i].attribute_name_index].info;
//        if (strcmp(info.bytes, "LocalVariableTable") == 0) {
//            LocalVariableTableAttribute *local_variable_table = (LocalVariableTableAttribute*)malloc(sizeof(LocalVariableTableAttribute));
//            local_variable_table->attribute_name_index = *(u2*)code->attributes[i].info;
//            local_variable_table->attribute_length = *(u4*)code->attributes[i].info;
//            local_variable_table->local_variable_table_length = *(u2*)code->attributes[i].info;
//        }
//    }
//    int k = 0;
//    for (int i = 0; i < method_desc_info.length; i++) {
//        if (method_desc_info.bytes[i] == '(') {
//            for (int j = i + 1; j < method_desc_info.length; j++) {
//                if (method_desc_info.bytes[j] == ')') {
//                    return;
//                }
//                if (method_desc_info.bytes[j] == 'B' ||
//                    method_desc_info.bytes[j] == 'C' ||
//                    method_desc_info.bytes[j] == 'I' ||
//                    method_desc_info.bytes[j] == 'S' ||
//                    method_desc_info.bytes[j] == 'Z') {
//                    //Int
//                    new_frame->local_variables[k]->value = pop_int(frame->operand_stack);
//                }
//                else if (method_desc_info.bytes[j] == 'F') {
//                    //Float
//                    new_frame->local_variables[k]->value = pop_float(frame->operand_stack);
//                }
//                else if (method_desc_info.bytes[j] == 'D' ||
//                         method_desc_info.bytes[j] == 'J') {
//                    //Long
//                    new_frame->local_variables[k]->value = pop_int(frame->operand_stack);
//                    new_frame->local_variables[++k]->value = pop_int(frame->operand_stack);
//                }
//                else if (method_desc_info.bytes[j] == 'L' ||
//                         method_desc_info.bytes[j] == '[') {
//                    //Object | Array
//                    new_frame->local_variables[k]->object_value = pop_stack(frame->operand_stack);
//                }
//                k++;
//            }
//        }
//    }
}