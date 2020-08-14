//
// Created by wangzhanzhi on 2020/8/14.
//

#include "Runtime.h"

void java_lang_Runtime_registerNatives_90V(Thread *thread, SerialHeap *heap, Frame *frame) {}

void java_lang_Runtime_availableProcessors_90I(Thread *thread, SerialHeap *heap, Frame *frame)
{
    push_int(frame->operand_stack, get_nprocs_conf());
}