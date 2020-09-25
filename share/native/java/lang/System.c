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

//    MethodInfo *method = find_method_with_desc(thread, heap, object->class, "setProperty", "(Ljava/lang/String;Ljava/lang/String;)Ljava/lang/Object;");
    char **_keys = keys(&VM_OPTS);
    for (int i = 0; i < VM_OPTS->size; i++) {
//        push_object(frame->operand_stack, object);
//        create_string_object_without_back(thread, heap, frame, _keys[i]);
//        create_string_object_without_back(thread, heap, frame, get_map(&VM_OPTS, _keys[i]));
//        Frame *new_frame = create_vm_frame_by_method(thread, object->class, method, get_method_code(object->class->constant_pool, *method));
//        add_params_and_plus1(frame, new_frame, method);
//        new_frame->pop_hook = (PopHook)pop_return_hook_;
//        push_stack(thread->vm_stack, new_frame);

        Stack *params = create_unlimit_stack();
        push_slot(params, create_object_slot_set_object(heap, object));
        push_slot(params, create_str_slot_set_str(thread, heap, _keys[i]));
        push_slot(params, create_str_slot_set_str(thread, heap, get_map(&VM_OPTS, _keys[i])));
        single_invoke(heap, object->class, "setProperty", "(Ljava/lang/String;Ljava/lang/String;)Ljava/lang/Object;", params);

//        Stack *params2 = create_unlimit_stack();
//        push_slot(params2, create_object_slot_set_object(heap, object));
//        push_slot(params2, create_str_slot_set_str(thread, heap, _keys[i]));
//        single_invoke(heap, object->class, "getProperty", "(Ljava/lang/String;)Ljava/lang/String;", params2);
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
    if (is_primitive_array(source)) {
        int type_size = primitive_size(source->raw_class->class_name);
        memcpy((char*)dest->objects + (d_pos * type_size), (char*)source->objects + (s_pos * type_size), length * type_size);
    } else {
        for (int i = s_pos, j = d_pos; i < s_pos + length; i++, j++) {
            Object *s_obj = source->objects[i];
            Object *t_obj = malloc_object(heap, s_obj->raw_class);
            for (int k = 0; k < s_obj->raw_class->object_fields_count; k++) {
                t_obj->fields[k].value = s_obj->fields[k].value;
                t_obj->fields[k].object_value = s_obj->fields[k].object_value;
            }
            dest->objects[j] = t_obj;
        }
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

void java_lang_System_setIn0_9Ljava_io_InputStream10V(Thread *thread, SerialHeap *heap, Frame *frame)
{
    Object *in = get_ref_localvar(frame, 0);
    put_static_field_by_name_and_desc(frame->class, "in", "Ljava/io/InputStream;", in);
}

void java_lang_System_setOut0_9Ljava_io_PrintStream10V(Thread *thread, SerialHeap *heap, Frame *frame)
{
    Object *out = get_ref_localvar(frame, 0);
    put_static_field_by_name_and_desc(frame->class, "out", "Ljava/io/PrintStream;", out);
}

void java_lang_System_setErr0_9Ljava_io_PrintStream10V(Thread *thread, SerialHeap *heap, Frame *frame)
{
    Object *err = get_ref_localvar(frame, 0);
    put_static_field_by_name_and_desc(frame->class, "err", "Ljava/io/PrintStream;", err);
}