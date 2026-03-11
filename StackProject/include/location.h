#pragma once

#include "status.h"
#include <stdint.h>

typedef struct Location_t Location;

Status Location__init(Location** const loc);
Status Location__free(Location** const loc);
Status Location__copy(Location* const dst, const Location* const src);

Status Location__set(Location* const loc, int32_t x, int32_t y);
Status Location__get(const Location* const loc, int32_t* const x, int32_t* const y);
