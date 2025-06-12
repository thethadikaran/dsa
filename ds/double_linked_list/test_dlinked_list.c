#include "dlinked_list.h"

// Function prototypes for testing
void test_dll_init();
void test_dll_insert();
void test_dll_insert_at();
void test_dll_delete_at();
void test_dll_print();
void test_dll_free();
void test_dll_reverse();
void test_edge_cases();

int main() {
  puts("\n=== test init function ===\n");
  test_dll_init();

  puts("\n=== test insert function ===\n");
  test_dll_insert();

  puts("\n=== test insert_at function ===\n");
  test_dll_insert_at();

  puts("\n=== test delete function ===\n");
  test_dll_delete_at();

  puts("\n=== test print function ===\n");
  test_dll_print();

  puts("\n=== test free function ===\n");
  test_dll_free();

  puts("\n=== test reverse function ===\n");
  test_dll_reverse();

  puts("\n=== test edgecases function ===\n");
  test_edge_cases();

  return 0;
}

void test_dll_init() {
  printf("Running initialization test...\n");
  struct dnode *head = dll_init();
  if (head == NULL) {
      printf("Initialization failed.\n");
  } else {
      printf("Initialization successful. Head node type: %d\n", head->ele.etype);
      dll_free(head); // Free the initialized node
  }
}

void test_edge_cases() {
  printf("Running edge case tests...\n");

  // Test initialization
  struct dnode *head = dll_init();
  if (head == NULL) {
      printf("Initialization failed.\n");
  } else {
      printf("Initialization successful.\n");
  }

  // Test inserting into an empty list
  int value = 10;
  if (dll_insert(head, INT, &value)) {
      printf("Inserted into empty list successfully.\n");
  } else {
      printf("Failed to insert into empty list.\n");
  }

  // Test printing the list
  dll_print(head);

  // Test inserting at position 0
  int value2 = 20;
  if (dll_insert_at(&head, 0, INT, &value2)) {
      printf("Inserted at position 0 successfully.\n");
  } else {
      printf("Failed to insert at position 0.\n");
  }
  dll_print(head);

  // Test inserting at position 1 (end of the list)
  int value3 = 30;
  if (dll_insert_at(&head, 1, INT, &value3)) {
      printf("Inserted at position 1 successfully.\n");
  } else {
      printf("Failed to insert at position 1.\n");
  }
  dll_print(head);

  // Test inserting at an invalid position
  if (!dll_insert_at(&head, 5, INT, &value3)) {
      printf("Correctly failed to insert at invalid position.\n");
  }

  // Test deleting the head
  dll_delete_at(&head, 0);
  printf("After deleting head:\n");
  dll_print(head);

  // Test deleting the last element
  dll_delete_at(&head, 1);
  printf("After deleting last element:\n");
  dll_print(head);

  // Test deleting at an invalid position
  dll_delete_at(&head, 5);
  printf("Correctly handled deletion at invalid position.\n");

  // Free the list
  dll_free(head);
  printf("List freed successfully.\n");
}

void test_dll_insert() {
  printf("Running insert tests...\n");
  struct dnode *head = dll_init();
  int value = 10;

  if (dll_insert(head, INT, &value)) {
      printf("Inserted into empty list successfully.\n");
  } else {
      printf("Failed to insert into empty list.\n");
  }

  dll_print(head);
  dll_free(head);
}

void test_dll_insert_at() {
  printf("Running insert_at tests...\n");
  struct dnode *head = dll_init();
  int value1 = 10, value2 = 20, value3 = 30;

  dll_insert(head, INT, &value1);
  dll_insert_at(&head, 0, INT, &value2); // Insert at head
  dll_insert_at(&head, 1, INT, &value3); // Insert at end

  dll_print(head);
  dll_free(head);
}

void test_dll_delete_at() {
  printf("Running delete_at tests...\n");
  struct dnode *head = dll_init();
  int value1 = 10, value2 = 20, value3 = 30;

  dll_insert(head, INT, &value1);
  dll_insert_at(&head, 0, INT, &value2);
  dll_insert_at(&head, 1, INT, &value3);

  dll_print(head);
  dll_delete_at(&head, 1); // Delete second element
  dll_print(head);
  dll_free(head);
}

void test_dll_print() {
  printf("Running print tests...\n");
  struct dnode *head = dll_init();
  int value1 = 10, value2 = 20;

  dll_insert(head, INT, &value1);
  dll_insert_at(&head, 0, INT, &value2); // Insert at head

  dll_print(head);
  dll_free(head);
}

void test_dll_free() {
  printf("Running free tests...\n");
  struct dnode *head = dll_init();
  int value1 = 10, value2 = 20;

  dll_insert(head, INT, &value1);
  dll_insert_at(&head, 0, INT, &value2); // Insert at head

  dll_print(head);
  dll_free(head);
  printf("List freed successfully.\n");
}

void test_dll_reverse() {
  printf("Running reverse tests...\n");
  struct dnode *head = dll_init();
  int value1 = 10, value2 = 20, value3 = 30;

  dll_insert(head, INT, &value1);
  dll_insert_at(&head, 0, INT, &value2); // Insert at head
  dll_insert_at(&head, 1, INT, &value3); // Insert at end

  printf("Original list:\n");
  dll_print(head);

  dll_reverse(&head);
  printf("Reversed list:\n");
  dll_print(head);

  dll_free(head);
}

