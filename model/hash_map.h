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
    int max_size;
    float cap;
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
HashMap *create_map_manual(int max_size, float cap)
{

    HashMap *map = (HashMap*)malloc(map_size + entry_size * max_size);
    map->size = 0;
    map->max_size = max_size;
    map->cap = cap;
    for (int i = 0; i < max_size; i++) {
        map->entries[i].key = NULL;
        map->entries[i].value = NULL;
        map->entries[i].next = NULL;
    }
    return map;
}

HashMap *create_map_by_size(int max_size)
{
    return create_map_manual(max_size, 0.7f);
}

HashMap *create_map()
{
    return create_map_by_size(16);
}

void resize_map(HashMap *map)
{

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
    if ((map->size + 1) >= (int)(map->max_size * map->cap)) resize_map(map);
    int index = hash_code(key) % map->max_size;
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
    int index = hash_code(key) % map->max_size;
    HashEntry entry = map->entries[index];
    while (NULL != entry.key) {
        if (strcmp(entry.key, key) == 0) return entry.value;
        entry = *entry.next;
    }
    return NULL;
}

void *del_map(HashMap *map, char *key)
{
    int index = hash_code(key) % map->max_size;
    HashEntry *entry = &map->entries[index];
    HashEntry *pre = entry;
    while (NULL != entry->key) {
        if (strcmp(entry->key, key) == 0) {
            pre->next = entry->next;
            return entry->value;
        }
        pre = entry;
        entry = entry->next;
    }
    return NULL;
}

#endif //DISCJVM_HASH_MAP_H
