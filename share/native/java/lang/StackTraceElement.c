//
// Created by wangzhanzhi on 2020/10/28.
//

#include "StackTraceElement.h"

/*
 * Sets the given stack trace elements with the backtrace
 * of the given Throwable.
 */
void java_lang_StackTraceElement_initStackTraceElements_9sLjava_lang_StackTraceElement1Ljava_lang_Throwable10V(Thread *thread, SerialHeap *heap, Frame *frame)
{
    Array *elements = get_ref_localvar(frame, 0);
    Object *x = get_ref_localvar(frame, 1);
    Array *ar = get_field_object_value_by_name_and_desc(x, "stackTrace", "[Ljava/lang/StackTraceElement;");
    printf(ar);
//    put_object_value_field_by_name_and_desc(x, "stackTrace", "[Ljava/lang/StackTraceElement;", elements);
}