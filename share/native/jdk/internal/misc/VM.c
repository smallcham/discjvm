//
// Created by wangzhanzhi on 2020/8/30.
//

#include "VM.h"

void jdk_internal_misc_VM_initialize_90V(Thread *thread, SerialHeap *heap, Frame *frame)
{
    //TODO
    // Registers implementations of native methods described in methods[]
    // above.
    // In particular, registers JVM_GetNanoTimeAdjustment as the implementation
    // of the native VM.getNanoTimeAdjustment - avoiding the cost of
    // introducing a Java_jdk_internal_misc_VM_getNanoTimeAdjustment wrapper
    printf_warn("TODO, Do Nothing.");
    sleep(1);
}

void jdk_internal_misc_VM_initializeFromArchive_9Ljava_lang_Class10V(Thread *thread, SerialHeap *heap, Frame *frame)
{
    Object *object = get_ref_localvar(frame, 0);
    //TODO
    printf_warn("TODO, Do Nothing.");
    sleep(1);
}