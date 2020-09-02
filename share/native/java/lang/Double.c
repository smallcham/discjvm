//
// Created by wangzhanzhi on 2020/9/2.
//

#include "Double.h"

void java_lang_Double_doubleToRawLongBits_9D0J(Thread *thread, SerialHeap *heap, Frame *frame)
{
    double value = get_long_localvar(frame, 0);
    push_long(frame->operand_stack, value);
}

void java_lang_Double_longBitsToDouble_9J0D(Thread *thread, SerialHeap *heap, Frame *frame)
{
    long value = get_long_localvar(frame, 0);
    push_double(frame->operand_stack, (double)value);
}