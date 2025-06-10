#include "linked_list.h"

void test_linked_list() {
  struct node *head = ll_init();
  if (head == NULL) {
    fprintf(stderr, "Failed to initialize linked list\n");
    return;
  }

  // Test inserting integers
  int val1 = 10;
  if (!ll_insert(head, INT, &val1)) {
    fprintf(stderr, "Failed to insert value: %d\n", val1);
  }

  int val2 = 20;
  if (!ll_insert(head, INT, &val2)) {
    fprintf(stderr, "Failed to insert value: %d\n", val2);
  }

  // Test inserting a string
  char *str_val = "Hello";
  if (!ll_insert(head, STR, str_val)) {
    fprintf(stderr, "Failed to insert value: %s\n", str_val);
  }

  // Print the linked list
  printf("Linked List after insertions: ");
  ll_print(head);

  // Test length
  int length = ll_length(head);
  printf("Length of linked list: %d\n", length);

  // Test searching for values
  int search_val = 20;
  int position = ll_search(head, INT, &search_val);
  printf("Position of %d: %d\n", search_val, position);

  // Test inserting at a specific position
  int new_val = 15;
  if (!ll_insert_at(&head, 1, INT, &new_val)) {
    fprintf(stderr, "Failed to insert value: %d at position 1\n", new_val);
  }
  printf("Linked List after inserting %d at position 1: ", new_val);
  ll_print(head);

  // Test deleting a node
  ll_delete_at(&head, 0);
  printf("Linked List after deleting at position 0: ");
  ll_print(head);

  // Test reversing the linked list
  ll_reverse(&head);
  printf("Linked List after reversing: ");
  ll_print(head);

  // Free the linked list
  ll_free(head);
  printf("Linked List freed successfully.\n");
}

void test_edge_cases() {
  struct node *head = ll_init();
  if (head == NULL) {
    fprintf(stderr, "Failed to initialize linked list\n");
    return;
  }

  // Test inserting into an empty list
  int val1 = 42;
  if (!ll_insert(head, INT, &val1)) {
    fprintf(stderr, "Failed to insert value: %d\n", val1);
  }
  printf("Linked List after inserting into empty list: ");
  ll_print(head);

  // Test inserting at the beginning
  int val2 = 30;
  if (!ll_insert_at(&head, 0, INT, &val2))
  {
    fprintf(stderr, "Failed to insert value: %d at position 0\n", val2);
  }
  printf("Linked List after inserting %d at position 0: ", val2);
  ll_print(head);

  // Test inserting at the end
  int val3 = 50;
  if (!ll_insert_at(&head, 3, INT, &val3)) {
    fprintf(stderr, "Failed to insert value: %d at position 3\n", val3);
  }
  printf("Linked List after inserting %d at position 3: ", val3);
  ll_print(head);

  // Test inserting at an invalid position
  if (ll_insert_at(&head, 10, INT, &val1)) {
    fprintf(stderr, "Insertion should have failed at invalid position 10\n");
  }

  // Test deleting from an empty list
  struct node *empty_head = NULL;
  ll_delete_at(&empty_head, 0); // Should not crash

  // Test deleting the only element
  ll_delete_at(&head, 0);
  printf("Linked List after deleting the only element: ");
  ll_print(head);

  // Test deleting from a single-element list
  int val4 = 100;
  if (!ll_insert(head, INT, &val4)) {
    fprintf(stderr, "Failed to insert value: %d\n", val4);
  }
  ll_delete_at(&head, 0);
  printf("Linked List after deleting the last element: ");
  ll_print(head);

  // Test searching in an empty list
  int search_val = 10;
  int position = ll_search(head, INT, &search_val);
  printf("Searching for %d in empty list: Position = %d\n", search_val, position);

  // Test searching for a non-existent value
  search_val = 999;
  position = ll_search(head, INT, &search_val);
  printf("Searching for non-existent value %d: Position = %d\n", search_val, position);

  // Test searching for an existing value
  int val5 = 20;
  if (!ll_insert(head, INT, &val5)) {
    fprintf(stderr, "Failed to insert value: %d\n", val5);
  }
  position = ll_search(head, INT, &val5);
  printf("Searching for existing value %d: Position = %d\n", val5, position);

  // Test reversing an empty list
  struct node *empty_list = NULL;
  ll_reverse(&empty_list); // Should not crash

  // Test reversing a single-element list
  ll_reverse(&head);
  printf("Linked List after reversing: ");
  ll_print(head);

  // Free the linked list
  ll_free(head);
  printf("Linked List freed successfully.\n");
}














/* ALL STARTS HERE !!! */
int main() {
  printf("\n *** TESTING BASIC FEATURES *** \n");
  test_linked_list();          // Run the initial test

  printf("\n *** TESTING EDGE CASES *** \n");
  test_edge_cases();          // Run the edge cases test

  return 0;
}