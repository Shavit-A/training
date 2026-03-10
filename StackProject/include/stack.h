#pragma once

#include "status.h"

#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>

typedef struct Stack_t Stack;

Status Stack__init(Stack** stack);
Status Stack__free(Stack** stack);

Status Stack__push(Stack* stack, int32_t value);
Status Stack__pop(Stack* stack, int32_t* value);
Status Stack__peek(Stack* stack, int32_t* value);
Status Stack__is_empty(Stack* stack, bool* is_empty);