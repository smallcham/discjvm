//
// Created by wangzhanzhi on 2020/8/6.
//

#include "Object.h"

void java_lang_Object_registerNatives_90V(Thread *thread, Frame *frame)
{
}

void java_lang_Object_getClass_90Ljava_lang_Class(Thread *thread, Frame *frame)
{
    push_object(frame->operand_stack, frame->class->class_object);
}