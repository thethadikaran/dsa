#ifndef __PRIORITY_QUEUE_HEADER__
#define __PRIORITY_QUEUE_HEADER__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

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
  int priority;         // priority of a node's value
  struct node *next;
} node_t;


/* struct representation of a priority queue */
typedef struct {
  int size;          // no of nodes in queue
  node_t *first;     // values are removed from first
  node_t *last;      // valuse are added from last
} priority_queue_t;


/* !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! */
/* ---------- FUNCTION PROTOTYPES ---------- */
/* !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! */

/**
 * @brief Allocate memory for the priority_queue_t struct and initialize the
 *        members with default value
 * 
 *        time complexity  - O(1)
 *        space complexity - O(1)
 * 
 * @return priority_queue_t* 
 */
priority_queue_t* pq_init();

/**
 * @brief Push an value into the queue
 *        This is done by iterating the queue to find the proper position
 *        with correct prirority value and insert it
 * 
 *        time complexity  - O(N)
 *        space complexity - O(1)
 * 
 * @param priority_queue_t - ref to priority_queue_t struct
 * @param etype_t - element type enum (allowed INT, FLO, STR)
 * @param int - priority value
 * @param void * - void pointer to value, will be typecasted based on enum type * 
 * @return true 
 * @return false 
 */
bool pq_enqueue(priority_queue_t *, etype_t, void *, int);

/**
 * @brief Removes the first element and returns it
 * 
 *        time complexity  - O(1)
 *        space complexity - O(1) 
 * 
 * @param priority_queue_t - ref to priority_queue_t struct
 * @return node_t* 
 */
node_t* pq_dequeue(priority_queue_t *);

node_t* pq_peek(priority_queue_t *);

bool pq_is_empty(priority_queue_t *);

int pq_size(priority_queue_t *);

void pq_free(priority_queue_t **);

/* ---------- UTIL FUNCTION PROTOTYPES ---------- */

node_t* pq_new_node(etype_t, void *, int);

#endif   // __PRIORITY_QUEUE_HEADER__