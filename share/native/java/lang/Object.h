//
// Created by wangzhanzhi on 2020/8/6.
//

#ifndef DISCJVM_OBJECT_H
#define DISCJVM_OBJECT_H

#include "../../../../model/thread.h"

void java_lang_Object_registerNatives_90V(Thread *thread, Frame *frame);

void java_lang_Object_getClass_90Ljava_lang_Class(Thread *thread, Frame *frame);

#endif //DISCJVM_OBJECT_H
