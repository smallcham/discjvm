//
// Created by wangzhanzhi on 2020/9/2.
//

#include "Float.h"

void java_lang_Float_floatToRawIntBits_9F0I(Thread *thread, SerialHeap *heap, Frame *frame)
{
    float value = get_localvar(frame, 0);
    push_int(frame->operand_stack, (int)value);
}