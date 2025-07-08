#include <assert.h>

#include "dlinked_list.h"

// Test function for dll_init
void test_dll_init() {
    dlinkedlist_t *dll = dll_init();
    printf("Testing dll_init: %s\n", dll != NULL ? "Passed" : "Failed");
    dll_free(dll);
}

// Test function for dll_append
void test_dll_append() {
    dlinkedlist_t *dll = dll_init();
    int val = 10;
    bool result = dll_append(dll, INT, &val);
    printf("Testing dll_append: %s\n", result ? "Passed" : "Failed");
    dll_print(dll); // Expected: [10]

    // Edge case: append NULL value
    bool append_null_result = dll_append(dll, INT, NULL);
    printf("Testing dll_append with NULL value: %s (Expected: false)\n", !append_null_result ? "Passed" : "Failed");

    dll_free(dll);
}

// Test function for dll_insert
void test_dll_insert() {
    dlinkedlist_t *dll = dll_init();
    int val1 = 10, val2 = 20, val3 = 15;
    dll_append(dll, INT, &val1);
    dll_append(dll, INT, &val2);
    bool result = dll_insert(dll, 1, INT, &val3);
    printf("Testing dll_insert at index 1: %s\n", result ? "Passed" : "Failed");
    dll_print(dll); // Expected: [10, 15, 20]

    // Edge case: insert at invalid index
    bool insert_invalid_result = dll_insert(dll, 10, INT, &val3);
    printf("Testing dll_insert at invalid index: %s (Expected: false)\n", !insert_invalid_result ? "Passed" : "Failed");

    // Edge case: insert into empty list
    bool insert_empty_result = dll_insert(dll, 0, INT, &val3);
    printf("Testing dll_insert into empty list: %s\n", insert_empty_result ? "Passed" : "Failed");
    dll_print(dll); // Expected: [15]

    dll_free(dll);
}

// Test function for dll_get
void test_dll_get() {
    dlinkedlist_t *dll = dll_init();
    int val1 = 10, val2 = 20;
    dll_append(dll, INT, &val1);
    dll_append(dll, INT, &val2);
    node_t *node = dll_get(dll, 1);
    printf("Testing dll_get at index 1: %s (Expected: 20)\n", node && node->data.value.ival == 20 ? "Passed" : "Failed");

    // Edge case: get from an empty list
    dlinkedlist_t *empty_dll = dll_init();
    node_t *empty_get = dll_get(empty_dll, 0);
    printf("Testing dll_get on empty list: %s (Expected: NULL)\n", empty_get == NULL ? "Passed" : "Failed");
    dll_free(empty_dll);

    // Edge case: get with invalid index
    node_t *invalid_get = dll_get(dll, 10);
    printf("Testing dll_get with invalid index: %s (Expected: NULL)\n", invalid_get == NULL ? "Passed" : "Failed");

    dll_free(dll);
}

// Test function for dll_count
void test_dll_count() {
    dlinkedlist_t *dll = dll_init();
    int val1 = 10, val2 = 10;
    dll_append(dll, INT, &val1);
    dll_append(dll, INT, &val2);
    int count = dll_count(dll, INT, &val1);
    printf("Testing dll_count for 10: %s (Expected: 2)\n", count == 2 ? "Passed" : "Failed");

    // Edge case: count in an empty list
    dlinkedlist_t *empty_dll = dll_init();
    int empty_count = dll_count(empty_dll, INT, &val1);
    printf("Testing dll_count on empty list: %s (Expected: 0)\n", empty_count == 0 ? "Passed" : "Failed");
    dll_free(empty_dll);

    dll_free(dll);
}


// Test function for dll_index
void test_dll_index() {
    dlinkedlist_t *dll = dll_init();
    int val1 = 10, val2 = 20;
    dll_append(dll, INT, &val1);
    dll_append(dll, INT, &val2);
    int index = dll_index(dll, INT, &val1);
    printf("Testing dll_index for 10: %s (Expected: 0)\n", index == 0 ? "Passed" : "Failed");

    // Edge case: index in an empty list
    dlinkedlist_t *empty_dll = dll_init();
    int empty_index = dll_index(empty_dll, INT, &val1);
    printf("Testing dll_index on empty list: %s (Expected: -1)\n", empty_index == -1 ? "Passed" : "Failed");
    dll_free(empty_dll);

    // Edge case: index of a non-existent value
    int non_existent_val = 30;
    int non_existent_index = dll_index(dll, INT, &non_existent_val);
    printf("Testing dll_index for non-existent value: %s (Expected: -1)\n", non_existent_index == -1 ? "Passed" : "Failed");

    dll_free(dll);
}



// Test function for dll_pop
void test_dll_pop() {
    dlinkedlist_t *dll = dll_init();
    int val1 = 10, val2 = 20;
    dll_append(dll, INT, &val1);
    dll_append(dll, INT, &val2);
    node_t *popped_node = dll_pop(dll);
    printf("Testing dll_pop: %s (Popped value: %d)\n", popped_node && popped_node->data.value.ival == 20 ? "Passed" : "Failed");
    dll_free_node(popped_node);
    dll_print(dll); // Expected: [10]

    // Edge case: pop from an empty list
    dlinkedlist_t *empty_dll = dll_init();
    node_t *empty_pop = dll_pop(empty_dll);
    printf("Testing dll_pop on empty list: %s (Expected: NULL)\n", empty_pop == NULL ? "Passed" : "Failed");
    dll_free(empty_dll);

    dll_free(dll);
}


// Test function for dll_size
void test_dll_size() {
    dlinkedlist_t *dll = dll_init();
    int val1 = 10, val2 = 20;
    dll_append(dll, INT, &val1);
    dll_append(dll, INT, &val2);
    int size = dll_size(dll);
    printf("Testing dll_size: %s (Expected: 2)\n", size == 2 ? "Passed" : "Failed");

    // Edge case: size of an empty list
    dlinkedlist_t *empty_dll = dll_init();
    int empty_size = dll_size(empty_dll);
    printf("Testing dll_size on empty list: %s (Expected: 0)\n", empty_size == 0 ? "Passed" : "Failed");
    dll_free(empty_dll);

    dll_free(dll);
}





// TESTING STARTS HERE
int main() {
  test_dll_init();
  test_dll_append();
  test_dll_insert();
  test_dll_get();
  test_dll_count();
  test_dll_index();
  test_dll_pop();
  test_dll_size();


  printf("\n*** ALL TEST PASSES ***\n");
  return 0;
}