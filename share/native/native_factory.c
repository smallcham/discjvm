//
// Created by wangzhanzhi on 2020/8/6.
//

#include "native_factory.h"

Frame *create_c_frame(Thread *thread, SerialHeap *heap, Frame *frame, char *class_name, MethodInfo* method);

void init_native_factory()
{
    //函数名 '左括号' 替换为 '9', '右括号' 替换为 '0', '/' 替换为 '_', ';' 替换为 '1'
    native_pool = create_map();
    //Object
    put_map(&native_pool, "java/lang/Object.registerNatives()V", java_lang_Object_registerNatives_90V);
    put_map(&native_pool, "java/lang/Object.getClass()Ljava/lang/Class;", java_lang_Object_getClass_90Ljava_lang_Class);
    put_map(&native_pool, "java/lang/Object.hashCode()I", java_lang_Object_hashCode_90I);

    //Class
    put_map(&native_pool, "java/lang/Class.registerNatives()V", java_lang_Class_registerNatives_90V);
    put_map(&native_pool, "java/lang/Class.getPrimitiveClass(Ljava/lang/String;)Ljava/lang/Class;", java_lang_Class_getPrimitiveClass_9Ljava_lang_String10Ljava_lang_Class);
    put_map(&native_pool, "java/lang/Class.desiredAssertionStatus0(Ljava/lang/Class;)Z", java_lang_Class_desiredAssertionStatus0_9Ljava_lang_Class10Z);
    put_map(&native_pool, "java/lang/Class.isArray()Z", java_lang_Class_isArray_90Z);

    //System
    put_map(&native_pool, "java/lang/System.registerNatives()V", java_lang_System_registerNatives_90V);
    put_map(&native_pool, "java/lang/System.initProperties(Ljava/util/Properties;)Ljava/util/Properties;", java_lang_System_initProperties_9Ljava_util_Properties10Ljava_util_Properties1);

    //Thread
    put_map(&native_pool, "java/lang/Thread.registerNatives()V", java_lang_Thread_registerNatives_90V);
    put_map(&native_pool, "java/lang/Thread.currentThread()Ljava/lang/Thread;", java_lang_Thread_currentThread_90Ljava_lang_Thread1);
    put_map(&native_pool, "java/lang/Thread.setPriority0(I)V", java_lang_Thread_setPriority0_9I0V);

    //Unsafe
    put_map(&native_pool, "jdk/internal/misc/Unsafe.registerNatives()V", jdk_internal_misc_Unsafe_registerNatives_90V);
    put_map(&native_pool, "jdk/internal/misc/Unsafe.arrayBaseOffset0(Ljava/lang/Class;)I", jdk_internal_misc_Unsafe_arrayBaseOffset0_9java_lang_Class10I);
    put_map(&native_pool, "jdk/internal/misc/Unsafe.arrayIndexScale0(Ljava/lang/Class;)I", jdk_internal_misc_Unsafe_arrayIndexScale0_9Ljava_lang_Class10I);
    put_map(&native_pool, "jdk/internal/misc/Unsafe.addressSize0()I", jdk_internal_misc_Unsafe_addressSize0_90I);
    put_map(&native_pool, "jdk/internal/misc/Unsafe.isBigEndian0()Z", jdk_internal_misc_Unsafe_isBigEndian0_90Z);
    put_map(&native_pool, "jdk/internal/misc/Unsafe.unalignedAccess0()Z", jdk_internal_misc_Unsafe_unalignedAccess0_90Z);
    put_map(&native_pool, "jdk/internal/misc/Unsafe.objectFieldOffset1(Ljava/lang/Class;Ljava/lang/String;)J", jdk_internal_misc_Unsafe_objectFieldOffset1_9Ljava_lang_Class1Ljava_lang_String10J);
    put_map(&native_pool, "jdk/internal/misc/Unsafe.storeFence()V", jdk_internal_misc_Unsafe_storeFence_90V);
    put_map(&native_pool, "jdk/internal/misc/Unsafe.compareAndSetInt(Ljava/lang/Object;JII)Z", jdk_internal_misc_Unsafe_compareAndSetInt_9Ljava_lang_Object1JII0Z);
    put_map(&native_pool, "jdk/internal/misc/Unsafe.getObjectVolatile(Ljava/lang/Object;J)Ljava/lang/Object;", jdk_internal_misc_Unsafe_getObjectVolatile_9Ljava_lang_Object1J0Ljava_lang_Object1);
    put_map(&native_pool, "jdk/internal/misc/Unsafe.compareAndSetObject(Ljava/lang/Object;JLjava/lang/Object;Ljava/lang/Object;)Z", jdk_internal_misc_Unsafe_compareAndSetObject_9Ljava_lang_Object1JLjava_lang_Object1Ljava_lang_Object10Z);
    put_map(&native_pool, "jdk/internal/misc/Unsafe.compareAndSetLong(Ljava/lang/Object;JJJ)Z", jdk_internal_misc_Unsafe_compareAndSetLong_9Ljava_lang_Object1JJJ0Z);

    //ClassLoader
    put_map(&native_pool, "java/lang/ClassLoader.registerNatives()V", java_lang_ClassLoader_registerNatives_90V);

    //Runtime
    put_map(&native_pool, "java/lang/Runtime.registerNatives()V", java_lang_Runtime_registerNatives_90V);
    put_map(&native_pool, "java/lang/Runtime.availableProcessors()I", java_lang_Runtime_availableProcessors_90I);

    //AccessController
    put_map(&native_pool, "java/security/AccessController.getStackAccessControlContext()Ljava/security/AccessControlContext;", java_security_AccessController_getStackAccessControlContext_90Ljava_security_AccessControlContext1);

    //Throwable
    put_map(&native_pool, "java/lang/Throwable.fillInStackTrace(I)Ljava/lang/Throwable;", java_lang_Throwable_fillInStackTrace_9I0Ljava_lang_Throwable1);

    //VM
    put_map(&native_pool, "jdk/internal/misc/VM.initialize()V", jdk_internal_misc_VM_initialize_90V);

    //Array
    put_map(&native_pool, "java/lang/reflect/Array.newArray(Ljava/lang/Class;I)Ljava/lang/Object;", java_lang_reflect_Array_newArray_9Ljava_lang_Class1I0Ljava_lang_Object1);
}

NativeMethod find_native(char *class_name, char *method_name, char *method_desc)
{
    char *key = malloc(strlen(class_name) + strlen(method_name) + strlen(method_desc) + 2);
    sprintf(key, "%s.%s%s", class_name, method_name, method_desc);
    NativeMethod method = get_map(&native_pool, key);
    free(key);
    if (NULL == method) {
        printf_err("native method \"%s.%s%s\" not exists!\n", class_name, method_name, method_desc);
        exit(-1);
    }
    return method;
}

void invoke_native(Thread *thread, SerialHeap *heap)
{
    if (NULL == get_stack(thread->c_stack)) return;
    do {
        printf("\t\t\t\t[nativestack]");
        Frame *frame = pop_stack(thread->c_stack);
        NativeMethod method = frame->native_method;
        method(thread, heap, frame);
        frame->native_method = NULL;
        free(frame);
    } while (!is_empty_stack(thread->c_stack));
}

void print_native_log(Frame *frame, MethodInfo *method)
{
    printf("\t\t\t\t[opstack.%s.%s]", frame->class->class_name, frame->method->name);
    print_stack(frame->operand_stack);
    printf("\t\t\t\t[localvars.%s.%s]", frame->class->class_name, frame->method->name);
    print_local_variables(frame);
    printf_warn("[**ESC-NATIVE] %s.%s.%s\n", frame->class->class_name, method->name, method->desc);
}

Frame *create_c_frame(Thread *thread, SerialHeap *heap, Frame *frame, char *class_name, MethodInfo* method)
{
    Frame *new_frame = malloc(sizeof(Frame) + sizeof(Slot) * (method->params_count + 1));
    new_frame->native_method = find_native(class_name, method->name, method->desc);
    new_frame->operand_stack = frame->operand_stack;
    new_frame->constant_pool = frame->constant_pool;
    new_frame->method = method;
    new_frame->code_info = NULL;
    new_frame->pop_hook = NULL;
    new_frame->class = frame->class;
    new_frame->pc = 0;
    push_stack(thread->c_stack, new_frame);
    return new_frame;
}

Frame *create_c_frame_and_invoke_add_params_plus1(Thread *thread, SerialHeap *heap, Frame *frame, char *class_name, MethodInfo *method)
{
    Frame *new_frame = create_c_frame(thread, heap, frame, class_name, method);
    add_params_and_plus1(frame, new_frame, method);
    printf_warn("[**INVOKE-NATIVE] %s.%s.%s\n", class_name, method->name, method->desc);
    invoke_native(thread, heap);
    print_native_log(frame, method);
    return new_frame;
}

Frame *create_c_frame_and_invoke_add_params(Thread *thread, SerialHeap *heap, Frame *frame, char *class_name, MethodInfo *method)
{
    Frame *new_frame = create_c_frame(thread, heap, frame, class_name, method);
    add_params(frame, new_frame, method);
    printf_warn("[**INVOKE-NATIVE] %s.%s.%s\n", class_name, method->name, method->desc);
    invoke_native(thread, heap);
    print_native_log(frame, method);
    return new_frame;
}