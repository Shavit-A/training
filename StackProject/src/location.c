#include "location.h"
#include "validation_utils.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Location_t {
    int32_t x;
    int32_t y;
};

Status Location__init(Location** const location)
{
    Status status = STATUS_INIT_ERROR;
    VALIDATE(location != NULL, STATUS_NULL_POINTER_ERROR, status, l_finish);

    *location = (Location*)malloc(sizeof(Location));
    VALIDATE(*location != NULL, STATUS_MEMORY_ALLOCATION_ERROR, status, l_finish);

    (*location)->x = 0;
    (*location)->y = 0;

    status = STATUS_SUCCESS;

l_finish:
    return status;
}

Status Location__free(Location** const location)
{
    Status status = STATUS_INIT_ERROR;
    VALIDATE(location != NULL && *location != NULL, STATUS_NULL_POINTER_ERROR, status, l_finish);

    free(*location);
    *location = NULL;
    status = STATUS_SUCCESS;

l_finish:
    return status;
}

Status Location__copy(Location* const dst, const Location* const src)
{
    Status status = STATUS_INIT_ERROR;
    VALIDATE(dst != NULL && src != NULL, STATUS_NULL_POINTER_ERROR, status, l_finish);

    ((Location*)dst)->x = ((Location*)src)->x;
    ((Location*)dst)->y = ((Location*)src)->y;

    status = STATUS_SUCCESS;

l_finish:
    return status;
}

Status Location__set(Location* const loc, const int32_t x, const int32_t y)
{
    Status status = STATUS_INIT_ERROR;
    VALIDATE(loc != NULL, STATUS_NULL_POINTER_ERROR, status, l_finish);

    loc->x = x;
    loc->y = y;

    status = STATUS_SUCCESS;

l_finish:
    return status;
}

Status Location__get(const Location* const loc, int32_t* const x, int32_t* const y)
{
    Status status = STATUS_INIT_ERROR;
    VALIDATE(loc != NULL && x != NULL && y != NULL, STATUS_NULL_POINTER_ERROR, status, l_finish);

    *x = loc->x;
    *y = loc->y;

    status = STATUS_SUCCESS;

l_finish:
    return status;
}
