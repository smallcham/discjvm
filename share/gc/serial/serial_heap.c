//
// Created by wangzhanzhi on 2020/6/30.
//

#include "serial_heap.h"

SerialHeap *init_gc()
{
    SerialHeap *heap = (SerialHeap*)malloc(sizeof(SerialHeap));
    heap->class_pool = create_class_pool();
    return heap;
}

HashMap *create_class_pool()
{
    return create_map();
}

ClassFile *get_class_from_cache(HashMap *pool, char *class_full_name)
{
    return get_map(&pool, class_full_name);
}

void del_class_from_cache(HashMap *pool, char *class_full_name)
{
    del_map(&pool, class_full_name);
}

void put_class_to_cache(HashMap **pool, ClassFile *class)
{
    CONSTANT_Class_info class_info = *(CONSTANT_Class_info*)class->constant_pool[class->this_class].info;
    CONSTANT_Utf8_info name_info = *(CONSTANT_Utf8_info*)class->constant_pool[class_info.name_index].info;
    put_map(pool, name_info.bytes, class);
}

Object *malloc_object(SerialHeap *heap, ClassFile *class)
{
    Object *object = malloc(sizeof(Object));
    object->class = class;
    object->fields = create_map(class->fields_count * 1.3 + 1);
    return object;
}

Object *malloc_null_object(SerialHeap *heap)
{
    Object *object = malloc(sizeof(Object));
    object->class = NULL;
    object->fields = NULL;
    return object;
}

Array *malloc_array(SerialHeap *heap, ClassFile *class, int length)
{
    Array *array = malloc(sizeof(Array) + sizeof(Object) * length);
    array->length = length;
    array->class = class;
    return array;
}