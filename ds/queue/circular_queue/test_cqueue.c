#include <assert.h>
#include "cqueue.h"

void test_circular_queue() {
  // Initialize the circular queue
  cqueue_t *cq = cq_init();
  assert(cq != NULL);
  printf("Test 1: Queue initialized successfully.\n");

  // Test is_empty on a new queue
  assert(cq_is_empty(cq) == true);
  printf("Test 2: Queue is empty.\n");

  // Test enqueueing elements
  int val1 = 10;
  assert(cq_enqueue(cq, INT, &val1) == true);
  assert(cq_is_empty(cq) == false);
  printf("Test 3: Enqueued integer 10.\n");

  float val2 = 20.5;
  assert(cq_enqueue(cq, FLO, &val2) == true);
  printf("Test 4: Enqueued float 20.5.\n");

  char *val3 = "Hello";
  assert(cq_enqueue(cq, STR, val3) == true);
  printf("Test 5: Enqueued string 'Hello'.\n");

  // Test peek
  element_t *peeked = cq_peek(cq);
  assert(peeked != NULL && peeked->etype == INT && peeked->value.ival == 10);
  printf("Test 6: Peeked value is 10.\n");

  // Test dequeueing elements
  element_t *dequeued1 = cq_dequeue(cq);
  assert(dequeued1 != NULL && dequeued1->etype == INT && dequeued1->value.ival == 10);
  free(dequeued1);
  printf("Test 7: Dequeued integer 10.\n");

  element_t *dequeued2 = cq_dequeue(cq);
  assert(dequeued2 != NULL && dequeued2->etype == FLO && dequeued2->value.fval == 20.5);
  free(dequeued2);
  printf("Test 8: Dequeued float 20.5.\n");

  // Test dequeueing the string
  element_t *dequeued3 = cq_dequeue(cq);
  assert(dequeued3 != NULL && dequeued3->etype == STR && strcmp(dequeued3->value.sval, "Hello") == 0);
  free(dequeued3);
  printf("Test 9: Dequeued string 'Hello'.\n");

  // Test is_empty after dequeuing all elements
  assert(cq_is_empty(cq) == true);
  printf("Test 10: Queue is empty after dequeuing all elements.\n");

  // Test enqueueing until full
  for (int i = 0; i < SIZE - 1; i++) {
      assert(cq_enqueue(cq, INT, &i) == true);
      printf("Test 11: Enqueued integer %d.\n", i);
  }

  // Test is_full
  assert(cq_is_full(cq) == true);
  printf("Test 12: Queue is full.\n");

  // Test enqueueing when full
  assert(cq_enqueue(cq, INT, &val1) == false);
  printf("Test 13: Failed to enqueue when queue is full.\n");

  // Test dequeueing all elements
  for (int i = 0; i < SIZE - 1; i++) {
      element_t *dequeued = cq_dequeue(cq);
      assert(dequeued != NULL && dequeued->etype == INT && dequeued->value.ival == i);
      free(dequeued);
      printf("Test 14: Dequeued integer %d.\n", i);
  }

  // Test is_empty after dequeuing all elements
  assert(cq_is_empty(cq) == true);
  printf("Test 15: Queue is empty after dequeuing all elements.\n");

  // Free the queue
  cq_free(&cq);
  assert(cq == NULL);
  printf("Test 16: Queue freed successfully.\n");

  printf("All tests passed!\n");
}



/* ALL STARTS HERE */
int main() {
  test_circular_queue();
  puts("ALL TESTS PASSED");
  return 0;
}
