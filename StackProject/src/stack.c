#include "stack.h"
#include "validation_utils.h"

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

#define INIT_STACK_CAPACITY (100)
#define CAPACITY_MULTIPLIER (2)

struct Stack_t {
    StackObject* start_stack_ptr;
    uint32_t size;
    uint32_t capacity;
    uint32_t object_size;
};

Status Stack__init(Stack **stack, uint32_t object_size)
{
    Status status = STATUS_INIT_ERROR;
    VALIDATE(stack != NULL, STATUS_NULL_POINTER_ERROR, status, l_finish);

    *stack = (Stack*)malloc(sizeof(Stack));
    VALIDATE(*stack != NULL, STATUS_MEMORY_ALLOCATION_ERROR, status, l_finish);

    (*stack)->start_stack_ptr = (StackObject*)malloc(object_size * INIT_STACK_CAPACITY);
    VALIDATE((*stack)->start_stack_ptr != NULL, STATUS_MEMORY_ALLOCATION_ERROR, status, l_cleanup);
    (*stack)->size = 0;
    (*stack)->capacity = INIT_STACK_CAPACITY;
    (*stack)->object_size = object_size;

    status = STATUS_SUCCESS;
    goto l_finish;

l_cleanup:
    free(*stack);

l_finish:
    return status;
}

Status Stack__free(Stack **stack)
{
    Status status = STATUS_INIT_ERROR;
    VALIDATE(stack != NULL, STATUS_NULL_POINTER_ERROR, status, l_finish);

    free((*stack)->start_stack_ptr);
    free(*stack);
    *stack = NULL;

    status = STATUS_SUCCESS;

l_finish:
    return status;
}

Status Stack__push(Stack* stack, StackObject value)
{
    Status status = STATUS_INIT_ERROR;
    VALIDATE(stack != NULL, STATUS_NULL_POINTER_ERROR, status, l_finish);

    if (stack->size >= stack->capacity) {
        uint32_t new_capacity = stack->capacity * CAPACITY_MULTIPLIER;
        StackObject* new_stack_ptr = (StackObject*)realloc(stack->start_stack_ptr, stack->object_size * new_capacity);
        VALIDATE(new_stack_ptr != NULL, STATUS_MEMORY_ALLOCATION_ERROR, status, l_finish);

        stack->start_stack_ptr = new_stack_ptr;
        stack->capacity = new_capacity;
    }

    *(stack->start_stack_ptr + stack->size * stack->object_size) = value; //TODO: check if need to do pointer arithmetic here
    stack->size++;

    status = STATUS_SUCCESS;
l_finish:
    return status;
}

Status Stack__pop(Stack* stack, StackObject* value)
{
    Status status = STATUS_INIT_ERROR;
    VALIDATE(stack != NULL, STATUS_NULL_POINTER_ERROR, status, l_finish);

    bool is_empty = false;
    status = Stack__is_empty(stack, &is_empty);
    VALIDATE(status == STATUS_SUCCESS, STATUS_STACK_UNDERFLOW_ERROR, status, l_finish);

    stack->size--;
    *value = *(stack->start_stack_ptr + stack->size * stack->object_size);

    status = STATUS_SUCCESS;
l_finish:
    return status;
}

Status Stack__peek(Stack* stack, StackObject* value)
{
    Status status = STATUS_INIT_ERROR;
    VALIDATE(stack != NULL, STATUS_NULL_POINTER_ERROR && value != NULL, status, l_finish);

    bool is_empty = false;
    status = Stack__is_empty(stack, &is_empty);
    VALIDATE(status == STATUS_SUCCESS, STATUS_STACK_UNDERFLOW_ERROR, status, l_finish);

    *value = *(stack->start_stack_ptr + (stack->size - 1) * stack->object_size); // Implement copy of the object
    status = STATUS_SUCCESS;

l_finish:
    return status;
}

Status Stack__is_empty(Stack* stack, bool* is_empty)
{
    Status status = STATUS_INIT_ERROR;
    VALIDATE(stack != NULL, STATUS_NULL_POINTER_ERROR && is_empty != NULL, status, l_finish);

    *is_empty = (stack->size == 0);
    status = STATUS_SUCCESS;

l_finish:
    return status;
}
