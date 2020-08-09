//
// Created by wangzhanzhi on 2020/6/30.
//

#ifndef DISCJVM_SERIAL_HEAP_H
#define DISCJVM_SERIAL_HEAP_H

#include "stdlib.h"
#include "../../../model/hash_map.h"
#include "../../../model/class.h"

typedef struct {
    HashMap *class_pool;
} SerialHeap;

SerialHeap *init_gc();

HashMap *create_class_pool();

ClassFile *get_primitive_class_from_cache(HashMap *pool, char *class_primitive_name);

char *primitive_to_full_name(char *name);

ClassFile *get_class_from_cache(HashMap *pool, char *class_full_name);

void del_class_from_cache(HashMap *pool, char *class_full_name);

Object *malloc_object(SerialHeap *heap, ClassFile *class);

Object *malloc_null_object(SerialHeap *heap);

Array *malloc_array(SerialHeap *heap, ClassFile *class, int length);

void put_class_to_cache(HashMap **pool, ClassFile *class);

#endif //DISCJVM_SERIAL_HEAP_H
