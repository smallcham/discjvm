//
// Created by wangzhanzhi on 2020/7/2.
//

#ifndef DISCJVM_HASH_MAP_H
#define DISCJVM_HASH_MAP_H
#include <stdlib.h>
#include <string.h>

typedef struct HashEntry {
    char *key;
    void *value;
    struct HashEntry *next;
} HashEntry;

typedef struct {
    int size;
    int capacity;
    int threshold;
    float factor;
    HashEntry entries[];
} HashMap;


int hash_code(char *key)
{
    int hash = 0;
    for (int i = 0; i < strlen(key); i++) {
        hash = (31 * hash + key[i]);
    }
    return hash;
}

static int entry_size = sizeof(HashEntry);
static int map_size = sizeof(HashMap);
HashMap *create_map_manual(int capacity, float factor)
{

    HashMap *map = (HashMap*)malloc(map_size + entry_size * capacity);
    map->size = 0;
    map->capacity = capacity;
    map->factor = factor;
    map->threshold = entry_size * factor;
    for (int i = 0; i < capacity; i++) {
        map->entries[i].key = NULL;
        map->entries[i].value = NULL;
        map->entries[i].next = NULL;
    }
    return map;
}

HashMap *create_map_by_size(int capacity)
{
    return create_map_manual(capacity, 0.75f);
}

HashMap *create_map()
{
    return create_map_by_size(16);
}

void resize_map(HashMap *map)
{
    HashMap *new_map = create_map_by_size(map->size * 2);
    HashEntry *head = map->entries;
    HashEntry *pre = head;
    HashEntry *entry = head->next;
    for (int i = 0; i < map->capacity; i++) {}
}

HashEntry *create_entry(char *key, void *value)
{
    HashEntry *new_entry = (HashEntry*)malloc(entry_size);
    new_entry->key = key;
    new_entry->value = value;
    new_entry->next = NULL;
    return new_entry;
}

void put_map(HashMap *map, char *key, void *value)
{
    if ((map->size + 1) >= map->threshold) resize_map(map);
    int index = hash_code(key) % map->capacity;
    HashEntry entry = map->entries[index];
    if (NULL == entry.key) {
        HashEntry *new_entry = create_entry(key, value);
        map->entries[index] = *new_entry;
    } else {
        while (NULL != entry.key) {
            if (strcmp(entry.key, key) == 0) {
                entry.value = value;
                break;
            }
            if (NULL == entry.next) {
                HashEntry *new_entry = create_entry(key, value);
                entry.next = new_entry;
                break;
            }
            entry = *entry.next;
        }
    }
    map->size ++;
}

void *get_map(HashMap *map, char *key)
{
    int index = hash_code(key) % map->capacity;
    HashEntry entry = map->entries[index];
    while (NULL != entry.key) {
        if (strcmp(entry.key, key) == 0) return entry.value;
        entry = *entry.next;
    }
    return NULL;
}

void *del_map(HashMap *map, char *key)
{
    int index = hash_code(key) % map->capacity;
    HashEntry *entry = &map->entries[index];
    HashEntry *pre = entry;
    while (NULL != entry->key) {
        if (strcmp(entry->key, key) == 0) {
            pre->next = entry->next;
            entry = pre->next;
            return entry->value;
        }
        pre = entry;
        entry = entry->next;
    }
    return NULL;
}

#endif //DISCJVM_HASH_MAP_H
