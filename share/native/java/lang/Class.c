//
// Created by wangzhanzhi on 2020/8/6.
//

#include "Class.h"

void java_lang_Class_registerNatives_90V(Thread *thread, SerialHeap *heap, Frame *frame)
{
}

void java_lang_Class_getPrimitiveClass_9Ljava_lang_String10Ljava_lang_Class(Thread *thread, SerialHeap *heap, Frame *frame)
{
    Object *object = get_localvar_this(frame);
//    Slot *field = get_field_from_map(&object->fields, "value", "[C");
    FieldInfo *field = get_field_by_name_and_desc(object->class, "value", "[B");
    ClassFile *class = load_primitive_class(thread, heap, object->fields[field->offset].object_value);
    push_object(frame->operand_stack, class->class_object);
}

void java_lang_Class_desiredAssertionStatus0_9Ljava_lang_Class10Z(Thread *thread, SerialHeap *heap, Frame *frame)
{
    push_int(frame->operand_stack, 0);
}

void java_lang_Class_isArray_90Z(Thread *thread, SerialHeap *heap, Frame *frame)
{
    Object *object = get_localvar_this(frame);
    push_int(frame->operand_stack, is_array_by_name(object->raw_class->class_name));
}