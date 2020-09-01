//
// Created by wangzhanzhi on 2020/7/31.
//

#include "class.h"

u1 *get_utf8_bytes(ConstantPool *pool, u2 index)
{
    CONSTANT_Utf8_info *info = (CONSTANT_Utf8_info*)pool[index].info;
    return info->bytes;
}

Slot *create_slot()
{
    Slot *slot = malloc(sizeof(Slot));
    slot->value = 0;
    slot->object_value = NULL;
    return slot;
}

Slot *create_slot_set_value(u4 value)
{
    Slot *slot = create_slot();
    slot->value = value;
    return slot;
}

Slot *create_slot_by_size(int size)
{
    if (size < 1) {
        return NULL;
    }
    Slot *slot = malloc(sizeof(Slot) * size);
    memset(slot, 0, sizeof(Slot) * size);
    for (int i = 0; i < size; i++) {
        slot[i].value = 0;
        slot[i].object_value = NULL;
    }
    return slot;
}

int is_array_by_name(char *name)
{
    return name[0] == '[';
}

int is_array(void *ref)
{
    Array *object = ref;
    return is_array_by_name(object->class->class_name);
}

int is_array_by_raw(void *raw_class)
{
    Object *object = raw_class;
    return is_array_by_name(object->raw_class->class_name);
}

int is_object_array(void *ref)
{
    Array *object = ref;
    return is_array(ref) && object->class->class_name[1] == 'L';
}

int is_object_array_by_raw(void *raw_class)
{
    Object *object = raw_class;
    return is_array_by_raw(raw_class) && object->raw_class->class_name[1] == 'L';
}

int is_primitive_array(void *ref)
{
    Array *object = ref;
    return is_array(ref) && object->class->class_name[1] != 'L';
}

int is_primitive_array_by_raw(void *raw_class)
{
    Object *object = raw_class;
    return is_array_by_raw(raw_class) && object->raw_class->class_name[1] != 'L';
}