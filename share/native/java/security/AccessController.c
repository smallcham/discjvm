//
// Created by wangzhanzhi on 2020/8/15.
//

#include "AccessController.h"

void java_security_AccessController_getStackAccessControlContext_90Ljava_security_AccessControlContext1(Thread *thread, SerialHeap *heap, Frame *frame)
{
    //TODO in jdk11 source "src/java.base/share/native/libjava/AccessController.c" JVM_GetStackAccessControlContext
   push_slot(frame->operand_stack, NULL_SLOT);
}