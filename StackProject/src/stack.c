#include "stack.h"
#include "validation_utils.h"

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

#define INIT_STACK_CAPACITY (100)
#define CAPACITY_MULTIPLIER (2)

struct Stack_t {
    int32_t* start_stack_ptr;
    int32_t* top_stack_ptr;
    uint32_t capacity;
};

Status Stack__init(Stack **stack)
{
    Status status = STATUS_INIT_ERROR;
    VALIDATE(stack != NULL, STATUS_NULL_POINTER_ERROR, status, l_finish);

    *stack = (Stack*)malloc(sizeof(Stack));
    VALIDATE(*stack != NULL, STATUS_MEMORY_ALLOCATION_ERROR, status, l_finish);

    (*stack)->start_stack_ptr = (int32_t*)malloc(sizeof(int32_t) * INIT_STACK_CAPACITY);
    VALIDATE((*stack)->start_stack_ptr != NULL, STATUS_MEMORY_ALLOCATION_ERROR, status, l_cleanup);
    (*stack)->top_stack_ptr = (*stack)->start_stack_ptr;
    (*stack)->capacity = INIT_STACK_CAPACITY;

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

Status Stack__push(Stack* stack, int32_t value)
{
    Status status = STATUS_INIT_ERROR;
    VALIDATE(stack != NULL, STATUS_NULL_POINTER_ERROR, status, l_finish);

    if ((uint32_t)(stack->top_stack_ptr - stack->start_stack_ptr) >= stack->capacity) {
        uint32_t new_capacity = stack->capacity * CAPACITY_MULTIPLIER;
        int32_t* new_stack_ptr = (int32_t*)realloc(stack->start_stack_ptr, sizeof(int32_t) * new_capacity);
        VALIDATE(new_stack_ptr != NULL, STATUS_MEMORY_ALLOCATION_ERROR, status, l_finish);

        stack->top_stack_ptr = new_stack_ptr + (stack->top_stack_ptr - stack->start_stack_ptr);
        stack->start_stack_ptr = new_stack_ptr;
        stack->capacity = new_capacity;
    }

    *(stack->top_stack_ptr) = value;
    stack->top_stack_ptr++;

    status = STATUS_SUCCESS;
l_finish:
    return status;
}

Status Stack__pop(Stack* stack, int32_t* value)
{
    Status status = STATUS_INIT_ERROR;
    VALIDATE(stack != NULL, STATUS_NULL_POINTER_ERROR && value != NULL, status, l_finish);

    if (stack->top_stack_ptr == stack->start_stack_ptr) {
        status = STATUS_STACK_UNDERFLOW_ERROR;
        goto l_finish;
    }

    stack->top_stack_ptr--;
    *value = *(stack->top_stack_ptr);

    status = STATUS_SUCCESS;
l_finish:
    return status;
}

Status Stack__peek(Stack* stack, int32_t* value)
{
    Status status = STATUS_INIT_ERROR;
    VALIDATE(stack != NULL, STATUS_NULL_POINTER_ERROR && value != NULL, status, l_finish);

    if (stack->top_stack_ptr == stack->start_stack_ptr) {
        status = STATUS_STACK_UNDERFLOW_ERROR;
        goto l_finish;
    }

    *value = *(stack->top_stack_ptr - 1);
    status = STATUS_SUCCESS;

l_finish:
    return status;
}

Status Stack__is_empty(Stack* stack, bool* is_empty)
{
    Status status = STATUS_INIT_ERROR;
    VALIDATE(stack != NULL, STATUS_NULL_POINTER_ERROR && is_empty != NULL, status, l_finish);

    *is_empty = (stack->top_stack_ptr == stack->start_stack_ptr);
    status = STATUS_SUCCESS;

l_finish:
    return status;
}
