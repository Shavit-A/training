#include "stack.h"

#include <stdio.h>

int main(void)
{
    Stack* stack = NULL;
    Status status = Stack__init(&stack);
    if (status != STATUS_SUCCESS) {
        printf("Failed to initialize stack. Status code: %d\n", status);
        return -1;
    }

    printf("Hello, World!\n");
    return 0;
}