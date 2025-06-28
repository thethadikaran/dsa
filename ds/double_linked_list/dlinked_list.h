#ifndef __HEADER_DOUBLE_LINKED_LIST__
#define __HEADER_DOUBLE_LINKED_LIST__

/**
 * @file dlinked_list.h
 * @author thethadikaran
 * @brief Double linked list.
 *        Each node has two links one to next node and another to previous node.
 * @version 0.1
 * @date 2025-06-27
 * 
 * @copyright Copyright (c) 2025
 * 
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>


/* specify the type of value in the element */
typedef enum { INT, FLO, STR } etype_t;



/* structure to hold value in the node */
typedef struct {
  etype_t etype;

  union {
    int ival;
    float fval;
    char *sval;
  } value;
} element_t;



/* structure to represent the node of double linked list */
typedef struct node {
  element_t data;       // info part - stores value
  struct node *prev;    // pointer part - reference to prev node
  struct node *next;    // pointer part - reference to next node
} node_t;



/* structure to define the linkedlist */
typedef struct {
  node_t *head;       // refer the head of the linked list
} dlinkedlist_t;



/* !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! */
/* ---------- FUNCTION PROTOTYPES ---------- */
/* !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! */

/**
 * @brief Allocate memory for dlinkedlist_t struct.
 * 
 *        time complexity  - O(1)
 *        space complecity - O(1)
 *  
 * @return dlinkedlist_t*  
 */
dlinkedlist_t* dll_init();

/**
 * @brief Allocate memeory for new node and append it at the end of linked list
 * 
 *        time complexity  - O(N); N - no of nodes
 *        space complexity - O(1)
 * 
 * @param dlinkedlist_t* - pointer to linkedlist_t struct
 * @param etype_t - enume type to specify type of value (allowed - INT, FLO, STR)
 * @param void* - value as void pointer, typecase to the etype
 * 
 * @return true 
 * @return false 
 */
bool dll_append(dlinkedlist_t *, etype_t, void *);

/**
 * @brief Insert the value at the given position.
 * 
 *        time complexity  - O(N) ; N - node positon to be inserted
 *        space complexity - O(1)
 * 
 * @param dlinkedlist_t* - reference to dlinkedlist_t struct
 * @param int - new value insert positon
 * @param etype_t - specify type of data. allowed - INT, FLO, STR
 * @param void* - data as void pointer, will type casted based on etype
 * @return true - if insertion of value is success
 * @return false - insertion failed
 */
bool dll_insert(dlinkedlist_t *, int, etype_t, void *);

/**
 * @brief Loop though the linked list and retun the node at the index posiiton
 * 
 *        time complexity  - O(N), N is the index position
 *        space complexity - O(1)
 * 
 * @param dlinkedlist_t* - pointer to dlinkedlist_t struct
 * @param int - index positon to retrieve the node
 * @return node_t* - return node at the index positon
 *                   NULL is returned for invalid positon
 */
node_t* dll_get(dlinkedlist_t *, int);

/**
 * @brief Count no of times the value appears.
 * 
 *        time complexity  - O(N) ; in case of int or float
 *                           O(N * M) ; in case of string, M - length of string
 *        space complexity - O(1)
 * 
 * @param dlinkedlist_t* - reference to dlinkedlist_t struct
 * @param etype_t - specify type of data. allowed - INT, FLO, STR
 * @param void* - data as void pointer, will type casted based on etype
 * @return int - frequency of the value
 */
int dll_count(dlinkedlist_t *, etype_t, void *);

/**
 * @brief Identify the first occurance of the value and return the index
 * 
 *        time complexity  - O(N) ; in case of int or float
 *                           O(N * M) ; in case of string, M - length of string
 *        space complexity - O(1)
 * 
 * @param dlinkedlist_t* - reference to dlinkedlist_t struct
 * @param etype_t - specify type of data. allowed - INT, FLO, STR
 * @param void* - data as void pointer, will type casted based on etype
 * @return int - returns the first occurance index
 *               returns -1 if not found
 */
int dll_index(dlinkedlist_t *, etype_t, void *);

/**
 * @brief Removes the last node from the linked list and returns it
 * 
 *        time complexity  - O(N)
 *        space complexity - O(1)
 * 
 * @param dlinkedlist_t* - reference to dlinkedlist_t struct 
 * @return node_t* - returns the last node, NULL if not present
 *                   user has to take care of freeing the memeory of popped node
 */
node_t* dll_pop(dlinkedlist_t *);

/**
 * @brief Remove the first occurance of the element.
 * 
 *        time complexity  - O(N)
 *        space complexity - O(1)
 * 
 * @param dlinkedlist_t* - reference to dlinkedlist_t struct
 * @param etype_t - specify type of data. allowed - INT, FLO, STR
 * @param void* - data as void pointer, will type casted based on etype
 * @return true - if value is removed successfully
 * @return false - value removel failed, or value not found
 */
bool dll_remove(dlinkedlist_t *, etype_t, void *);

/**
 * @brief reverses the linked list in-place by modifing the links.
 *        Done by updating the next pointer of each node to point to the previous
 *        node, thus reversing the order of nodes in list.
 * 
 *        time complexity  - O(N)
 *        space complexity - O(1)
 * 
 * @param dlinkedlist_t* - pointer to dlinkedlist_t struct 
 */
void dll_reverse(dlinkedlist_t *);

/**
 * @brief Get no of nodes in the linked list.
 * 
 *        time complexity - O(N) ; N -  no of nodes in the linked list
 *        space complexiy - O(1)
 * 
 * @param linkedlist_t* - pointer to dlinkedlist_t struct 
 * @return int - no of nodes
 */
int dll_size(dlinkedlist_t *);  

/**
 * @brief Prints the value in the linked list.
 * 
 *        time complexity  - O(N) ; N - no of nodes in linked list
 *        space complexity - O(1)
 * 
 * @param linkedlist_t* - pointer to dlinkedlist_t struct 
 */
void dll_print(dlinkedlist_t *);

/**
 * @brief Release the memory of the entire list
 * 
 *        time complexity  - O(N) ; N - no of nodes in the list
 *        space complexity - O(1)
 * 
 * @param linkedlist_t* - pointer to dlinkedlist_t struct 
 */
void dll_free(dlinkedlist_t *);


/* ---------- UTIL FUNCTION PROTOTYPES ---------- */

/**
 * @brief Allocate memory for new node and update it with value
 * 
 *        time complexity  - O(1)
 *                           O(N); if etype is STR, N - length of string
 *        space complexity - O(1)
 * 
 * @param etype_t - type of the data. allowed - INT, FLO, STR
 * @param void* - data as null pointer, will type casted based on etype
 * @return node_t* 
 */
node_t* dll_new_node(etype_t, void *);

/**
 * @brief Loop through the linked list and returns the last node
 * 
 *        time complexity  - O(N), N - no of nodes in the list
 *        space complexity - O(1)
 * 
 * @param linkedlist_t* - pointer to dlinkedlist_t struct  
 * @return node_t* -> reference to the last node of linked list
 */
node_t* dll_last_node(dlinkedlist_t *);

/**
 * @brief Free the node. if the node's value is string, then free the string too
 * 
 * @param node_t* - pointer to node_t struct
 */
void dll_free_node(node_t *);

#endif   // __HEADER_DOUBLE_LINKED_LIST__