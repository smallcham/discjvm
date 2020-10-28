//
// Created by wangzhanzhi on 2020/8/15.
//

#include "Throwable.h"

/*
 * Fill in the current stack trace in this exception.  This is
 * usually called automatically when the exception is created but it
 * may also be called explicitly by the user.  This routine returns
 * `this' so you can write 'throw e.fillInStackTrace();'
 */
void java_lang_Throwable_fillInStackTrace_9I0Ljava_lang_Throwable1(Thread *thread, SerialHeap *heap, Frame *frame)
{
    Object *throwable = get_localvar_this(frame);
    Stack *vm_stack = thread->vm_stack;
//    if (vm_stack->size <= 0) {
//        if (VM_STACK_SIZE >= 1 && NULL != frame->method) {
//            put_value_field_by_name_and_desc(throwable, "depth", "I", 1);
//            put_object_value_field_by_name_and_desc(throwable, "backtrace", "Ljava/lang/Object;", malloc_object(thread, heap, load_class(thread, heap, "java/lang/Object")));
//        }
//        return;
//    }
    Array *stack_trace_element = malloc_array(thread, heap, load_primitive_class(thread, heap, "[Ljava/lang/StackTraceElement"), vm_stack->size);
    ClassFile *stack_trace_class = load_class_ensure_init(thread, heap, "java/lang/StackTraceElement");
    for (int i = 0; i < stack_trace_element->length; ++i) {
        Frame *top_frame = get_stack_offset(thread->vm_stack, i);
        ClassFile *method_class = top_frame->method->class;
        Object *element = malloc_object(thread, heap, stack_trace_class);
        put_object_value_field_by_name_and_desc(element, "classLoaderName", "Ljava/lang/String;", create_str_slot_set_str(thread, heap, "NULL")->object_value);
        put_object_value_field_by_name_and_desc(element, "moduleName", "Ljava/lang/String;", create_str_slot_set_str(thread, heap, "java.base")->object_value);
        put_object_value_field_by_name_and_desc(element, "moduleVersion", "Ljava/lang/String;", create_str_slot_set_str(thread, heap, "0")->object_value);
        put_object_value_field_by_name_and_desc(element, "declaringClass", "Ljava/lang/String;", create_str_slot_set_str(thread, heap, method_class->standard_class_name)->object_value);
        put_object_value_field_by_name_and_desc(element, "methodName", "Ljava/lang/String;", create_str_slot_set_str(thread, heap, top_frame->method->name)->object_value);
        put_object_value_field_by_name_and_desc(element, "fileName", "Ljava/lang/String;", create_str_slot_set_str(thread, heap, "java.base.jmod")->object_value);
        put_value_field_by_name_and_desc(element, "lineNumber", "I", 0);
        stack_trace_element->objects[i] = element;
    }
//    put_object_value_field_by_name_and_desc(throwable, "stackTrace", "[Ljava/lang/StackTraceElement;", stack_trace_element);
    put_static_field_by_name_and_desc(throwable->class, "UNASSIGNED_STACK", "[Ljava/lang/StackTraceElement;", stack_trace_element);
    Array *_array = get_static_field_slot_by_name_and_desc(throwable->class, "UNASSIGNED_STACK", "[Ljava/lang/StackTraceElement;")->object_value;

    push_object(frame->operand_stack, throwable);
}