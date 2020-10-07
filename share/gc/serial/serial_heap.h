//
// Created by wangzhanzhi on 2020/6/30.
//

#ifndef DISCJVM_SERIAL_HEAP_H
#define DISCJVM_SERIAL_HEAP_H

#include "stdlib.h"
#include "stdio.h"
#include "../../../model/hash_map.h"
#include "../../../model/monitor.h"
#include "../../../model/class.h"
#include "../../../model/thread.h"

void *_reference_pending_list;

typedef struct {
    HashMap *class_pool;
} SerialHeap;

SerialHeap *init_gc();

HashMap *create_class_pool();

char *primitive_to_full_name(char *name);

ClassFile *get_class_from_cache(HashMap *pool, char *class_full_name);

void del_class_from_cache(HashMap *pool, char *class_full_name);

Object *malloc_object(Thread *thread, SerialHeap *heap, ClassFile *class);

Object *malloc_null_object(Thread *thread, SerialHeap *heap);

void copy_object(Thread *thread, SerialHeap *heap, Object **t, Object *s);

Array *malloc_array(Thread *thread, SerialHeap *heap, ClassFile *class, int length);

Array *malloc_array_by_type_size(Thread *thread, SerialHeap *heap, ClassFile *class, int length, int type_size);

void put_class_to_cache(HashMap **pool, ClassFile *class);

char *primitive_to_name(char *name);

#endif //DISCJVM_SERIAL_HEAP_H
