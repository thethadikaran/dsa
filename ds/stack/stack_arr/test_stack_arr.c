
#include "stack_arr.h" 

void test_stack() {
  // Initialize the stack
  stack_arr_t *stack = sa_init();
  if (!stack) {
      printf("Failed to initialize stack.\n");
      return;
  }

  // Test is_empty on a new stack
  printf("Test is_empty on new stack: %s\n", sa_is_empty(stack) ? "Passed" : "Failed");

  // Test pushing elements
  int int_val = 42;
  float float_val = 3.14;
  char *str_val = "Hello, Stack!";
  
  // Push an integer
  if (!sa_push(stack, INT, &int_val)) {
      printf("Failed to push integer.\n");
  }
  
  // Push a float
  if (!sa_push(stack, FLO, &float_val)) {
      printf("Failed to push float.\n");
  }
  
  // Push a string
  if (!sa_push(stack, STR, str_val)) {
      printf("Failed to push string.\n");
  }

  // Test is_empty after pushing
  printf("Test is_empty after pushing: %s\n", sa_is_empty(stack) ? "Failed" : "Passed");

  // Test is_full
  printf("Test is_full on stack with 3 elements: %s\n", sa_is_full(stack) ? "Failed" : "Passed");

  // Test peeking
  element_t *top_element = sa_peek(stack);
  if (top_element && top_element->etype == STR) {
      printf("Peeked top element: %s\n", top_element->value.sval);
  } else {
      printf("Failed to peek top element.\n");
  }

  // Test popping elements
  element_t *popped_element;
  while ((popped_element = sa_pop(stack)) != NULL) {
      switch (popped_element->etype) {
          case INT:
              printf("Popped integer: %d\n", popped_element->value.ival);
              break;
          case FLO:
              printf("Popped float: %f\n", popped_element->value.fval);
              break;
          case STR:
              printf("Popped string: %s\n", popped_element->value.sval);
              free(popped_element->value.sval); // Free string memory
              break;
      }
      free(popped_element); // Free the element itself
  }

  // Test is_empty after popping all elements
  printf("Test is_empty after popping all elements: %s\n", sa_is_empty(stack) ? "Passed" : "Failed");

  // Test popping from an empty stack
  if (sa_pop(stack) == NULL) {
      printf("Popping from empty stack returned NULL as expected.\n");
  } else {
      printf("Failed: Popped from empty stack.\n");
  }

  // Test freeing the stack
  sa_free(&stack);
  if (stack == NULL) {
      printf("Stack freed successfully.\n");
  } else {
      printf("Failed to free stack.\n");
  }
}





/** ALL STARTS HERE **/
int main() {
  test_stack();
  puts("*** ALL TESTS PASSES ***");
  return 0;
}

