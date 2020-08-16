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
    Slot *value = get_field_from_map(&object->fields, "slot", "I");
    push_long(frame->operand_stack, value->value);
}

void jdk_internal_misc_Unsafe_storeFence_90V(Thread *thread, SerialHeap *heap, Frame *frame)
{
    //TODO src/hotspot/share/prims/unsafe.cpp call OrderAccess::release();
}