#ifndef __STACK_LINKED_LIST_HEADER__
#define __STACK_LINKED_LIST_HEADER__

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>


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


/* struct representation of a stack */
typedef struct {
  int size;       // no of nodes in the stack
  node_t *top;    // head of the linked list, act as the top
} stack_ll_t;


/* !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! */
/* ---------- FUNCTION PROTOTYPES ---------- */
/* !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! */

/**
 * @brief Allocate memory for the stack_ll_t struct and initialize the
 *        members with default value
 * 
 *        time complexity  - O(1)
 *        space complexity - O(1)
 * 
 * @return stack_ll_t* 
 */
stack_ll_t* sll_init();

/**
 * @brief Push an value into the top of the stack.
 *        here head node is considered at the top of the stack
 *        so on every push() new nodes are inserted at the front of linked list
 * 
 *        time complexity  - O(1)
 *        space complexity - O(1)
 * 
 * @param stack_ll_t - ref to stack_ll_t struct
 * @param etype_t - element type enum (allowed INT, FLO, STR)
 * @param void * - void pointer to value, will be typecasted based on enum type * 
 * @return true 
 * @return false 
 */
bool sll_push(stack_ll_t *, etype_t, void *);

/**
 * @brief Pops the top element and returns it
 * 
 *        time complexity  - O(1)
 *        space complexity - O(1) 
 * 
 * @param stack_ll_t - ref to stack_ll_t struct
 * @return node_t* 
 */
node_t* sll_pop(stack_ll_t *);

/**
 * @brief Take a peek at the top element of the stack
 * 
 *        time complexity  - O(1)
 *        space complexity - O(1) 
 * 
 * @param stack_ll_t - ref to stack_ll_t struct
 * @return node_t* 
 */
node_t* sll_peek(stack_ll_t *);

/**
 * @brief Verify if the stack is empty
 * 
 *        time complexity  - O(1)
 *        space complexity - O(1) 
 * 
 * @param stack_ll_t - ref to stack_ll_t struct
 * @return true 
 * @return false 
 */
bool sll_is_empty(stack_ll_t *);

/**
 * @brief Release the memory of entire stack
 * 
 *        time complexity  - O(N); N - no of elements in stack
 *        space complexity - O(1) 
 * 
 * @param stack_ll_t - ref of ref to stack_ll_t struct
 */
void sll_free(stack_ll_t **);


/* ---------- UTIL FUNCTION PROTOTYPES ---------- */

/**
 * @brief Print the elements in the stack
 *        we iterate the stack using linked list iteration.
 * 
 *        time complexity  - O(N); N - no of elements in stack
 *        space complexity - O(1)
 * 
 * @param stack_ll_t - ref to stack_ll_t struct
 */
void sll_print(stack_ll_t *);

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
node_t* sll_new_node(etype_t, void *);

#endif   // __STACK_LINKED_LIST_HEADER__