//
// Created by wangzhanzhi on 2020/6/26.
//

#include "stack.h"

Stack *create_unlimit_stack()
{
    Stack *stack = (Stack*)malloc(sizeof(Stack));
    stack->size = 0;
    stack->max_size = -1;
    stack->head = NULL;
    stack->tail = NULL;
    return stack;
}

Stack *create_stack(int max_size)
{
    Stack *stack = (Stack*)malloc(sizeof(Stack));
    stack->size = 0;
    stack->max_size = max_size;
    stack->head = malloc(sizeof(Entry));
    stack->tail = malloc(sizeof(Entry));
    stack->head->value = NULL;
    stack->head->prev = NULL;
    stack->head->next = NULL;
    stack->tail->next = NULL;
    stack->tail->next = NULL;
    stack->tail->next = NULL;
    return stack;
}

int is_full(Stack *stack)
{
    return stack->max_size == -1 ? 0 : stack->size >= stack->max_size;
}

int push_stack(Stack *stack, void *value)
{
    if (is_full(stack)) return 0;
    if (NULL == stack->head || (NULL == stack->head->value && NULL == stack->head->next))
    {
        if (NULL == stack->head) {
            Entry *next = (Entry*) malloc(sizeof(Entry));
            stack->head = next;
        }
        stack->head->value = value;
        stack->head->prev = (struct Entry *) stack->head;
        stack->head->next = (struct Entry *) stack->tail;
        stack->tail = stack->head;
    }
    else
    {
        Entry *next = (Entry*) malloc(sizeof(Entry));
        next->value = value;
        next->next = NULL;
        Entry *tail = stack->tail;
        tail->next = (struct Entry *) next;
        next->prev = (struct Entry *) tail;
        stack->tail = next;
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

int is_empty_stack(Stack *stack)
{
    return NULL == stack || stack->size == 0 || NULL == stack->tail;
}

void* pop_stack(Stack *stack)
{
    if (is_empty_stack(stack)) return NULL;
    void* value = stack->tail->value;
    stack->tail = (Entry *) stack->tail->prev;
    free(stack->tail->next);
    stack->tail->next = NULL;
    stack->size--;
    if (stack->size == 0) stack->head = NULL;
    return value;
}

void* get_stack(Stack *stack)
{
    if (is_empty_stack(stack)) return NULL;
    return (void *) stack->tail->value;
}

char* find_in_stack(Stack *stack, char* value)
{
    while (!is_empty_stack(stack))
    {
        char* temp = pop_stack(stack);
        if (strcmp(temp, value) == 0) return temp;
    }
    return NULL;
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
    long higher = (long)pop_int(stack);
    int lower = pop_int(stack);
    return higher | lower;
}

double pop_double(Stack *stack)
{
    return (double) pop_long(stack);
}
