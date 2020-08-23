//
// Created by wangzhanzhi on 2020/8/13.
//

#include "Unsafe.h"

void jdk_internal_misc_Unsafe_registerNatives_90V(Thread *thread, SerialHeap *heap, Frame *frame)
{
}

void jdk_internal_misc_Unsafe_arrayBaseOffset0_9java_lang_Class10I(Thread *thread, SerialHeap *heap, Frame *frame)
{
    push_int(frame->operand_stack, 0);
}

void jdk_internal_misc_Unsafe_arrayIndexScale0_9Ljava_lang_Class10I(Thread *thread, SerialHeap *heap, Frame *frame)
{
    push_int(frame->operand_stack, 1);
}

void jdk_internal_misc_Unsafe_addressSize0_90I(Thread *thread, SerialHeap *heap, Frame *frame)
{
    push_int(frame->operand_stack, 8);
}

void jdk_internal_misc_Unsafe_isBigEndian0_90Z(Thread *thread, SerialHeap *heap, Frame *frame)
{
    push_int(frame->operand_stack, 1);
}

void jdk_internal_misc_Unsafe_unalignedAccess0_90Z(Thread *thread, SerialHeap *heap, Frame *frame)
{
    push_int(frame->operand_stack, 1);
}

void jdk_internal_misc_Unsafe_objectFieldOffset1_9Ljava_lang_Class1Ljava_lang_String10J(Thread *thread, SerialHeap *heap, Frame *frame)
{
    Object *object = frame->local_variables[1]->object_value;
    Object *string = frame->local_variables[2]->object_value;
    char *name = get_str_field_value_by_object(string);
    FieldInfo *field = get_field_by_name(object->class, name);
    push_long(frame->operand_stack, field->offset);
}

void jdk_internal_misc_Unsafe_storeFence_90V(Thread *thread, SerialHeap *heap, Frame *frame)
{
    //TODO src/hotspot/share/prims/unsafe.cpp call OrderAccess::release();
}

void jdk_internal_misc_Unsafe_compareAndSetInt_9Ljava_lang_Object1JII0Z(Thread *thread, SerialHeap *heap, Frame *frame)
{
    Object *ref = frame->local_variables[1]->object_value;
    u8 higher = frame->local_variables[2]->value;
    u8 lower = frame->local_variables[3]->value;
    Slot *slot = &ref->fields[higher | lower];
    u8 expect = frame->local_variables[4]->value;
    u8 value = frame->local_variables[5]->value;
    if (expect == slot->value) {
        slot->value = value;
        push_int(frame->operand_stack, 1);
    } else {
        push_int(frame->operand_stack, 0);
    }
}

void jdk_internal_misc_Unsafe_getObjectVolatile_9Ljava_lang_Object1J0Ljava_lang_Object1(Thread *thread, SerialHeap *heap, Frame *frame)
{
    Object *ref = frame->local_variables[1]->object_value;
    long higher = frame->local_variables[2]->value;
    long lower = frame->local_variables[3]->value;
    push_object(frame->operand_stack, ref->fields[higher | lower].object_value);
//    push_object(frame->operand_stack, ref->fields[higher | lower].object_value);
//    printf_err("err");
//    exit(-1);
}