//
// Created by wangzhanzhi on 2020/8/6.
//

#include "Object.h"

void java_lang_Object_registerNatives_90V(Thread *thread, SerialHeap *heap, Frame *frame)
{
}

void java_lang_Object_getClass_90Ljava_lang_Class(Thread *thread, SerialHeap *heap, Frame *frame)
{
    Object *this = get_localvar_this(frame);
    push_object(frame->operand_stack, this->class->class_object);
}

void java_lang_Object_hashCode_90I(Thread *thread, SerialHeap *heap, Frame *frame)
{
    Slot *slot = get_slot_localvar(frame, 0);
    push_int(frame->operand_stack, hash_code((char*)&slot->object_value));
}

void java_lang_Object_notifyAll_90V(Thread *thread, SerialHeap *heap, Frame *frame)
{
    //TODO
}