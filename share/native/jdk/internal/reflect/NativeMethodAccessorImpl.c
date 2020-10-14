//
// Created by wangzhanzhi on 2020/10/13.
//

#include "NativeMethodAccessorImpl.h"

void jdk_internal_reflect_NativeMethodAccessorImpl_invoke0_9Ljava_lang_reflect_Method1Ljava_lang_Object1sLjava_lang_Object10Ljava_lang_Object1(Thread *thread, SerialHeap *heap, Frame *frame)
{
    Object *method = get_ref_localvar(frame, 0);
    Object *object = get_ref_localvar(frame, 1);
    Array *args = get_ref_localvar(frame, 2);
    int slot = get_field_value_by_name_and_desc(method, "slot", "I");
    MethodInfo *method_info = &object->raw_class->methods[slot];
    Stack *params = create_unlimit_stack();
    if (!is_static(method_info->access_flags)) {
        push_object(params, object->raw_class->class_object);
    }
    for (int i = 0; i < args->length; i++) {
        //TODO
        printf_err("not complete");
        args->objects[i];
        exit(-1);
    }
    if (!is_static(method_info->access_flags)) {
        create_vm_frame_by_method_add_params_plus1(thread, object->raw_class, params, method_info);
    } else {
        create_vm_frame_by_method_add_params(thread, object->raw_class, params, method_info);
    }
}