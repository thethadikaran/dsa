
#include "astack.h" 

void test_stack() {
    // Test 1: Initialize the stack
    stack *s = astack_init();
    if (!s) {
        fprintf(stderr, "Stack initialization failed.\n");
        return;
    }
    printf("Test 1: Stack initialized successfully.\n");

    // Test 2: Push elements of different types
    int int_val = 10;
    float float_val = 5.5;
    char *str_val = "Test String";

    if (!astack_push(s, INT, &int_val)) {
        fprintf(stderr, "Failed to push integer.\n");
    }
    if (!astack_push(s, FLO, &float_val)) {
        fprintf(stderr, "Failed to push float.\n");
    }
    if (!astack_push(s, STR, str_val)) {
        fprintf(stderr, "Failed to push string.\n");
    }
    printf("Test 2: Pushed elements successfully.\n");

    // Test 3: Peek at the top element
    struct element *top_element = astack_peek(s);
    if (top_element) {
        printf("Test 3: Peeked top element: ");
        switch (top_element->etype) {
            case INT: printf("INT = %d\n", top_element->value.ival); break;
            case FLO: printf("FLOAT = %.2f\n", top_element->value.fval); break;
            case STR: printf("STRING = %s\n", top_element->value.sval); break;
        }
    }

    // Test 4: Pop elements and check their values
    struct element *popped_element;
    while ((popped_element = astack_pop(s)) != NULL) {
        printf("Test 4: Popped element: ");
        switch (popped_element->etype) {
            case INT: printf("INT = %d\n", popped_element->value.ival); break;
            case FLO: printf("FLOAT = %.2f\n", popped_element->value.fval); break;
            case STR: printf("STRING = %s\n", popped_element->value.sval); break;
        }
        astack_free_element(popped_element); // Free the popped element
    }

    // Test 5: Attempt to pop from an empty stack
    popped_element = astack_pop(s);
    if (!popped_element) {
        printf("Test 5: Stack Underflow handled correctly.\n");
    }

    // Test 6: Push elements until overflow
    for (int i = 0; i < SIZE; i++) {
        if (!astack_push(s, INT, &int_val)) {
            printf("Test 6: Stack Overflow handled correctly at size %d.\n", i);
            break;
        }
    }

    // Clean up
    free(s); // Free the stack itself
    printf("All tests completed successfully.\n");
}

int main() {
    test_stack();
    return 0;
}
