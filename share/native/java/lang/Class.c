//
// Created by wangzhanzhi on 2020/8/6.
//

#include "Class.h"

void java_lang_Class_registerNatives_90V(Thread *thread, SerialHeap *heap, Frame *frame)
{
}

void java_lang_Class_getPrimitiveClass_9Ljava_lang_String10Ljava_lang_Class(Thread *thread, SerialHeap *heap, Frame *frame)
{
    Object *object = frame->local_variables[0]->object_value;
    Slot *field = get_field_from_map(&object->fields, "value", "[C");
    ClassFile *class = load_primitive_class(thread, heap, field->object_value);
    push_object(frame->operand_stack, class->class_object);
}

void java_lang_Class_desiredAssertionStatus0_9Ljava_lang_Class10Z(Thread *thread, SerialHeap *heap, Frame *frame)
{
    push_int(frame->operand_stack, 0);
}