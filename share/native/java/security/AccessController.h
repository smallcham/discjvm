//
// Created by wangzhanzhi on 2020/8/15.
//

#ifndef DISCJVM_ACCESSCONTROLLER_H
#define DISCJVM_ACCESSCONTROLLER_H

#include "../../../../model/thread.h"
#include "../../../../runtime/jvm.h"

void java_security_AccessController_getStackAccessControlContext_90Ljava_security_AccessControlContext1(Thread *thread, SerialHeap *heap, Frame *frame);

void java_security_AccessController_doPrivileged_9Ljava_security_PrivilegedAction10Ljava_lang_Object1(Thread *thread, SerialHeap *heap, Frame *frame);

#endif //DISCJVM_ACCESSCONTROLLER_H
