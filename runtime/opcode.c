//
// Created by wangzhanzhi on 2020/6/25.
//

#include "opcode.h"

void xastore_(SerialHeap *heap, Thread *thread, Frame *frame, char desc);
void ifx_(SerialHeap *heap, Thread *thread, Frame *frame, int cond);
void if_icmpx_(SerialHeap *heap, Thread *thread, Frame *frame, int cond);
void if_acmpx_(SerialHeap *heap, Thread *thread, Frame *frame, int cond);
void fcmpx_(SerialHeap *heap, Thread *thread, Frame *frame, int res);

void step_pc(Frame *frame, int offset)
{
    frame->pc += offset;
}


int step_pc_and_read_pc(Frame *frame, int offset)
{
    frame->pc += offset;
    return frame->pc;
}

void step_pc_1(Frame *frame)
{
    frame->pc ++;
}

void back_pc(Frame *frame, u4 offset)
{
    frame->pc -= offset;
}

void back_pc_1(Frame *frame)
{
    frame->pc --;
}

void back_pc_2(Frame *frame)
{
    frame->pc -= 2;
}

u4 step_pc_no_submit(Frame *frame, u4 offset)
{
    return frame->pc + offset;
}

u4 back_pc_no_submit(Frame *frame, u4 offset)
{
    return frame->pc - offset;
}

u4 step_pc_1_no_submit(Frame *frame)
{
    return step_pc_no_submit(frame, 1);
}

u4 back_pc_1_no_submit(Frame *frame)
{
    return back_pc_no_submit(frame, 1);
}

u4 step_pc_2_no_submit(Frame *frame)
{
    return step_pc_no_submit(frame, 2);
}

u4 back_pc_2_no_submit(Frame *frame)
{
    return back_pc_no_submit(frame, 2);
}

int step_pc_1_read_pc(Frame *frame)
{
    step_pc_1(frame);
    return frame->pc;
}

int back_pc_1_read_pc(Frame *frame)
{
    back_pc_1(frame);
    return frame->pc;
}

void step_pc_2(Frame *frame)
{
    frame->pc += 2;
}

int step_pc_2_read_pc(Frame *frame)
{
    step_pc_2(frame);
    return frame->pc;
}

u1 read_code(Frame *frame)
{
    return frame->code_info->code[frame->pc];
}

u1 read_code_and_step_pc1(Frame *frame)
{
    u1 op_code = read_code(frame);
    step_pc_1(frame);
    return op_code;
}

u1 step_pc1_and_read_code_no_submit(Frame *frame)
{
    return frame->code_info->code[step_pc_1_no_submit(frame)];
}

u1 step_pc2_and_read_code_no_submit(Frame *frame)
{
    return frame->code_info->code[step_pc_2_no_submit(frame)];
}

u1 step_pc_and_read_code_no_submit(u1 *code, Frame *frame, u4 offset)
{
    return code[step_pc_no_submit(frame, offset)];
}

u1 step_pc1_and_read_code(Frame *frame)
{
    step_pc_1(frame);
    u1 op_code = read_code(frame);
    return op_code;
}

u4 step_pc4_and_read_u4(Frame *frame)
{
    step_pc_1(frame);
    u1 var1 = read_code(frame);
    step_pc_1(frame);
    u1 var2 = read_code(frame);
    step_pc_1(frame);
    u1 var3 = read_code(frame);
    step_pc_1(frame);
    u1 var4 = read_code(frame);
    return (var1 << 24 | var2 << 16 | var3 << 8 | var4);
}

u4* step_pc4_and_read_u4_by_count(Frame *frame, int count)
{
    u4 *vars = malloc(count * sizeof(u4));
    for (int i = 0; i < count; i++) {
        vars[i] = step_pc4_and_read_u4(frame);
    }
    return vars;
}

void nop(SerialHeap *heap, Thread *thread, Frame *frame) {
    step_pc_1(frame);
}

void aconst_null(SerialHeap *heap, Thread *thread, Frame *frame) {
    push_slot(frame->operand_stack, NULL_SLOT);
    step_pc_1(frame);
}

void iconst_m1(SerialHeap *heap, Thread *thread, Frame *frame) {
    push_int(frame->operand_stack, -1);
    step_pc_1(frame);
}

void iconst_0(SerialHeap *heap, Thread *thread, Frame *frame) {
    push_int(frame->operand_stack, 0);
    step_pc_1(frame);
}

void iconst_1(SerialHeap *heap, Thread *thread, Frame *frame) {
    push_int(frame->operand_stack, 1);
    step_pc_1(frame);
}

void iconst_2(SerialHeap *heap, Thread *thread, Frame *frame) {
    push_int(frame->operand_stack, 2);
    step_pc_1(frame);
}

void iconst_3(SerialHeap *heap, Thread *thread, Frame *frame) {
    push_int(frame->operand_stack, 3);
    step_pc_1(frame);
}

void iconst_4(SerialHeap *heap, Thread *thread, Frame *frame) {
    push_int(frame->operand_stack, 4);
    step_pc_1(frame);
}

void iconst_5(SerialHeap *heap, Thread *thread, Frame *frame) {
    push_int(frame->operand_stack, 5);
    step_pc_1(frame);
}

void lconst_0(SerialHeap *heap, Thread *thread, Frame *frame) {
    push_long(frame->operand_stack, 0);
    step_pc_1(frame);
}

void lconst_1(SerialHeap *heap, Thread *thread, Frame *frame) {
    push_long(frame->operand_stack, 1);
    step_pc_1(frame);
}

void fconst_0(SerialHeap *heap, Thread *thread, Frame *frame) {
    push_float(frame->operand_stack, 0.0f);
    step_pc_1(frame);
}

void fconst_1(SerialHeap *heap, Thread *thread, Frame *frame) {
    push_float(frame->operand_stack, 1.0f);
    step_pc_1(frame);
}

void fconst_2(SerialHeap *heap, Thread *thread, Frame *frame) {
    push_float(frame->operand_stack, 2.0f);
    step_pc_1(frame);
}

void dconst_0(SerialHeap *heap, Thread *thread, Frame *frame) {
    push_double(frame->operand_stack, 0);
    step_pc_1(frame);
}

void dconst_1(SerialHeap *heap, Thread *thread, Frame *frame) {
    push_double(frame->operand_stack, 1);
    step_pc_1(frame);
}

void bipush(SerialHeap *heap, Thread *thread, Frame *frame) {
    push_int(frame->operand_stack, (int)((signed char)step_pc1_and_read_code(frame)));
    step_pc_1(frame);
}

void sipush(SerialHeap *heap, Thread *thread, Frame *frame) {
    u1 byte1 = step_pc1_and_read_code(frame);
    u1 byte2 = step_pc1_and_read_code(frame);
    short value = (byte1 << 8) | byte2;
    push_int(frame->operand_stack, (int)value);
    step_pc_1(frame);
}

void ldc(SerialHeap *heap, Thread *thread, Frame *frame) {
    u1 index = step_pc1_and_read_code(frame);
    switch (frame->constant_pool[index].tag) {
        case CONSTANT_String: {
            CONSTANT_Utf8_info *info = get_utf8_info_from_string_index(frame->constant_pool, index);
            create_string_object_with_length(thread, heap, frame, info->bytes, info->length);
            break;
        }
        case CONSTANT_Class: {
            CONSTANT_Class_info class_info = *(CONSTANT_Class_info*)frame->constant_pool[index].info;
            u1 *class_name = get_utf8_bytes(frame->constant_pool, class_info.name_index);
            push_object(frame->operand_stack, load_class(thread, heap, class_name)->class_object);
//            create_object_with_backpc(thread, heap, frame, index, 2);
            break;
        }
        case CONSTANT_InterfaceMethodref: {
            CONSTANT_InterfaceMethodref_info info = *(CONSTANT_InterfaceMethodref_info*)frame->constant_pool[index].info;
            create_object_with_backpc(thread, heap, frame, info.class_index, 2);
            break;
        }
        case CONSTANT_MethodType: {
            create_object_with_class_name_and_backpc(thread, heap, frame, "java/lang/invoke/MethodType", 2);
            break;
        }
        case CONSTANT_MethodHandle:
            create_object_with_class_name_and_backpc(thread, heap, frame, "java/lang/invoke/MethodHandle", 2);
            break;
        case CONSTANT_Integer:
            push_int(frame->operand_stack, get_u4_value_from_index(frame->constant_pool, index));
            break;
        case CONSTANT_Float: {
            push_float_by_u4(frame->operand_stack, get_u4_value_from_index(frame->constant_pool, index));
            break;
        }
    }
    step_pc_1(frame);
}

void ldc_w(SerialHeap *heap, Thread *thread, Frame *frame) {
    u1 byte1 = step_pc1_and_read_code(frame);
    u1 byte2 = step_pc1_and_read_code(frame);
    u4 index = (byte1 << 8) | byte2;
    switch (frame->constant_pool[index].tag) {
        case CONSTANT_String: {
            CONSTANT_Utf8_info *info = get_utf8_info_from_string_index(frame->constant_pool, index);
            create_string_object_with_length(thread, heap, frame, info->bytes, info->length);
            break;
        }
        case CONSTANT_Class: {
            CONSTANT_Class_info class_info = *(CONSTANT_Class_info*)frame->constant_pool[index].info;
            u1 *class_name = get_utf8_bytes(frame->constant_pool, class_info.name_index);
            push_object(frame->operand_stack, load_class(thread, heap, class_name)->class_object);
//            create_object_with_backpc(thread, heap, frame, index, 3);
            break;
        }
        case CONSTANT_InterfaceMethodref: {
            CONSTANT_InterfaceMethodref_info info = *(CONSTANT_InterfaceMethodref_info*)frame->constant_pool[index].info;
            create_object_with_backpc(thread, heap, frame, info.class_index, 3);
            break;
        }
        case CONSTANT_MethodType: {
            create_object_with_class_name_and_backpc(thread, heap, frame, "java/lang/invoke/MethodType", 3);
            break;
        }
        case CONSTANT_MethodHandle:
            create_object_with_class_name_and_backpc(thread, heap, frame, "java/lang/invoke/MethodHandle", 3);
            break;
        case CONSTANT_Integer:
            push_int(frame->operand_stack, get_u4_value_from_index(frame->constant_pool, index));
            break;
        case CONSTANT_Float:
            push_float_by_u4(frame->operand_stack, get_u4_value_from_index(frame->constant_pool, index));
            break;
    }
    step_pc_1(frame);
}

void ldc2_w(SerialHeap *heap, Thread *thread, Frame *frame) {
    u1 byte1 = step_pc1_and_read_code(frame);
    u1 byte2 = step_pc1_and_read_code(frame);
    u2 index = (byte1 << 8) | byte2;
    CONSTANT_Long_info long_info = *(CONSTANT_Long_info*)frame->constant_pool[index].info;
    push_long(frame->operand_stack, long_info.high_bytes | long_info.low_bytes);
    step_pc_1(frame);
}

void iload(SerialHeap *heap, Thread *thread, Frame *frame) {
    push_int(frame->operand_stack, get_localvar(frame, step_pc1_and_read_code(frame)));
    step_pc_1(frame);
}

void lload(SerialHeap *heap, Thread *thread, Frame *frame) {
    u1 index = step_pc1_and_read_code(frame);
    push_long(frame->operand_stack, get_long_localvar(frame, index));
    step_pc_1(frame);
}

void fload(SerialHeap *heap, Thread *thread, Frame *frame) {
    push_float(frame->operand_stack, (float)get_localvar(frame, step_pc1_and_read_code(frame)));
    step_pc_1(frame);
}

void dload(SerialHeap *heap, Thread *thread, Frame *frame) {
    u1 index = step_pc1_and_read_code(frame);
    push_double(frame->operand_stack, get_long_localvar(frame, index));
//    push_int(frame->operand_stack, frame->local_variables[index + 1]->value);
//    push_int(frame->operand_stack, frame->local_variables[index]->value);
    step_pc_1(frame);
}

void aload(SerialHeap *heap, Thread *thread, Frame *frame) {
    push_slot(frame->operand_stack, get_slot_localvar(frame, step_pc1_and_read_code(frame)));
    step_pc_1(frame);
}

void iload_0(SerialHeap *heap, Thread *thread, Frame *frame) {
    push_int(frame->operand_stack, get_localvar(frame, 0));
    step_pc_1(frame);
}

void iload_1(SerialHeap *heap, Thread *thread, Frame *frame) {
    push_int(frame->operand_stack, get_localvar(frame, 1));
    step_pc_1(frame);
}

void iload_2(SerialHeap *heap, Thread *thread, Frame *frame) {
    push_int(frame->operand_stack, get_localvar(frame, 2));
    step_pc_1(frame);
}

void iload_3(SerialHeap *heap, Thread *thread, Frame *frame) {
    push_int(frame->operand_stack, get_localvar(frame, 3));
    step_pc_1(frame);
}

void lload_0(SerialHeap *heap, Thread *thread, Frame *frame) {
    push_long(frame->operand_stack, get_long_localvar(frame, 0));
    step_pc_1(frame);
}

void lload_1(SerialHeap *heap, Thread *thread, Frame *frame) {
    push_long(frame->operand_stack, get_long_localvar(frame, 1));
    step_pc_1(frame);
}

void lload_2(SerialHeap *heap, Thread *thread, Frame *frame) {
    push_long(frame->operand_stack, get_long_localvar(frame, 2));
    step_pc_1(frame);
}

void lload_3(SerialHeap *heap, Thread *thread, Frame *frame) {
    push_long(frame->operand_stack, get_long_localvar(frame, 3));
    step_pc_1(frame);
}

void fload_0(SerialHeap *heap, Thread *thread, Frame *frame) {
    push_float(frame->operand_stack, get_localvar_float(frame, 0));
    step_pc_1(frame);
}

void fload_1(SerialHeap *heap, Thread *thread, Frame *frame) {
    push_float(frame->operand_stack, get_localvar_float(frame, 1));
    step_pc_1(frame);
}

void fload_2(SerialHeap *heap, Thread *thread, Frame *frame) {
    push_float(frame->operand_stack, get_localvar_float(frame, 2));
    step_pc_1(frame);
}

void fload_3(SerialHeap *heap, Thread *thread, Frame *frame) {
    push_float(frame->operand_stack, get_localvar_float(frame, 3));
    step_pc_1(frame);
}

void dload_0(SerialHeap *heap, Thread *thread, Frame *frame) {
    push_double(frame->operand_stack, get_long_localvar(frame, 0));
    step_pc_1(frame);
}

void dload_1(SerialHeap *heap, Thread *thread, Frame *frame) {
    push_double(frame->operand_stack, get_long_localvar(frame, 1));
    step_pc_1(frame);
}

void dload_2(SerialHeap *heap, Thread *thread, Frame *frame) {
    push_double(frame->operand_stack, get_long_localvar(frame, 2));
    step_pc_1(frame);
}

void dload_3(SerialHeap *heap, Thread *thread, Frame *frame) {
    push_double(frame->operand_stack, get_long_localvar(frame, 3));
    step_pc_1(frame);
}

void aload_0(SerialHeap *heap, Thread *thread, Frame *frame) {
    push_slot(frame->operand_stack, get_slot_localvar(frame, 0));
    step_pc_1(frame);
}

void aload_1(SerialHeap *heap, Thread *thread, Frame *frame) {
    push_slot(frame->operand_stack, get_slot_localvar(frame, 1));
    step_pc_1(frame);
}

void aload_2(SerialHeap *heap, Thread *thread, Frame *frame) {
    push_slot(frame->operand_stack, get_slot_localvar(frame, 2));
    step_pc_1(frame);
}

void aload_3(SerialHeap *heap, Thread *thread, Frame *frame) {
    push_slot(frame->operand_stack, get_slot_localvar(frame, 3));
    step_pc_1(frame);
}

void iaload(SerialHeap *heap, Thread *thread, Frame *frame) {
    int index = pop_int(frame->operand_stack);
    Slot *slot = pop_slot(frame->operand_stack);
    Array *array = slot->object_value;
    int *value = (int*)array->objects;
    push_int(frame->operand_stack, (int)(value[index]));
    step_pc_1(frame);
}

void laload(SerialHeap *heap, Thread *thread, Frame *frame) {
    int index = pop_int(frame->operand_stack);
    Slot *slot = pop_slot(frame->operand_stack);
    Array *array = slot->object_value;
    long *value = (long*)array->objects;
    push_long(frame->operand_stack, (long)(value[index]));
    step_pc_1(frame);
}

void faload(SerialHeap *heap, Thread *thread, Frame *frame) {
    int index = pop_int(frame->operand_stack);
    Slot *slot = pop_slot(frame->operand_stack);
    Array *array = slot->object_value;
    float *value = (float*)array->objects;
    push_float(frame->operand_stack, (float)(value[index]));
    step_pc_1(frame);
}

void daload(SerialHeap *heap, Thread *thread, Frame *frame) {
    int index = pop_int(frame->operand_stack);
    Slot *slot = pop_slot(frame->operand_stack);
    Array *array = slot->object_value;
    double *value = (double*)array->objects;
    push_double(frame->operand_stack, (double)(value[index]));
    step_pc_1(frame);
}

void aaload(SerialHeap *heap, Thread *thread, Frame *frame) {
    int index = pop_int(frame->operand_stack);
    Array *array = pop_object(frame->operand_stack);
    push_object(frame->operand_stack, array->objects[index]);
    step_pc_1(frame);
}

void baload(SerialHeap *heap, Thread *thread, Frame *frame) {
    int index = pop_int(frame->operand_stack);
    Slot *slot = pop_slot(frame->operand_stack);
    Array *array = slot->object_value;
    u1 *value = (u1*)array->objects;
    push_int(frame->operand_stack, (int)(value[index]));
    step_pc_1(frame);
}

void caload(SerialHeap *heap, Thread *thread, Frame *frame) {
    int index = pop_int(frame->operand_stack);
    Slot *slot = pop_slot(frame->operand_stack);
    Array *array = slot->object_value;
    char *value = (char*)array->objects;
    push_int(frame->operand_stack, (int)(value[index]));
    step_pc_1(frame);
}

void saload(SerialHeap *heap, Thread *thread, Frame *frame) {
    int index = pop_int(frame->operand_stack);
    Slot *slot = pop_slot(frame->operand_stack);
    Array *array = slot->object_value;
    short *value = (short*)array->objects;
    push_int(frame->operand_stack, (int)(value[index]));
    step_pc_1(frame);
}

void istore(SerialHeap *heap, Thread *thread, Frame *frame) {
    frame->local_variables[step_pc1_and_read_code(frame)]->value = pop_int(frame->operand_stack);
    step_pc_1(frame);
}
void lstore(SerialHeap *heap, Thread *thread, Frame *frame) {
    u8 value = pop_long(frame->operand_stack);
    int index = step_pc1_and_read_code(frame);
    set_long_localvar(frame, index, value);
    step_pc_1(frame);
}

void fstore(SerialHeap *heap, Thread *thread, Frame *frame) {
    Slot *value = pop_slot(frame->operand_stack);
    int index = step_pc1_and_read_code(frame);
    set_localvar_with_slot_copy(frame, index, value);
    step_pc_1(frame);
}

void dstore(SerialHeap *heap, Thread *thread, Frame *frame) {
    u8 value = pop_long(frame->operand_stack);
    int index = step_pc1_and_read_code(frame);
    set_long_localvar(frame, index, value);
    step_pc_1(frame);
}

void astore(SerialHeap *heap, Thread *thread, Frame *frame) {
    u1 index = step_pc1_and_read_code(frame);
    set_localvar_with_slot_copy(frame, index, pop_slot(frame->operand_stack));
    step_pc_1(frame);
}

void istore_0(SerialHeap *heap, Thread *thread, Frame *frame) {
    set_localvar(frame, 0, pop_int(frame->operand_stack));
    step_pc_1(frame);
}

void istore_1(SerialHeap *heap, Thread *thread, Frame *frame) {
    set_localvar(frame, 1, pop_int(frame->operand_stack));
    step_pc_1(frame);
}

void istore_2(SerialHeap *heap, Thread *thread, Frame *frame) {
    set_localvar(frame, 2, pop_int(frame->operand_stack));
    step_pc_1(frame);
}

void istore_3(SerialHeap *heap, Thread *thread, Frame *frame) {
    set_localvar(frame, 3, pop_int(frame->operand_stack));
    step_pc_1(frame);
}

void lstore_0(SerialHeap *heap, Thread *thread, Frame *frame) {
//    frame->local_variables[0]->value = pop_int(frame->operand_stack);
//    frame->local_variables[1]->value = pop_int(frame->operand_stack);
//    step_pc_1(frame);

    u8 value = pop_long(frame->operand_stack);
    set_long_localvar(frame, 0, value);
    step_pc_1(frame);
}

void lstore_1(SerialHeap *heap, Thread *thread, Frame *frame) {
    u8 value = pop_long(frame->operand_stack);
    set_long_localvar(frame, 1, value);
    step_pc_1(frame);
}

void lstore_2(SerialHeap *heap, Thread *thread, Frame *frame) {
    u8 value = pop_long(frame->operand_stack);
    set_long_localvar(frame, 2, value);
    step_pc_1(frame);
}

void lstore_3(SerialHeap *heap, Thread *thread, Frame *frame) {
    u8 value = pop_long(frame->operand_stack);
    set_long_localvar(frame, 3, value);
    step_pc_1(frame);
}

void fstore_0(SerialHeap *heap, Thread *thread, Frame *frame) {
    Slot *value = pop_slot(frame->operand_stack);
    set_localvar_with_slot_copy(frame, 0, value);
    step_pc_1(frame);
}

void fstore_1(SerialHeap *heap, Thread *thread, Frame *frame) {
    Slot *value = pop_slot(frame->operand_stack);
    set_localvar_with_slot_copy(frame, 1, value);
    step_pc_1(frame);
}

void fstore_2(SerialHeap *heap, Thread *thread, Frame *frame) {
    Slot *value = pop_slot(frame->operand_stack);
    set_localvar_with_slot_copy(frame, 2, value);
    step_pc_1(frame);
}

void fstore_3(SerialHeap *heap, Thread *thread, Frame *frame) {
    Slot *value = pop_slot(frame->operand_stack);
    set_localvar_with_slot_copy(frame, 3, value);
    step_pc_1(frame);
}

void dstore_0(SerialHeap *heap, Thread *thread, Frame *frame) {
    u8 value = pop_long(frame->operand_stack);
    set_long_localvar(frame, 0, value);
    step_pc_1(frame);
}

void dstore_1(SerialHeap *heap, Thread *thread, Frame *frame) {
    u8 value = pop_long(frame->operand_stack);
    set_long_localvar(frame, 1, value);
    step_pc_1(frame);
}

void dstore_2(SerialHeap *heap, Thread *thread, Frame *frame) {
    u8 value = pop_long(frame->operand_stack);
    set_long_localvar(frame, 2, value);
    step_pc_1(frame);
}

void dstore_3(SerialHeap *heap, Thread *thread, Frame *frame) {
    u8 value = pop_long(frame->operand_stack);
    set_long_localvar(frame, 3, value);
    step_pc_1(frame);
}

void astore_0(SerialHeap *heap, Thread *thread, Frame *frame) {
//    frame->local_variables[0] = pop_slot(frame->operand_stack);
    set_localvar_with_slot_copy(frame, 0, pop_slot(frame->operand_stack));
    step_pc_1(frame);
}

void astore_1(SerialHeap *heap, Thread *thread, Frame *frame) {
//    frame->local_variables[1] = pop_slot(frame->operand_stack);
    set_localvar_with_slot_copy(frame, 1, pop_slot(frame->operand_stack));
    step_pc_1(frame);
}

void astore_2(SerialHeap *heap, Thread *thread, Frame *frame) {
    set_localvar_with_slot_copy(frame, 2, pop_slot(frame->operand_stack));
    step_pc_1(frame);
}

void astore_3(SerialHeap *heap, Thread *thread, Frame *frame) {
    set_localvar_with_slot_copy(frame, 3, pop_slot(frame->operand_stack));
    step_pc_1(frame);
}

void xastore_(SerialHeap *heap, Thread *thread, Frame *frame, char desc) {
    Slot *value;
    if (desc == 'J' || desc == 'D') {
        pop_slot(frame->operand_stack);
        value = pop_slot(frame->operand_stack);
    } else {
        value = pop_slot(frame->operand_stack);
    }
    if (NULL == value) {
        printf_err("throw NULLPointerException");
        exit(-1);
    }
    int index = pop_int(frame->operand_stack);
    Array *ref = pop_object(frame->operand_stack);
    switch (desc) {
        case 'Z': case 'I': {
            int *objects = (int*)ref->objects + index;
            *objects = value->value;
            break;
        }
        case 'C': case 'B': {
            char *objects = (char*)ref->objects + index;
            *objects = value->value;
            break;
        }
        case 'F': {
            float *objects = (float*)ref->objects + index;
            *objects = value->value;
            break;
        }
        case 'D': {
            double *objects = (double*)ref->objects + index;
            *objects = value->value;
            break;
        }
        case 'S': {
            short *objects = (short*)ref->objects + index;
            *objects = value->value;
            break;
        }
        case 'J': {
            long *objects = (long*)ref->objects + index;
            *objects = value->value;
            break;
        }
    }
}

void iastore(SerialHeap *heap, Thread *thread, Frame *frame) {
    xastore_(heap, thread, frame, 'I');
    step_pc_1(frame);
}

void lastore(SerialHeap *heap, Thread *thread, Frame *frame) {
    xastore_(heap, thread, frame, 'J');
    step_pc_1(frame);
}

void fastore(SerialHeap *heap, Thread *thread, Frame *frame) {
    xastore_(heap, thread, frame, 'F');
    step_pc_1(frame);
}

void dastore(SerialHeap *heap, Thread *thread, Frame *frame) {
    xastore_(heap, thread, frame, 'D');
    step_pc_1(frame);
}

void aastore(SerialHeap *heap, Thread *thread, Frame *frame) {
    Object *value = pop_object(frame->operand_stack);
    int index = pop_int(frame->operand_stack);
    Array *ref = pop_object(frame->operand_stack);
    ref->objects[index] = value;
    step_pc_1(frame);
}

void bastore(SerialHeap *heap, Thread *thread, Frame *frame) {
    xastore_(heap, thread, frame, 'B');
    step_pc_1(frame);
}

void castore(SerialHeap *heap, Thread *thread, Frame *frame) {
    xastore_(heap, thread, frame, 'C');
    step_pc_1(frame);
}

void sastore(SerialHeap *heap, Thread *thread, Frame *frame) {
    xastore_(heap, thread, frame, 'S');
    step_pc_1(frame);
}

void j_pop(SerialHeap *heap, Thread *thread, Frame *frame) {
    pop_slot(frame->operand_stack);
    step_pc_1(frame);
}

void pop2(SerialHeap *heap, Thread *thread, Frame *frame) {
    //TODO the logic is not complete here is form1
    pop_slot(frame->operand_stack);
    pop_slot(frame->operand_stack);
    step_pc_1(frame);
}

void j_dup(SerialHeap *heap, Thread *thread, Frame *frame) {
    push_slot_copy(frame->operand_stack, get_slot(frame->operand_stack));
    step_pc_1(frame);
}

void dup_x1(SerialHeap *heap, Thread *thread, Frame *frame) {
    Slot *value1 = pop_slot(frame->operand_stack);
    Slot *value2 = pop_slot(frame->operand_stack);
    push_slot_copy(frame->operand_stack, value1);
    push_slot_copy(frame->operand_stack, value2);
    push_slot_copy(frame->operand_stack, value1);
    step_pc_1(frame);
}

void dup_x2(SerialHeap *heap, Thread *thread, Frame *frame) {
    //TODO the logic is not complete here is form1
    Slot *value1 = pop_slot(frame->operand_stack);
    Slot *value2 = pop_slot(frame->operand_stack);
    Slot *value3 = pop_slot(frame->operand_stack);
    push_slot_copy(frame->operand_stack, value1);
    push_slot_copy(frame->operand_stack, value2);
    push_slot_copy(frame->operand_stack, value3);
    push_slot_copy(frame->operand_stack, value1);
    step_pc_1(frame);
}

void j_dup2(SerialHeap *heap, Thread *thread, Frame *frame) {
    //TODO the logic is not complete here is form1
    Slot *value1 = pop_slot(frame->operand_stack);
    Slot *value2 = pop_slot(frame->operand_stack);
    push_slot_copy(frame->operand_stack, value1);
    push_slot_copy(frame->operand_stack, value2);
    push_slot_copy(frame->operand_stack, value1);
    push_slot_copy(frame->operand_stack, value2);
    step_pc_1(frame);
}

void dup2_x1(SerialHeap *heap, Thread *thread, Frame *frame) {
    //TODO the logic is not complete here is form1
    Slot *value1 = pop_slot(frame->operand_stack);
    Slot *value2 = pop_slot(frame->operand_stack);
    Slot *value3 = pop_slot(frame->operand_stack);
    push_slot_copy(frame->operand_stack, value1);
    push_slot_copy(frame->operand_stack, value2);
    push_slot_copy(frame->operand_stack, value3);
    push_slot_copy(frame->operand_stack, value1);
    push_slot_copy(frame->operand_stack, value2);
    step_pc_1(frame);
}

void dup2_x2(SerialHeap *heap, Thread *thread, Frame *frame) {
    //TODO the logic is not complete here is form1
    Slot *value1 = pop_slot(frame->operand_stack);
    Slot *value2 = pop_slot(frame->operand_stack);
    Slot *value3 = pop_slot(frame->operand_stack);
    Slot *value4 = pop_slot(frame->operand_stack);
    push_slot_copy(frame->operand_stack, value1);
    push_slot_copy(frame->operand_stack, value2);
    push_slot_copy(frame->operand_stack, value3);
    push_slot_copy(frame->operand_stack, value4);
    push_slot_copy(frame->operand_stack, value1);
    push_slot_copy(frame->operand_stack, value2);
    step_pc_1(frame);
}

void swap(SerialHeap *heap, Thread *thread, Frame *frame) {
    Slot *value1 = pop_slot(frame->operand_stack);
    Slot *value2 = pop_slot(frame->operand_stack);
    push_slot(frame->operand_stack, value1);
    push_slot(frame->operand_stack, value2);
    step_pc_1(frame);
}

void iadd(SerialHeap *heap, Thread *thread, Frame *frame) {
    int value2 = pop_int(frame->operand_stack);
    int value1 = pop_int(frame->operand_stack);
    push_int(frame->operand_stack, value1 + value2);
    step_pc_1(frame);
}

void ladd(SerialHeap *heap, Thread *thread, Frame *frame) {
    long value2 = pop_long(frame->operand_stack);
    long value1 = pop_long(frame->operand_stack);
    push_long(frame->operand_stack, value1 + value2);
    step_pc_1(frame);
}

void fadd(SerialHeap *heap, Thread *thread, Frame *frame) {
    float value2 = pop_float(frame->operand_stack);
    float value1 = pop_float(frame->operand_stack);
    push_float(frame->operand_stack, value1 + value2);
    step_pc_1(frame);
}

void dadd(SerialHeap *heap, Thread *thread, Frame *frame) {
    double value2 = pop_double(frame->operand_stack);
    double value1 = pop_double(frame->operand_stack);
    push_double(frame->operand_stack, value1 + value2);
    step_pc_1(frame);
}

void isub(SerialHeap *heap, Thread *thread, Frame *frame) {
    int value2 = pop_int(frame->operand_stack);
    int value1 = pop_int(frame->operand_stack);
    push_int(frame->operand_stack, value1 - value2);
    step_pc_1(frame);
}

void lsub(SerialHeap *heap, Thread *thread, Frame *frame) {
    long value2 = pop_long(frame->operand_stack);
    long value1 = pop_long(frame->operand_stack);
    push_long(frame->operand_stack, value1 - value2);
    step_pc_1(frame);
}

void fsub(SerialHeap *heap, Thread *thread, Frame *frame) {
    float value2 = pop_float(frame->operand_stack);
    float value1 = pop_float(frame->operand_stack);
    push_float(frame->operand_stack, value1 - value2);
    step_pc_1(frame);
}

void dsub(SerialHeap *heap, Thread *thread, Frame *frame) {
    double value2 = pop_double(frame->operand_stack);
    double value1 = pop_double(frame->operand_stack);
    push_double(frame->operand_stack, value1 - value2);
    step_pc_1(frame);
}

void imul(SerialHeap *heap, Thread *thread, Frame *frame) {
    int value2 = pop_int(frame->operand_stack);
    int value1 = pop_int(frame->operand_stack);
    push_int(frame->operand_stack, value1 * value2);
    step_pc_1(frame);
}

void lmul(SerialHeap *heap, Thread *thread, Frame *frame) {
    long value2 = pop_long(frame->operand_stack);
    long value1 = pop_long(frame->operand_stack);
    push_long(frame->operand_stack, value1 * value2);
    step_pc_1(frame);
}

void fmul(SerialHeap *heap, Thread *thread, Frame *frame) {
    float value2 = pop_float(frame->operand_stack);
    float value1 = pop_float(frame->operand_stack);
    push_float(frame->operand_stack, value1 * value2);
    step_pc_1(frame);
}

void dmul(SerialHeap *heap, Thread *thread, Frame *frame) {
    double value2 = pop_double(frame->operand_stack);
    double value1 = pop_double(frame->operand_stack);
    push_double(frame->operand_stack, value1 * value2);
    step_pc_1(frame);
}

void idiv(SerialHeap *heap, Thread *thread, Frame *frame) {
    int value2 = pop_int(frame->operand_stack);
    int value1 = pop_int(frame->operand_stack);
    push_int(frame->operand_stack, value1 / value2);
    step_pc_1(frame);
}

void j_ldiv(SerialHeap *heap, Thread *thread, Frame *frame) {
    long value2 = pop_long(frame->operand_stack);
    long value1 = pop_long(frame->operand_stack);
    push_long(frame->operand_stack, value1 / value2);
    step_pc_1(frame);
}

void fdiv(SerialHeap *heap, Thread *thread, Frame *frame) {
    float value2 = pop_float(frame->operand_stack);
    float value1 = pop_float(frame->operand_stack);
    push_float(frame->operand_stack, value1 / value2);
    step_pc_1(frame);
}

void ddiv(SerialHeap *heap, Thread *thread, Frame *frame) {
    double value2 = pop_double(frame->operand_stack);
    double value1 = pop_double(frame->operand_stack);
    push_double(frame->operand_stack, value1 / value2);
    step_pc_1(frame);
}

void irem(SerialHeap *heap, Thread *thread, Frame *frame) {
    int value2 = pop_int(frame->operand_stack);
    int value1 = pop_int(frame->operand_stack);
    push_int(frame->operand_stack, value1 - (value1 / value2) * value2);
    step_pc_1(frame);
}

void lrem(SerialHeap *heap, Thread *thread, Frame *frame) {
    long value2 = pop_long(frame->operand_stack);
    long value1 = pop_long(frame->operand_stack);
    push_long(frame->operand_stack, value1 - (value1 / value2) * value2);
    step_pc_1(frame);
}

void frem(SerialHeap *heap, Thread *thread, Frame *frame) {
    float value2 = pop_float(frame->operand_stack);
    float value1 = pop_float(frame->operand_stack);
    push_float(frame->operand_stack, value1 - (value1 / value2) * value2);
    step_pc_1(frame);
}

void j_drem(SerialHeap *heap, Thread *thread, Frame *frame) {
    double value2 = pop_double(frame->operand_stack);
    double value1 = pop_double(frame->operand_stack);
    push_double(frame->operand_stack, value1 - (value1 / value2) * value2);
    step_pc_1(frame);
}

void ineg(SerialHeap *heap, Thread *thread, Frame *frame) {
    push_int(frame->operand_stack, -pop_int(frame->operand_stack));
    step_pc_1(frame);
}

void lneg(SerialHeap *heap, Thread *thread, Frame *frame) {
    push_long(frame->operand_stack, -pop_long(frame->operand_stack));
    step_pc_1(frame);
}

void fneg(SerialHeap *heap, Thread *thread, Frame *frame) {
    push_float(frame->operand_stack, -pop_float(frame->operand_stack));
    step_pc_1(frame);
}

void dneg(SerialHeap *heap, Thread *thread, Frame *frame) {
    push_double(frame->operand_stack, -pop_double(frame->operand_stack));
    step_pc_1(frame);
}

void ishl(SerialHeap *heap, Thread *thread, Frame *frame) {
    int value2 = pop_int(frame->operand_stack);
    int value1 = pop_int(frame->operand_stack);
    push_int(frame->operand_stack, value1 << (value2 & 0x1f));
    step_pc_1(frame);
}

void lshl(SerialHeap *heap, Thread *thread, Frame *frame) {
    int value2 = pop_int(frame->operand_stack);
    long value1 = pop_long(frame->operand_stack);
    push_long(frame->operand_stack, value1 << (value2 & 0x3f));
    step_pc_1(frame);
}

void ishr(SerialHeap *heap, Thread *thread, Frame *frame) {
    int value2 = pop_int(frame->operand_stack);
    int value1 = pop_int(frame->operand_stack);
    push_int(frame->operand_stack, value1 >> (value2 & 0x1f));
    step_pc_1(frame);
}

void lshr(SerialHeap *heap, Thread *thread, Frame *frame) {
    int value2 = pop_int(frame->operand_stack);
    long value1 = pop_long(frame->operand_stack);
    push_long(frame->operand_stack, value1 >> (value2 & 0x3f));
    step_pc_1(frame);
}

void iushr(SerialHeap *heap, Thread *thread, Frame *frame) {
    int value2 = pop_int(frame->operand_stack);
    int value1 = pop_int(frame->operand_stack);
    push_int(frame->operand_stack, (int)(value1 >> ((unsigned int)value2 & 0x1f)));
    step_pc_1(frame);
}

void lushr(SerialHeap *heap, Thread *thread, Frame *frame) {
    int value2 = pop_int(frame->operand_stack);
    long value1 = pop_long(frame->operand_stack);
    push_long(frame->operand_stack, (long)((unsigned long)value1 >> (value2 & 0x3f)));
    step_pc_1(frame);
}

void iand(SerialHeap *heap, Thread *thread, Frame *frame) {
    int value2 = pop_int(frame->operand_stack);
    int value1 = pop_int(frame->operand_stack);
    push_int(frame->operand_stack, value1 & value2);
    step_pc_1(frame);
}

void land(SerialHeap *heap, Thread *thread, Frame *frame) {
    long value2 = pop_long(frame->operand_stack);
    long value1 = pop_long(frame->operand_stack);
    push_long(frame->operand_stack, value1 & value2);
    step_pc_1(frame);
}

void ior(SerialHeap *heap, Thread *thread, Frame *frame) {
    int value2 = pop_int(frame->operand_stack);
    int value1 = pop_int(frame->operand_stack);
    push_int(frame->operand_stack, value1 | value2);
    step_pc_1(frame);
}

void lor(SerialHeap *heap, Thread *thread, Frame *frame) {
    long value2 = pop_long(frame->operand_stack);
    long value1 = pop_long(frame->operand_stack);
    push_long(frame->operand_stack, value1 | value2);
    step_pc_1(frame);
}

void ixor(SerialHeap *heap, Thread *thread, Frame *frame) {
    int value2 = pop_int(frame->operand_stack);
    int value1 = pop_int(frame->operand_stack);
    push_int(frame->operand_stack, value1 ^ value2);
    step_pc_1(frame);
}

void lxor(SerialHeap *heap, Thread *thread, Frame *frame) {
    long value2 = pop_long(frame->operand_stack);
    long value1 = pop_long(frame->operand_stack);
    push_long(frame->operand_stack, value1 ^ value2);
    step_pc_1(frame);
}

void iinc(SerialHeap *heap, Thread *thread, Frame *frame) {
    u1 index = step_pc1_and_read_code(frame);
    u1 increment = step_pc1_and_read_code(frame);
    frame->local_variables[index]->value += (char)increment;
    step_pc_1(frame);
}

void i2l(SerialHeap *heap, Thread *thread, Frame *frame) {
    push_long(frame->operand_stack, pop_int(frame->operand_stack));
    step_pc_1(frame);
}

void i2f(SerialHeap *heap, Thread *thread, Frame *frame) {
    push_float(frame->operand_stack, (float)pop_int(frame->operand_stack));
    step_pc_1(frame);
}

void i2d(SerialHeap *heap, Thread *thread, Frame *frame) {
    push_double(frame->operand_stack, pop_int(frame->operand_stack));
    step_pc_1(frame);
}

void l2i(SerialHeap *heap, Thread *thread, Frame *frame) {
    push_int(frame->operand_stack, (int)pop_long(frame->operand_stack));
    step_pc_1(frame);
}

void l2f(SerialHeap *heap, Thread *thread, Frame *frame) {
    u8 value = pop_long(frame->operand_stack);
    push_float(frame->operand_stack, (float)value);
    step_pc_1(frame);
}

void l2d(SerialHeap *heap, Thread *thread, Frame *frame) {
    push_double(frame->operand_stack, (double)pop_long(frame->operand_stack));
    step_pc_1(frame);
}

void f2i(SerialHeap *heap, Thread *thread, Frame *frame) {
    push_int(frame->operand_stack, (int)pop_float(frame->operand_stack));
    step_pc_1(frame);
}

void f2l(SerialHeap *heap, Thread *thread, Frame *frame) {
    push_long(frame->operand_stack, (long)pop_float(frame->operand_stack));
    step_pc_1(frame);
}

void f2d(SerialHeap *heap, Thread *thread, Frame *frame) {
    push_double(frame->operand_stack, pop_float(frame->operand_stack));
    step_pc_1(frame);
}

void d2i(SerialHeap *heap, Thread *thread, Frame *frame) {
    push_int(frame->operand_stack, (int)pop_double(frame->operand_stack));
    step_pc_1(frame);
}

void d2l(SerialHeap *heap, Thread *thread, Frame *frame) {
    push_long(frame->operand_stack, (long)pop_double(frame->operand_stack));
    step_pc_1(frame);
}

void d2f(SerialHeap *heap, Thread *thread, Frame *frame) {
    push_float(frame->operand_stack, (float)pop_double(frame->operand_stack));
    step_pc_1(frame);
}

void i2b(SerialHeap *heap, Thread *thread, Frame *frame) {
    push_int(frame->operand_stack, (signed int)((signed char)pop_int(frame->operand_stack)));
    step_pc_1(frame);
}

void i2c(SerialHeap *heap, Thread *thread, Frame *frame) {
    push_int(frame->operand_stack, (char)pop_int(frame->operand_stack));
    step_pc_1(frame);
}

void i2s(SerialHeap *heap, Thread *thread, Frame *frame) {
    push_int(frame->operand_stack, (short)pop_int(frame->operand_stack));
    step_pc_1(frame);
}

void lcmp(SerialHeap *heap, Thread *thread, Frame *frame) {
    long value2 = pop_long(frame->operand_stack);
    long value1 = pop_long(frame->operand_stack);
    push_int(frame->operand_stack, value1 > value2 ? 1 : value1 == value2 ? 0 : -1);
    step_pc_1(frame);
}

void fcmpx_(SerialHeap *heap, Thread *thread, Frame *frame, int res) {
    float value2 = pop_float(frame->operand_stack);
    float value1 = pop_float(frame->operand_stack);
    if (value1 > value2) {
        push_int(frame->operand_stack, 1);
    } else if (value1 == value2) {
        push_int(frame->operand_stack, 0);
    } else if (value1 < value2) {
        push_int(frame->operand_stack, -1);
    } else {
        push_int(frame->operand_stack, res);
    }
}

void fcmpl(SerialHeap *heap, Thread *thread, Frame *frame) {
    fcmpx_(heap, thread, frame, -1);
    step_pc_1(frame);
}

void fcmpg(SerialHeap *heap, Thread *thread, Frame *frame) {
    fcmpx_(heap, thread, frame, 1);
    step_pc_1(frame);
}

void dcmpl(SerialHeap *heap, Thread *thread, Frame *frame) {}
void dcmpg(SerialHeap *heap, Thread *thread, Frame *frame) {}

void ifx_(SerialHeap *heap, Thread *thread, Frame *frame, int cond) {
    u1 branch1 = step_pc1_and_read_code_no_submit(frame);
    u1 branch2 = step_pc2_and_read_code_no_submit(frame);
    frame->pc = (cond) ? step_pc_and_read_pc(frame, (short)(branch1 << 8) | branch2) : step_pc_and_read_pc(frame, 3);
}

void ifeq(SerialHeap *heap, Thread *thread, Frame *frame) {
    int value = pop_int(frame->operand_stack);
    ifx_(heap, thread, frame, value == 0);
}

void ifne(SerialHeap *heap, Thread *thread, Frame *frame) {
    int value = pop_int(frame->operand_stack);
    ifx_(heap, thread, frame, value != 0);
}

void iflt(SerialHeap *heap, Thread *thread, Frame *frame) {
    int value = pop_int(frame->operand_stack);
    ifx_(heap, thread, frame, value < 0);
}

void ifge(SerialHeap *heap, Thread *thread, Frame *frame) {
    int value = pop_int(frame->operand_stack);
    ifx_(heap, thread, frame, value >= 0);
}

void ifgt(SerialHeap *heap, Thread *thread, Frame *frame) {
    int value = pop_int(frame->operand_stack);
    ifx_(heap, thread, frame, value > 0);
}
void ifle(SerialHeap *heap, Thread *thread, Frame *frame) {
    int value = pop_int(frame->operand_stack);
    ifx_(heap, thread, frame, value <= 0);
}

void if_icmpx_(SerialHeap *heap, Thread *thread, Frame *frame, int cond) {
    u1 branch1 = step_pc1_and_read_code_no_submit(frame);
    u1 branch2 = step_pc2_and_read_code_no_submit(frame);
    // 如果条件成立，则将程序计数器pc前移分支1、2计算得出的offset偏移量， 否则将程pc前移3步（分别为 - 1：前移指令、2：分支一指令、3：分支二指令）
    frame->pc = (cond) ? step_pc_and_read_pc(frame, (short)(branch1 << 8) | branch2) : step_pc_and_read_pc(frame, 3);
}

void if_icmpeq(SerialHeap *heap, Thread *thread, Frame *frame) {
    int value2 = pop_int(frame->operand_stack);
    int value1 = pop_int(frame->operand_stack);
    if_icmpx_(heap, thread, frame, value1 == value2);
}

void if_icmpne(SerialHeap *heap, Thread *thread, Frame *frame) {
    int value2 = pop_int(frame->operand_stack);
    int value1 = pop_int(frame->operand_stack);
    if_icmpx_(heap, thread, frame, value1 != value2);
}

void if_icmplt(SerialHeap *heap, Thread *thread, Frame *frame) {
    int value2 = pop_int(frame->operand_stack);
    int value1 = pop_int(frame->operand_stack);
    if_icmpx_(heap, thread, frame, value1 < value2);
}

void if_icmpge(SerialHeap *heap, Thread *thread, Frame *frame) {
    int value2 = pop_int(frame->operand_stack);
    int value1 = pop_int(frame->operand_stack);
    if_icmpx_(heap, thread, frame, value1 >= value2);
}

void if_icmpgt(SerialHeap *heap, Thread *thread, Frame *frame) {
    int value2 = pop_int(frame->operand_stack);
    int value1 = pop_int(frame->operand_stack);
    if_icmpx_(heap, thread, frame, value1 > value2);
}

void if_icmple(SerialHeap *heap, Thread *thread, Frame *frame) {
    int value2 = pop_int(frame->operand_stack);
    int value1 = pop_int(frame->operand_stack);
    if_icmpx_(heap, thread, frame, value1 <= value2);
}

void if_acmpx_(SerialHeap *heap, Thread *thread, Frame *frame, int cond) {
    u1 branch1 = step_pc1_and_read_code_no_submit(frame);
    u1 branch2 = step_pc2_and_read_code_no_submit(frame);
    // 如果条件成立，则将程序计数器pc前移分支1、2计算得出的offset偏移量， 否则将程pc前移3步（分别为 - 1：前移指令、2：分支一指令、3：分支二指令）
    frame->pc = (cond) ? step_pc_and_read_pc(frame, (short)(branch1 << 8) | branch2) : step_pc_and_read_pc(frame, 3);
}

void if_acmpeq(SerialHeap *heap, Thread *thread, Frame *frame) {
    Object *value2 = pop_object(frame->operand_stack);
    Object *value1 = pop_object(frame->operand_stack);
    if_acmpx_(heap, thread, frame, value1 == value2);
}

void if_acmpne(SerialHeap *heap, Thread *thread, Frame *frame) {
    Object *value2 = pop_object(frame->operand_stack);
    Object *value1 = pop_object(frame->operand_stack);
    if_acmpx_(heap, thread, frame, value1 != value2);
}

void j_goto(SerialHeap *heap, Thread *thread, Frame *frame) {
    u1 branch1 = step_pc1_and_read_code_no_submit(frame);
    u1 branch2 = step_pc2_and_read_code_no_submit(frame);
    frame->pc = step_pc_and_read_pc(frame, (short)(branch1 << 8) | branch2);
}

void jsr(SerialHeap *heap, Thread *thread, Frame *frame) {
    u1 branch1 = step_pc1_and_read_code(frame);
    u1 branch2 = step_pc1_and_read_code(frame);
    short address = (short)(branch1 << 8) | branch2;
    push_int(frame->operand_stack, address);
    frame->pc = address;
}

void ret(SerialHeap *heap, Thread *thread, Frame *frame) {
    u1 index = step_pc1_and_read_code(frame);
    frame->pc = frame->local_variables[index]->value;
}

void tableswitch(SerialHeap *heap, Thread *thread, Frame *frame) {
    u4 _pc = frame->pc;
    step_pc(frame, 3);
    int index = pop_int(frame->operand_stack);
    int default_offset = step_pc4_and_read_u4(frame);
    int lower = step_pc4_and_read_u4(frame);
    int higher = step_pc4_and_read_u4(frame);
    int count = higher - lower + 1;
    u4 *offsets = step_pc4_and_read_u4_by_count(frame, count);
    u4 offset;
    if (index < lower || index > higher) {
        offset = default_offset;
    } else {
        offset = offsets[index - lower];
    }
    frame->pc = _pc;
    frame->pc = step_pc_and_read_pc(frame, offset);
    free(offsets);
}

void lookupswitch(SerialHeap *heap, Thread *thread, Frame *frame) {}

void ireturn(SerialHeap *heap, Thread *thread, Frame *frame) {
    Frame *next = get_prev(thread->vm_stack);
    if (NULL != next) push_slot_from(frame->operand_stack, next->operand_stack);
    frame = pop_frame(thread, heap);
    free_frame(&frame);
}

void lreturn(SerialHeap *heap, Thread *thread, Frame *frame) {
    Frame *next = get_prev(thread->vm_stack);
    if (NULL != next) push_long_from(frame->operand_stack, next->operand_stack);
    frame = pop_frame(thread, heap);
    free_frame(&frame);
}

void freturn(SerialHeap *heap, Thread *thread, Frame *frame) {
    Frame *next = get_prev(thread->vm_stack);
    if (NULL != next) push_float(next->operand_stack, pop_float(frame->operand_stack));
    frame = pop_frame(thread, heap);
    free_frame(&frame);
}

void dreturn(SerialHeap *heap, Thread *thread, Frame *frame) {
    Frame *next = get_prev(thread->vm_stack);
    if (NULL != next) push_double_from(frame->operand_stack, next->operand_stack);
    frame = pop_frame(thread, heap);
    free_frame(&frame);
}

void areturn(SerialHeap *heap, Thread *thread, Frame *frame) {
    Frame *next = get_prev(thread->vm_stack);
    if (NULL != next) push_slot_from(frame->operand_stack, next->operand_stack);
    frame = pop_frame(thread, heap);
    free_frame(&frame);
}

void j_return(SerialHeap *heap, Thread *thread, Frame *frame) {
    frame = pop_frame(thread, heap);
    free_frame(&frame);
}

void getstatic(SerialHeap *heap, Thread *thread, Frame *frame) {
    u1 byte1 = step_pc1_and_read_code(frame);
    u1 byte2 = step_pc1_and_read_code(frame);
    get_static_field_to_opstack_by_index(thread, heap, frame, (byte1 << 8) | byte2);
    step_pc_1(frame);
}

void putstatic(SerialHeap *heap, Thread *thread, Frame *frame) {
    u1 byte1 = step_pc1_and_read_code(frame);
    u1 byte2 = step_pc1_and_read_code(frame);
    put_static_field_by_index(thread, heap, frame, (byte1 << 8) | byte2);
    step_pc_1(frame);
}

void getfield(SerialHeap *heap, Thread *thread, Frame *frame) {
    u1 byte1 = step_pc1_and_read_code(frame);
    u1 byte2 = step_pc1_and_read_code(frame);
    get_field_to_opstack_by_index(thread, heap, frame, (byte1 << 8) | byte2);
    step_pc_1(frame);
}

void putfield(SerialHeap *heap, Thread *thread, Frame *frame) {
    u1 byte1 = step_pc1_and_read_code(frame);
    u1 byte2 = step_pc1_and_read_code(frame);
    put_field_by_index(thread, heap, frame, (byte1 << 8) | byte2);
    step_pc_1(frame);
}
void invokevirtual(SerialHeap *heap, Thread *thread, Frame *frame) {
    u1 byte1 = step_pc1_and_read_code(frame);
    u1 byte2 = step_pc1_and_read_code(frame);
    do_invokevirtual_by_index(thread, heap, frame, (byte1 << 8) | byte2);
    step_pc(frame, 1);
}

void invokespecial(SerialHeap *heap, Thread *thread, Frame *frame) {
    u1 byte1 = step_pc1_and_read_code(frame);
    u1 byte2 = step_pc1_and_read_code(frame);
    do_invokespecial_by_index(thread, heap, frame, (byte1 << 8) | byte2);
    step_pc(frame, 1);
}

void invokestatic(SerialHeap *heap, Thread *thread, Frame *frame) {
    u1 byte1 = step_pc1_and_read_code(frame);
    u1 byte2 = step_pc1_and_read_code(frame);
    do_invokestatic_by_index(thread, heap, frame, (byte1 << 8) | byte2);
    step_pc(frame, 1);
}

void invokeinterface(SerialHeap *heap, Thread *thread, Frame *frame) {
    u1 byte1 = step_pc1_and_read_code(frame);
    u1 byte2 = step_pc1_and_read_code(frame);
    u1 count = step_pc1_and_read_code(frame);
    step_pc_1(frame);
    do_invokeinterface_by_index(thread, heap, frame, (byte1 << 8) | byte2, count);
    step_pc(frame, 1);
}

void invokedynamic(SerialHeap *heap, Thread *thread, Frame *frame) {
    u1 byte1 = step_pc1_and_read_code(frame);
    u1 byte2 = step_pc1_and_read_code(frame);
    step_pc_2(frame);
    do_invokedynamic_by_index(thread, heap, frame, (byte1 << 8) | byte2);
    step_pc(frame, 1);
}

void new(SerialHeap *heap, Thread *thread, Frame *frame) {
    u1 byte1 = step_pc1_and_read_code(frame);
    u1 byte2 = step_pc1_and_read_code(frame);
    create_object(thread, heap, frame, (byte1 << 8) | byte2);
    step_pc_1(frame);
}

void newarray(SerialHeap *heap, Thread *thread, Frame *frame) {
    u1 type = step_pc1_and_read_code(frame);
    int count = pop_int(frame->operand_stack);
    create_array_by_type(thread, heap, frame, type, count);
    step_pc_1(frame);
}

void anewarray(SerialHeap *heap, Thread *thread, Frame *frame) {
    u1 byte1 = step_pc1_and_read_code(frame);
    u1 byte2 = step_pc1_and_read_code(frame);
    create_array_reference(thread, heap, frame, (byte1 << 8) | byte2);
    step_pc_1(frame);
}

void arraylength(SerialHeap *heap, Thread *thread, Frame *frame) {
    Slot *slot = pop_slot(frame->operand_stack);
    Array *array = slot->object_value;
    if (NULL == array) {
        printf_err("op:arraylength, array is NULL");
        exit(-1);
    }
    push_int(frame->operand_stack, array->length);
    step_pc_1(frame);
}

void athrow(SerialHeap *heap, Thread *thread, Frame *frame) {
    Object *exception = pop_object(frame->operand_stack);
    printf_err("throw %s", exception->raw_class->class_name);
    ExceptionsAttribute *exceptions = get_exception_handle(frame->constant_pool, frame->method, exception->raw_class);
    if (NULL == exceptions) {
        pop_frame(thread, heap);
    } else {
        for(int i = 0; i < exceptions->number_of_exceptions; i++) {
            ClassFile *class = get_class_by_attr_index(thread, heap, frame->constant_pool, exceptions->exception_index_table[i]);
            if (class == exception->raw_class) {}
        }
    }
    exit(-1);
}

void checkcast(SerialHeap *heap, Thread *thread, Frame *frame) {
    u1 byte1 = step_pc1_and_read_code(frame);
    u1 byte2 = step_pc1_and_read_code(frame);
    ConstantPool constant = frame->constant_pool[(byte1 << 8) | byte2];
    Object *ref = get_object(frame->operand_stack);
    if (NULL != ref) {
        ClassFile *class;
        switch (constant.tag) {
            case CONSTANT_Class: {
                CONSTANT_Class_info info = *(CONSTANT_Class_info*)constant.info;
                class = load_class_by_class_info_name_index(thread, heap, frame->constant_pool, info.name_index);
                break;
            }
            case CONSTANT_InterfaceMethodref: {
                CONSTANT_InterfaceMethodref_info info = *(CONSTANT_InterfaceMethodref_info*)constant.info;
                class = load_class_by_class_info(thread, heap, frame->constant_pool, *(CONSTANT_Class_info*)frame->constant_pool[info.class_index].info);
                break;
            }
            case CONSTANT_String: {
                CONSTANT_String_info info = *(CONSTANT_String_info*)constant.info;
                class = load_class(thread, heap, get_str_from_string_index(frame->constant_pool, info.string_index));
                break;
            }
        }
        //TODO
        if (!is_instance_of(ref->class, class)) {
            printf_err("throws ClassCastException!");
            printf_warn("DEBUG HANDLE!");
            exit(-1);
        }
    }
    step_pc_1(frame);
}

void instanceof(SerialHeap *heap, Thread *thread, Frame *frame) {
    Object *source = pop_object(frame->operand_stack);
    u1 byte1 = step_pc1_and_read_code(frame);
    u1 byte2 = step_pc1_and_read_code(frame);
    if (NULL == source) {
        push_int(frame->operand_stack, 0);
    } else {
        ClassFile *target = load_class_by_class_info_index(thread, heap, frame->constant_pool, byte1 << 8 | byte2);
        push_int(frame->operand_stack, is_instance_of(source->raw_class, target));
    }
    step_pc_1(frame);
}

void monitorenter(SerialHeap *heap, Thread *thread, Frame *frame) {
    Object *object = pop_object(frame->operand_stack);
    if (NULL == object) {
        printf_err("NULLPointerException");
        exit(-1);
    }
    monitor_enter(object->monitor, thread);
    step_pc_1(frame);
}

void monitorexit(SerialHeap *heap, Thread *thread, Frame *frame) {
    Object *object = pop_object(frame->operand_stack);
    if (NULL == object) {
        printf_err("NULLPointerException");
        exit(-1);
    }
    monitor_exit(object->monitor, thread);
    step_pc_1(frame);
}

void wide(SerialHeap *heap, Thread *thread, Frame *frame) {}

void multianewarray(SerialHeap *heap, Thread *thread, Frame *frame) {}

void ifnull(SerialHeap *heap, Thread *thread, Frame *frame) {
    Object *value = pop_object(frame->operand_stack);
    u1 branch1 = step_pc1_and_read_code_no_submit(frame);
    u1 branch2 = step_pc2_and_read_code_no_submit(frame);
    frame->pc = (value == NULL) ? step_pc_and_read_pc(frame, (short)((branch1 << 8) | branch2)) : step_pc_and_read_pc(frame, 3);
}

void ifnonnull(SerialHeap *heap, Thread *thread, Frame *frame) {
    Object *object = pop_object(frame->operand_stack);
    u1 branch1 = step_pc1_and_read_code_no_submit(frame);
    u1 branch2 = step_pc2_and_read_code_no_submit(frame);
    frame->pc = (NULL != object) ? step_pc_and_read_pc(frame, (short)((branch1 << 8) | branch2)) : step_pc_and_read_pc(frame, 3);
}

void goto_w(SerialHeap *heap, Thread *thread, Frame *frame) {
    u1 branch1 = step_pc1_and_read_code_no_submit(frame);
    u1 branch2 = step_pc2_and_read_code_no_submit(frame);
    u1 branch3 = step_pc2_and_read_code_no_submit(frame);
    u1 branch4 = step_pc2_and_read_code_no_submit(frame);
    frame->pc = step_pc_and_read_pc(frame, (int)((branch1 << 24) | (branch2 << 16) | (branch3 << 8) | branch4));
}

void jsr_w(SerialHeap *heap, Thread *thread, Frame *frame) {
    u1 branch1 = step_pc1_and_read_code(frame);
    u1 branch2 = step_pc1_and_read_code(frame);
    u1 branch3 = step_pc1_and_read_code(frame);
    u1 branch4 = step_pc1_and_read_code(frame);
    int address = (branch1 << 24) | (branch2 << 16) | (branch3 << 8) | branch4;
    push_int(frame->operand_stack, address);
    frame->pc = address;
}

//Reserved Opcodes
void breakpoint(SerialHeap *heap, Thread *thread, Frame *frame) {}
void impdep1(SerialHeap *heap, Thread *thread, Frame *frame) {}
void impdep2(SerialHeap *heap, Thread *thread, Frame *frame) {}

void init_instructions()
{
    // Constants
    instructions[0x00] = nop;
    instructions[0x01] = aconst_null;
    instructions[0x02] = iconst_m1;
    instructions[0x03] = iconst_0;
    instructions[0x04] = iconst_1;
    instructions[0x05] = iconst_2;
    instructions[0x06] = iconst_3;
    instructions[0x07] = iconst_4;
    instructions[0x08] = iconst_5;
    instructions[0x09] = lconst_0;
    instructions[0x0a] = lconst_1;
    instructions[0x0b] = fconst_0;
    instructions[0x0c] = fconst_1;
    instructions[0x0d] = fconst_2;
    instructions[0x0e] = dconst_0;
    instructions[0x0f] = dconst_1;
    instructions[0x10] = bipush;
    instructions[0x11] = sipush;
    instructions[0x12] = ldc;
    instructions[0x13] = ldc_w;
    instructions[0x14] = ldc2_w;

    //Loads
    instructions[0x15] = iload;
    instructions[0x16] = lload;
    instructions[0x17] = fload;
    instructions[0x18] = dload;
    instructions[0x19] = aload;
    instructions[0x1a] = iload_0;
    instructions[0x1b] = iload_1;
    instructions[0x1c] = iload_2;
    instructions[0x1d] = iload_3;
    instructions[0x1e] = lload_0;
    instructions[0x1f] = lload_1;
    instructions[0x20] = lload_2;
    instructions[0x21] = lload_3;
    instructions[0x22] = fload_0;
    instructions[0x23] = fload_1;
    instructions[0x24] = fload_2;
    instructions[0x25] = fload_3;
    instructions[0x26] = dload_0;
    instructions[0x27] = dload_1;
    instructions[0x28] = dload_2;
    instructions[0x29] = dload_3;
    instructions[0x2a] = aload_0;
    instructions[0x2b] = aload_1;
    instructions[0x2c] = aload_2;
    instructions[0x2d] = aload_3;
    instructions[0x2e] = iaload;
    instructions[0x2f] = laload;
    instructions[0x30] = faload;
    instructions[0x31] = daload;
    instructions[0x32] = aaload;
    instructions[0x33] = baload;
    instructions[0x34] = caload;
    instructions[0x35] = saload;

    //Stores
    instructions[0x36] = istore;
    instructions[0x37] = lstore;
    instructions[0x38] = fstore;
    instructions[0x39] = dstore;
    instructions[0x3a] = astore;
    instructions[0x3b] = istore_0;
    instructions[0x3c] = istore_1;
    instructions[0x3d] = istore_2;
    instructions[0x3e] = istore_3;
    instructions[0x3f] = lstore_0;
    instructions[0x40] = lstore_1;
    instructions[0x41] = lstore_2;
    instructions[0x42] = lstore_3;
    instructions[0x43] = fstore_0;
    instructions[0x44] = fstore_1;
    instructions[0x45] = fstore_2;
    instructions[0x46] = fstore_3;
    instructions[0x47] = dstore_0;
    instructions[0x48] = dstore_1;
    instructions[0x49] = dstore_2;
    instructions[0x4a] = dstore_3;
    instructions[0x4b] = astore_0;
    instructions[0x4c] = astore_1;
    instructions[0x4d] = astore_2;
    instructions[0x4e] = astore_3;
    instructions[0x4f] = iastore;
    instructions[0x50] = lastore;
    instructions[0x51] = fastore;
    instructions[0x52] = dastore;
    instructions[0x53] = aastore;
    instructions[0x54] = bastore;
    instructions[0x55] = castore;
    instructions[0x56] = sastore;

    //Stack
    instructions[0x57] = j_pop;
    instructions[0x58] = pop2;
    instructions[0x59] = j_dup;
    instructions[0x5a] = dup_x1;
    instructions[0x5b] = dup_x2;
    instructions[0x5c] = j_dup2;
    instructions[0x5d] = dup2_x1;
    instructions[0x5e] = dup2_x2;
    instructions[0x5f] = swap;

    //Math
    instructions[0x60] = iadd;
    instructions[0x61] = ladd;
    instructions[0x62] = fadd;
    instructions[0x63] = dadd;
    instructions[0x64] = isub;
    instructions[0x65] = lsub;
    instructions[0x66] = fsub;
    instructions[0x67] = dsub;
    instructions[0x68] = imul;
    instructions[0x69] = lmul;
    instructions[0x6a] = fmul;
    instructions[0x6b] = dmul;
    instructions[0x6c] = idiv;
    instructions[0x6d] = j_ldiv;
    instructions[0x6e] = fdiv;
    instructions[0x6f] = ddiv;
    instructions[0x70] = irem;
    instructions[0x71] = lrem;
    instructions[0x72] = frem;
    instructions[0x73] = j_drem;
    instructions[0x74] = ineg;
    instructions[0x75] = lneg;
    instructions[0x76] = fneg;
    instructions[0x77] = dneg;
    instructions[0x78] = ishl;
    instructions[0x79] = lshl;
    instructions[0x7a] = ishr;
    instructions[0x7b] = lshr;
    instructions[0x7c] = iushr;
    instructions[0x7d] = lushr;
    instructions[0x7e] = iand;
    instructions[0x7f] = land;
    instructions[0x80] = ior;
    instructions[0x81] = lor;
    instructions[0x82] = ixor;
    instructions[0x83] = lxor;
    instructions[0x84] = iinc;

    //Conversions
    instructions[0x85] = i2l;
    instructions[0x86] = i2f;
    instructions[0x87] = i2d;
    instructions[0x88] = l2i;
    instructions[0x89] = l2f;
    instructions[0x8a] = l2d;
    instructions[0x8b] = f2i;
    instructions[0x8c] = f2l;
    instructions[0x8d] = f2d;
    instructions[0x8e] = d2i;
    instructions[0x8f] = d2l;
    instructions[0x90] = d2f;
    instructions[0x91] = i2b;
    instructions[0x92] = i2c;
    instructions[0x93] = i2s;

    //Comparisons
    instructions[0x94] = lcmp;
    instructions[0x95] = fcmpl;
    instructions[0x96] = fcmpg;
    instructions[0x97] = dcmpl;
    instructions[0x98] = dcmpg;
    instructions[0x99] = ifeq;
    instructions[0x9a] = ifne;
    instructions[0x9b] = iflt;
    instructions[0x9c] = ifge;
    instructions[0x9d] = ifgt;
    instructions[0x9e] = ifle;
    instructions[0x9f] = if_icmpeq;
    instructions[0xa0] = if_icmpne;
    instructions[0xa1] = if_icmplt;
    instructions[0xa2] = if_icmpge;
    instructions[0xa3] = if_icmpgt;
    instructions[0xa4] = if_icmple;
    instructions[0xa5] = if_acmpeq;
    instructions[0xa6] = if_acmpne;

    //Control
    instructions[0xa7] = j_goto;
    instructions[0xa8] = jsr;
    instructions[0xa9] = ret;
    instructions[0xaa] = tableswitch;
    instructions[0xab] = lookupswitch;
    instructions[0xac] = ireturn;
    instructions[0xad] = lreturn;
    instructions[0xae] = freturn;
    instructions[0xaf] = dreturn;
    instructions[0xb0] = areturn;
    instructions[0xb1] = j_return;

    //References
    instructions[0xb2] = getstatic;
    instructions[0xb3] = putstatic;
    instructions[0xb4] = getfield;
    instructions[0xb5] = putfield;
    instructions[0xb6] = invokevirtual;
    instructions[0xb7] = invokespecial;
    instructions[0xb8] = invokestatic;
    instructions[0xb9] = invokeinterface;
    instructions[0xba] = invokedynamic;
    instructions[0xbb] = new;
    instructions[0xbc] = newarray;
    instructions[0xbd] = anewarray;
    instructions[0xbe] = arraylength;
    instructions[0xbf] = athrow;
    instructions[0xc0] = checkcast;
    instructions[0xc1] = instanceof;
    instructions[0xc2] = monitorenter;
    instructions[0xc3] = monitorexit;

    //Extended
    instructions[0xc4] = wide;
    instructions[0xc5] = multianewarray;
    instructions[0xc6] = ifnull;
    instructions[0xc7] = ifnonnull;
    instructions[0xc8] = goto_w;
    instructions[0xc9] = jsr_w;

    //Reserved
    instructions[0xca] = breakpoint;
    instructions[0xfe] = impdep1;
    instructions[0xff] = impdep2;
}

void init_instructions_desc()
{
    instructions_desc[0x00] = "nop";
    instructions_desc[0x01] = "aconst_null";
    instructions_desc[0x02] = "iconst_m1";
    instructions_desc[0x03] = "iconst_0";
    instructions_desc[0x04] = "iconst_1";
    instructions_desc[0x05] = "iconst_2";
    instructions_desc[0x06] = "iconst_3";
    instructions_desc[0x07] = "iconst_4";
    instructions_desc[0x08] = "iconst_5";
    instructions_desc[0x09] = "lconst_0";
    instructions_desc[0x0a] = "lconst_1";
    instructions_desc[0x0b] = "fconst_0";
    instructions_desc[0x0c] = "fconst_1";
    instructions_desc[0x0d] = "fconst_2";
    instructions_desc[0x0e] = "dconst_0";
    instructions_desc[0x0f] = "dconst_1";
    instructions_desc[0x10] = "bipush";
    instructions_desc[0x11] = "sipush";
    instructions_desc[0x12] = "ldc";
    instructions_desc[0x13] = "ldc_w";
    instructions_desc[0x14] = "ldc2_w";
    instructions_desc[0x15] = "iload";
    instructions_desc[0x16] = "lload";
    instructions_desc[0x17] = "fload";
    instructions_desc[0x18] = "dload";
    instructions_desc[0x19] = "aload";
    instructions_desc[0x1a] = "iload_0";
    instructions_desc[0x1b] = "iload_1";
    instructions_desc[0x1c] = "iload_2";
    instructions_desc[0x1d] = "iload_3";
    instructions_desc[0x1e] = "lload_0";
    instructions_desc[0x1f] = "lload_1";
    instructions_desc[0x20] = "lload_2";
    instructions_desc[0x21] = "lload_3";
    instructions_desc[0x22] = "fload_0";
    instructions_desc[0x23] = "fload_1";
    instructions_desc[0x24] = "fload_2";
    instructions_desc[0x25] = "fload_3";
    instructions_desc[0x26] = "dload_0";
    instructions_desc[0x27] = "dload_1";
    instructions_desc[0x28] = "dload_2";
    instructions_desc[0x29] = "dload_3";
    instructions_desc[0x2a] = "aload_0";
    instructions_desc[0x2b] = "aload_1";
    instructions_desc[0x2c] = "aload_2";
    instructions_desc[0x2d] = "aload_3";
    instructions_desc[0x2e] = "iaload";
    instructions_desc[0x2f] = "laload";
    instructions_desc[0x30] = "faload";
    instructions_desc[0x31] = "daload";
    instructions_desc[0x32] = "aaload";
    instructions_desc[0x33] = "baload";
    instructions_desc[0x34] = "caload";
    instructions_desc[0x35] = "saload";
    instructions_desc[0x36] = "istore";
    instructions_desc[0x37] = "lstore";
    instructions_desc[0x38] = "fstore";
    instructions_desc[0x39] = "dstore";
    instructions_desc[0x3a] = "astore";
    instructions_desc[0x3b] = "istore_0";
    instructions_desc[0x3c] = "istore_1";
    instructions_desc[0x3d] = "istore_2";
    instructions_desc[0x3e] = "istore_3";
    instructions_desc[0x3f] = "lstore_0";
    instructions_desc[0x40] = "lstore_1";
    instructions_desc[0x41] = "lstore_2";
    instructions_desc[0x42] = "lstore_3";
    instructions_desc[0x43] = "fstore_0";
    instructions_desc[0x44] = "fstore_1";
    instructions_desc[0x45] = "fstore_2";
    instructions_desc[0x46] = "fstore_3";
    instructions_desc[0x47] = "dstore_0";
    instructions_desc[0x48] = "dstore_1";
    instructions_desc[0x49] = "dstore_2";
    instructions_desc[0x4a] = "dstore_3";
    instructions_desc[0x4b] = "astore_0";
    instructions_desc[0x4c] = "astore_1";
    instructions_desc[0x4d] = "astore_2";
    instructions_desc[0x4e] = "astore_3";
    instructions_desc[0x4f] = "iastore";
    instructions_desc[0x50] = "lastore";
    instructions_desc[0x51] = "fastore";
    instructions_desc[0x52] = "dastore";
    instructions_desc[0x53] = "aastore";
    instructions_desc[0x54] = "bastore";
    instructions_desc[0x55] = "castore";
    instructions_desc[0x56] = "sastore";
    instructions_desc[0x57] = "j_pop";
    instructions_desc[0x58] = "pop2";
    instructions_desc[0x59] = "j_dup";
    instructions_desc[0x5a] = "dup_x1";
    instructions_desc[0x5b] = "dup_x2";
    instructions_desc[0x5c] = "j_dup2";
    instructions_desc[0x5d] = "dup2_x1";
    instructions_desc[0x5e] = "dup2_x2";
    instructions_desc[0x5f] = "swap";
    instructions_desc[0x60] = "iadd";
    instructions_desc[0x61] = "ladd";
    instructions_desc[0x62] = "fadd";
    instructions_desc[0x63] = "dadd";
    instructions_desc[0x64] = "isub";
    instructions_desc[0x65] = "lsub";
    instructions_desc[0x66] = "fsub";
    instructions_desc[0x67] = "dsub";
    instructions_desc[0x68] = "imul";
    instructions_desc[0x69] = "lmul";
    instructions_desc[0x6a] = "fmul";
    instructions_desc[0x6b] = "dmul";
    instructions_desc[0x6c] = "idiv";
    instructions_desc[0x6d] = "j_ldiv";
    instructions_desc[0x6e] = "fdiv";
    instructions_desc[0x6f] = "ddiv";
    instructions_desc[0x70] = "irem";
    instructions_desc[0x71] = "lrem";
    instructions_desc[0x72] = "frem";
    instructions_desc[0x73] = "j_drem";
    instructions_desc[0x74] = "ineg";
    instructions_desc[0x75] = "lneg";
    instructions_desc[0x76] = "fneg";
    instructions_desc[0x77] = "dneg";
    instructions_desc[0x78] = "ishl";
    instructions_desc[0x79] = "lshl";
    instructions_desc[0x7a] = "ishr";
    instructions_desc[0x7b] = "lshr";
    instructions_desc[0x7c] = "iushr";
    instructions_desc[0x7d] = "lushr";
    instructions_desc[0x7e] = "iand";
    instructions_desc[0x7f] = "land";
    instructions_desc[0x80] = "ior";
    instructions_desc[0x81] = "lor";
    instructions_desc[0x82] = "ixor";
    instructions_desc[0x83] = "lxor";
    instructions_desc[0x84] = "iinc";
    instructions_desc[0x85] = "i2l";
    instructions_desc[0x86] = "i2f";
    instructions_desc[0x87] = "i2d";
    instructions_desc[0x88] = "l2i";
    instructions_desc[0x89] = "l2f";
    instructions_desc[0x8a] = "l2d";
    instructions_desc[0x8b] = "f2i";
    instructions_desc[0x8c] = "f2l";
    instructions_desc[0x8d] = "f2d";
    instructions_desc[0x8e] = "d2i";
    instructions_desc[0x8f] = "d2l";
    instructions_desc[0x90] = "d2f";
    instructions_desc[0x91] = "i2b";
    instructions_desc[0x92] = "i2c";
    instructions_desc[0x93] = "i2s";
    instructions_desc[0x94] = "lcmp";
    instructions_desc[0x95] = "fcmpl";
    instructions_desc[0x96] = "fcmpg";
    instructions_desc[0x97] = "dcmpl";
    instructions_desc[0x98] = "dcmpg";
    instructions_desc[0x99] = "ifeq";
    instructions_desc[0x9a] = "ifne";
    instructions_desc[0x9b] = "iflt";
    instructions_desc[0x9c] = "ifge";
    instructions_desc[0x9d] = "ifgt";
    instructions_desc[0x9e] = "ifle";
    instructions_desc[0x9f] = "if_icmpeq";
    instructions_desc[0xa0] = "if_icmpne";
    instructions_desc[0xa1] = "if_icmplt";
    instructions_desc[0xa2] = "if_icmpge";
    instructions_desc[0xa3] = "if_icmpgt";
    instructions_desc[0xa4] = "if_icmple";
    instructions_desc[0xa5] = "if_acmpeq";
    instructions_desc[0xa6] = "if_acmpne";
    instructions_desc[0xa7] = "j_goto";
    instructions_desc[0xa8] = "jsr";
    instructions_desc[0xa9] = "ret";
    instructions_desc[0xaa] = "tableswitch";
    instructions_desc[0xab] = "lookupswitch";
    instructions_desc[0xac] = "ireturn";
    instructions_desc[0xad] = "lreturn";
    instructions_desc[0xae] = "freturn";
    instructions_desc[0xaf] = "dreturn";
    instructions_desc[0xb0] = "areturn";
    instructions_desc[0xb1] = "j_return";
    instructions_desc[0xb2] = "getstatic";
    instructions_desc[0xb3] = "putstatic";
    instructions_desc[0xb4] = "getfield";
    instructions_desc[0xb5] = "putfield";
    instructions_desc[0xb6] = "invokevirtual";
    instructions_desc[0xb7] = "invokespecial";
    instructions_desc[0xb8] = "invokestatic";
    instructions_desc[0xb9] = "invokeinterface";
    instructions_desc[0xba] = "invokedynamic";
    instructions_desc[0xbb] = "new";
    instructions_desc[0xbc] = "newarray";
    instructions_desc[0xbd] = "anewarray";
    instructions_desc[0xbe] = "arraylength";
    instructions_desc[0xbf] = "athrow";
    instructions_desc[0xc0] = "checkcast";
    instructions_desc[0xc1] = "instanceof";
    instructions_desc[0xc2] = "monitorenter";
    instructions_desc[0xc3] = "monitorexit";
    instructions_desc[0xc4] = "wide";
    instructions_desc[0xc5] = "multianewarray";
    instructions_desc[0xc6] = "ifnull";
    instructions_desc[0xc7] = "ifnonnull";
    instructions_desc[0xc8] = "goto_w";
    instructions_desc[0xc9] = "jsr_w";
    instructions_desc[0xca] = "breakpoint";
    instructions_desc[0xfe] = "impdep1";
    instructions_desc[0xff] = "impdep2";
}

Frame *pop_frame(Thread *thread, SerialHeap *heap)
{
    printf_debug("\t\t\t\t[framestack]");
    Frame *frame = pop_stack(thread->vm_stack);
    if (NULL != frame->pop_hook) {
        printf_warn("[INVOKE-HOOK]");
        frame->pop_hook(thread, heap, frame, get_stack(thread->vm_stack));
    }
    printf_warn("\n\t\t\t<-[ESC] %s - %s.%s%s\n\n", instructions_desc[read_code(frame)], frame->class->class_name, frame->method->name, frame->method->desc);
    return frame;
}

long count = 0;

void exec(Operator operator, SerialHeap *heap, Thread *thread, Frame *frame)
{
    char *t_name = "";
    if (NULL != thread->jthread) {
        Object *t_name_obj = get_field_object_value_by_name_and_desc(thread->jthread, "name", "Ljava/lang/String;");
        if (NULL != t_name_obj) t_name = get_str_field_value_by_object(t_name_obj);
    }
    printf_debug("\t\t\t[%ld - %s] - %s.%s%s\t\t\t#%d %s:\n", count++, t_name, frame->class->class_name, frame->method->name, frame->method->desc, frame->pc, instructions_desc[read_code(frame)]);
    frame->count = count;
    operator(heap, thread, frame);
    Frame *_frame = get_stack(thread->vm_stack);
    if (NULL != _frame && NULL != _frame->class) {
        printf_debug("\t\t\t\t[opstack.%s.%s]", _frame->class->class_name, _frame->method->name);
        print_stack(_frame->operand_stack);
        printf_debug("\t\t\t\t[localvars.%s.%s]", _frame->class->class_name, _frame->method->name);
        print_local_variables(_frame);
    }
}

void single_invoke(SerialHeap *heap, ClassFile *class, char *method_name, char *method_desc, Stack *params)
{
    printf_warn("\t\t\t[SINGLE-INVOKE-IN] %s.%s%s", class->class_name, method_name, method_desc);
    Thread *thread = create_thread(100, 100);
    MethodInfo *method = find_method_with_desc(thread, heap, class, method_name, method_desc);
    Frame *frame = create_vm_frame_by_method_with_push(thread, class, method);
    int size = params->size;
    Slot **slots = pop_slot_with_num(params, params->size);
    for (int i = 0; i < size; i++) {
        set_localvar_with_slot_copy(frame, i, slots[i]);
    }
    run(thread, heap);
    printf_warn("\t\t\t[SINGLE-INVOKE-ESC] %s.%s%s", class->class_name, method_name, method_desc);
}

void run(Thread *thread, SerialHeap *heap) {
    if (NULL == get_stack(thread->vm_stack)) return;
    do {
        Frame *frame = get_stack(thread->vm_stack);
        exec(instructions[read_code(frame)], heap, thread, frame);
    } while (!is_empty_stack(thread->vm_stack));
}

void run_by_env(Env *env) {
    run(env->thread, env->heap);
}