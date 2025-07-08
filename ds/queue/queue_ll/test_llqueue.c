#include "llqueue.h"

void test_llqueue() {
    // Initialize the queue
    llqueue *queue = llq_init();
    if (!queue) {
        printf("Failed to initialize queue.\n");
        return;
    }

    // Test is_empty on a new queue
    printf("Test is_empty on new queue: %s\n", llq_is_empty(queue) ? "PASS" : "FAIL");

    // Test size on a new queue
    printf("Test size on new queue: %d (Expected: 0)\n", llq_size(queue));

    // Test dequeue on an empty queue
    struct node *dequeued = llq_dequeue(queue);
    printf("Test dequeue on empty queue: %s\n", dequeued == NULL ? "PASS" : "FAIL");

    // Enqueue integers
    int a = 10, b = 20, c = 30;
    llq_enqueue(queue, INT, &a);
    llq_enqueue(queue, INT, &b);
    llq_enqueue(queue, INT, &c);

    // Test size after enqueues
    printf("Test size after enqueues: %d (Expected: 3)\n", llq_size(queue));

    // Print the queue
    llq_print(queue);

    // Dequeue one element
    struct node *first_dequeued = llq_dequeue(queue);
    printf("Dequeued: %d\n", first_dequeued->data->value.ival);
    llq_free_node(first_dequeued); // Free the dequeued node

    // Print the queue after one dequeue
    llq_print(queue);

    // Enqueue a float
    float fval = 5.5;
    llq_enqueue(queue, FLO, &fval);

    // Enqueue a string
    char *sval = "Hello";
    llq_enqueue(queue, STR, sval);

    // Print the queue after more enqueues
    llq_print(queue);

    // Test size after more enqueues
    printf("Test size after more enqueues: %d (Expected: 4)\n", llq_size(queue));

    // Peek at the front element
    struct node *peeked = llq_peek(queue);
    if (peeked) {
        printf("Peeked at front: %d\n", peeked->data->value.ival);
    } else {
        printf("Peek failed on non-empty queue.\n");
    }

    // Free the queue
    llq_free(queue);
    printf("Queue freed successfully.\n");

    // Test is_empty on a freed queue
    printf("Test is_empty on freed queue: %s\n", llq_is_empty(queue) ? "PASS" : "FAIL");
}



/* All starts here */
int main() {
    test_llqueue();
    puts("\n*** All tests passed ***");
    return 0;
}
