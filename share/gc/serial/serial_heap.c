//
// Created by wangzhanzhi on 2020/6/30.
//

#include "serial_heap.h"

char *primitive_to_full_name(char *name);

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
//    CONSTANT_Class_info class_info = *(CONSTANT_Class_info*)class->constant_pool[class->this_class].info;
//    CONSTANT_Utf8_info name_info = *(CONSTANT_Utf8_info*)class->constant_pool[class_info.name_index].info;
    put_map(pool, class->class_name, class);
}

Object *malloc_object(SerialHeap *heap, ClassFile *class)
{
    Object *object = malloc(sizeof(Object));
    memset(object, 0, sizeof(Object));
    object->class = class;
    object->raw_class = class;
    object->fields = create_slot_by_size(class->object_fields_count);
//    object->fields = create_map(class->fields_count * 1.3 + 1);
    return object;
}

Object *malloc_null_object(SerialHeap *heap)
{
    Object *object = malloc(sizeof(Object));
    memset(object, 0, sizeof(Object));
    object->class = NULL;
    object->raw_class = NULL;
    object->fields = NULL;
    return object;
}

Array *malloc_array(SerialHeap *heap, ClassFile *class, int length)
{
    Array *array = malloc(sizeof(Array) + sizeof(Object) * length);
    memset(array, 0, sizeof(Array) + sizeof(Object) * length);
    array->length = length;
    array->class = class;
    array->raw_class = class;
    for (int i = 0; i < length; i++) {
        array->objects[i] = NULL;
    }
    return array;
}

Array *malloc_raw_array(SerialHeap *heap, ClassFile *class, int length, int type_size)
{
    Array *array = malloc(sizeof(Array));
    memset(array, 0, sizeof(Array));
    array->length = length;
    array->class = class;
    array->raw_object = malloc(length * type_size);
    array->raw_class = class;
    return array;
}

char *primitive_to_full_name(char *name)
{
    if (strcmp(name, "int") == 0) return "java/lang/Integer";
    if (strcmp(name, "float") == 0) return "java/lang/Float";
    if (strcmp(name, "long") == 0) return "java/lang/Long";
    if (strcmp(name, "double") == 0) return "java/lang/Double";
    if (strcmp(name, "short") == 0) return "java/lang/Short";
    if (strcmp(name, "byte") == 0) return "java/lang/Byte";
    if (strcmp(name, "boolean") == 0) return "java/lang/Boolean";
    if (strcmp(name, "void") == 0) return "java/lang/Void";
    if (strcmp(name, "char") == 0) return "java/lang/Character";
    return name;
}