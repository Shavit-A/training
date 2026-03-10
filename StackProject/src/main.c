#include "stack.h"

#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    printf("About to run the Stack test...\n");

    Status status = STATUS_INIT_ERROR;
    Stack* stack = NULL;
    status = Stack__init(&stack);
    if (status != STATUS_SUCCESS) {
        printf("Failed to initialize stack. Status code: %d\n", status);
        return EXIT_FAILURE;
    }

    status = Stack__push(stack, 42);
    if (status != STATUS_SUCCESS) {
        printf("Failed to push value onto stack. Status code: %d\n", status);
        return EXIT_FAILURE;
    }

    status = Stack__push(stack, 43);
    if (status != STATUS_SUCCESS) {
        printf("Failed to push value onto stack. Status code: %d\n", status);
        return EXIT_FAILURE;
    }

    int32_t value = 0;
    status = Stack__pop(stack, &value);
    if (status != STATUS_SUCCESS) {
        printf("Failed to pop value from stack. Status code: %d\n", status);
        return EXIT_FAILURE;
    }

    printf("Popped value: %d\n", value);

    status = Stack__pop(stack, &value);
    if (status != STATUS_SUCCESS) {
        printf("Failed to pop value from stack. Status code: %d\n", status);
        return EXIT_FAILURE;
    }

    printf("Popped value: %d\n", value);

    status = Stack__pop(stack, &value);
    if (status != STATUS_SUCCESS) {
        printf("Failed to pop value from stack. Status code: %d\n", status);
        return EXIT_FAILURE;
    }

    printf("Popped value: %d\n", value);
    printf("Finished running successfully!\n");
    return EXIT_SUCCESS;
}