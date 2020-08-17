//
// Created by wangzhanzhi on 2020/8/6.
//

#include "Object.h"

void java_lang_Object_registerNatives_90V(Thread *thread, SerialHeap *heap, Frame *frame)
{
}

void java_lang_Object_getClass_90Ljava_lang_Class(Thread *thread, SerialHeap *heap, Frame *frame)
{
    push_object(frame->operand_stack, frame->class->class_object);
}

void java_lang_Object_hashCode_90I(Thread *thread, SerialHeap *heap, Frame *frame)
{
    Object *object = frame->local_variables[0]->object_value;
    push_int(frame->operand_stack, (int)object);
}