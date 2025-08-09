#ifndef __QUEUE_CIRCULAR_HEADER__
#define __QUEUE_CIRCULAR_HEADER__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define SIZE 10

// Queue implementation using Array (circular nature)
// intially set first and last to 0
// 
// for enqueue -> add value and update last
// for dequeue -> remove value and update first
// 
// if first == last, then the queue is empty
//
// to differentiate full & empty queue, we sacrifice one element
// if first + 1 == last, then the queue is full
// 
// so the total elements queue can hold = SIZE - 1


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


/* struct representation of a circular queue */
typedef struct {
  int first;
  int last;
  element_t *data[SIZE];
} cqueue_t;



/* !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! */
/* ---------- FUNCTION PROTOTYPES ---------- */
/* !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! */

/**
 * @brief Allocate memory for the cqueue_t struct and initialize the
 *        members with default value
 * 
 *        time complexity  - O(1)
 *        space complexity - O(1)
 * 
 * @return cqueue_t* 
 */
cqueue_t* cq_init();

/**
 * @brief Push an value into the last of the queue
 * 
 *        time complexity  - O(1)
 *        space complexity - O(1)
 * 
 * @param cqueue_t - ref to cqueue_t struct
 * @param etype_t - element type enum (allowed INT, FLO, STR)
 * @param void * - void pointer to value, will be typecasted based on enum type * 
 * @return true 
 * @return false 
 */
bool cq_enqueue(cqueue_t *, etype_t, void *);

/**
 * @brief Removes the first element and returns it
 * 
 *        time complexity  - O(1)
 *        space complexity - O(1) 
 * 
 * @param cqueue_t - ref to cqueue_t struct
 * @return element_t* 
 */
element_t* cq_dequeue(cqueue_t *);

/**
 * @brief Take a peek at the first element in queue
 * 
 *        time complexity  - O(1)
 *        space complexity - O(1) 
 * 
 * @param cqueue_t - ref to cqueue_t struct
 * @return node_t* 
 */
element_t* cq_peek(cqueue_t *);

/**
 * @brief Verify if the queue is empty
 * 
 *        time complexity  - O(1)
 *        space complexity - O(1) 
 * 
 * @param cqueue_t - ref to cqueue_t struct
 * @return true 
 * @return false 
 */
bool cq_is_empty(cqueue_t *);

bool cq_is_full(cqueue_t *);

/**
 * @brief Release the memory of entire queue
 * 
 *        time complexity  - O(N); N - no of elements in queue
 *        space complexity - O(1) 
 * 
 * @param cqueue_t - ref to ref to cqueue_t struct
 */
void cq_free(cqueue_t **);

/* ---------- UTIL FUNCTION PROTOTYPES ---------- */

/**
 * @brief Allocate memeory for element_t and update it with the value
 * 
 *        time complexity  - O(1)
 *                           O(N); if etype is str, N - length of string
 *        space complexity - O(1)
 *                           O(N); if etype is str, N - length of string
 * 
 * @param etype_t - element type enum (allowed INT, FLO, STR)
 * @param void * - void pointer to value, will be typecasted based on enum type * 
 * 
 * @return element_t* 
 */
element_t* cq_new_element(etype_t, void *);

#endif   // __QUEUE_CIRCULAR_HEADER__