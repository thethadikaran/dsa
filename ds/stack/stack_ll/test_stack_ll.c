#include "stack_ll.h"
#include <assert.h>

// Function to test stack initialization
void test_sll_init() {
    stack_ll_t *stack = sll_init();
    assert(stack != NULL);
    assert(stack->size == 0);
    assert(stack->top == NULL);
    sll_free(&stack);
}

// Function to test pushing elements onto the stack
void test_sll_push() {
    stack_ll_t *stack = sll_init();
    int val1 = 10;
    float val2 = 20.5;
    char *val3 = "Hello";

    assert(sll_push(stack, INT, &val1) == true);
    assert(stack->size == 1);
    assert(stack->top->data.etype == INT);
    assert(stack->top->data.value.ival == 10);

    assert(sll_push(stack, FLO, &val2) == true);
    assert(stack->size == 2);
    assert(stack->top->data.etype == FLO);
    assert(stack->top->data.value.fval == 20.5);

    assert(sll_push(stack, STR, val3) == true);
    assert(stack->size == 3);
    assert(stack->top->data.etype == STR);
    assert(strcmp(stack->top->data.value.sval, "Hello") == 0);

    sll_free(&stack);
}

// Function to test popping elements from the stack
void test_sll_pop() {
  stack_ll_t *stack = sll_init();
  int val1 = 10;
  float val2 = 20.5;
  char *val3 = "Hello";

  sll_push(stack, INT, &val1);
  sll_push(stack, FLO, &val2);
  sll_push(stack, STR, val3);

  node_t *popped_node = sll_pop(stack);
  assert(popped_node != NULL);
  assert(popped_node->data.etype == STR);
  assert(strcmp(popped_node->data.value.sval, "Hello") == 0);
  free(popped_node->data.value.sval);
  free(popped_node);

  assert(stack->size == 2);
  popped_node = sll_pop(stack);
  assert(popped_node != NULL);
  assert(popped_node->data.etype == FLO);
  assert(popped_node->data.value.fval == 20.5);
  free(popped_node);

  popped_node = sll_pop(stack);
  assert(popped_node != NULL);
  assert(popped_node->data.etype == INT);
  assert(popped_node->data.value.ival == 10);
  free(popped_node);

  assert(sll_pop(stack) == NULL); // Stack should be empty now
  sll_free(&stack);
}

// Function to test peeking at the top element
void test_sll_peek() {
  stack_ll_t *stack = sll_init();
  int val1 = 10;
  float val2 = 20.5;

  sll_push(stack, INT, &val1);
  assert(sll_peek(stack) != NULL);
  assert(sll_peek(stack)->data.etype == INT);
  assert(sll_peek(stack)->data.value.ival == 10);

  sll_push(stack, FLO, &val2);
  assert(sll_peek(stack) != NULL);
  assert(sll_peek(stack)->data.etype == FLO);
  assert(sll_peek(stack)->data.value.fval == 20.5);

  sll_pop(stack); // Pop the float
  assert(sll_peek(stack) != NULL);
  assert(sll_peek(stack)->data.etype == INT);
  assert(sll_peek(stack)->data.value.ival == 10);

  sll_pop(stack); // Pop the int
  assert(sll_peek(stack) == NULL); // Stack should be empty now

  sll_free(&stack);
}

// Function to test checking if the stack is empty
void test_sll_is_empty() {
  stack_ll_t *stack = sll_init();
  assert(sll_is_empty(stack) == true);

  int val = 10;
  sll_push(stack, INT, &val);
  assert(sll_is_empty(stack) == false);

  sll_pop(stack);
  assert(sll_is_empty(stack) == true);

  sll_free(&stack);
}

// Function to test freeing the stack
void test_sll_free() {
  stack_ll_t *stack = sll_init();
  char *val1 = strdup("Test1");
  char *val2 = strdup("Test2");

  sll_push(stack, STR, val1);
  sll_push(stack, STR, val2);

  // Free the stack and check if it is properly freed
  sll_free(&stack);
  assert(stack == NULL); // Stack should be NULL after freeing
}

// Function to test printing the stack
void test_sll_print() {
  stack_ll_t *stack = sll_init();
  int val1 = 10;
  float val2 = 20.5;
  char *val3 = "Hello";

  sll_push(stack, INT, &val1);
  sll_push(stack, FLO, &val2);
  sll_push(stack, STR, val3);

  // Expected output: [ "Hello", 20.5, 10 ]
  printf("Expected output: [ \"Hello\", 20.5, 10 ]\n");
  sll_print(stack); // This will print the stack contents

  // Clean up
  sll_free(&stack);
}

// Main function to run all tests
int main() {
  test_sll_init();
  test_sll_push();
  test_sll_pop();
  test_sll_peek();
  test_sll_is_empty();
  test_sll_free();
  test_sll_print();

  printf("All tests passed successfully!\n");
  return 0;
}

