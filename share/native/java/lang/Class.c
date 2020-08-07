//
// Created by wangzhanzhi on 2020/8/6.
//

#include "Class.h"

void java_lang_Class_registerNatives_90V(Thread *thread, Frame *frame)
{
}

void java_lang_Class_getPrimitiveClass_9Ljava_lang_String10Ljava_lang_Class(Thread *thread, Frame *frame)
{
    Object *object = pop_object(frame->operand_stack);
    Slot *field = get_field_from_map(&object->fields, object->class->class_name, "value", "[B");
    field->object_value;
    frame->class->class_name;
}