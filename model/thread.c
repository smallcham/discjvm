//
// Created by wangzhanzhi on 2020/6/26.
//

#include "thread.h"

void add_params(Frame *frame, Frame *new_frame, MethodInfo *method);

void add_params_and_this(Frame *frame, Frame *new_frame, MethodInfo *method);

void free_frame(Frame **frame)
{
//    free_stack(&(*frame)->operand_stack);
    (*frame)->operand_stack = NULL;
//    free((*frame)->code_info->code);
//    free((*frame)->code_info->attributes->info);
//    free((*frame)->code_info->attributes);
//    free((*frame)->code_info);
    (*frame)->code_info = NULL;
    (*frame)->method = NULL;
    (*frame)->class = NULL;
    (*frame)->constant_pool = NULL;
    free(*frame);
    *frame = NULL;
}

Frame *create_vm_frame_by_method(Thread* thread, ClassFile *class, MethodInfo *method, CodeAttribute *code)
{
    if (NULL == code) return NULL;
    Frame *frame = (Frame*)malloc(sizeof(Frame) + (sizeof(Slot) * code->max_locals));
    for (int i = 0; i < code->max_locals; i++) {
        frame->local_variables[i] = create_slot();
//        frame->local_variables[i] = malloc(sizeof(Slot));
//        frame->local_variables[i]->value = 0;
//        frame->local_variables[i]->object_value = NULL;
    }
    frame->operand_stack = create_stack(code->max_stack);
    frame->constant_pool = class->constant_pool;
    frame->method = method;
    frame->code_info = code;
    frame->pop_hook = NULL;
    frame->class = class;
    frame->pc = 0;
    push_stack(thread->vm_stack, frame);
//    printf("[INVOKE] %s - %s.%s\n", frame->class->class_name, frame->method->name, frame->method->desc);
    return frame;
}

Frame *create_vm_frame_by_method_add_params(Thread* thread, ClassFile *class, Frame *frame, MethodInfo *method, CodeAttribute *code)
{
    Frame *new_frame = create_vm_frame_by_method(thread, class, method, code);
    if (NULL != new_frame) add_params(frame, new_frame, method);
    return new_frame;
}

Frame *create_vm_frame_by_method_add_params_and_this(Thread* thread, ClassFile *class, Frame *frame, MethodInfo *method, CodeAttribute *code)
{
    Frame *new_frame = create_vm_frame_by_method(thread, class, method, code);
    if (NULL != new_frame) add_params_and_this(frame, new_frame, method);
    return new_frame;
}

Frame *create_vm_frame_by_method_add_hook(Thread* thread, ClassFile *class, MethodInfo *method, CodeAttribute *code, PopHook hook)
{
    Frame *frame = create_vm_frame_by_method(thread, class, method, code);
    if (NULL == frame) return NULL;
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

LocalVariableTableAttribute *get_local_variable(ConstantPool *pool, CodeAttribute *code)
{
    if (NULL == code) return NULL;
    for (int i = 0; i < code->attributes_count; i++) {
        CONSTANT_Utf8_info info = *(CONSTANT_Utf8_info*)pool[code->attributes[i].attribute_name_index].info;
        if (strcmp(info.bytes, "LocalVariableTable") == 0) {
            unsigned long size = sizeof(LocalVariableTableAttribute) + code->attributes[i].attribute_length * 10;
            LocalVariableTableAttribute *local_variable_table_attr = malloc(size);
            local_variable_table_attr->attribute_name_index = code->attributes[i].attribute_name_index;
            local_variable_table_attr->attribute_length = code->attributes[i].attribute_length;
            local_variable_table_attr->local_variable_table_length = l2b_2(*(u2*)code->attributes[i].info);
            code->attributes[i].info += sizeof(u2);
            for (int j = 0; j < local_variable_table_attr->local_variable_table_length; j++) {
                local_variable_table_attr->local_variable_table[j].start_pc = l2b_2(*(u2*)code->attributes[i].info);
                code->attributes[i].info += sizeof(u2);
                local_variable_table_attr->local_variable_table[j].length = l2b_2(*(u2*)code->attributes[i].info);
                code->attributes[i].info += sizeof(u2);
                local_variable_table_attr->local_variable_table[j].name_index = l2b_2(*(u2*)code->attributes[i].info);
                code->attributes[i].info += sizeof(u2);
                local_variable_table_attr->local_variable_table[j].descriptor_index = l2b_2(*(u2*)code->attributes[i].info);
                code->attributes[i].info += sizeof(u2);
                local_variable_table_attr->local_variable_table[j].index = l2b_2(*(u2*)code->attributes[i].info);
                code->attributes[i].info += sizeof(u2);
                local_variable_table_attr->local_variable_table[j].name = get_utf8_bytes(pool, local_variable_table_attr->local_variable_table[j].name_index);
                local_variable_table_attr->local_variable_table[j].desc = get_utf8_bytes(pool, local_variable_table_attr->local_variable_table[j].descriptor_index);
            }
            return local_variable_table_attr;
        }
    }
    return NULL;
}

void add_params_and_this(Frame *frame, Frame *new_frame, MethodInfo *method)
{
    printf("\t\t\t\t[addparams+this]\n");
    int count = method->params_count + 1;
    Slot **slots = pop_slot_with_num(frame->operand_stack, count);
    for (int i = 0; i < count; i++) {
        new_frame->local_variables[i] = slots[i];
    }
    free(slots);
}

void add_params(Frame *frame, Frame *new_frame, MethodInfo *method)
{
//    LocalVariableTableAttribute *local_variable_table = get_local_variable(new_frame->constant_pool, code);
//    if (NULL == local_variable_table) return;
    if (method->params_count == 0) return;
    printf("\t\t\t\t[addparams(%d)]\n", method->params_count);
    Slot **slots = pop_slot_with_num(frame->operand_stack, method->params_count);
    for (int i = 0; i < method->params_count; i++) {
        new_frame->local_variables[i] = slots[i];
//        switch (local_variable_table->local_variable_table[i].desc[0]) {
//            case 'B': case 'C':case 'I':case 'S':case 'Z':
//                //Int
//                new_frame->local_variables[local_variable_table->local_variable_table[i].index]->value = pop_int(frame->operand_stack);
//            case 'F':
//                //Float
//                new_frame->local_variables[local_variable_table->local_variable_table[i].index]->value = pop_float(frame->operand_stack);
//            case 'D': case 'J': {
//                //Long
//                int value2 = pop_int(frame->operand_stack);
//                int value1 = pop_int(frame->operand_stack);
//                new_frame->local_variables[local_variable_table->local_variable_table[i].index]->value = value1;
//                new_frame->local_variables[local_variable_table->local_variable_table[i].index + 1]->value = value2;
//            }
//            case 'L': case '[':
//                //Object | Array
//                new_frame->local_variable[local_variable_table->local_variable_table[i].index]->object_value = pop_stack(frame->operand_stack);
//        }
    }
    free(slots);
}

void print_local_variables(Frame *frame)
{
    printf("\t\t\t<");
    for (int i = 0; i < frame->code_info->max_locals; i++) {
        Slot *value = frame->local_variables[i];
        if (NULL != value) {
            if (NULL != value->object_value) {
                Object *obj = value->object_value;
                if (NULL != obj->class) printf("[%d-> %s],", i, obj->class->class_name);
                else printf("[%d-> NULL-OBJECT(%p)],", i, obj);
            } else {
                printf("[%d-> %d],", i, value->value);
            }
        } else {
            printf("[NULL]");
        }

    }
    printf(">");
    printf("\n\n");
}