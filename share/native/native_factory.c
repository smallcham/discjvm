//
// Created by wangzhanzhi on 2020/8/6.
//

#include "native_factory.h"

void init_native_factory()
{
    //函数名 '左括号' 替换为 '9', '右括号' 替换为 '0', '/' 替换为 '_'
    native_pool = create_map();
    //Object
    put_map(&native_pool, "java/lang/Object.registerNatives()V", java_lang_Object_registerNatives_90V);
    put_map(&native_pool, "java/lang/Object.getClass()Ljava/lang/Class;", java_lang_Object_getClass_90Ljava_lang_Class);

    //Class
    put_map(&native_pool, "java/lang/Class.registerNatives()V", java_lang_Class_registerNatives_90V);
    put_map(&native_pool, "java/lang/Class.getPrimitiveClass(Ljava/lang/String;)Ljava/lang/Class;", java_lang_Class_getPrimitiveClass_9Ljava_lang_String10Ljava_lang_Class);

    //System
    put_map(&native_pool, "java/lang/System.registerNatives()V", java_lang_System_registerNatives_90V);

    //Thread
    put_map(&native_pool, "java/lang/Thread.registerNatives()V", java_lang_Thread_registerNatives_90V);
}

NativeMethod find_native(char *class_name, char *method_name, char *method_desc)
{
    char *key = malloc(strlen(class_name) + strlen(method_name) + strlen(method_desc) + 2);
    sprintf(key, "%s.%s%s", class_name, method_name, method_desc);
    NativeMethod method = get_map(&native_pool, key);
    free(key);
    return method;
}

void invoke_native(Thread *thread)
{
    if (NULL == get_stack(thread->c_stack)) return;
    do {
        printf("\t\t\t\t[nativestack]");
        Frame *frame = pop_stack(thread->c_stack);
        NativeMethod method = frame->native_method;
        method(thread, frame);
        frame->native_method = NULL;
    } while (!is_empty_stack(thread->c_stack));
}

void create_c_frame_and_invoke(Thread *thread, Frame *frame, char *class_name, char *method_name, char *method_desc)
{
    frame->native_method = find_native(class_name, method_name, method_desc);
    push_stack(thread->c_stack, frame);
    printf("[**INVOKENATIVE] %s.%s.%s\n", class_name, method_name, method_desc);
    invoke_native(thread);
    printf("\t\t\t\t[opstack.%s.%s]", frame->class->class_name, frame->method->name);
    print_stack(frame->operand_stack);
    printf("\t\t\t\t[localvars.%s.%s]", frame->class->class_name, frame->method->name);
    print_local_variables(frame);
    printf("[**EXCNATIVE] %s.%s.%s\n", class_name, method_name, method_desc);
}