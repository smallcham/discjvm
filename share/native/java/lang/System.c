//
// Created by wangzhanzhi on 2020/8/6.
//

#include "System.h"

void java_lang_System_registerNatives_90V(Thread *thread, SerialHeap *heap, Frame *frame)
{
}

void java_lang_System_initProperties_9Ljava_util_Properties10Ljava_util_Properties1(Thread *thread, SerialHeap *heap, Frame *frame)
{
    //TODO 这里逻辑有问题
    Object *object = frame->local_variables[0]->object_value;
//    push_object(frame->operand_stack, object);

    MethodInfo *method = find_method_with_desc(thread, heap, object->class, "setProperty", "(Ljava/lang/String;Ljava/lang/String;)Ljava/lang/Object;");
    char **_keys = keys(&VM_OPTS);
    for (int i = 0; i < VM_OPTS->size; i++) {
        push_object(frame->operand_stack, object);
        create_string_object_without_back(thread, heap, frame, _keys[i]);
        create_string_object_without_back(thread, heap, frame, get_map(&VM_OPTS, _keys[i]));
        create_vm_frame_by_method_add_params_plus1(thread, object->class, frame, method, get_method_code(object->class->constant_pool, *method));
    }
    free(_keys);
//    printf_err("java_lang_System_initProperties_9Ljava_util_Properties10Ljava_util_Properties1 not complete");
//    exit(-1);
}