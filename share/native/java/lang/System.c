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
    }
    free(_keys);
}

void java_lang_System_arraycopy_9Ljava_lang_Object1ILjava_lang_Object1II0V(Thread *thread, SerialHeap *heap, Frame *frame)
{
    Array *source = get_localvar_this(frame);
    u8 s_pos = get_localvar(frame, 1);
    Array *dest = get_ref_localvar(frame, 2);
    u8 d_pos = get_localvar(frame, 3);
    u8 length = get_localvar(frame, 4);
    if (NULL == source || NULL == dest) {
        printf_err("Need Throw Exception");
        exit(-1);
    }
    if (s_pos < 0 || d_pos < 0 || length < 0 || s_pos + length > source->length || d_pos + length > dest->length) {
        printf_err("Need Throw IndexOutOfBoundsException");
        exit(-1);
    }
    for (int i = s_pos, j = d_pos; i < s_pos + length; i++, j++) {
//        dest->objects[j] = source->objects[i];
        Object *s_obj = source->objects[i];
        Object *t_obj;
        copy_object(heap, &t_obj, s_obj);
//        for (int k = 0; k < s_obj->raw_class->object_fields_count; k++) {
//            t_obj->fields[k].value = s_obj->fields[k].value;
//            t_obj->fields[k].object_value = s_obj->fields[k].object_value;

//        }
        dest->objects[j] = t_obj;
    }
}

void java_lang_System_nanoTime_90J(Thread *thread, SerialHeap *heap, Frame *frame)
{
    struct timespec spec;
    clock_gettime(CLOCK_REALTIME, &spec);
    long sec = spec.tv_sec;
    push_long(frame->operand_stack, 1000 * sec + spec.tv_nsec / 1000);
}

//添加frame弹出钩子, 用以消除setProperty方法areturn指令返回的值
void pop_return_hook_(Thread *thread, SerialHeap *heap, Frame *frame, Frame *next_frame)
{
    if (NULL != next_frame) pop_slot(next_frame->operand_stack);
}