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
    Thread *_thread = NULL == thread->real_thread ? thread : thread->real_thread;
    Stack *vm_stack = _thread->vm_stack;
    if (vm_stack->size <= 0) {
        if (VM_STACK_SIZE >= 1 && NULL != frame->method) {
            put_value_field_by_name_and_desc(throwable, "depth", "I", 1);
            put_object_value_field_by_name_and_desc(throwable, "backtrace", "Ljava/lang/Object;", malloc_object(_thread, heap, load_class(_thread, heap, "java/lang/Object")));
        }
        return;
    }
    put_value_field_by_name_and_desc(throwable, "depth", "I", vm_stack->size);
    Array *stack_trace_element = malloc_array(_thread, heap, load_primitive_class(_thread, heap, "[Ljava/lang/StackTraceElement"), vm_stack->size);
    ClassFile *stack_trace_class = load_class(_thread, heap, "java/lang/StackTraceElement");
    for (int i = 0; i < stack_trace_element->length; ++i) {
        Frame *top_frame = get_stack_offset(vm_stack, i);
        ClassFile *method_class = top_frame->method->class;
        Object *element = malloc_object(_thread, heap, stack_trace_class);
        put_object_value_field_by_name_and_desc(element, "classLoaderName", "Ljava/lang/String;", create_str_slot_set_str(_thread, heap, "")->object_value);
        put_object_value_field_by_name_and_desc(element, "moduleName", "Ljava/lang/String;", create_str_slot_set_str(_thread, heap, "")->object_value);
        put_object_value_field_by_name_and_desc(element, "moduleVersion", "Ljava/lang/String;", create_str_slot_set_str(_thread, heap, "0")->object_value);
        put_object_value_field_by_name_and_desc(element, "declaringClass", "Ljava/lang/String;", create_str_slot_set_str(_thread, heap, method_class->class_name)->object_value);
        put_object_value_field_by_name_and_desc(element, "methodName", "Ljava/lang/String;", create_str_slot_set_str(_thread, heap, top_frame->method->name)->object_value);
        put_object_value_field_by_name_and_desc(element, "fileName", "Ljava/lang/String;", create_str_slot_set_str(_thread, heap, method_class->simple_class_name)->object_value);
        put_value_field_by_name_and_desc(element, "lineNumber", "I", get_line_number(top_frame->pc - 1, top_frame->method->code_attribute->line_number_table_attr));
        stack_trace_element->objects[i] = element;
    }
    put_static_field_by_name_and_desc(throwable->class, "UNASSIGNED_STACK", "[Ljava/lang/StackTraceElement;", stack_trace_element);
    push_object(frame->operand_stack, throwable);
}