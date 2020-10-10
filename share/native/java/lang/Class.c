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
    ClassFile *class = load_primitive_class_by_str_array(thread, heap, get_str_field_array_value_by_object(object));
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

void java_lang_Class_initClassName_90Ljava_lang_String1(Thread *thread, SerialHeap *heap, Frame *frame)
{
    Object *this = get_localvar_this(frame);
    push_slot(frame->operand_stack, create_str_slot_set_str(thread, heap, this->raw_class->class_name));
}

void java_lang_Class_forName0_9Ljava_lang_String1ZLjava_lang_ClassLoader1Ljava_lang_Class10Ljava_lang_Class1(Thread *thread, SerialHeap *heap, Frame *frame)
{
    char *name = get_str_field_value_by_object(get_ref_localvar(frame, 0));
    int initialize = get_localvar(frame, 1);
    ClassFile *class = load_class(thread, heap, name);
    if (initialize && class_is_not_init(class)) {
        Frame *current = get_stack(thread->vm_stack);
        push_slot(current->operand_stack, get_slot_localvar(frame, 0));
        push_slot(current->operand_stack, get_slot_localvar(frame, 1));
        push_slot(current->operand_stack, get_slot_localvar(frame, 2));
        push_slot(current->operand_stack, get_slot_localvar(frame, 3));
        back_pc(current, 3);
        init_class(thread, heap, class);
    } else {
        push_object(frame->operand_stack, class->class_object);
    }
}

void java_lang_Class_isPrimitive_90Z(Thread *thread, SerialHeap *heap, Frame *frame)
{
    Object *this = get_localvar_this(frame);
    push_int(frame->operand_stack, is_full_primitive_desc(this->raw_class->class_name));
}