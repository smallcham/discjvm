//
// Created by wangzhanzhi on 2020/10/13.
//

#include "StringUTF16.h"

void java_lang_StringUTF16_isBigEndian_90Z(Thread *thread, SerialHeap *heap, Frame *frame)
{
    unsigned int endianTest = 0xff000000;
    push_int(frame->operand_stack, ((char*)(&endianTest))[0] != 0 ? 1 : 0);
}