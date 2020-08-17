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
    char *value = get_str_field_from_map(&string->fields);
    //TODO computer field offset, being complete.
    long offset = -1;
    for (int i = 0; i < object->class->fields_count; i++) {
        if (0 != (object->class->fields[i].access_flags & ACC_STATIC)) continue;
        if (strcmp(object->class->fields[i].name, value) == 0) {
            offset = (long)get_field_from_map(&object->fields, value, object->class->fields[i].desc);
            break;
        }
    }
    if (offset < 0) {
        printf_err("offset calc err!");
        exit(-1);
    }
    push_long(frame->operand_stack, offset);
}

void jdk_internal_misc_Unsafe_storeFence_90V(Thread *thread, SerialHeap *heap, Frame *frame)
{
    //TODO src/hotspot/share/prims/unsafe.cpp call OrderAccess::release();
}

void jdk_internal_misc_Unsafe_compareAndSetInt_9Ljava_lang_Object1JII0Z(Thread *thread, SerialHeap *heap, Frame *frame)
{
//    Object *ref = frame->local_variables[1]->object_value;
    int higher = frame->local_variables[2]->value;
    int lower = frame->local_variables[3]->value;
    Slot *slot = (Slot*)(((int)higher & 0xffff0000) | (long)lower & 0x0000ffff);
    int expect = frame->local_variables[4]->value;
    int value = frame->local_variables[5]->value;
    if (expect == slot->value) {
        slot->value = value;
        push_int(frame->operand_stack, 1);
    } else {
        push_int(frame->operand_stack, 0);
    }
}