//
// Created by wangzhanzhi on 2020/6/26.
//

#ifndef DISCJVM_STACK_H
#define DISCJVM_STACK_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

int push_float(Stack *stack, float value);

int push_long(Stack *stack, long value);

int push_double(Stack *stack, double value);

int is_empty_stack(Stack *stack);

void* pop_stack(Stack *stack);

void* get_stack(Stack *stack);

char* find_in_stack(Stack *stack, char* value);

int pop_int(Stack *stack);

float pop_float(Stack *stack);

long pop_long(Stack *stack);

double pop_double(Stack *stack);

#endif //DISCJVM_STACK_H
