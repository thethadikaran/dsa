#ifndef __ALGO_SORTING_HEADER__
#define __ALGO_SORTING_HEADER__

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>



/* !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! */
/* ---------- FUNCTION PROTOTYPES ---------- */
/* !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! */

/**
 * @brief SELECTION SORT ALGORITHM
 * 
 *        time complexity  - O(N^2)
 *        space complexity - O(1)   ; in-place sort
 *        Not stable
 *        not data sensisitve
 *        easy to implement
 * 
 * @param int* - integer array
 * @param int - size of the array
 */
void s_selection_sort(int *, int);

/**
 * @brief BUBBLE SORT ALGORITHM
 * 
 *        time complexity  - O(N^2)
 *        space complexity - O(1)   ; in-place sort
 *        stable
 *        data sensisitve
 *        easy to implement
 * 
 * @param int* - integer array
 * @param int - size of the array
 */
void s_bubble_sort(int *, int);

/**
 * @brief INSERTION SORT ALGORITHM
 * 
 *        time complexity  - O(N^2)
 *        space complexity - O(1)   ; in-place sort
 *        stable
 *        data sensisitve
 *        easy to implement
 * 
 * @param int* - integer array
 * @param int - size of the array
 */
void s_insertion_sort(int *, int);

/**
 * @brief SHELL SORT ALGORITHM (DIMINISHING INSERTION SORT)
 * 
 *        time complexity  - 
 *        space complexity -    ; in-place sort
 *        stable
 *        data sensisitve
 *        easy to implement
 * 
 * @param int* - integer array
 * @param int - size of the array
 */
void s_shell_sort(int *, int);


#endif   // __ALGO_SORTING_HEADER__