//
// Created by wangzhanzhi on 2020/10/10.
//

#include "AtomicLong.h"

/**
* Returns whether underlying JVM supports lockless CompareAndSet
* for longs. Called only once and cached in VM_SUPPORTS_LONG_CAS.
*/
void java_util_concurrent_atomic_AtomicLong_VMSupportsCS8_90Z(Thread *thread, SerialHeap *heap, Frame *frame)
{
   push_int(frame->operand_stack, 0);
}

