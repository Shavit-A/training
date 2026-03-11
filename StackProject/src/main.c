#include "stack.h"
#include "location.h"

#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    printf("About to run the Stack test...\n");

    Status status = STATUS_INIT_ERROR;
    Stack* stack = NULL;
    status = Stack__init(
        &stack,
        (StackObjectInitCallback)Location__init,
        (StackObjectFreeCallback)Location__free,
        (StackObjectCopyCallback)Location__copy
    );
    if (status != STATUS_SUCCESS) {
        printf("Failed to initialize stack. Status code: %d\n", status);
        return EXIT_FAILURE;
    }

    Location* loc1 = NULL;
    status = Location__init(&loc1);
    if (status != STATUS_SUCCESS) {
        printf("Failed to init loc1\n");
        return EXIT_FAILURE;
    }

    status = Location__set(loc1, 1, 2);
    if (status != STATUS_SUCCESS) {
        printf("Failed to set loc1\n"); 
        return EXIT_FAILURE;
    }

    status = Stack__push(stack, loc1);
    if (status != STATUS_SUCCESS) {
        printf("Failed to push value onto stack. Status code: %d\n", status);
        return EXIT_FAILURE;
    }

    status = Location__set(loc1, 3, 4);
    if (status != STATUS_SUCCESS) {
        printf("Failed to set loc1\n"); 
        return EXIT_FAILURE;
    }

    status = Stack__push(stack, loc1);
    if (status != STATUS_SUCCESS) {
        printf("Failed to push value onto stack. Status code: %d\n", status);
        return EXIT_FAILURE;
    }

    status = Location__free(&loc1);
    if (status != STATUS_SUCCESS) {
        printf("Failed to free loc1\n");
        return EXIT_FAILURE;
    }

    printf("Finished pushing to stack, About to Pop...\n");

    Location* out_location = NULL;
    status = Location__init(&out_location);
    if (status != STATUS_SUCCESS) {
        printf("Failed to init out_location\n");
        return EXIT_FAILURE;
    }

    status = Stack__pop(stack, out_location);
    if (status != STATUS_SUCCESS) {
        printf("Failed to pop value from stack. Status code: %d\n", status);
        return EXIT_FAILURE;
    }

    int32_t x = 0, y = 0;
    status = Location__get(out_location, &x, &y);
    if (status != STATUS_SUCCESS) {
        printf("Failed to pop value from stack. Status code: %d\n", status);
        return EXIT_FAILURE;
    }

    printf("Popped value: (%d, %d)\n", x, y);

    status = Stack__peek(stack, out_location);
    if (status != STATUS_SUCCESS) {
        printf("Failed to peek value from stack. Status code: %d\n", status);
        return EXIT_FAILURE;
    }

    status = Location__get(out_location, &x, &y);
    if (status != STATUS_SUCCESS) {
        printf("Failed to pop value from stack. Status code: %d\n", status);
        return EXIT_FAILURE;
    }

    printf("Peeked value: (%d, %d)\n", x, y);

    status = Stack__pop(stack, out_location);
    if (status != STATUS_SUCCESS) {
        printf("Failed to pop value from stack. Status code: %d\n", status);
        return EXIT_FAILURE;
    }

    status = Location__get(out_location, &x, &y);
    if (status != STATUS_SUCCESS) {
        printf("Failed to pop value from stack. Status code: %d\n", status);
        return EXIT_FAILURE;
    }

    printf("Popped value: (%d, %d)\n", x, y);

    bool is_empty = false;
    status = Stack__is_empty(stack, &is_empty);
    if (status != STATUS_SUCCESS) {
        printf("Failed to check if stack is empty. Status code: %d\n", status);
        return EXIT_FAILURE;
    }

    printf("Is stack empty? %s\n", is_empty ? "Yes" : "No");

    uint32_t stack_size = 0;
    status = Stack__get_size(stack, &stack_size);
    if (status != STATUS_SUCCESS) {
        printf("Failed to get stack size. Status code: %d\n", status);
        return EXIT_FAILURE;
    }

    printf("Stack size: %u\n", stack_size);

    status = Stack__free(&stack);
    if (status != STATUS_SUCCESS) {
        printf("Failed to free stack. Status code: %d\n", status);
        return EXIT_FAILURE;
    }

    printf("Finished running successfully!\n");
    return EXIT_SUCCESS;
}