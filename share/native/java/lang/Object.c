//
// Created by wangzhanzhi on 2020/8/6.
//

#include "Object.h"

void java_lang_Object_registerNatives_90V(Thread *thread, SerialHeap *heap, Frame *frame)
{
}

void java_lang_Object_getClass_90Ljava_lang_Class(Thread *thread, SerialHeap *heap, Frame *frame)
{
    Object *this = get_localvar_this(frame);
    push_object(frame->operand_stack, this->class->class_object);
}

void java_lang_Object_hashCode_90I(Thread *thread, SerialHeap *heap, Frame *frame)
{
    Slot *slot = get_slot_localvar(frame, 0);
    int hash;
    if (slot->is_string) {
        hash = hash_code(slot->object_value);
    } else {
        Object *object = slot->object_value;
        if (strcmp(object->class->class_name, "java/lang/String") == 0) {
            hash = hash_code(get_str_field_value_by_object(object));
        } else {
            hash = hash_code((char*)&object);
        }
    }
    push_int(frame->operand_stack, hash);
}