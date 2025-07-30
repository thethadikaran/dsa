#ifndef __QUEUE_LINKED_LIST_HEADER__
#define __QUEUE_LINKED_LIST_HEADER__


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>


// Queue implementation using linked list
// head of linked list - first of the queue (front)
// tail of linked list - last of the queue (rear)
// values are added at the last(rear) and removed from the first(front)


/* specify the type of value in the element */
typedef enum { INT, FLO, STR } etype_t;


/* struct representation of a element */
typedef struct {
  etype_t etype;

  union {
    int ival;
    float fval;
    char *sval;
  } value;
} element_t;


/* struct representation of a node */
typedef struct node {
  element_t data;
  struct node *next;
} node_t;


/* struct representation of a queue */
typedef struct {
  int size;          // no of nodes in queue
  node_t *first;     // values are removed from first
  node_t *last;      // valuse are added from last
} queue_ll_t;



/* !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! */
/* ---------- FUNCTION PROTOTYPES ---------- */
/* !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! */

/**
 * @brief Allocate memory for the queue_ll_t struct and initialize the
 *        members with default value
 * 
 *        time complexity  - O(1)
 *        space complexity - O(1)
 * 
 * @return queue_ll_t* 
 */
queue_ll_t* qll_init();

/**
 * @brief Push an value into the last of the queue
 * 
 *        time complexity  - O(1)
 *        space complexity - O(1)
 * 
 * @param queue_ll_t - ref to queue_ll_t struct
 * @param etype_t - element type enum (allowed INT, FLO, STR)
 * @param void * - void pointer to value, will be typecasted based on enum type * 
 * @return true 
 * @return false 
 */
bool qll_enqueue(queue_ll_t *, etype_t, void *);

/**
 * @brief Removes the first element and returns it
 * 
 *        time complexity  - O(1)
 *        space complexity - O(1) 
 * 
 * @param queue_ll_t - ref to queue_ll_t struct
 * @return node_t* 
 */
node_t* qll_dequeue(queue_ll_t *);

/**
 * @brief Take a peek at the first node in queue
 * 
 *        time complexity  - O(1)
 *        space complexity - O(1) 
 * 
 * @param queue_ll_t - ref to queue_ll_t struct
 * @return node_t* 
 */
node_t* qll_peek(queue_ll_t *);

/**
 * @brief Verify if the queue is empty
 * 
 *        time complexity  - O(1)
 *        space complexity - O(1) 
 * 
 * @param queue_ll_t - ref to queue_ll_t struct
 * @return true 
 * @return false 
 */
bool qll_is_empty(queue_ll_t *);

/**
 * @brief Get the no of nodes in the queue
 * 
 *        time complexity  - O(1)
 *        space complexity - O(1) 
 * 
 * @param queue_ll_t - ref to queue_ll_t struct
 * @return int 
 */
int qll_size(queue_ll_t *);

/**
 * @brief Release the memory of entire queue
 * 
 *        time complexity  - O(N); N - no of elements in queue
 *        space complexity - O(1) 
 * 
 * @param queue_ll_t - ref of ref to queue_ll_t struct
 */
void qll_free(queue_ll_t **);


/* ---------- UTIL FUNCTION PROTOTYPES ---------- */

/**
 * @brief Print the elements in the queue
 *        we iterate the queue using linked list iteration.
 * 
 *        time complexity  - O(N); N - no of elements in queue
 *        space complexity - O(1)
 * 
 * @param queue_ll_t - ref to queue_ll_t struct
 */
void qll_print(queue_ll_t *);

/**
 * @brief Allocate memeory for node_t and update it with the value
 * 
 *        time complexity  - O(1)
 *                           O(N); if etype is str, N - length of string
 *        space complexity - O(1)
 *                           O(N); if etype is str, N - length of string
 * 
 * @param etype_t - element type enum (allowed INT, FLO, STR)
 * @param void * - void pointer to value, will be typecasted based on enum type * 
 * 
 * @return node_t* 
 */
node_t* qll_new_node(etype_t, void *);


#endif   // __QUEUE_LINKED_LIST_HEADER__