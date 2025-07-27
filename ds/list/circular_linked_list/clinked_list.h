#ifndef __CIRCULAR_LINKED_LIST__
#define __CIRCULAR_LINKED_LIST__

/**
 * @file clinked_list.h
 * @author thethadikaran
 * @brief Circular Linked List
 * Here the head node points to the last node of the linked list
 * We keep track of the last node to do all operations. Tracking last node helps
 * to insert elements either in front and in last with O(1) complexity.
 * @version 0.1
 * @date 2025-06-16
 * 
 * @copyright Copyright (c) 2025
 * 
 */
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>


/* struct represent the permitted element types */
typedef enum { INT, FLO, STR } etype_t;


/* struct used as info part in the node */
typedef struct {
  int etype;

  union {
    int ival;
    float fval;
    char *sval;
  } value;
} element_t;


/* struct defines a single node */
typedef struct node {
  element_t data;       // info part - stores value
  struct node *next;    // pointer part - reference to next node
} node_t;



/* struct to define a cirtular linked list */
typedef struct {
  node_t *head;         // refer to the tail position of the lined list
} clinkedlist_t;



/* !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! */
/* ---------- FUNCTION PROTOTYPES ---------- */
/* !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! */

/**
 * @brief Allocate memory for circular linkedlist and returns it.
 *        Head of circular linkedlist is marked as NULL.
 * 
 *        time complexity  - O(1)
 *        space complexity - O(1)
 * 
 * @return linkedlist_t* 
 */
clinkedlist_t* cll_init();

/**
 * @brief Loop though the linked list and retun the node at the index posiiton
 * 
 *        time complexity  - O(N), N is the index position
 *        space complexity - O(1)
 * 
 * @param clinkedlist_t* - pointer to clinkedlist_t struct
 * @param int - index positon to retrieve the node
 * @return node_t* - return node at the index positon
 *                   NULL is returned for invalid positon
 */
node_t* cll_get(clinkedlist_t *, int);

/**
 * @brief Append the value at the end of the linked list.
 *        If the linked list is empty, then it will be the first value.
 * 
 *        time complexity  - O(1), as head points to last node
 *        space complexity - O(1)
 * 
 * @param clinkedlist_t* - reference to clinkedlist_t struct
 * @param etype_t - specify type of data. allowed - INT, FLO, STR
 * @param void* - data as void pointer, will type casted based on etype
 * @return true - append is success
 * @return false - append fails
 */
bool cll_append(clinkedlist_t *, etype_t, void *);

/**
 * @brief Insert the value at the given position.
 * 
 *        time complexity  - O(N) ; N- node positon to be inserted
 *        space complexity - O(1)
 * 
 * @param clinkedlist_t* - reference to clinkedlist_t struct
 * @param int - new value insert positon
 * @param etype_t - specify type of data. allowed - INT, FLO, STR
 * @param void* - data as void pointer, will type casted based on etype
 * @return true - if insertion of value is success
 * @return false - insertion failed
 */
bool cll_insert(clinkedlist_t *, int, etype_t, void *);

/**
 * @brief Count no of times the value appears.
 * 
 *        time complexity  - O(N) ; in case of int or float
 *                           O(N * M) ; in case of string, M - length of string
 *        space complexity - O(1)
 * 
 * @param clinkedlist_t* - reference to clinkedlist_t struct
 * @param etype_t - specify type of data. allowed - INT, FLO, STR
 * @param void* - data as void pointer, will type casted based on etype
 * @return int - frequency of the value
 */
int cll_count(clinkedlist_t *, etype_t, void *);

/**
 * @brief Identify the first occurance of the value and return the index
 * 
 *        time complexity  - O(N) ; in case of int or float
 *                           O(N * M) ; in case of string, M - length of string
 *        space complexity - O(1)
 * 
 * @param clinkedlist_t* - reference to clinkedlist_t struct
 * @param etype_t - specify type of data. allowed - INT, FLO, STR
 * @param void* - data as void pointer, will type casted based on etype
 * @return int - returns the first occurance index
 *               returns -1 if not found
 */
int cll_index(clinkedlist_t *, etype_t, void *);

/**
 * @brief Removes the last node form the linked list and returns it
 * 
 *        time complexity  - O(N)
 *        space complexity - O(1)
 * 
 * @param linkedlist_t* - reference to linkedlist_t struct 
 * @return node_t* - returns the last node, NULL if not present
 *                   user has to take care of freeing the memory of popped node
 */
node_t* cll_pop(clinkedlist_t *);

/**
 * @brief Remove the first occurance of the element.
 * 
 *        time complexity  - O(N)
 *        space complexity - O(1)
 * 
 * @param clinkedlist_t* - reference to clinkedlist_t struct
 * @param etype_t - specify type of data. allowed - INT, FLO, STR
 * @param void* - data as void pointer, will type casted based on etype
 * @return true - if value is removed successfully
 * @return false - value removel failed, or value not found
 */
bool cll_remove(clinkedlist_t *, etype_t, void *);

/**
 * @brief Get no of nodes in the linked list.
 * 
 *        time complexity - O(N) ; N -  no of nodes in the linked list
 *        space complexiy - O(1)
 * 
 * @param clinkedlist_t* - pointer to clinkedlist_t struct 
 * @return int - no of nodes
 */
int cll_size(clinkedlist_t *);

/**
 * @brief Release the memory of the entire list
 * 
 *        time complexity  - O(N) ; N - no of nodes in the list
 *        space complexity - O(1)
 * 
 * @param clinkedlist_t* - pointer to clinkedlist_t struct 
 */
void cll_free(clinkedlist_t *);



/* ---------- UTIL FUNCTION PROTOTYPES ---------- */

/**
 * @brief Prints the value in the linked list.
 * 
 *        time complexity  - O(N) ; N - no of nodes in linked list
 *        space complexity - O(1)
 * 
 * @param clinkedlist_t* - pointer to clinkedlist_t struct 
 */
void cll_print(clinkedlist_t *);

/**
 * @brief Allocate memory for new node and update it with the value.
 * 
 *        time complexity  - O(1)
 *                           O(N), if etype is string, N is length of string
 *        space complexity - O(1)
 *                           O(N), if etype is string, N is length of string
 * 
 * @param etype_t - type of the data. allowed - INT, FLO, STR
 * @param void* - data as null pointer, will type casted based on etype
 * @return node_t* - return the note_t struct pointer
 */
node_t* cll_new_node(etype_t, void *);

/**
 * @brief Free the node. if the node's value is string, then free the string too
 * 
 * @param node_t* - pointer to node_t struct
 */
void cll_free_node(node_t *);

#endif   // __CIRCULAR_LINKED_LIST__