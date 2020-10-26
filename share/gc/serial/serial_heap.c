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
    put_map(pool, class->class_name, class);
}

Object *malloc_object(Thread *thread, SerialHeap *heap, ClassFile *class)
{
    Object *object = malloc(sizeof(Object));
    memset(object, 0, sizeof(Object));
    object->class = class;
    object->raw_class = class;
    object->fields = create_slot_by_size(class->object_fields_count);
    object->monitor = create_monitor(NULL);
    object->_debug_flag = thread->count;
    return object;
}

Object *malloc_null_object(Thread *thread, SerialHeap *heap)
{
    return NULL;
}

Array *malloc_array(Thread *thread, SerialHeap *heap, ClassFile *class, int length)
{
    Array *array = malloc_array_by_type_size(thread, heap, class, length, sizeof(Object));
    Object **objects = (Object **) array->objects;
    for (int i = 0; i < length; i++) {
        objects[i] = NULL;
    }
    return array;
}

Array *malloc_array_by_type_size(Thread *thread, SerialHeap *heap, ClassFile *class, int length, int type_size)
{
    Array *array = malloc(sizeof(Array) + type_size * length);
    memset(array, 0, sizeof(Array) + type_size * length);
    array->monitor = create_monitor(NULL);
    array->length = length;
    array->class = class;
    array->raw_class = class;
    return array;
}

void copy_object(Thread *thread, SerialHeap *heap, Object **t, Object *s)
{
    *t = (Object*)malloc_object(thread, heap, s->raw_class);
    (*t)->class = s->class;
    (*t)->raw_class = s->raw_class;
    for (int i = 0; i < s->raw_class->fields_count; i++) {
        FieldInfo field = s->raw_class->fields[i];
        if (is_static(field.access_flags)) continue;
        if (is_array_by_name(field.desc)) {
            if (is_object_array_by_desc(field.desc)) {
                Array *s_array = s->fields[field.offset].object_value;
                if (NULL == s_array) {
                    (*t)->fields[field.offset].object_value = NULL;
                    continue;
                }
                Array *t_array = malloc_array(thread, heap, s_array->raw_class, s_array->length);
                for (int j = 0; j < s_array->length; j++) {
                    Object *s_obj = s_array->objects[j];
                    if (NULL == s_obj) continue;
                    Object *t_obj;
                    copy_object(thread, heap, &t_obj, s_obj);
                    t_array->objects[j] = t_obj;
                }
                (*t)->fields[field.offset].object_value = t_array;
            } else {
                int type_size = primitive_size(field.desc);
                Array *array = s->fields[field.offset].object_value;
                if (NULL != array) {
                    Array *new_array = malloc_array_by_type_size(thread, heap, array->raw_class, array->length, type_size);
                    memcpy(new_array->objects, array->objects, type_size * array->length);
                    (*t)->fields[field.offset].object_value = new_array;
                }
            }
        } else {
            if (is_object_by_name(field.desc)) {
                if (NULL != s->fields[field.offset].object_value) {
                    copy_object(thread, heap, &((*t)->fields[field.offset].object_value), s->fields[field.offset].object_value);
                } else {
                    continue;
                }
            } else {
                (*t)->fields[field.offset].value = s->fields[field.offset].value;
            }
        }
    }
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

char *primitive_to_name(char *name)
{
    if (strcmp(name, "Z") == 0) return "boolean";
    if (strcmp(name, "I") == 0) return "int";
    if (strcmp(name, "C") == 0) return "char";
    if (strcmp(name, "B") == 0) return "byte";
    if (strcmp(name, "F") == 0) return "float";
    if (strcmp(name, "D") == 0) return "double";
    if (strcmp(name, "S") == 0) return "short";
    if (strcmp(name, "J") == 0) return "long";
    if (strcmp(name, "V") == 0) return "void";
    return name;
}