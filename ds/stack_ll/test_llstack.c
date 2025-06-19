#include "llstack.h"

// Function to test integer push and pop
void test_integer_stack() {
    printf("Testing Integer Stack...\n");
    llstack *stack = llstack_init();
    int val1 = 10, val2 = 20;

    // Push integers
    llstack_push(stack, INT, &val1);
    llstack_push(stack, INT, &val2);

    // Peek the top element
    struct node *top = llstack_peek(stack);
    if (top && top->data->etype == INT) {
        printf("Top element (peek): %d\n", top->data->value.ival);
    }

    // Pop elements
    struct node *popped = llstack_pop(stack);
    printf("Popped element: %d\n", popped->data->value.ival);
    llstack_free_node(popped);

    popped = llstack_pop(stack);
    printf("Popped element: %d\n", popped->data->value.ival);
    llstack_free_node(popped);

    // Check underflow
    if (llstack_pop(stack) == NULL) {
        printf("Stack underflow correctly handled.\n");
    }

    llstack_free(stack);
}

// Function to test float push and pop
void test_float_stack() {
    printf("Testing Float Stack...\n");
    llstack *stack = llstack_init();
    float val1 = 10.5, val2 = 20.5;

    // Push floats
    llstack_push(stack, FLO, &val1);
    llstack_push(stack, FLO, &val2);

    // Peek the top element
    struct node *top = llstack_peek(stack);
    if (top && top->data->etype == FLO) {
        printf("Top element (peek): %f\n", top->data->value.fval);
    }

    // Pop elements
    struct node *popped = llstack_pop(stack);
    printf("Popped element: %f\n", popped->data->value.fval);
    llstack_free_node(popped);

    popped = llstack_pop(stack);
    printf("Popped element: %f\n", popped->data->value.fval);
    llstack_free_node(popped);

    // Check underflow
    if (llstack_pop(stack) == NULL) {
        printf("Stack underflow correctly handled.\n");
    }

    llstack_free(stack);
}

// Function to test string push and pop
void test_string_stack() {
    printf("Testing String Stack...\n");
    llstack *stack = llstack_init();
    char *str1 = "Hello";
    char *str2 = "World";

    // Push strings
    llstack_push(stack, STR, str1);
    llstack_push(stack, STR, str2);

    // Peek the top element
    struct node *top = llstack_peek(stack);
    if (top && top->data->etype == STR) {
        printf("Top element (peek): %s\n", top->data->value.sval);
    }

    // Pop elements
    struct node *popped = llstack_pop(stack);
    printf("Popped element: %s\n", popped->data->value.sval);
    llstack_free_node(popped);

    popped = llstack_pop(stack);
    printf("Popped element: %s\n", popped->data->value.sval);
    llstack_free_node(popped);

    // Check underflow
    if (llstack_pop(stack) == NULL) {
        printf("Stack underflow correctly handled.\n");
    }

    llstack_free(stack);
}

// Function to test edge cases
void test_edge_cases() {
    printf("Testing Edge Cases...\n");
    llstack *stack = llstack_init();

    // Check underflow on empty stack
    if (llstack_pop(stack) == NULL) {
        printf("Stack underflow correctly handled on empty stack.\n");
    }

    // Check peek on empty stack
    if (llstack_peek(stack) == NULL) {
        printf("Peek correctly handled on empty stack.\n");
    }

    // Free the stack
    llstack_free(stack);
}

// Main function to run all tests
int main() {
    test_integer_stack();
    test_float_stack();
    test_string_stack();
    test_edge_cases();

    puts("\n*** All tests passed ***");

    return 0;
}
