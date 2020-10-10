//
// Created by wangzhanzhi on 2020/8/6.
//

#include "Object.h"

void java_lang_Object_registerNatives_90V(Thread *thread, SerialHeap *heap, Frame *frame)
{
}

void java_lang_Object_getClass_90Ljava_lang_Class(Thread *thread, SerialHeap *heap, Frame *frame)
{
    Object *this = get_localvar_this(frame);
    push_object(frame->operand_stack, this->class->class_object);
}

void java_lang_Object_hashCode_90I(Thread *thread, SerialHeap *heap, Frame *frame)
{
    Slot *slot = get_slot_localvar(frame, 0);
    push_int(frame->operand_stack, hash_code((char*)&slot->object_value));
}

void java_lang_Object_notifyAll_90V(Thread *thread, SerialHeap *heap, Frame *frame)
{
    //TODO
    Object *this = get_localvar_this(frame);
    pthread_cond_broadcast(this->monitor->cond);
}

void java_lang_Object_clone_90Ljava_lang_Object1(Thread *thread, SerialHeap *heap, Frame *frame)
{
    Object *this = get_localvar_this(frame);
    void *res;
    if (is_array(this)) {
        Array *_array = get_localvar_this(frame);
        if (is_primitive_array(_array)) {
            int size = primitive_size(_array->raw_class->class_name);
            Array *copy = malloc_array_by_type_size(thread, heap, _array->class, _array->length, size);
            memcpy(copy->objects, _array->objects, size * _array->length);
            res = copy;
        } else {
            Array *copy = malloc_array(thread, heap, _array->class, _array->length);
            for (int i = 0; i < copy->length; i++) {
                copy->objects[i] = _array->objects[i];
            }
            res = copy;
        }
    } else {
        Object *copy = malloc_object(thread, heap, this->class);
        for(int i = 0; i < copy->raw_class->object_fields_count; i++) {
            copy->fields[i].value = this->fields[i].value;
            copy->fields[i].object_value = this->fields[i].object_value;
        }
        res = copy;
    }
    push_object(frame->operand_stack, res);
}

/**
 * Causes the current thread to wait until it is awakened, typically
 * by being <em>notified</em> or <em>interrupted</em>, or until a
 * certain amount of real time has elapsed.
 * <p>
 * In all respects, this method behaves as if {@code wait(timeoutMillis, 0)}
 * had been called. See the specification of the {@link #wait(long, int)} method
 * for details.
 *
 * @param  timeoutMillis the maximum time to wait, in milliseconds
 * @throws IllegalArgumentException if {@code timeoutMillis} is negative
 * @throws IllegalMonitorStateException if the current thread is not
 *         the owner of the object's monitor
 * @throws InterruptedException if any thread interrupted the current thread before or
 *         while the current thread was waiting. The <em>interrupted status</em> of the
 *         current thread is cleared when this exception is thrown.
 * @see    #notify()
 * @see    #notifyAll()
 * @see    #wait()
 * @see    #wait(long, int)
 */
void java_lang_Object_wait_9J0V(Thread *thread, SerialHeap *heap, Frame *frame)
{
    Object *this = get_localvar_this(frame);
    long time = get_long_localvar(frame, 1);

    if (time < 0) {
        printf_err("throw IllegalArgumentException");
        exit(-1);
    }
    if (NULL == this->monitor->owner) {
        printf_err("throw IllegalMonitorStateException");
        exit(-1);
    }

    struct timespec abstime;
    clock_gettime(CLOCK_MONOTONIC, &abstime);
    abstime.tv_sec += time / 1000;
    uint64_t us = abstime.tv_nsec / 1000 + 1000 * (time % 1000);
    abstime.tv_sec += us / 1000000;
    us = us % 1000000;
    abstime.tv_nsec = us * 1000;

    pthread_mutex_lock(this->monitor->lock);
//    pthread_cond_wait(this->monitor->cond, this->monitor->lock);
    pthread_cond_timedwait(this->monitor->cond, this->monitor->lock, &abstime);
    pthread_mutex_unlock(this->monitor->lock);
}