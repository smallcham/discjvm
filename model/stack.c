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

void push_u4(Stack *stack, u4 value)
{
    Slot *slot = create_slot();
    slot->value = value;
    push_slot(stack, slot);
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

float push_float(Stack *stack, float value)
{
    Slot *slot = create_slot();
    memcpy(&slot->value, &value, 4);
    push_slot(stack, slot);
    return value;
}

float push_float_by_u4(Stack *stack, u4 value)
{
    char str[4];
    memcpy(str, &value, 4);
    float val = *(float*)str;
    push_float(stack, val);
    return val;
}

int push_long(Stack *stack, u8 value)
{
    Slot *slot = create_slot();
    slot->value = value;
    push_slot(stack, slot);
    push_int(stack, 0);
    return value;
}

void push_long_from(Stack *source, Stack *target)
{
    push_long(target, pop_long(source));
}

int push_double(Stack *stack, double value)
{
    return push_long(stack, (u8) value);
}

void push_double_from(Stack *source, Stack *target)
{
    push_long(target, pop_long(source));
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
    return stack->tail->value;
}

void *get_prev(Stack *stack)
{
    if (is_empty_stack(stack) || NULL == stack->tail->prev) return NULL;
    return ((Entry*)(stack->tail->prev))->value;
}

Slot *get_slot(Stack *stack)
{
    return get_stack(stack);
}

void *get_stack_offset(Stack *stack, int offset)
{
    Entry *temp = (Entry *) stack->tail;
    for (int i = 0; i < offset; i++) {
        if (NULL == temp) return NULL;
        temp = (Entry*)temp->prev;
    }
    return NULL == temp ? NULL : temp->value;
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
    return pop_slot(stack)->value;
}

void *pop_object(Stack *stack)
{
    Slot *slot = pop_slot(stack);
    return slot->object_value;
}

float pop_float(Stack *stack)
{
    char str[4];
    Slot *slot = pop_slot(stack);
    memcpy(str, &(slot->value), 4);
    return *(float*)str;
}

u8 pop_long(Stack *stack)
{
    pop_int(stack);
    return pop_slot(stack)->value;
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
            if (NULL != obj->class) {
                if (object_is_string(obj)) {
                    Array *array = obj->fields->object_value;
                    if (NULL == array) {
                        printf("[NULL-STR]");
                    } else {
                        char *str = malloc(array->length + 1);
                        memcpy(str, (char*)array->objects, array->length);
                        str[array->length] = '\0';
                        if (str[0] == '\n') {
                            printf("\"\\n\"");
                        } else {
                            printf("\"%s\"", str);
                        }
                        free(str);
                    }
                } else {
                    printf("%s", obj->class->class_name);
                }
            }
            else printf("NULL-OBJECT(%p)", obj);
        } else {
            printf("%ld", (long)value->value);
        }
        printf(", ");
        memcpy(next, next->prev, sizeof(Entry));
    }
    printf("\n");
    free(next);
}
