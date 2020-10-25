//
// Created by wangzhanzhi on 2020/10/19.
//

#ifndef DISCJVM_METHODHANDLENATIVES_H
#define DISCJVM_METHODHANDLENATIVES_H

#include "../../../../../model/thread.h"
#include "../../../../../runtime/jvm.h"

enum {
    MN_IS_METHOD            = 0x00010000,
    MN_IS_CONSTRUCTOR       = 0x00020000,
    MN_IS_FIELD             = 0x00040000,
    MN_IS_TYPE              = 0x00080000,
    MN_CALLER_SENSITIVE     = 0x00100000,
    MN_REFERENCE_KIND_SHIFT = 24,
    MN_REFERENCE_KIND_MASK  = 0x0F000000 >> MN_REFERENCE_KIND_SHIFT,
    MN_SEARCH_SUPERCLASSES  = 0x00100000,
    MN_SEARCH_INTERFACES    = 0x00200000,
    ALL_KINDS               = MN_IS_METHOD | MN_IS_CONSTRUCTOR | MN_IS_FIELD | MN_IS_TYPE
};

typedef struct {
    MethodInfo *vm_target;
    void *vm_holder;
} ResolvedMethodName;

void java_lang_invoke_MethodHandleNatives_registerNatives_90V(Thread *thread, SerialHeap *heap, Frame *frame);

void java_lang_invoke_MethodHandleNatives_resolve_9Ljava_lang_invoke_MemberName1Ljava_lang_Class1Z0Ljava_lang_invoke_MemberName1(Thread *thread, SerialHeap *heap, Frame *frame);

#endif //DISCJVM_METHODHANDLENATIVES_H
