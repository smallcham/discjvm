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
    printf("\t\t\t\tpush ↓\n");
    return 0;
}

int push_int(Stack *stack, int value)
{
//    int *temp = malloc(sizeof(int));
//    *temp = value;
    Slot *slot = create_slot();
    slot->value = value;
    push_slot(stack, slot);
    return slot->value;
}

Slot *push_slot(Stack *stack, Slot *slot)
{
    push_stack(stack, slot);
    return slot;
}

Slot *push_object(Stack *stack, void *object)
{
    Slot *slot = create_slot();
    slot->object_value = object;
    push_slot(stack, slot);
    return slot;
}

Slot *pop_slot(Stack *stack)
{
    return pop_stack(stack);
}

void push_slot_from(Stack *source, Stack *target)
{
    push_slot(target, pop_slot(source));
}

Slot **pop_slot_with_num(Stack *stack, int num)
{
    Slot **slots = malloc(sizeof(Slot) * num);
//    for (int i = 0; i < num; i++) {
    for (int i = num - 1; i >= 0; i--) {
        slots[i] = pop_slot(stack);
    }
    return slots;
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

void push_long_from(Stack *source, Stack *target)
{
    int higher = pop_int(source);
    int lower = pop_int(source);
    push_int(target, lower);
    push_int(target, higher);
}

int push_double(Stack *stack, double value)
{
    return push_long(stack, (long) value);
}

void push_double_from(Stack *source, Stack *target)
{
    int higher = pop_int(source);
    int lower = pop_int(source);
    push_int(target, higher);
    push_int(target, lower);
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
    printf("\t\t\t\tpop ↑\n");
    return value;
}

void *get_stack(Stack *stack)
{
    if (is_empty_stack(stack)) return NULL;
    return (void *) stack->tail->value;
}

Slot *get_slot(Stack *stack)
{
    return get_stack(stack);
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

int get_int(Stack *stack)
{
    return *(int*) get_stack(stack);
}

Object *get_object(Stack *stack)
{
    Slot *slot = get_slot(stack);
    return slot->object_value;
}

int pop_int(Stack *stack)
{
    Slot *slot = pop_stack(stack);
    return slot->value;
}

void *pop_object(Stack *stack)
{
    Slot *slot = pop_slot(stack);
    return slot->object_value;
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

void free_stack(Stack **stack)
{
    while (!is_empty_stack(*stack)) {
        free(pop_stack(*stack));
    }
    free(*stack);
    stack = NULL;
}

void print_stack(Stack *stack)
{
    printf("[size: %d, max: %d]", stack->size, stack->max_size);
    printf("\t\t\t");
    if (NULL == stack || stack->size == 0 || NULL == stack->tail) {
        printf("-> ...\n\n");
        return;
    }
    Entry *next = malloc(sizeof(Entry));
    memcpy(next, stack->tail, sizeof(Entry));
//    Slot *value = temp->value;
//    if (NULL != value->object_value) {
//        Object *obj = value->object_value;
//        if (NULL != obj->class) printf("%s", obj->class->class_name);
//        else printf("%p", obj);
//    } else {
//        printf("%u", value->value);
//    }
//    Entry *next = malloc(sizeof(Entry));
//    memcpy(next, temp, sizeof(Entry));
    printf("-> ");
    for  (int i = 0; i < stack->size; i++) {
        if (NULL == next || NULL == next->value || NULL == next->prev) break;
        Slot *value = next->value;
        if (NULL != value->object_value) {
            Object *obj = value->object_value;
            if (NULL != obj->class) printf("%s", obj->class->class_name);
            else printf("NULL-OBJECT(%p)", obj);
        } else {
            printf("%d", value->value);
        }
        printf(", ");
        memcpy(next, next->prev, sizeof(Entry));
    }
    printf("\n");
    free(next);
}
