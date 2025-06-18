#include "hlinked_list.h"
#include <assert.h>


void test_hll_init() {
    hlinkedlist *list = hll_init();
    assert(list != NULL);
    assert(list->len == 0);
    assert(list->first == NULL);
    assert(list->last == NULL);
    hll_free(list);
}

void test_hll_append() {
    hlinkedlist *list = hll_init();
    int value = 42;
    assert(hll_append(list, INT, &value) == true);
    assert(list->len == 1);
    assert(list->first->ele.value.ival == 42);
    assert(list->last->ele.value.ival == 42);
    hll_free(list);
}

void test_hll_insert() {
    hlinkedlist *list = hll_init();
    int value1 = 10, value2 = 20, value3 = 30;

    hll_append(list, INT, &value1);
    hll_append(list, INT, &value2);
    assert(hll_insert(list, 1, INT, &value3) == true); // Insert in the middle
    assert(list->len == 3);
    assert(list->first->next->ele.value.ival == 30); // Check if value3 is in the middle

    hll_free(list);
}

void test_hll_remove() {
  hlinkedlist *list = hll_init();
  int value1 = 10, value2 = 20, value3 = 30;

  hll_append(list, INT, &value1);
  hll_append(list, INT, &value2);
  hll_append(list, INT, &value3);

  assert(hll_remove(list, INT, &value2) == true); // Remove middle element
  assert(list->len == 2);
  assert(list->first->next->ele.value.ival == 30); // Check if value2 is removed

  assert(hll_remove(list, INT, &value1) == true); // Remove first element
  assert(list->len == 1);
  assert(list->first->ele.value.ival == 30); // Check if value1 is removed

  assert(hll_remove(list, INT, &value3) == true); // Remove last element
  assert(list->len == 0); // List should be empty now

  hll_free(list);
}

void test_hll_pop() {
  hlinkedlist *list = hll_init();
  int value1 = 10, value2 = 20;

  hll_append(list, INT, &value1);
  hll_append(list, INT, &value2);

  struct node *popped_node = hll_pop(list);
  assert(popped_node != NULL);
  assert(popped_node->ele.value.ival == 20); // Check if the first element is popped
  hll_free_node(popped_node); // Free the popped node

  popped_node = hll_pop(list);
  assert(popped_node != NULL);
  assert(popped_node->ele.value.ival == 10); // Check if the last element is popped
  hll_free_node(popped_node); // Free the popped node

  assert(hll_pop(list) == NULL); // List should be empty now
  hll_free(list);
}

void test_hll_print() {
  hlinkedlist *list = hll_init();
  int value1 = 10, value2 = 20, value3 = 30;

  hll_append(list, INT, &value1);
  hll_append(list, INT, &value2);
  hll_append(list, INT, &value3);

  hll_print(list); // This will print the list; visually check the output

  hll_free(list);
}

void test_hll_edge_cases() {
  hlinkedlist *list = hll_init();
  assert(hll_remove(list, INT, NULL) == false); // Remove from empty list
  assert(hll_pop(list) == NULL); // Pop from empty list
  assert(hll_insert(list, 0, INT, NULL) == false); // Insert into empty list with NULL value
  assert(hll_append(list, INT, NULL) == false); // Append NULL value
  hll_free(list);
}



// ALL STARTS HERE
int main() {
  test_hll_init();
  test_hll_append();
  test_hll_insert();
  test_hll_remove();
  test_hll_pop();
  test_hll_print();
  test_hll_edge_cases();

  printf("\n\n *** All tests passed! *** \n");
  return 0;
}