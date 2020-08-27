//
// Created by wangzhanzhi on 2020/8/13.
//

#include "Unsafe.h"

void jdk_internal_misc_Unsafe_registerNatives_90V(Thread *thread, SerialHeap *heap, Frame *frame)
{
}

void jdk_internal_misc_Unsafe_arrayBaseOffset0_9java_lang_Class10I(Thread *thread, SerialHeap *heap, Frame *frame)
{
    Object *object = frame->local_variables[1]->object_value;
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

void jdk_internal_misc_Unsafe_compareAndSetObject_9Ljava_lang_Object1JLjava_lang_Object1Ljava_lang_Object10Z(Thread *thread, SerialHeap *heap, Frame *frame)
{
    u8 higher = frame->local_variables[2]->value;
    u8 lower = frame->local_variables[3]->value;
    Object *expect = frame->local_variables[4]->object_value;
    Object *value = frame->local_variables[5]->object_value;
    Slot *slot = NULL;
    if(is_array(frame->local_variables[1]->object_value)) {
        Array *ref = frame->local_variables[1]->object_value;
        slot = &ref->objects[0]->fields[higher | lower];
    } else {
        Object *ref = frame->local_variables[1]->object_value;
        slot = &ref->fields[higher | lower];
    }
    if (expect == slot->object_value) {
        slot->object_value = value;
        push_int(frame->operand_stack, 1);
    } else {
        push_int(frame->operand_stack, 0);
    }
}

void jdk_internal_misc_Unsafe_compareAndSetLong_9Ljava_lang_Object1JJJ0Z(Thread *thread, SerialHeap *heap, Frame *frame)
{
    u8 higher = frame->local_variables[2]->value;
    u8 lower = frame->local_variables[3]->value;
    u8 expect = frame->local_variables[4]->value;
    u8 value = frame->local_variables[5]->value;
    Slot *slot = NULL;
    if(is_array(frame->local_variables[1]->object_value)) {
        Array *ref = frame->local_variables[1]->object_value;
        slot = &ref->objects[0]->fields[higher | lower];
    } else {
        Object *ref = frame->local_variables[1]->object_value;
        slot = &ref->fields[higher | lower];
    }
    if (expect == slot->value) {
        slot->value = value;
        push_int(frame->operand_stack, 1);
    } else {
        push_int(frame->operand_stack, 0);
    }
}

void jdk_internal_misc_Unsafe_getObjectVolatile_9Ljava_lang_Object1J0Ljava_lang_Object1(Thread *thread, SerialHeap *heap, Frame *frame)
{
    u8 higher = frame->local_variables[2]->value;
    u8 lower = frame->local_variables[3]->value;
    Slot *slot = NULL;
    if(is_array(frame->local_variables[1]->object_value)) {
        Array *ref = frame->local_variables[1]->object_value;
        slot = &ref->objects[0]->fields[higher | lower];
    } else {
        Object *ref = frame->local_variables[1]->object_value;
        slot = &ref->fields[higher | lower];
    }
//    FieldInfo field = ref->class->fields[idx];
//    if (field.offset >= ref->class->object_fields_count) {
//        push_slot(frame->operand_stack, NULL_SLOT);
//    } else {
//        push_slot(frame->operand_stack, ref->fields[field.offset].object_value);
//    }
    //TODO
    push_slot(frame->operand_stack, NULL_SLOT);
}