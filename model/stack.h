//
// Created by wangzhanzhi on 2020/6/26.
//

#ifndef DISCJVM_STACK_H
#define DISCJVM_STACK_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "stack.h"
#include "class.h"
#include "../util/ioutil.h"

typedef struct {
    void *value;
    struct Entry *prev;
    struct Entry *next;
} Entry;

typedef struct {
    int size;
    int max_size;
    Entry *head;
    Entry *tail;
} Stack;

Stack *create_unlimit_stack();

Stack *create_stack(int max_size);

int is_full(Stack *stack);

int push_stack(Stack *stack, void *value);

int push_int(Stack *stack, int value);

float push_float(Stack *stack, float value);

int push_long(Stack *stack, u8 value);

void push_u4(Stack *stack, u4 value);

void push_long_from(Stack *source, Stack *target);

int push_double(Stack *stack, double value);

void push_double_from(Stack *source, Stack *target);

Slot *push_object(Stack *stack, void *object);

void *pop_object(Stack *stack);

int is_empty_stack(Stack *stack);

void* pop_stack(Stack *stack);

void* get_stack(Stack *stack);

void *get_prev(Stack *stack);

char* find_in_stack(Stack *stack, char* value);

int get_int(Stack *stack);

Object *get_object(Stack *stack);

Slot *get_slot(Stack *stack);

int pop_int(Stack *stack);

float pop_float(Stack *stack);

float push_float_by_u4(Stack *stack, u4 value);

u8 pop_long(Stack *stack);

double pop_double(Stack *stack);

Slot *push_slot(Stack *stack, Slot *slot);

Slot *pop_slot(Stack *stack);

void push_slot_from(Stack *source, Stack *target);

Slot **pop_slot_with_num(Stack *stack, int num);

void print_stack(Stack *stack);

void free_stack(Stack **stack);

void *get_stack_offset(Stack *stack, int offset);

Slot *push_slot_copy(Stack *stack, Slot *slot);

void empty_stack(Stack *stack);

#endif //DISCJVM_STACK_H
