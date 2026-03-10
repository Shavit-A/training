#pragma once

#define VALIDATE(condition, error_code, status, label) \
    do { \
        if (!(condition)) { \
            printf("Validation failed: %s\n", #condition); \
            (status) = (error_code); \
            goto label; \
        } \
    } while (0)
