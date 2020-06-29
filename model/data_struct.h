//
// Created by wangzhanzhi on 2020/6/26.
//

#ifndef DISCJVM_DATA_STRUCT_H
#define DISCJVM_DATA_STRUCT_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "base_type.h"

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

Stack create_stack(int max_size)
{
    Stack stack = *(Stack*)malloc(sizeof(Stack));
    stack.size = 0;
    stack.max_size = max_size;
    stack.head = NULL;
    stack.tail = NULL;
    return stack;
}

Stack *create_pstack(int max_size)
{
    Stack *stack = (Stack*)malloc(sizeof(Stack));
    stack->size = 0;
    stack->max_size = max_size;
    stack->head = NULL;
    stack->tail = NULL;
    return stack;
}

int is_full(Stack *stack)
{
    return stack->size >= stack->max_size;
}

int push_stack(Stack *stack, void *value)
{
    if (is_full(stack)) return 0;
    if (NULL == stack->head)
    {
        stack->head = malloc(sizeof(Entry));
        stack->head->value = value;
        stack->head->prev = NULL;
        stack->head->next = NULL;
        stack->tail = stack->head;
    }
    else
    {
        Entry next = *(Entry*) malloc(sizeof(Entry));
        next.value = value;
        next.next = NULL;
        next.prev = (struct Entry *) stack->tail;
        int len = sizeof(next);
        stack->tail->next = malloc(len);
        memcpy(stack->tail->next, &next, len);
        stack->tail = (Entry *) stack->tail->next;
    }
    stack->size ++;
    return 0;
}

int push_int(Stack *stack, int value)
{
    int *temp = malloc(sizeof(int));
    *temp = value;
    return push_stack(stack, temp);
}

int push_float(Stack *stack, float value)
{
    return push_int(stack, (int) value);
}

int push_long(Stack *stack, long value)
{
    int c = push_int(stack, (int) value);
    return c + push_int(stack, (int) (value >> 32)) == 2;
}

int push_double(Stack *stack, double value)
{
    return push_long(stack, (long) value);
}

int empty_stack(Stack *stack)
{
    return NULL == stack || stack->size == 0 || NULL == stack->tail;
}

void* pop_stack(Stack *stack)
{
    if (empty_stack(stack)) return NULL;
    void* value = (void *) stack->tail->value;
    stack->tail = (Entry *) stack->tail->prev;
    stack->size--;
    if (stack->size == 0) stack->head = NULL;
    return value;
}

void* get_stack(Stack *stack)
{
    if (empty_stack(stack)) return NULL;
    return (void *) stack->tail->value;
}

int pop_int(Stack *stack)
{
    return *(int*) pop_stack(stack);
}

float pop_float(Stack *stack)
{
    return (float) pop_int(stack);
}

long pop_long(Stack *stack)
{
    int higher = pop_int(stack);
    int lower = pop_int(stack);
    return (((long)higher << 32) | lower);
}

double pop_double(Stack *stack)
{
    return (double) pop_long(stack);
}

#endif //DISCJVM_DATA_STRUCT_H
