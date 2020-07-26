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