#include "stack.h"

#include <stdio.h>
#include <stdlib.h>

typedef struct Location_t {
    int32_t x;
    int32_t y;
} Location;

int main(void)
{
    printf("About to run the Stack test...\n");

    Status status = STATUS_INIT_ERROR;
    Stack* stack = NULL;
    status = Stack__init(&stack, sizeof(Location));
    if (status != STATUS_SUCCESS) {
        printf("Failed to initialize stack. Status code: %d\n", status);
        return EXIT_FAILURE;
    }

    Location loc1 = { .x = 1, .y = 2 };
    status = Stack__push(stack, &loc1);
    if (status != STATUS_SUCCESS) {
        printf("Failed to push value onto stack. Status code: %d\n", status);
        return EXIT_FAILURE;
    }

    Location loc2 = { .x = 3, .y = 4 };
    status = Stack__push(stack, &loc2);
    if (status != STATUS_SUCCESS) {
        printf("Failed to push value onto stack. Status code: %d\n", status);
        return EXIT_FAILURE;
    }

    Location *location_ptr = NULL;
    status = Stack__pop(stack, (StackObject*)&location_ptr);
    if (status != STATUS_SUCCESS) {
        printf("Failed to pop value from stack. Status code: %d\n", status);
        return EXIT_FAILURE;
    }

    printf("Popped value: (%d, %d)\n", location_ptr->x, location_ptr->y);

    status = Stack__peek(stack, (StackObject*)&location_ptr);
    if (status != STATUS_SUCCESS) {
        printf("Failed to peek value from stack. Status code: %d\n", status);
        return EXIT_FAILURE;
    }

    printf("Peeked value: (%d, %d)\n", location_ptr->x, location_ptr->y);

    status = Stack__pop(stack, (StackObject*)&location_ptr);
    if (status != STATUS_SUCCESS) {
        printf("Failed to pop value from stack. Status code: %d\n", status);
        return EXIT_FAILURE;
    }

    printf("Popped value: (%d, %d)\n", location_ptr->x, location_ptr->y);

    bool is_empty = false;
    status = Stack__is_empty(stack, &is_empty);
    if (status != STATUS_SUCCESS) {
        printf("Failed to check if stack is empty. Status code: %d\n", status);
        return EXIT_FAILURE;
    }

    printf("Is stack empty? %s\n", is_empty ? "Yes" : "No");

    printf("Finished running successfully!\n");
    return EXIT_SUCCESS;
}