//
// Created by wangzhanzhi on 2020/6/26.
//

#include "thread.h"

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

Frame *create_vm_frame_by_method_with_push(Thread* thread, ClassFile *class, MethodInfo *method, CodeAttribute *code)
{
    Frame *frame = create_vm_frame_by_method(thread, class, method, code);
    if (NULL != frame) push_stack(thread->vm_stack, frame);
    return frame;
}

Frame *create_vm_frame_by_method(Thread* thread, ClassFile *class, MethodInfo *method, CodeAttribute *code)
{
    if (NULL == code) return NULL;
    Frame *frame = (Frame*)malloc(sizeof(Frame) + (sizeof(Slot) * code->max_locals));
    for (int i = 0; i < code->max_locals; i++) {
        frame->local_variables[i] = create_slot();
    }
    frame->operand_stack = create_stack(code->max_stack);
    frame->constant_pool = class->constant_pool;
    frame->method = method;
    frame->code_info = code;
    frame->pop_hook = NULL;
    frame->class = class;
    frame->pc = 0;
    return frame;
}

Frame *create_vm_frame_by_method_add_params(Thread* thread, ClassFile *class, Frame *frame, MethodInfo *method, CodeAttribute *code)
{
    Frame *new_frame = create_vm_frame_by_method_with_push(thread, class, method, code);
    if (NULL != new_frame) add_params(frame, new_frame, method);
    return new_frame;
}

Frame *create_vm_frame_by_method_add_params_plus1(Thread* thread, ClassFile *class, Frame *frame, MethodInfo *method, CodeAttribute *code)
{
    Frame *new_frame = create_vm_frame_by_method_with_push(thread, class, method, code);
    if (NULL != new_frame) add_params_and_plus1(frame, new_frame, method);
    return new_frame;
}

Frame *create_vm_frame_by_method_add_hook(Thread* thread, ClassFile *class, MethodInfo *method, CodeAttribute *code, PopHook hook)
{
    Frame *frame = create_vm_frame_by_method_with_push(thread, class, method, code);
    if (NULL == frame) return NULL;
    frame->pop_hook = hook;
    return frame;
}

Thread *create_thread(int vm_stack_size, int c_stack_size)
{
    Thread *thread = malloc(sizeof(Thread));
    thread->vm_stack = create_stack(vm_stack_size);
    thread->c_stack = create_stack(c_stack_size);
    thread->jthread = NULL;
    return thread;
}

Thread *create_thread_with_jthread(int vm_stack_size, int c_stack_size, Object *jthread)
{
    Thread *thread = create_thread(vm_stack_size, c_stack_size);
    thread->jthread = jthread;
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

void add_params_and_plus1(Frame *frame, Frame *new_frame, MethodInfo *method)
{
    int count = method->params_count + 1;
    printf_debug("\t\t\t\t[addparams(%d)]\n", count);
    Slot **slots = pop_slot_with_num(frame->operand_stack, count);
    for (int i = 0; i < count; i++) {
        set_localvar_with_slot_copy(new_frame, i, slots[i]);
//        new_frame->local_variables[i] = slots[i];
    }
    free(slots);
}

void add_params(Frame *frame, Frame *new_frame, MethodInfo *method)
{
    if (method->params_count == 0) return;
    printf_debug("\t\t\t\t[addparams(%d)]\n", method->params_count);
    Slot **slots = pop_slot_with_num(frame->operand_stack, method->params_count);
    for (int i = 0; i < method->params_count; i++) {
        set_localvar_with_slot_copy(new_frame, i, slots[i]);
//        new_frame->local_variables[i] = slots[i];
    }
    free(slots);
}

u8 get_long_localvar(Frame *frame, int index)
{
    u8 higher = frame->local_variables[index]->value;
    u8 lower = frame->local_variables[index + 1]->value;
    return higher | lower;
}

u8 get_localvar(Frame *frame, int index)
{
    return frame->local_variables[index]->value;
}

float get_localvar_float(Frame *frame, int index)
{
    char str[4];
    memcpy(str, &(frame->local_variables[index]->value), 4);
    float val = *(float*)str;
    return val;
}

Slot *get_slot_localvar(Frame *frame, int index)
{
    return frame->local_variables[index];
}

void *get_ref_localvar(Frame *frame, int index)
{
    return frame->local_variables[index]->object_value;
}

void **get_ref_addr_localvar(Frame *frame, int index)
{
    return &(frame->local_variables[index]->object_value);
}

void *get_localvar_this(Frame *frame)
{
    return get_ref_localvar(frame, 0);
}

void set_localvar(Frame *frame, int index, u8 value)
{
    frame->local_variables[index]->value = value;
}

void set_localvar_with_slot(Frame *frame, int index, Slot *value)
{
    frame->local_variables[index]->value = value->value;
    frame->local_variables[index]->object_value = value->object_value;
}

void set_localvar_with_slot_copy(Frame *frame, int index, Slot *value)
{
    frame->local_variables[index] = create_slot_set_value(value->value);
    frame->local_variables[index]->object_value = value->object_value;
}

void set_long_localvar(Frame *frame, int index, u8 value)
{
    set_localvar(frame, index, 0);
    set_localvar(frame, index + 1, value);
}

void *set_ref_localvar(Frame *frame, int index, void *object_value)
{
    return frame->local_variables[index]->object_value = object_value;
}

void print_local_variables(Frame *frame)
{
    printf_debug("\t\t\t<");
    for (int i = 0; i < frame->code_info->max_locals; i++) {
        Slot *value = frame->local_variables[i];
        if (NULL != value) {
            if (NULL != value->object_value) {
                Object *obj = value->object_value;
                if (NULL != obj->class) {
                    if (object_is_string(obj)) {
                        if (obj->fields == NULL) {
                            printf_debug("[NULL-STR]");
                        } else {
                            Array *array = obj->fields->object_value;
                            if (NULL == array) {
                                printf_debug("[NULL-STR]");
                            } else {
                                char *str = malloc(array->length + 1);
                                memcpy(str, (char*)array->objects, array->length);
                                str[array->length] = '\0';
                                if (str[0] == '\n') {
                                    printf_debug("[%d-> \"\\n\"],", i);
                                } else {
                                    printf_debug("[%d-> \"%s\"],", i, str);
                                }
                                free(str);
                            }
                        }
                    } else {
                        if (strcmp(obj->class->class_name, "[B") == 0) {
                            Array *array = value->object_value;
                            char *str = malloc(array->length + 1);
                            memcpy(str, (char*)array->objects, array->length);
                            str[array->length] = '\0';
                            printf_debug("[%d-> \"%s\"],", i, str);
                        } else {
                            printf_debug("[%d-> %s],", i, obj->class->class_name);
                        }
                    }
                }
                else printf_debug("[%d-> NULL-OBJECT(%p)],", i, obj);
            } else {
                printf_debug("[%d-> %ld],", i, (long)value->value);
            }
        } else {
            printf_debug("[NULL]");
        }

    }
    printf_debug(">");
    printf_debug("\n\n");
}