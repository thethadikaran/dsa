#include "darray.h"

#include <assert.h>

// Helper function to print test results
void print_test_result(const char *test_name, bool result)
{
  printf("%s: %s\n", test_name, result ? "PASS" : "FAIL");
}

// Test for da_init
void test_da_init()
{
  darray_t *da = da_init();
  print_test_result("test_da_init", da != NULL && da->size == 0 && da->capacity == INIT_CAPACITY);
  if (da)
  {
    free(da->data);
    free(da);
  }
}

// Test for da_append
void test_da_append()
{
  darray_t *da = da_init();
  int value = 42;
  bool result = da_append(da, INT, &value);
  print_test_result("test_da_append", result && da->size == 1 && da->data[0]->value.ival == 42);
  da_free_element(da->data[0]);
  free(da->data);
  free(da);
}

// Test for da_get
void test_da_get()
{
  darray_t *da = da_init();
  int value = 42;
  da_append(da, INT, &value);
  const element_t *elem = da_get(da, 0);
  print_test_result("test_da_get", elem != NULL && elem->value.ival == 42);
  da_free_element(da->data[0]);
  free(da->data);
  free(da);
}

// Test for da_insert
void test_da_insert()
{
  darray_t *da = da_init();
  int value1 = 42, value2 = 84;
  da_append(da, INT, &value1);
  bool result = da_insert(da, 0, INT, &value2); // Insert at the beginning
  print_test_result("test_da_insert", result && da->size == 2 && da->data[0]->value.ival == 84);
  da_free_element(da->data[0]);
  da_free_element(da->data[1]);
  free(da->data);
  free(da);
}

// Test for da_count
void test_da_count()
{
  darray_t *da = da_init();
  int value1 = 42, value2 = 42;
  da_append(da, INT, &value1);
  da_append(da, INT, &value2);
  int count = da_count(da, INT, &value1);
  print_test_result("test_da_count", count == 2);
  da_free_element(da->data[0]);
  da_free_element(da->data[1]);
  free(da->data);
  free(da);
}

// Test for da_index
void test_da_index()
{
  darray_t *da = da_init();
  int value = 42;
  da_append(da, INT, &value);
  int index = da_index(da, INT, &value);
  print_test_result("test_da_index", index == 0);
  da_free_element(da->data[0]);
  free(da->data);
  free(da);
}

// Test for da_pop
void test_da_pop()
{
  darray_t *da = da_init();
  int value = 42;
  da_append(da, INT, &value);
  element_t *elem = da_pop(da);
  print_test_result("test_da_pop", elem != NULL && elem->value.ival == 42 && da->size == 0);
  da_free_element(elem);
  free(da->data);
  free(da);
}

// Test for da_remove
void test_da_remove()
{
  darray_t *da = da_init();
  int value1 = 42, value2 = 84;
  da_append(da, INT, &value1);
  da_append(da, INT, &value2);
  da_remove(da, INT, &value1);
  print_test_result("test_da_remove", da->size == 1 && da->data[0]->value.ival == 84);
  da_free_element(da->data[0]);
  free(da->data);
  free(da);
}

// Test for da_size
void test_da_size()
{
  darray_t *da = da_init();
  int value = 42;
  da_append(da, INT, &value);
  int size = da_size(da);
  print_test_result("test_da_size", size == 1);
  da_free_element(da->data[0]);
  free(da->data);
  free(da);
}

// Test for da_resize
void test_da_resize()
{
  darray_t *da = da_init();
  for (int i = 0; i < INIT_CAPACITY; i++)
  {
    int value = i;
    da_append(da, INT, &value);
  }

  int val = 10;

  bool result = da_append(da, INT, &val); // This should trigger a resize
  print_test_result("test_da_resize", result && da->capacity == INIT_CAPACITY * SCALE_SIZE);
  for (int i = 0; i < da->size; i++)
  {
    da_free_element(da->data[i]);
  }
  free(da->data);
  free(da);
}

// Test for da_move_right
void test_da_move_right()
{
  darray_t *da = da_init();
  int value1 = 42, value2 = 84;
  da_append(da, INT, &value1);
  da_append(da, INT, &value2);
  bool result = da_move_right(da, 0); // Move right at index 0
  da->data[0] = NULL;

  print_test_result("test_da_move_right", result && da->size == 3 && da->data[1]->value.ival == 42);
  for (int i = 0; i < da->size; i++)
  {
    da_free_element(da->data[i]);
  }
  free(da->data);
  free(da);

}

// Test for da_move_left
void test_da_move_left()
{
  darray_t *da = da_init();
  int value1 = 42, value2 = 84;
  da_append(da, INT, &value1);
  da_append(da, INT, &value2);
  da_move_right(da, 0);          // Move right to create space
  da->data[0] = NULL;

  da_move_left(da, 0);           // Remove the first element
  
  print_test_result("test_da_move_left", da->size == 2 && da->data[0]->value.ival == 42);
  for (int i = 0; i < da->size; i++)
  {
    da_free_element(da->data[i]);
  }
  free(da->data);
  free(da);
}

// Test for da_is_full
void test_da_is_full()
{
  darray_t *da = da_init();
  for (int i = 0; i < INIT_CAPACITY; i++)
  {
    int value = i;
    da_append(da, INT, &value);
  }
  bool result = da_is_full(da);
  print_test_result("test_da_is_full", result);
  for (int i = 0; i < da->size; i++)
  {
    da_free_element(da->data[i]);
  }
  free(da->data);
  free(da);
}

// Test for da_is_empty
void test_da_is_empty()
{
  darray_t *da = da_init();
  bool result = da_is_empty(da);
  print_test_result("test_da_is_empty", result);
  int value = 42;
  da_append(da, INT, &value);
  result = da_is_empty(da);
  print_test_result("test_da_is_empty_after_append", !result);
  da_free_element(da->data[0]);
  free(da->data);
  free(da);
}

// test the array reverse
void test_da_reverse() {
  darray_t *da = da_init();

  int a = 11, b = 12, c = 13, d = 14, e = 15, f = 22;
  da_append(da, INT, &a);
  da_append(da, INT, &b);
  da_append(da, INT, &c);
  da_append(da, INT, &d);
  da_append(da, INT, &e);
  da_append(da, INT, &f);

  puts("before reverse");
  da_print(da);

  puts("after reverse");
  da_reverse(da);
  da_print(da);
}

// Main function to run all tests
int main()
{
  test_da_init();
  test_da_append();
  test_da_get();
  test_da_insert();
  test_da_count();
  test_da_index();
  test_da_pop();
  test_da_remove();
  test_da_size();
  test_da_resize();
  test_da_move_right();
  test_da_move_left();
  test_da_is_full();
  test_da_is_empty();
  test_da_reverse();

  printf("*** All tests completed ***\n");
  return 0;
}
