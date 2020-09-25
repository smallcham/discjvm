//
// Created by wangzhanzhi on 2020/9/26.
//

#include "Reflection.h"

void jdk_internal_reflect_Reflection_getCallerClass_90Ljava_lang_Class1(Thread *thread, SerialHeap *heap, Frame *frame)
{
    Frame *caller_frame = get_stack_offset(thread->vm_stack, 2);
    push_object(frame->operand_stack, caller_frame->class->class_object);
}