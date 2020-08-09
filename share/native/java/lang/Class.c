//
// Created by wangzhanzhi on 2020/8/6.
//

#include "Class.h"

void java_lang_Class_registerNatives_90V(Thread *thread, SerialHeap *heap, Frame *frame)
{
}

void java_lang_Class_getPrimitiveClass_9Ljava_lang_String10Ljava_lang_Class(Thread *thread, SerialHeap *heap, Frame *frame)
{
    Object *object = pop_object(frame->operand_stack);
    Slot *field = get_field_from_map(&object->fields, object->class->class_name, "value", "[B");
    ClassFile *class = load_primitive_class(thread, heap, field->object_value);
    push_object(frame->operand_stack, class->class_object);
}