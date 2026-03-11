#pragma once

#include "status.h"

#include <stdint.h>
#include <stdbool.h>

typedef struct Stack_t Stack;
typedef void* ObjectPtr;

typedef Status (*StackObjectInitCallback)(const ObjectPtr* obj);
typedef Status (*StackObjectFreeCallback)(ObjectPtr* const obj);
typedef Status (*StackObjectCopyCallback)(ObjectPtr const dst, const ObjectPtr const src);

Status Stack__init(
    Stack** const stack,
    StackObjectInitCallback init_callback,
    StackObjectFreeCallback free_callback,
    StackObjectCopyCallback copy_callback);
Status Stack__free(Stack** const stack);

Status Stack__push(Stack* const stack, const ObjectPtr object);
Status Stack__pop(Stack* const stack,  ObjectPtr const out_object);
Status Stack__peek(const Stack* const stack, ObjectPtr const out_object);
Status Stack__is_empty(const Stack* const stack, bool* const is_empty);
Status Stack__get_size(const Stack* const stack, uint32_t* const size);
