#pragma once

#include "status.h"

#include <stdint.h>
#include <stdbool.h>

typedef struct Stack_t Stack;
typedef void* StackObject;

Status Stack__init(Stack** stack, uint32_t object_size);
Status Stack__free(Stack** stack);

Status Stack__push(Stack* stack, StackObject object);
Status Stack__pop(Stack* stack, StackObject* value);
Status Stack__peek(Stack* stack, StackObject* value);
Status Stack__is_empty(Stack* stack, bool* is_empty);