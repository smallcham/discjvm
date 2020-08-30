//
// Created by wangzhanzhi on 2020/8/13.
//

#include "Unsafe.h"

void jdk_internal_misc_Unsafe_registerNatives_90V(Thread *thread, SerialHeap *heap, Frame *frame)
{
}

void jdk_internal_misc_Unsafe_arrayBaseOffset0_9java_lang_Class10I(Thread *thread, SerialHeap *heap, Frame *frame)
{
    Array *ref = frame->local_variables[1]->object_value;
    if (!is_array(ref)) {
        printf_err("Invalid Class, [%s] Not A Array", ref->class->class_name);
        exit(-1);
    } else if (is_object_array(ref)) {
        push_int(frame->operand_stack, 1);
    } else if (is_primitive_array(ref)) {
        push_int(frame->operand_stack, 0);
    } else {
        //ShouldNotReachHere
        printf_err("ShouldNotReachHere");
    }
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
    Object *object = get_ref_localvar(frame, 1);
    Object *string = get_ref_localvar(frame, 2);
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
    Object *ref = get_ref_localvar(frame, 1);
    u8 offset = get_long_localvar(frame, 2);
    Slot *slot = &ref->fields[offset];
    u8 e = get_localvar(frame, 4);
    u8 x = get_localvar(frame, 5);
    if (e == slot->value) {
        slot->value = x;
        push_int(frame->operand_stack, 1);
    } else {
        push_int(frame->operand_stack, 0);
    }
}

void jdk_internal_misc_Unsafe_compareAndSetObject_9Ljava_lang_Object1JLjava_lang_Object1Ljava_lang_Object10Z(Thread *thread, SerialHeap *heap, Frame *frame)
{
    u8 offset = get_long_localvar(frame, 2);
    Object *e = get_ref_localvar(frame, 4);
    Object *x = get_ref_localvar(frame, 5);
    void *object = get_ref_localvar(frame, 1);
    if (offset > 0) {
        Array *ref = object;
        ref->objects[0] = x;
    } else {
        set_ref_localvar(frame, 1, x);
    }
    push_int(frame->operand_stack, 1);

//    if (e == x) {
//        push_int(frame->operand_stack, 1);
//    } else {
//        push_int(frame->operand_stack, 0);
//    }
}

void jdk_internal_misc_Unsafe_compareAndSetLong_9Ljava_lang_Object1JJJ0Z(Thread *thread, SerialHeap *heap, Frame *frame)
{
    u8 offset = get_long_localvar(frame, 2);
    u8 e = get_localvar(frame, 4);
    u8 x = get_localvar(frame, 5);
    Slot *slot = NULL;
    if(is_array(get_ref_localvar(frame, 1))) {
        Array *ref = get_ref_localvar(frame, 1);
        slot = &ref->objects[0]->fields[offset];
    } else {
        Object *ref = get_ref_localvar(frame, 1);
        slot = &ref->fields[offset];
    }
    if (e == slot->value) {
        slot->value = x;
        push_int(frame->operand_stack, 1);
    } else {
        push_int(frame->operand_stack, 0);
    }
}

void jdk_internal_misc_Unsafe_getObjectVolatile_9Ljava_lang_Object1J0Ljava_lang_Object1(Thread *thread, SerialHeap *heap, Frame *frame)
{
    //TODO
    u8 offset = get_long_localvar(frame, 2);
    Slot *slot = NULL;
    if(is_array(get_ref_localvar(frame, 1))) {
        Array *ref = get_ref_localvar(frame, 1);
        if (NULL == ref->objects[0]) {
            push_slot(frame->operand_stack, NULL_SLOT);
            return;
        } else {
            slot = &ref->objects[0]->fields[offset];
        }
    } else {
        Object *ref = get_ref_localvar(frame, 1);
        slot = &ref->fields[offset];
    }
    push_slot(frame->operand_stack, slot);
}