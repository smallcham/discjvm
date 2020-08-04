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

Slot *create_slot_by_size(int size)
{
    Slot *slot = malloc(sizeof(Slot) * size);
    for (int i = 0; i < size; i++) {
        slot[i].value = 0;
        slot[i].object_value = NULL;
    }
    return slot;
}