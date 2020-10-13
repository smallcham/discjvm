//
// Created by wangzhanzhi on 2020/9/26.
//

#include "Reflection.h"

void jdk_internal_reflect_Reflection_getCallerClass_90Ljava_lang_Class1(Thread *thread, SerialHeap *heap, Frame *frame)
{
    Frame *caller_frame = get_stack_offset(thread->vm_stack, 2);
    push_object(frame->operand_stack, caller_frame->class->class_object);
}

/** Retrieves the access flags written to the class file. For
    inner classes these flags may differ from those returned by
    Class.getModifiers(), which searches the InnerClasses
    attribute to find the source-level access flags. This is used
    instead of Class.getModifiers() for run-time access checks due
    to compatibility reasons; see 4471811. Only the values of the
    low 13 bits (i.e., a mask of 0x1FFF) are guaranteed to be
    valid. */
void jdk_internal_reflect_Reflection_getClassAccessFlags_9Ljava_lang_Class10I(Thread *thread, SerialHeap *heap, Frame *frame)
{
    Object *class = get_ref_localvar(frame, 0);
    push_int(frame->operand_stack, class->raw_class->access_flags);
}