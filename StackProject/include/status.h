#pragma once

#include <stdio.h>

typedef enum {
    STATUS_SUCCESS = 0,
    STATUS_INIT_ERROR,
    STATUS_NULL_POINTER_ERROR,
    STATUS_MEMORY_ALLOCATION_ERROR,
} Status;