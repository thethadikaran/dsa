#include <assert.h>

#include "linked_list.h"

// Function prototypes for test cases
void test_ll_init();
void test_ll_append();
void test_ll_insert();
void test_ll_get();
void test_ll_count();
void test_ll_index();
void test_ll_pop();
void test_ll_remove();
void test_ll_reverse();
void test_ll_size();
void test_ll_print();
void test_ll_free();

int main() {
  test_ll_init();
  test_ll_append();
  test_ll_insert();
  test_ll_get();
  test_ll_count();
  test_ll_index();
  test_ll_pop();
  test_ll_remove();
  test_ll_reverse();
  test_ll_size();
  test_ll_print();
  test_ll_free();

  printf("\n*** All tests passed!***\n");
  return 0;
}

void test_ll_init() {
  linkedlist_t *ll = ll_init();
  assert(ll != NULL);
  assert(ll->head == NULL);
  ll_free(ll);
}

void test_ll_append() {
  linkedlist_t *ll = ll_init();
  int val1 = 10;
  float val2 = 20.5;
  char *val3 = "Hello";

  assert(ll_append(ll, INT, &val1) == true);
  assert(ll_append(ll, FLO, &val2) == true);
  assert(ll_append(ll, STR, val3) == true);
  assert(ll->head != NULL);
  assert(ll->head->data.value.ival == 10);
  assert(ll->head->next->data.value.fval == 20.5);
  assert(strcmp(ll->head->next->next->data.value.sval, "Hello") == 0);

  ll_free(ll);
}

void test_ll_insert() {
  linkedlist_t *ll = ll_init();
  int val1 = 10;
  int val2 = 20;
  int val3 = 30;

  ll_append(ll, INT, &val1);
  ll_append(ll, INT, &val2);
  assert(ll_insert(ll, 1, INT, &val3) == true);
  assert(ll->head->next->data.value.ival == 30); // Check if 30 is inserted at index 1

  assert(ll_insert(ll, 0, INT, &val3) == true); // Insert at head
  assert(ll->head->data.value.ival == 30); // Check if 30 is now at head

  assert(ll_insert(ll, 5, INT, &val3) == false); // Invalid index
  ll_free(ll);
}

void test_ll_get() {
  linkedlist_t *ll = ll_init();
  int val1 = 10;
  int val2 = 20;

  ll_append(ll, INT, &val1);
  ll_append(ll, INT, &val2);

  assert(ll_get(ll, 0)->data.value.ival == 10);
  assert(ll_get(ll, 1)->data.value.ival == 20);
  assert(ll_get(ll, 2) == NULL); // Out of bounds

  ll_free(ll);
}

void test_ll_count() {
  linkedlist_t *ll = ll_init();
  int val1 = 10;
  int val2 = 20;
  int val3 = 10;

  ll_append(ll, INT, &val1);
  ll_append(ll, INT, &val2);
  ll_append(ll, INT, &val3);

  assert(ll_count(ll, INT, &val1) == 2); // Count occurrences of 10
  assert(ll_count(ll, INT, &val2) == 1); // Count occurrences of 20
  assert(ll_count(ll, INT, &val3) == 2); // Count occurrences of 10

  ll_free(ll);
}

void test_ll_index() {
  linkedlist_t *ll = ll_init();
  int val1 = 10;
  int val2 = 20;
  int val3 = 30;

  ll_append(ll, INT, &val1);
  ll_append(ll, INT, &val2);

  assert(ll_index(ll, INT, &val1) == 0);
  assert(ll_index(ll, INT, &val2) == 1);
  assert(ll_index(ll, INT, &val3) == -1); // Not found

  ll_free(ll);
}

void test_ll_pop() {
  linkedlist_t *ll = ll_init();
  int val1 = 10;
  int val2 = 20;

  ll_append(ll, INT, &val1);
  ll_append(ll, INT, &val2);

  // Pop the last element
  node_t *popped_node = ll_pop(ll);
  assert(popped_node != NULL);
  assert(popped_node->data.value.ival == 20);
  ll_free_node(popped_node); // Free the popped node

  // Pop again to check if the first element is now the last
  popped_node = ll_pop(ll);
  assert(popped_node != NULL);
  assert(popped_node->data.value.ival == 10);
  ll_free_node(popped_node); // Free the popped node

  // Check if the list is now empty
  assert(ll_pop(ll) == NULL); // Should return NULL

  ll_free(ll);
}

void test_ll_remove() {
  linkedlist_t *ll = ll_init();
  int val1 = 10;
  int val2 = 20;
  int val3 = 30;

  ll_append(ll, INT, &val1);
  ll_append(ll, INT, &val2);
  ll_append(ll, INT, &val3);

  // Remove the second element (20)
  assert(ll_remove(ll, INT, &val2) == true);
  assert(ll_index(ll, INT, &val2) == -1); // Should not be found

  // Remove the head element (10)
  assert(ll_remove(ll, INT, &val1) == true);
  assert(ll_index(ll, INT, &val1) == -1); // Should not be found

  // Remove the last element (30)
  assert(ll_remove(ll, INT, &val3) == true);
  assert(ll_index(ll, INT, &val3) == -1); // Should not be found

  // Check if the list is empty
  assert(ll->head == NULL);

  ll_free(ll);
}

void test_ll_reverse() {
  linkedlist_t *ll = ll_init();
  int val1 = 10;
  int val2 = 20;
  int val3 = 30;

  ll_append(ll, INT, &val1);
  ll_append(ll, INT, &val2);
  ll_append(ll, INT, &val3);

  ll_reverse(ll);

  // After reversing, the head should now be the last element
  assert(ll->head->data.value.ival == 30);
  assert(ll->head->next->data.value.ival == 20);
  assert(ll->head->next->next->data.value.ival == 10);

  ll_free(ll);
}

void test_ll_size() {
  linkedlist_t *ll = ll_init();
  int val1 = 10;
  int val2 = 20;

  assert(ll_size(ll) == 0); // Size should be 0

  ll_append(ll, INT, &val1);
  assert(ll_size(ll) == 1); // Size should be 1

  ll_append(ll, INT, &val2);
  assert(ll_size(ll) == 2); // Size should be 2

  ll_remove(ll, INT, &val1);
  assert(ll_size(ll) == 1); // Size should be 1 after removal

  ll_free(ll);
}

void test_ll_print() {
  linkedlist_t *ll = ll_init();
  int val1 = 10;
  float val2 = 20.5;
  char *val3 = "Hello";

  ll_append(ll, INT, &val1);
  ll_append(ll, FLO, &val2);
  ll_append(ll, STR, val3);

  // Redirect stdout to capture printed output
  FILE *temp = fopen("temp_output.txt", "w");
  if (temp == NULL) {
      perror("Failed to open temp_output.txt");
      exit(EXIT_FAILURE);
  }

  // Use freopen to redirect stdout
  freopen("temp_output.txt", "w", stdout);

  ll_print(ll); // This should print the linked list

  // Restore stdout
  fflush(stdout);
  freopen("CON", "w", stdout); // Restore to original stdout (for Unix-like systems)
  // For Windows, use "CON" instead of "/dev/tty"

  // Check the output file for expected content
  temp = fopen("temp_output.txt", "r");
  char buffer[100];
  fgets(buffer, sizeof(buffer), temp);
  assert(strcmp(buffer, "[10, 20.500000, \"Hello\"]\n") == 0); // Check the printed output

  fclose(temp);
  remove("temp_output.txt"); // Clean up the temporary file

  ll_free(ll);
}


void test_ll_free() {
  linkedlist_t *ll = ll_init();
  int val1 = 10;
  char *val2 = "Test";

  ll_append(ll, INT, &val1);
  ll_append(ll, STR, val2);

  // Free the linked list
  ll_free(ll); // Ensure that this does not cause any memory leaks or crashes

  // After freeing, we should not be able to access the list
  // (This is more of a manual check; we can't assert anything here since the memory is freed)

  printf("Linked list freed successfully.\n");
}

