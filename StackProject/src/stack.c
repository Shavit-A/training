#include "stack.h"
#include "status.h"
#include "validation_utils.h"

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#define INIT_STACK_CAPACITY (100)
#define CAPACITY_MULTIPLIER (2)

struct Stack_t {
    ObjectPtr* object_array;
    uint32_t size;
    uint32_t capacity;
    StackObjectInitCallback init_callback;
    StackObjectFreeCallback free_callback;
    StackObjectCopyCallback copy_callback;
};

Status Stack__init(
    Stack** const stack,
    StackObjectInitCallback init_callback,
    StackObjectFreeCallback free_callback,
    StackObjectCopyCallback copy_callback)
{
    Status status = STATUS_INIT_ERROR;
    VALIDATE(
        stack != NULL && init_callback != NULL && free_callback != NULL && copy_callback != NULL,
        STATUS_NULL_POINTER_ERROR,
        status,
        l_finish);

    *stack = (Stack*)malloc(sizeof(Stack));
    VALIDATE(*stack != NULL, STATUS_MEMORY_ALLOCATION_ERROR, status, l_finish);

    (*stack)->object_array = (ObjectPtr*)malloc(sizeof(ObjectPtr) * INIT_STACK_CAPACITY);
    VALIDATE((*stack)->object_array != NULL, STATUS_MEMORY_ALLOCATION_ERROR, status, l_cleanup);
    (*stack)->size = 0;
    (*stack)->capacity = INIT_STACK_CAPACITY;
    (*stack)->init_callback = init_callback;
    (*stack)->free_callback = free_callback;
    (*stack)->copy_callback = copy_callback;

    status = STATUS_SUCCESS;
    goto l_finish;

l_cleanup:
    free(*stack);

l_finish:
    return status;
}

Status Stack__free(Stack** const stack)
{
    Status status = STATUS_INIT_ERROR;
    VALIDATE(stack != NULL && *stack != NULL && (*stack)->free_callback != NULL, STATUS_NULL_POINTER_ERROR, status, l_finish);

    for (uint32_t i = 0; i < (*stack)->size; i++)
    {
        ObjectPtr object = (*stack)->object_array[i];
        VALIDATE(object != NULL, STATUS_OBJECT_S_NULL_ERROR, status, l_finish);

        status = (*stack)->free_callback(&object);
        TRACE_ON_FAILURE(status == STATUS_SUCCESS, "Failed to free object\n");
    }

    free((*stack)->object_array);
    free(*stack);
    *stack = NULL;

    status = STATUS_SUCCESS;

l_finish:
    return status;
}

Status Stack__push(Stack* const stack, const ObjectPtr object)
{
    Status status = STATUS_INIT_ERROR;
    VALIDATE(stack != NULL && stack->init_callback != NULL, STATUS_NULL_POINTER_ERROR, status, l_finish);

    if (stack->size >= stack->capacity) {
        uint32_t new_capacity = stack->capacity * CAPACITY_MULTIPLIER;
        ObjectPtr* new_object_array = (ObjectPtr*)realloc(stack->object_array, sizeof(ObjectPtr) * new_capacity);
        VALIDATE(new_object_array != NULL, STATUS_MEMORY_ALLOCATION_ERROR, status, l_finish);

        stack->object_array = new_object_array;
        stack->capacity = new_capacity;
    }

    ObjectPtr new_object = NULL;
    status = stack->init_callback(&new_object);
    VALIDATE(status == STATUS_SUCCESS, STATUS_INIT_CALLBACK_ERROR, status, l_finish);

    status = stack->copy_callback(new_object, object);
    VALIDATE(status == STATUS_SUCCESS, STATUS_COPY_CALLBACK_ERROR, status, l_finish);

    stack->object_array[stack->size] = new_object;
    stack->size++;

    status = STATUS_SUCCESS;
l_finish:
    return status;
}

Status Stack__pop(Stack* const stack,  ObjectPtr const out_object)
{
    Status status = STATUS_INIT_ERROR;
    VALIDATE(
        stack != NULL && out_object != NULL && stack->copy_callback != NULL && stack->free_callback != NULL,
        STATUS_NULL_POINTER_ERROR,
        status,
        l_finish);

    bool is_empty = false;
    status = Stack__is_empty(stack, &is_empty);
    VALIDATE(status == STATUS_SUCCESS, STATUS_STACK_UNDERFLOW_ERROR, status, l_finish);
    VALIDATE(!is_empty, STATUS_STACK_UNDERFLOW_ERROR, status, l_finish);

    ObjectPtr object = stack->object_array[stack->size - 1];
    status = stack->copy_callback(out_object, object);
    VALIDATE(status == STATUS_SUCCESS, STATUS_COPY_CALLBACK_ERROR, status, l_finish);
    
    status = stack->free_callback(&object);
    VALIDATE(status == STATUS_SUCCESS, STATUS_FREE_ERROR, status, l_finish);

    stack->size--;
    status = STATUS_SUCCESS;

l_finish:
    return status;
}

Status Stack__peek(const Stack* const stack, ObjectPtr const out_object)
{
    Status status = STATUS_INIT_ERROR;
    VALIDATE(
        stack != NULL && out_object != NULL && stack->copy_callback != NULL,
        STATUS_NULL_POINTER_ERROR,
        status,
        l_finish);

    bool is_empty = false;
    status = Stack__is_empty(stack, &is_empty);
    VALIDATE(status == STATUS_SUCCESS, STATUS_STACK_UNDERFLOW_ERROR, status, l_finish);
    VALIDATE(!is_empty, STATUS_STACK_UNDERFLOW_ERROR, status, l_finish);

    ObjectPtr object = stack->object_array[stack->size - 1];
    status = stack->copy_callback(out_object, object);
    VALIDATE(status == STATUS_SUCCESS, STATUS_COPY_CALLBACK_ERROR, status, l_finish);

    status = STATUS_SUCCESS;

l_finish:
    return status;
}

Status Stack__is_empty(const Stack* const stack, bool* const is_empty)
{
    Status status = STATUS_INIT_ERROR;
    VALIDATE(stack != NULL, STATUS_NULL_POINTER_ERROR && is_empty != NULL, status, l_finish);

    *is_empty = (stack->size == 0);
    status = STATUS_SUCCESS;

l_finish:
    return status;
}

Status Stack__get_size(const Stack* const stack, uint32_t* const size)
{
    Status status = STATUS_INIT_ERROR;
    VALIDATE(stack != NULL && size != NULL, STATUS_NULL_POINTER_ERROR, status, l_finish);

    *size = stack->size;
    status = STATUS_SUCCESS;

l_finish:
    return status;
}
