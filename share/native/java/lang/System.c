//
// Created by wangzhanzhi on 2020/8/6.
//

#include "System.h"

void pop_return_hook_(Thread *thread, SerialHeap *heap, Frame *frame, Frame *next_frame);

void java_lang_System_registerNatives_90V(Thread *thread, SerialHeap *heap, Frame *frame)
{
}

void java_lang_System_initProperties_9Ljava_util_Properties10Ljava_util_Properties1(Thread *thread, SerialHeap *heap, Frame *frame)
{
    Object *object = frame->local_variables[0]->object_value;
    push_object(frame->operand_stack, object);

    MethodInfo *method = find_method_with_desc(thread, heap, object->class, "setProperty", "(Ljava/lang/String;Ljava/lang/String;)Ljava/lang/Object;");
    char **_keys = keys(&VM_OPTS);
    for (int i = 0; i < VM_OPTS->size; i++) {
        push_object(frame->operand_stack, object);
        create_string_object_without_back(thread, heap, frame, _keys[i]);
        create_string_object_without_back(thread, heap, frame, get_map(&VM_OPTS, _keys[i]));
        Frame *new_frame = create_vm_frame_by_method(thread, object->class, method, get_method_code(object->class->constant_pool, *method));
        add_params_and_plus1(frame, new_frame, method);
        new_frame->pop_hook = (PopHook)pop_return_hook_;
        push_stack(thread->vm_stack, new_frame);
//        create_vm_frame_by_method_add_params_plus1(thread, object->class, frame, method, get_method_code(object->class->constant_pool, *method));

    }
    free(_keys);
}

//添加frame弹出钩子, 用以消除setProperty方法areturn指令返回的值
void pop_return_hook_(Thread *thread, SerialHeap *heap, Frame *frame, Frame *next_frame)
{
    if (NULL != next_frame) pop_slot(next_frame->operand_stack);
}