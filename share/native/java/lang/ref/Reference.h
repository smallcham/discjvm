//
// Created by wangzhanzhi on 2020/10/5.
//

#ifndef DISCJVM_REFERENCE_H
#define DISCJVM_REFERENCE_H

#include "../../../../../model/thread.h"
#include "../../../../../runtime/class_loader.h"

void java_lang_ref_Reference_waitForReferencePendingList_90V(Thread *thread, SerialHeap *heap, Frame *frame);

void java_lang_ref_Reference_getAndClearReferencePendingList_90Ljava_lang_ref_Reference1(Thread *thread, SerialHeap *heap, Frame *frame);

#endif //DISCJVM_REFERENCE_H
