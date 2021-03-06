//
// Created by wangzhanzhi on 2020/7/9.
//

#include "hash_map.h"

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
    map->threshold = capacity * factor;
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

HashMap *resize_map(HashMap *map)
{
    HashMap *new_map = create_map_by_size(map->capacity * 2);
    for (int i = 0; i < map->capacity; i++) {
        HashEntry head = map->entries[i];
        while (NULL != head.key) {
            put_map(&new_map, head.key, head.value);
            if (NULL == head.next) break;
            head = *head.next;
        }
    }
    return new_map;
}

HashEntry *create_entry(char *key, void *value)
{
    HashEntry *new_entry = (HashEntry*)malloc(entry_size);
    new_entry->key = key;
    new_entry->value = value;
    new_entry->next = NULL;
    return new_entry;
}

void put_map_for_double(HashMap **map, char *key, double value)
{
    void *temp = malloc(sizeof(double));
    memcpy(temp, &value, sizeof(double));
    put_map(map, key, temp);
}

void put_map_for_float(HashMap **map, char *key, float value)
{
    void *temp = malloc(sizeof(double));
    memcpy(temp, &value, sizeof(double));
    put_map(map, key, temp);
}

float *get_map_for_float(HashMap **map, char *key)
{
    void *value = get_map(map, key);
    float *temp = malloc(sizeof(double));
    memcpy(temp, value, sizeof(double));
    return temp;
}

double *get_map_for_double(HashMap **map, char *key)
{
    void *value = get_map(map, key);
    double *temp = malloc(sizeof(double));
    memcpy(temp, value, sizeof(double));
    return temp;
}

void put_map(HashMap **map, char *key, void *value)
{
    if (((*map)->size + 1) >= (*map)->threshold) {
        HashMap *temp = *map;
        *map = resize_map((*map));
        free(temp);
    }
    int index = ((*map)->capacity - 1) & hash_code(key);
    HashEntry *entry = &(*map)->entries[index];
    if (NULL == entry->key) {
        HashEntry *new_entry = create_entry(key, value);
        (*map)->entries[index] = *new_entry;
    } else {
        while (NULL != entry->key) {
            if (strcmp(entry->key, key) == 0) {
                entry->value = value;
                break;
            }
            if (NULL == entry->next) {
                HashEntry *new_entry = create_entry(key, value);
                entry->next = new_entry;
                break;
            }
            entry = entry->next;
        }
    }
    (*map)->size ++;
}

void *get_map(HashMap **map, char *key)
{
    int index = ((*map)->capacity - 1) & hash_code(key);
    HashEntry entry = (*map)->entries[index];
    while (NULL != entry.key) {
        if (strcmp(entry.key, key) == 0) return entry.value;
        if (NULL == entry.next) return NULL;
        entry = *entry.next;
    }
    return NULL;
}

void clean_entry(HashEntry *entry)
{
    entry->key = NULL;
    entry->value = NULL;
    entry->next = NULL;
}

void del_map(HashMap **map, char *key)
{
    int index = hash_code(key) % (*map)->capacity;
    HashEntry *entry = &(*map)->entries[index];
    HashEntry *pre = entry;
    if (strcmp(entry->key, key) == 0 && NULL == entry->next) {
        clean_entry(entry);
        (*map)->size--;
        return;
    }
    while (NULL != entry->key) {
        if (strcmp(entry->key, key) == 0) {
            pre->next = entry->next;
            free(entry);
            (*map)->size--;
            return;
        }
        pre = entry;
        entry = entry->next;
    }
}

char **keys(HashMap **map)
{
    char **_keys = malloc((*map)->size * sizeof(char**));
    int idx = 0;
    for (int i = 0; i < (*map)->capacity; i++) {
        HashEntry next = (*map)->entries[i];
        while (NULL != next.key) {
            _keys[idx++] = next.key;
            if (NULL == next.next) break;
            next = *next.next;
        }
    }
    return _keys;
}