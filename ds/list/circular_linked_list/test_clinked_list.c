#include "clinked_list.h"

// Function prototypes for testing
void test_cll();

int main() {
    test_cll();
    return 0;
}

void test_cll() {
  clinkedlist *cll = cll_init();
  if (!cll) {
    printf("Failed to initialize circular linked list.\n");
    return;
  }

  // Test 1: Append to an empty list
  int val1 = 10;
  if (!cll_append_last(cll, INT, &val1)) {
    printf("Failed to append to empty list.\n");
  }
  printf("After appending 10: ");
  cll_print(cll); // Expected: 10 -> (head)

  // Test 2: Append to the list
  int val2 = 20;
  if (!cll_append_last(cll, INT, &val2)) {
    printf("Failed to append 20.\n");
  }
  printf("After appending 20: ");
  cll_print(cll); // Expected: 10 -> 20 -> (head)

  // Test 3: Append to the front
  int val3 = 5;
  if (!cll_append_front(cll, INT, &val3)) {
      printf("Failed to append front 5.\n");
  }
  printf("After appending front 5: ");
  cll_print(cll); // Expected: 5 -> 10 -> 20 -> (head)

  // Test 4: Delete a node
  cll_delete(cll, INT, &val2); // Delete 20
  printf("After deleting 20: ");
  cll_print(cll); // Expected: 5 -> 10 -> (head)

  // Test 5: Delete the head node
  cll_delete(cll, INT, &val3); // Delete 5
  printf("After deleting 5: ");
  cll_print(cll); // Expected: 10 -> (head)

  // Test 6: Delete the last node
  cll_delete(cll, INT, &val1); // Delete 10
  printf("After deleting 10: ");
  cll_print(cll); // Expected: List is empty

  // Test 7: Delete from an empty list
  cll_delete(cll, INT, &val1); // Should not crash
  printf("After trying to delete from empty list: ");
  cll_print(cll); // Expected: List is empty

  // Test 8: Append to an empty list again
  if (!cll_append_front(cll, INT, &val1)) {
      printf("Failed to append to empty list.\n");
  }
  printf("After appending 10 again: ");
  cll_print(cll); // Expected: 10 -> (head)

  // Test 9: Free the circular linked list
  cll_free(cll);
  printf("Circular linked list freed.\n");
}