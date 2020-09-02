//
// Created by wangzhanzhi on 2020/9/2.
//

#ifndef DISCJVM_DOUBLE_H
#define DISCJVM_DOUBLE_H

#include "../../../../model/thread.h"
#include "../../../../runtime/class_loader.h"

void java_lang_Double_doubleToRawLongBits_9D0J(Thread *thread, SerialHeap *heap, Frame *frame);

void java_lang_Double_longBitsToDouble_9J0D(Thread *thread, SerialHeap *heap, Frame *frame);

#endif //DISCJVM_DOUBLE_H
