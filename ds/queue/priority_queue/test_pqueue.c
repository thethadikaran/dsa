#include <assert.h>
#include "pqueue.h"

// Function to test the priority queue
void test_priority_queue() {
    // Initialize the priority queue
    priority_queue_t *pq = pq_init();
    assert(pq != NULL);
    printf("Test 1: Priority Queue Initialized\n");

    // Test is_empty on a new queue
    assert(pq_is_empty(pq) == true);
    printf("Test 2: is_empty on new queue passed\n");

    // Test enqueueing elements
    int val1 = 10, val2 = 20, val3 = 15;
    assert(pq_enqueue(pq, INT, &val1, 1) == true);
    assert(pq_enqueue(pq, INT, &val2, 3) == true);
    assert(pq_enqueue(pq, INT, &val3, 2) == true);
    printf("Test 3: Enqueued elements successfully\n");

    // Test size after enqueue
    assert(pq_size(pq) == 3);
    printf("Test 4: Size after enqueue is correct\n");

    // Test peek
    node_t* peeked_value;
    peeked_value = pq_peek(pq);
    assert(peeked_value != NULL);
    assert(peeked_value->data.value.ival == 10);
    printf("Test 5: Peek returned correct value\n");

    // Test dequeueing elements
    node_t *dequeued_node = pq_dequeue(pq);
    assert(dequeued_node != NULL);
    assert(dequeued_node->data.value.ival == 10);
    free(dequeued_node);
    printf("Test 6: Dequeued first element successfully\n");

    // Test size after dequeue
    assert(pq_size(pq) == 2);
    printf("Test 7: Size after dequeue is correct\n");

    // Test dequeueing remaining elements
    dequeued_node = pq_dequeue(pq);
    assert(dequeued_node != NULL);
    assert(dequeued_node->data.value.ival == 15);
    free(dequeued_node);

    dequeued_node = pq_dequeue(pq);
    assert(dequeued_node != NULL);
    assert(dequeued_node->data.value.ival == 20);
    free(dequeued_node);
    printf("Test 8: Dequeued all elements successfully\n");

    // Test is_empty after all dequeues
    assert(pq_is_empty(pq) == true);
    printf("Test 9: is_empty after all dequeues passed\n");

    // Test dequeue on empty queue
    assert(pq_dequeue(pq) == NULL);
    printf("Test 10: Dequeue on empty queue returned NULL\n");

    // Test free function
    pq_free(&pq);
    assert(pq == NULL);
    printf("Test 11: Freeing the queue passed\n");

    // Test enqueue with NULL queue
    assert(pq_enqueue(NULL, INT, &val1, 1) == false);
    printf("Test 12: Enqueue on NULL queue returned false\n");

    // Test peek on NULL queue
    assert(pq_peek(NULL) == NULL);
    printf("Test 13: Peek on NULL queue returned false\n");

    // Test free on NULL queue
    pq_free(NULL);
    printf("Test 14: Free on NULL queue passed\n");

    printf("All tests passed!\n");
}

int main() {
    test_priority_queue();
    return 0;
}

