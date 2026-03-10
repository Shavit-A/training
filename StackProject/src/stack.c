#include "stack.h"
#include "validation_utils.h"

#include <stdint.h>
#include <stdlib.h>

#define INIT_STACK_CAPACITY (100)

struct Stack_t {
    int32_t* start_stack_ptr;
    uint32_t* top_stack_ptr;
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
    (*stack)->capacity = INIT_STACK_CAPACITY;
    (*stack)->top_stack_ptr = (*stack)->start_stack_ptr;

    status = STATUS_SUCCESS;

l_cleanup:
    free(*stack);

l_finish:
    return status;
}