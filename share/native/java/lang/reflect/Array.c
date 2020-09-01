//
// Created by wangzhanzhi on 2020/8/31.
//

#include "Array.h"

void java_lang_reflect_Array_newArray_9Ljava_lang_Class1I0Ljava_lang_Object1(Thread *thread, SerialHeap *heap, Frame *frame)
{
    Object *this = get_localvar_this(frame);
    if (NULL == this) {
        printf_err("Need ThrowNullPointerException");
        exit(-1);
    }
    int length = get_localvar(frame, 1);
    ClassFile *class = this->raw_class;
    push_object(frame->operand_stack, malloc_array(heap, class, length));
}