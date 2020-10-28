//
// Created by wangzhanzhi on 2020/10/28.
//

#include "StackTraceElement.h"

/*
 * Sets the given stack trace elements with the backtrace
 * of the given Throwable.
 */
void java_lang_StackTraceElement_initStackTraceElements_9sLjava_lang_StackTraceElement1Ljava_lang_Throwable10V(Thread *thread, SerialHeap *heap, Frame *frame)
{
    Array *elements = get_ref_localvar(frame, 0);
    Object *x = get_ref_localvar(frame, 1);
    Array *traces = get_static_field_slot_by_name_and_desc(x->class, "UNASSIGNED_STACK", "[Ljava/lang/StackTraceElement;")->object_value;
    for (int i = 0; i < elements->length; ++i) {
        Object *class_name_obj = get_field_object_value_by_name_and_desc(traces->objects[i], "declaringClass", "Ljava/lang/String;");
        char *class_name = get_str_field_value_by_object(class_name_obj);
        ClassFile *declaring_class = load_class(thread, heap, class_name);
        put_object_value_field_by_name_and_desc(elements->objects[i], "declaringClassObject", "Ljava/lang/Class;", declaring_class->class_object);
        put_object_value_field_by_name_and_desc(elements->objects[i], "classLoaderName", "Ljava/lang/String;", get_field_object_value_by_name_and_desc(traces->objects[i], "classLoaderName", "Ljava/lang/String;"));
        put_object_value_field_by_name_and_desc(elements->objects[i], "moduleName", "Ljava/lang/String;", get_field_object_value_by_name_and_desc(traces->objects[i], "moduleName", "Ljava/lang/String;"));
        put_object_value_field_by_name_and_desc(elements->objects[i], "moduleVersion", "Ljava/lang/String;", get_field_object_value_by_name_and_desc(traces->objects[i], "moduleVersion", "Ljava/lang/String;"));
        put_object_value_field_by_name_and_desc(elements->objects[i], "declaringClass", "Ljava/lang/String;", create_str_slot_set_str(thread, heap, declaring_class->standard_class_name)->object_value);
        put_object_value_field_by_name_and_desc(elements->objects[i], "methodName", "Ljava/lang/String;", get_field_object_value_by_name_and_desc(traces->objects[i], "methodName", "Ljava/lang/String;"));
        put_object_value_field_by_name_and_desc(elements->objects[i], "fileName", "Ljava/lang/String;", get_field_object_value_by_name_and_desc(traces->objects[i], "fileName", "Ljava/lang/String;"));
        put_value_field_by_name_and_desc(elements->objects[i], "lineNumber", "I", get_field_value_by_name_and_desc(traces->objects[i], "lineNumber", "I"));
    }
}