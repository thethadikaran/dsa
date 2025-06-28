#ifndef __DOUBLE_HEADER_LINKED_LIST__
#define __DOUBLE_HEADER_LINKED_LIST__

/**
 * @file hlinked_list.c
 * @author thethadikaran
 * @brief Double linked list with header node
 * Comparing with other type of linked list, this type has a header node even
 * the linked list has values or not. This usually hold the meta data of the
 * linked chain like length, last node's address etc.
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

/* specify the permitted value type */
typedef enum { INT, FLO, STR } etype_t;


/* define an element, used in info part of the node */
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


/* define a header node */
typedef struct {
  int size;             // no of nodes in the linked list
  struct node *head;   // ref to first node of the linked list
  struct node *tail;    // ref to last node of the linked list
} dhlinkedlist_t;



/* !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! */
/* ---------- FUNCTION PROTOTYPES ---------- */
/* !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! */

/**
 * @brief Allocate memory for dhlinkedlist_t struct and initialize it
 * 
 *        time complexity  - O(1)
 *        space complexity - O(1)
 * 
 * @return dhlinkedlist_t* 
 */
dhlinkedlist_t* dhll_init();

/**
 * @brief Create a new node and add it to the end of linked list.
 *        If  linked list has no nodes, then upate it as the first node.
 * 
 *        time complexity  - O(1)
 *        space complexity - O(1)
 * 
 * @param dhlinkedlist_t* - pointer to dhlinkedlist_t struct
 * @param etype_t - specify type of data. allowed - INT, FLO, STR
 * @param void* - data as void pointer, will type casted based on etype
 * @return true - if new value additon is successful
 * @return false - new value additon fails
 */
bool dhll_append(dhlinkedlist_t *, etype_t, void *);

/**
 * @brief Insert the value at the given position.
 * 
 *        time complexity  - O(N) ; N - node positon to be inserted
 *        space complexity - O(1)
 * 
 * @param dhlinkedlist_t* - reference to dhlinkedlist_t struct
 * @param int - new value insert positon
 * @param etype_t - specify type of data. allowed - INT, FLO, STR
 * @param void* - data as void pointer, will type casted based on etype
 * @return true - if insertion of value is success
 * @return false - insertion failed
 */
bool dhll_insert(dhlinkedlist_t *, int, etype_t, void *);

/**
 * @brief Loop though the linked list and retun the node at the index posiiton
 * 
 *        time complexity  - O(N), N is the index position
 *        space complexity - O(1)
 * 
 * @param dhlinkedlist_t* - pointer to dlinkedlist_t struct
 * @param int - index positon to retrieve the node
 * @return node_t* - return node at the index positon
 *                   NULL is returned for invalid positon
 */
node_t* dhll_get(dhlinkedlist_t *, int);

/**
 * @brief Count no of times the value appears.
 * 
 *        time complexity  - O(N) ; in case of int or float
 *                           O(N * M) ; in case of string, M - length of string
 *        space complexity - O(1)
 * 
 * @param dhlinkedlist_t* - reference to dhlinkedlist_t struct
 * @param etype_t - specify type of data. allowed - INT, FLO, STR
 * @param void* - data as void pointer, will type casted based on etype
 * @return int - frequency of the value
 */
int dhll_count(dhlinkedlist_t *, etype_t, void *);

/**
 * @brief Identify the first occurance of the value and return the index
 * 
 *        time complexity  - O(N) ; in case of int or float
 *                           O(N * M) ; in case of string, M - length of string
 *        space complexity - O(1)
 * 
 * @param dhlinkedlist_t* - reference to dhlinkedlist_t struct
 * @param etype_t - specify type of data. allowed - INT, FLO, STR
 * @param void* - data as void pointer, will type casted based on etype
 * @return int - returns the first occurance index
 *               returns -1 if not found
 */
int dhll_index(dhlinkedlist_t *, etype_t, void *);

/**
 * @brief Removes the last node from the linked list and returns it
 * 
 *        time complexity  - O(1)
 *        space complexity - O(1)
 * 
 * @param dlinkedlist_t* - reference to dlinkedlist_t struct 
 * @return node_t* - returns the last node, NULL if not present
 *                   user has to take care of freeing the memeory of popped node
 */
node_t* dhll_pop(dhlinkedlist_t *);

/**
 * @brief Remove the first occurance of the element.
 * 
 *        time complexity  - O(1)
 *        space complexity - O(1)
 * 
 * @param dhlinkedlist_t* - reference to dhlinkedlist_t struct
 * @param etype_t - specify type of data. allowed - INT, FLO, STR
 * @param void* - data as void pointer, will type casted based on etype
 * @return true - if value is removed successfully
 * @return false - value removel failed, or value not found
 */
bool dhll_remove(dhlinkedlist_t *, etype_t, void *);

/**
 * @brief reverses the linked list in-place by modifing the links.
 *        Done by updating the next pointer of each node to point to the previous
 *        node, thus reversing the order of nodes in list.
 * 
 *        time complexity  - O(N)
 *        space complexity - O(1)
 * 
 * @param dhlinkedlist_t* - pointer to dhlinkedlist_t struct 
 */
void dhll_reverse(dhlinkedlist_t *);

/**
 * @brief Get no of nodes in the linked list.
 * 
 *        time complexity - O(1)
 *        space complexiy - O(1)
 * 
 * @param dhlinkedlist_t* - pointer to dhlinkedlist_t struct 
 * @return int - no of nodes
 */
int dhll_size(dhlinkedlist_t *);

/**
 * @brief Prints the value in the linked list.
 * 
 *        time complexity  - O(N) ; N - no of nodes in linked list
 *        space complexity - O(1)
 * 
 * @param dhlinkedlist_t* - pointer to dhlinkedlist_t struct 
 */
void dhll_print(dhlinkedlist_t *);

/**
 * @brief Release the memory of the entire list
 * 
 *        time complexity  - O(N) ; N - no of nodes in the list
 *        space complexity - O(1)
 * 
 * @param dhlinkedlist_t* - pointer to dhlinkedlist_t struct 
 */
void dhll_free(dhlinkedlist_t *);


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
node_t* dhll_new_node(etype_t, void *);

/**
 * @brief Free the node. if the node's value is string, then free the string too
 * 
 * @param node_t* - pointer to node_t struct
 */
void dhll_free_node(node_t *);


#endif   // __DOUBLE_HEADER_LINKED_LIST__