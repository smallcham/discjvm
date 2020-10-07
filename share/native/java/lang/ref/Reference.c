//
// Created by wangzhanzhi on 2020/10/5.
//

#include "Reference.h"

/*
 * Wait until the VM's pending-Reference list may be non-null.
 */
void java_lang_ref_Reference_waitForReferencePendingList_90V(Thread *thread, SerialHeap *heap, Frame *frame)
{
    //TODO
    pthread_mutex_lock(thread->jthread->monitor->lock);
    while (NULL == _reference_pending_list) {
        pthread_cond_wait(thread->jthread->monitor->cond, thread->jthread->monitor->lock);
    }
    pthread_mutex_unlock(thread->jthread->monitor->lock);
}

/*
 * Atomically get and clear (set to null) the VM's pending-Reference list.
 */
void java_lang_ref_Reference_getAndClearReferencePendingList_90Ljava_lang_ref_Reference1(Thread *thread, SerialHeap *heap, Frame *frame)
{
    pthread_mutex_lock(thread->jthread->monitor->lock);
    void *ref = _reference_pending_list;
    if (NULL != ref) {
        _reference_pending_list = NULL;
    }
    pthread_mutex_unlock(thread->jthread->monitor->lock);
    push_object(frame->operand_stack, ref);
}