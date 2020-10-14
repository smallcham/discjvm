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
    Object *this = get_localvar_this(frame);
    int priority = get_localvar(frame, 1);
    put_value_field_by_name_and_desc(this, "priority", "I", priority);
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
    Thread *_thread = this->monitor->owner;
    int alive = NULL != this && NULL != this->raw_class && NULL != this->monitor && NULL != this->monitor->owner && !is_empty_stack(_thread->vm_stack);
    if (alive) {
        printf_err("throw IllegalThreadStateException");
        exit(-1);
    }
    push_int(frame->operand_stack, alive);
}

void java_lang_Thread_start0_90V(Thread *thread, SerialHeap *heap, Frame *frame)
{
    //TODO
//    Object *this = get_localvar_this(frame);
//    ClassFile *class = this->class;
//
//    Thread *new_thread = create_thread_with_jthread(VM_STACK_SIZE, C_STACK_SIZE, this);
//    MethodInfo *method = find_method_with_desc(new_thread, heap, class, "run", "()V");
//    push_object(frame->operand_stack, this);
//    create_vm_frame_by_method_add_params_plus1(new_thread, class, frame, method);
//    Env *env = malloc(sizeof(Env));
//    env->thread = new_thread;
//    env->heap = heap;
//    pthread_t *new_pthread = malloc(sizeof(pthread_t));
//    this->monitor->owner = new_thread;
//    new_thread->pthread = new_pthread;
//    int ret;
//    ret = pthread_create(new_pthread, NULL, (void *(*)(void *)) run_by_env, env);
//    if (ret != 0) {
//        printf_err("thread create error!");
//        exit(-1);
//    }
}