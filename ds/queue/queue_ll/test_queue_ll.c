#include "queue_ll.h"
#include <assert.h>


void test_qll_init() {
  queue_ll_t *queue = qll_init();
  assert(queue != NULL);
  assert(queue->size == 0);
  assert(queue->first == NULL);
  assert(queue->last == NULL);
  qll_free(&queue);
}

void test_qll_enqueue() {
  queue_ll_t *queue = qll_init();
  int value = 10;
  assert(qll_enqueue(queue, INT, &value) == true);
  assert(queue->size == 1);
  assert(queue->first->data.value.ival == 10);
  assert(queue->last->data.value.ival == 10);

  char *str_value = "Hello";
  assert(qll_enqueue(queue, STR, str_value) == true);
  assert(queue->size == 2);
  assert(queue->last->data.value.sval != NULL);
  assert(strcmp(queue->last->data.value.sval, "Hello") == 0);

  qll_free(&queue);
}

void test_qll_dequeue() {
  queue_ll_t *queue = qll_init();
  int value1 = 10, value2 = 20;
  qll_enqueue(queue, INT, &value1);
  qll_enqueue(queue, INT, &value2);

  node_t *dequeued_node = qll_dequeue(queue);
  assert(dequeued_node != NULL);
  assert(dequeued_node->data.value.ival == 10);
  free(dequeued_node);

  assert(queue->size == 1);
  assert(queue->first->data.value.ival == 20);

  dequeued_node = qll_dequeue(queue);
  assert(dequeued_node != NULL);
  assert(dequeued_node->data.value.ival == 20);
  free(dequeued_node);

  assert(qll_is_empty(queue) == true);
  assert(qll_dequeue(queue) == NULL); // Dequeue from empty queue should return NULL

  qll_free(&queue);
}

void test_qll_peek() {
  queue_ll_t *queue = qll_init();
  assert(qll_peek(queue) == NULL); // Peek on empty queue should return NULL

  int value = 10;
  qll_enqueue(queue, INT, &value);
  node_t *peeked_node = qll_peek(queue);
  assert(peeked_node != NULL);
  assert(peeked_node->data.value.ival == 10);

  qll_free(&queue);
}

void test_qll_is_empty() {
  queue_ll_t *queue = qll_init();
  assert(qll_is_empty(queue) == true);

  int value = 10;
  qll_enqueue(queue, INT, &value);
  assert(qll_is_empty(queue) == false);

  qll_dequeue(queue);
  assert(qll_is_empty(queue) == true);

  qll_free(&queue);
}

void test_qll_size() {
  queue_ll_t *queue = qll_init();
  assert(qll_size(queue) == 0);

  int value = 10;
  qll_enqueue(queue, INT, &value);
  assert(qll_size(queue) == 1);

  qll_enqueue(queue, INT, &value);
  assert(qll_size(queue) == 2);

  qll_dequeue(queue);
  assert(qll_size(queue) == 1);

  qll_free(&queue);
}

void test_qll_free() {
  queue_ll_t *queue = qll_init();
  int value = 10;
  qll_enqueue(queue, INT, &value);
  qll_free(&queue);
  assert(queue == NULL); // Ensure the queue pointer is set to NULL after freeing
}

void test_qll_print() {
  queue_ll_t *queue = qll_init();
  qll_print(queue); // Should print []

  int value1 = 10, value2 = 20;
  qll_enqueue(queue, INT, &value1);
  qll_enqueue(queue, INT, &value2);
  qll_print(queue); // Should print [10, 20]

  qll_free(&queue);
}

void run_tests() {
  test_qll_init();
  test_qll_enqueue();
  test_qll_dequeue();
  test_qll_peek();
  test_qll_is_empty();
  test_qll_size();
  test_qll_free();
  test_qll_print();

  printf("All tests passed!\n");
}






int main() {
  run_tests();
  return 0;
}


