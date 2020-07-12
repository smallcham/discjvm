//
// Created by wangzhanzhi on 2020/7/2.
//

#ifndef DISCJVM_HASH_MAP_H
#define DISCJVM_HASH_MAP_H
#include <string.h>
#include <stdlib.h>

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


int hash_code(char *key);

HashMap *create_map_manual(int capacity, float factor);

HashMap *create_map_by_size(int capacity);

HashMap *create_map();

HashMap *resize_map(HashMap *map);

HashEntry *create_entry(char *key, void *value);

void put_map(HashMap **map, char *key, void *value);

void put_map_for_double(HashMap **map, char *key, double value);

void put_map_for_float(HashMap **map, char *key, float value);

double *get_map_for_double(HashMap **map, char *key);

float *get_map_for_float(HashMap **map, char *key);

void *get_map(HashMap **map, char *key);

void clean_entry(HashEntry *entry);

void del_map(HashMap **map, char *key);

#endif //DISCJVM_HASH_MAP_H
