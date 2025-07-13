#ifndef __DYNAMIC_ARRAY_HEADER__
#define __DYNAMIC_ARRAY_HEADER__

#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>

#define INIT_CAPACITY  10     // initial capacity of the array
#define SCALE_SIZE     2      // every time the arr is full, it's double while resizing

/*
Some Design Notes:
- start the size with 0

- whenever adding elements, add the element and increment size
- whenever removing element, decrement size and pick the element

- range = 0 to capacity - 1
- size always points to empty space

- value pointer by size, is equivalent to no of elements

- size == capacity, array full
*/


/* enum type to define the value type in union */
typedef enum { INT, FLO, STR } etype_t;


/* struct of an element */
typedef struct {
  etype_t etype;

  union {
    int ival;
    float fval;
    char *sval;
  } value;
} element_t;


/* struct to define the dynamic arraay */
typedef struct {
  int size;            // no of elements in the array
  int capacity;        // no of elements the array can hold
  element_t **data;    // array of pointers to element_t's struct
} darray_t;

/* !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! */
/* ---------- FUNCTION PROTOTYPES ---------- */
/* !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! */

/**
 * @brief Allocate memory for the darray_t struct
 * 
 * time complexity -> O(1)
 * space complexity -> O(N);   N - is the initial capacity
 * 
 * @return darray_t* 
 */
darray_t* da_init();

/**
 * @brief Get the element_t at the given index
 * 
 * time complexity  -> O(1)
 * space complexity -> O(1)
 * 
 * @param darray_t - pointer to the darray_t struct
 * @param int - index positon to get the value
 * 
 * @return const element_t* 
 */
const element_t* da_get(darray_t *, int);

/**
 * @brief Add an element at the end of the array
 * 
 * time complexity  -> O(1), O(N); incase resizing happens
 * space complexity -> O(1)
 * 
 * @param darray_t - pointer to the darray_t struct
 * @param etype_t - element type enum (allowed INT, FLO, STR)
 * @param void * - void pointer to value, will be typecasted based on enum type
 * 
 * @return true 
 * @return false 
 */
bool da_append(darray_t *, etype_t, void *);

/**
 * @brief Insert a value at the given index position and move the elements
 *        from that index to right direction
 * 
 * time complexity  -> O(N)
 * space complexity -> O(1)
 * 
 * @param darray_t - pointer to the darray_t struct
 * @param etype_t - element type enum (allowed INT, FLO, STR)
 * @param void * - void pointer to value, will be typecasted based on enum type
*
 * @return true 
 * @return false 
 */
bool da_insert(darray_t *, int, etype_t, void *);

/**
 * @brief Identify the frequency of a given value
 * 
 * time complexity  -> O(N)
 * space complexity -> O(1)
 * 
 * @param darray_t - pointer to the darray_t struct
 * @param etype_t - element type enum (allowed INT, FLO, STR)
 * @param void * - void pointer to value, will be typecasted based on enum type
 *
 * @return int 
 */
int da_count(darray_t *, etype_t, void *);

/**
 * @brief Identify the index of first occurance of the value
 * 
 * time complexity  -> O(N)
 * space complexity -> O(1)
 * 
 * @param darray_t - pointer to the darray_t struct
 * @param etype_t - element type enum (allowed INT, FLO, STR)
 * @param void * - void pointer to value, will be typecasted based on enum type
 * 
 * @return int 
 */
int da_index(darray_t *, etype_t, void *);

/**
 * @brief Remove the last element
 * 
 * time complexity  -> O(1)
 * space complexity -> O(1)
 * 
 * @param darray_t - pointer to the darray_t struct
 * 
 * @return element_t* 
 */
element_t* da_pop(darray_t *);

/**
 * @brief Remove the first occurance of the matching element
 * 
 * time complexity  -> O(N)
 * space complexity -> O(1)
 * 
 * @param darray_t - pointer to the darray_t struct
 * @param etype_t - element type enum (allowed INT, FLO, STR)
 * @param void * - void pointer to value, will be typecasted based on enum type
 */
void da_remove(darray_t *, etype_t, void *);

/**
 * @brief Reverse the elements in the array
 * 
 * time complexity  -> O(N)
 * space complexity -> O(1)
 * 
 */
void da_reverse(darray_t *);

/**
 * @brief No of elements present in the array
 * 
 * time complexity  -> O(1)
 * space complexity -> O(1)
 * 
 * @return int 
 */
int da_size(darray_t *);

void da_print(darray_t *);

/**
 * @brief Free the memory allocated for the dynamic array
 * 
 * time complexity  -> O(N)
 * space complexity -> O(1) 
 *
 * @param darray_t - pointer to the darray_t struct 
 */
void da_free(darray_t *);


/**
 * @brief Resize the array to be double the size and copy the old value to new array
 * 
 * time complexity  -> O(N)
 * space complexity -> O(N)
 * 
 * @param darray_t - pointer to the darray_t struct
 * @return true 
 * @return false 
 */
bool da_resize(darray_t *);

/**
 * @brief Move all the elements to right from the idx position
 * 
 * time complexity -> O(N)
 * space compleity -> O(1) 
 * 
 * @param darray_t - pointer to the darray_t struct
 * @param int - starting from this position, move the elemments to right
 * @return true 
 * @return false 
 */
bool da_move_right(darray_t *, int);

/**
 * @brief Move all the elements to left till the idx position
 * 
 * time complexity -> O(N)
 * space compleity -> O(1) 
 * 
 * @param darray_t - pointer to the darray_t struct
 * @param int - end at this position starting from the last
 * @return true 
 * @return false 
 */
bool da_move_left(darray_t *, int); 

/* ---------- UTIL FUNCTION PROTOTYPES ---------- */

/**
 * @brief Is the dynamic array it at full capacity?
 * 
 * time complexity -> O(1)
 * space compleity -> O(1) 
 * 
 * @param darray_t - pointer to the darray_t struct
 * @return true 
 * @return false 
 */
bool da_is_full(darray_t *);

/**
 * @brief Is the dynamic array is empty?
 * 
 * time complexity -> O(1)
 * space compleity -> O(1) 
 *
 * @param darray_t - pointer to the darray_t struct
 * @return true 
 * @return false 
 */
bool da_is_empty(darray_t *);

/**
 * @brief Allocate memory for element_t struct and update it with value
 * 
 * time complexity  -> O(1)
 * space complexity -> O(1)
 * 
 * @param etype_t - element type enum (allowed INT, FLO, STR)
 * @param void * - void pointer to value, will be typecasted based on enum type
 * @return element_t* 
 */
element_t* da_new_element(etype_t, void *);

/**
 * @brief Release the memory allocated for the element
 * 
 * time complexity  -> O(1)
 * space complexity -> O(1)
 * 
 * @param element_t - pointer to element_t struct
 */
void da_free_element(element_t *);


#endif   // __DYNAMIC_ARRAY_HEADER__