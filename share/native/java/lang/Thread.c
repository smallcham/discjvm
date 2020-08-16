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