#pragma once

#define VALIDATE(condition, error_code, status, label) \
    do { \
        if (!(condition)) { \
            printf("Validation failed: %s\n", #condition); \
            (status) = (error_code); \
            goto label; \
        } \
    } while (0)

#define TRACE_ON_FAILURE(condition, message) \
    do { \
        if (!(condition)) { \
            printf("Trace: %s\n", message); \
        } \
    } while (0)
