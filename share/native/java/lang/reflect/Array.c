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
    char *_arr_name = malloc(strlen(class->class_name) + 2);
    sprintf(_arr_name, "[L%s", class->class_name);
    Array *arr = malloc_array(thread, heap, load_primitive_class(thread, heap, _arr_name), length);
    free(_arr_name);
    push_object(frame->operand_stack, arr);
    if (NULL != class->class_object) {
        put_field_by_name_and_desc(arr->class->class_object, "componentType", "Ljava/lang/Class;", create_object_slot_set_object(heap, class->class_object));
    }
}