#include "stack.h"

#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    Status status = STATUS_INIT_ERROR;
    Stack* stack = NULL;
    status = Stack__init(&stack);
    if (status != STATUS_SUCCESS) {
        printf("Failed to initialize stack. Status code: %d\n", status);
        return EXIT_FAILURE;
    }

    status = Stack__free(&stack);
    if (status != STATUS_SUCCESS) {
        printf("Failed to free stack. Status code: %d\n", status);
        return EXIT_FAILURE;
    }

    printf("Hello, World!\n");
    return EXIT_SUCCESS;
}