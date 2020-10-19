//
// Created by wangzhanzhi on 2020/10/19.
//

#include "MethodHandleNatives.h"

void java_lang_invoke_MethodHandleNatives_registerNatives_90V(Thread *thread, SerialHeap *heap, Frame *frame)
{

}

void java_lang_invoke_MethodHandleNatives_resolve_9Ljava_lang_invoke_MemberName1Ljava_lang_Class1Z0Ljava_lang_invoke_MemberName1(Thread *thread, SerialHeap *heap, Frame *frame)
{
    Object *self = get_ref_localvar(frame, 0);
    Object *caller = get_ref_localvar(frame, 1);
    int speculative_resolve = get_localvar(frame, 3);

    Object *class = get_field_object_value_by_name_and_desc(self, "clazz", "Ljava/lang/Class;");
    char *name = get_str_field_value_by_object(get_field_object_value_by_name_and_desc(self, "name", "Ljava/lang/String;"));
    Object *type = get_field_object_value_by_name_and_desc(self, "type", "Ljava/lang/Object;");
    int flags = get_field_value_by_name_and_desc(self, "flags", "I");
}