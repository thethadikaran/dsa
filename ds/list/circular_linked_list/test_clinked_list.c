#include "clinked_list.h"
#include <assert.h>


// Function to test initialization of the circular linked list
void test_cll_init() {
  clinkedlist_t *cll = cll_init();
  assert(cll != NULL);
  assert(cll->head == NULL);
  printf("test_cll_init passed.\n");
}

// Function to test appending elements
void test_cll_append() {
  clinkedlist_t *cll = cll_init();
  int val1 = 10, val2 = 20;

  assert(cll_append(cll, INT, &val1) == true);
  assert(cll->head->data.value.ival == 10);
  assert(cll->head->next == cll->head); // Points to itself

  assert(cll_append(cll, INT, &val2) == true);
  assert(cll->head->data.value.ival == 20);
  assert(cll->head->next->next == cll->head); // Circular link
  printf("test_cll_append passed.\n");
}

// Function to test getting elements
void test_cll_get() {
  clinkedlist_t *cll = cll_init();
  int val1 = 10, val2 = 20;
  cll_append(cll, INT, &val1);
  cll_append(cll, INT, &val2);

  assert(cll_get(cll, 0)->data.value.ival == 10);
  assert(cll_get(cll, 1)->data.value.ival == 20);
  assert(cll_get(cll, 2) == NULL); // Out of bounds
  printf("test_cll_get passed.\n");
}

// Function to test inserting elements
void test_cll_insert() {
  clinkedlist_t *cll = cll_init();
  int val1 = 10, val2 = 20, val3 = 30;

  cll_append(cll, INT, &val1);
  cll_append(cll, INT, &val2);
  assert(cll_insert(cll, 0, INT, &val3) == true); // Insert at head
  assert(cll->head->next->data.value.ival == 30); // New head

  assert(cll_insert(cll, 1, INT, &val1) == true); // Insert in-between
  assert(cll_get(cll, 1)->data.value.ival == 10); // Check value at index 1
  printf("test_cll_insert passed.\n");
}

// Function to test counting elements
void test_cll_count() {
  clinkedlist_t *cll = cll_init();
  int val1 = 10, val2 = 20, val3 = 10;

  cll_append(cll, INT, &val1);
  cll_append(cll, INT, &val2);
  cll_append(cll, INT, &val3);

  assert(cll_count(cll, INT, &val1) == 2); // Count occurrences of 10
  assert(cll_count(cll, INT, &val2) == 1); // Count occurrences of 20
  printf("test_cll_count passed.\n");
}

// Function to test finding index of elements
void test_cll_index() {
  clinkedlist_t *cll = cll_init();
  int val1 = 10, val2 = 20, val3 = 400;

  cll_append(cll, INT, &val1);
  cll_append(cll, INT, &val2);

  assert(cll_index(cll, INT, &val1) == 0); // Index of 10
  assert(cll_index(cll, INT, &val2) == 1); // Index of 20
  assert(cll_index(cll, INT, &val3) == -1); // Not found
  printf("test_cll_index passed.\n");
}

// Function to test popping elements
void test_cll_pop() {
  clinkedlist_t *cll = cll_init();
  int val1 = 10, val2 = 20;

  cll_append(cll, INT, &val1);
  cll_append(cll, INT, &val2);

  node_t *popped_node = cll_pop(cll);
  assert(popped_node->data.value.ival == 20); // Last node popped
  cll_free_node(popped_node);

  popped_node = cll_pop(cll);
  assert(popped_node->data.value.ival == 10); // Last remaining node popped
  cll_free_node(popped_node);

  assert(cll_pop(cll) == NULL); // List should be empty now
  printf("test_cll_pop passed.\n");
}

// Function to test removing elements
void test_cll_remove() {
  clinkedlist_t *cll = cll_init();
  int val1 = 10, val2 = 20, val3 = 10;

  cll_append(cll, INT, &val1);
  cll_append(cll, INT, &val2);
  cll_append(cll, INT, &val3);

  assert(cll_remove(cll, INT, &val1) == true); // Remove first occurrence of 10
  assert(cll_count(cll, INT, &val1) == 1); // One 10 should remain
  assert(cll_remove(cll, INT, &val2) == true); // Remove 20
  assert(cll_count(cll, INT, &val2) == 0); // 20 should be gone
  assert(cll_remove(cll, INT, &val3) == true); // Remove last 10
  assert(cll_count(cll, INT, &val1) == 0); // All 10s should be gone
  printf("test_cll_remove passed.\n");
}

// Function to test size of the list
void test_cll_size() {
  clinkedlist_t *cll = cll_init();
  int val1 = 10, val2 = 20;

  assert(cll_size(cll) == 0); // Size should be 0

  cll_append(cll, INT, &val1);
  assert(cll_size(cll) == 1); // Size should be 1

  cll_append(cll, INT, &val2);
  assert(cll_size(cll) == 2); // Size should be 2

  cll_pop(cll);
  assert(cll_size(cll) == 1); // Size should be 1 after pop

  cll_remove(cll, INT, &val1);
  assert(cll_size(cll) == 0); // Size should be 0 after removing last element
  printf("test_cll_size passed.\n");
}

// Function to test freeing the list
void test_cll_free() {
  clinkedlist_t *cll = cll_init();
  int val1 = 10, val2 = 20;

  cll_append(cll, INT, &val1);
  cll_append(cll, INT, &val2);

  cll_free(cll); // Should free without errors
  printf("test_cll_free passed.\n");
}

// Main function to run all tests
int main() {
  test_cll_init();
  test_cll_append();
  test_cll_get();
  test_cll_insert();
  test_cll_count();
  test_cll_index();
  test_cll_pop();
  test_cll_remove();
  test_cll_size();
  test_cll_free();

  printf("All tests passed!\n");
  return 0;
}