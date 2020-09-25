//
// Created by wangzhanzhi on 2020/9/25.
//

#include "Signal.h"

/* Find the signal number, given a name. Returns -1 for unknown signals. */
/* kill -l 获取信号列表 */
void jdk_internal_misc_Signal_findSignal0_9Ljava_lang_String10I(Thread *thread, SerialHeap *heap, Frame *frame)
{
    Object *name_obj = get_ref_localvar(frame, 0);
    char *name = get_str_field_value_by_object(name_obj);
    if (NULL == name) {
        printf_err("jdk_internal_misc_Signal_findSignal0_9Ljava_lang_String10I Throw Error, Name Is NULL");
        exit(-1);
    }
    push_int(frame->operand_stack, 0);
}