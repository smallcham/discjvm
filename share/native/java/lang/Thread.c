//
// Created by wangzhanzhi on 2020/8/6.
//

#include "Thread.h"

void java_lang_Thread_registerNatives_90V(Thread *thread, SerialHeap *heap, Frame *frame)
{
}

void java_lang_Thread_currentThread_90Ljava_lang_Thread1(Thread *thread, SerialHeap *heap, Frame *frame)
{
    push_object(frame->operand_stack, thread->jthread);
}

void java_lang_Thread_setPriority0_9I0V(Thread *thread, SerialHeap *heap, Frame *frame)
{
    //TODO in jdk11 source "src/java.base/share/native/libjava/Thread.c" call -> jvm.cpp:2925:JVM_SetThreadPriority
}

/**
 * Tests if this thread is alive. A thread is alive if it has
 * been started and has not yet died.
 *
 * @return  {@code true} if this thread is alive;
 *          {@code false} otherwise.
 */
void java_lang_Thread_isAlive_90Z(Thread *thread, SerialHeap *heap, Frame *frame)
{
    //TODO
    Object *this = get_localvar_this(frame);
    int alive = 0;
//    int alive = !is_empty_stack(thread->vm_stack) && NULL != this && NULL != this->raw_class;
    if (alive) {
        printf_err("throw IllegalThreadStateException");
        exit(-1);
    }
    push_int(frame->operand_stack, alive);
}

void java_lang_Thread_start0_90V(Thread *thread, SerialHeap *heap, Frame *frame)
{
    //TODO
    Object *this = get_localvar_this(frame);
    ClassFile *class = this->raw_class;

    Thread new_thread = create_thread(100, 100);
    MethodInfo *method = find_method_with_desc(&new_thread, heap, class, "run", "()V");
    create_vm_frame_by_method_add_params_plus1(&new_thread, class, frame, method, get_method_code(class->constant_pool, *method));
    Env env = {&new_thread, heap};
    pthread_t new_pthread;
    int ret;
    ret = pthread_create(&new_pthread, NULL, (void *(*)(void *)) run_by_env, &env);
}