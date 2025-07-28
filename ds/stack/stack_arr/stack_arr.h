#ifndef __STACK_ARRAY_HEADER__
#define __STACK_ARRAY_HEADER__

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#define SIZE  1000

/**
 * SOME NOTES:
 * 
 * - initially top points to -1
 * - to push element, increment top and add element
 * - to pop element, copy the element and decrement top
 * 
 * - no of element in stack = top + 1
 * 
 * - top == -1, stack empty
 * - top + 1 == size, stack full
 */


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


/* struct representation of a stack */
typedef struct {
  int top;                    // points to index of stack top
  element_t *data[SIZE];     // array of pointers to struct element
} stack_arr_t;


/* !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! */
/* ---------- FUNCTION PROTOTYPES ---------- */
/* !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! */

/**
 * @brief Allocate memory for stack_arr_t struct and returs pointer to it
 *        Initially we set the top to -1 to represent empty stack
 * 
 *        time complexity  - O(1)
 *        space complecity - O(1)
 * 
 * @return stack_arr_t* 
 */
stack_arr_t* sa_init();

/**
 * @brief Push an value into the top of the stack
 * 
 *        time complexity  - O(1)
 *        space complexity - O(1)
 * 
 * @param stack_arr_t - ref to stack_arr_t struct
 * @param etype_t - element type enum (allowed INT, FLO, STR)
 * @param void * - void pointer to value, will be typecasted based on enum type * 
 * @return true 
 * @return false 
 */
bool sa_push(stack_arr_t *, etype_t, void *);

/**
 * @brief Pops the top element and returns it
 * 
 *        time complexity  - O(1)
 *        space complexity - O(1) 
 * 
 * @param stack_arr_t - ref to stack_arr_t struct
 * @return element_t* 
 */
element_t* sa_pop(stack_arr_t *);

/**
 * @brief Take a peek at the top element of the stack
 * 
 *        time complexity  - O(1)
 *        space complexity - O(1) 
 * 
 * @param stack_arr_t - ref to stack_arr_t struct
 * @return element_t* 
 */
element_t* sa_peek(stack_arr_t *);

/**
 * @brief Verify if the stack is empty
 * 
 *        time complexity  - O(1)
 *        space complexity - O(1) 
 * 
 * @param stack_arr_t - ref to stack_arr_t struct
 * @return true 
 * @return false 
 */
bool sa_is_empty(stack_arr_t *);

/**
 * @brief Verify if the stack is full
 * 
 *        time complexity  - O(1)
 *        space complexity - O(1) 
 * 
 * @param stack_arr_t - ref to stack_arr_t struct
 * @return true 
 * @return false 
 */
bool sa_is_full(stack_arr_t *);

/**
 * @brief Release the memory of entire stack
 * 
 *        time complexity  - O(N); N - no of elements in stack
 *        space complexity - O(1) 
 * 
 * @param stack_arr_t - ref to stack_arr_t struct
 */
void sa_free(stack_arr_t **);


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
element_t* sa_new_element(etype_t, void *);

/**
 * @brief Print the elements in the stack
 *        we iterate the stack via index (using the underlying array)
 * 
 *        time complexity  - O(N); N - no of elements in stack
 *        space complexity - O(1)
 * 
 * @param stack_arr_t - ref to stack_arr_t struct
 */
void sa_print(stack_arr_t *);

#endif   // __STACK_ARRAY_HEADER__