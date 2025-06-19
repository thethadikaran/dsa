#ifndef __LINKEDLIST_QUEUE_HEADER__
#define __LINKEDLIST_QUEUE_HEADER__

/**
 * @file llqueue.h
 * @author thethadikaran
 * @brief Linked List impkementation of Queue
 *   We maintain two pointers front and rear, where front will point to the
 *   first node of the linked list and the rear points to the last node.
 * @version 0.1
 * @date 2025-06-19
 * 
 * @copyright Copyright (c) 2025
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>


enum element_type { INT, FLO, STR };

/* struct representation of a info part in a Node */
struct element {
  enum element_type etype;

  union {
    int ival;
    float fval;
    char *sval;
  } value;
};


/* struct representation of single Node */
struct node {
  struct element *data;
  struct node *next;
};


/* struct representation of a queue */
struct llqueue {
  int size;               // no of nodes in queue
  struct node *front;     // values are removed from front
  struct node *rear;      // valuse are added from rear
};

typedef struct llqueue llqueue;


/* ***** FUNCTION PROTOTYPES ***** */

/**
 * @brief Allocated memory for llqueue struct and set the initial value for 
 *        members. Initially front and rear are marked as NULL.
 * 
 * @return llqueue* -> pointer to llqueue struct
 */
llqueue* llq_init();

/**
 * @brief Pushes value to the rear side of the queue.
 *        rear - end of the linked list.
 * 
 * @param etype -> Type of the value (INT, FLO, STR)
 * @return true -> Insertion is successful or not
 * @return false 
 */
bool llq_enqueue(llqueue*, enum element_type etype, void *);

/**
 * @brief Pops the element from the front and returns it
 * 
 * @return struct node* 
 */
struct node* llq_dequeue(llqueue*);

/**
 * @brief Take a peek at the first node.
 * 
 * @return struct node* 
 */
struct node* llq_peek(llqueue*);

/**
 * @brief Is queue is empty or not?
 *        ways to verify:
 *           front or rear is NULL
 *           size == 0
 * @return true 
 * @return false 
 */
bool llq_is_empty(llqueue*);

/**
 * @brief Return no of nodes present in the Queue
 *        Value recorded in size member of llqueue struct
 * 
 * @return int 
 */
int llq_size(llqueue*);

void llq_print(llqueue*);

/**
 * @brief Free the entire queue
 * 
 */
void llq_free(llqueue*);


/* UTIL */
/**
 * @brief Allocate memory for node and element.
 *        Update the element with the value and returns the node
 * 
 * @return struct node*
 */
struct node* llq_create_node(enum element_type, void*);

/**
 * @brief Free the memory allocated for a Node
 *        If the Node's element type is string, then it hsa to 
 *        be release first.
 */
void llq_free_node(struct node*);

#endif   // __LINKEDLIST_QUEUE_HEADER__