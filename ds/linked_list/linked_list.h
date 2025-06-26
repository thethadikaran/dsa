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



/* structure to represent the node */
typedef struct node {
  element_t data;       // info part - stores value
  struct node *next;    // pointer part - reference to next node
} node_t;



/* structure to define the linkedlist */
typedef struct {
  node_t *head;       // refer the head of the linked list
} linkedlist_t;



/* !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! */
/* ---------- FUNCTION PROTOTYPES ---------- */
/* !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! */

/**
 * @brief Allocate memory for linkedlist and returns it.
 *        Head of linkedlist is marked as NULL.
 * 
 *        time complexity  - O(1)
 *        space complexity - O(1)
 * 
 * @return linkedlist_t* 
 */
linkedlist_t* ll_init();

/**
 * @brief Append the value at the end of the linked list.
 *        If the linked list is empty, then it will be the first value.
 * 
 *        time complexity  - O(1) if linked list has no nodes
 *                           O(N) if linked has N nodes
 *        space complexity - O(1)
 * 
 * @param linkedlist_t* - reference to linkedlist_t struct
 * @param etype_t - specify type of data. allowed - INT, FLO, STR
 * @param void* - data as void pointer, will type casted based on etype
 * @return true - append is success
 * @return false - append fails
 */
bool ll_append(linkedlist_t *, etype_t, void *);

/**
 * @brief Insert the value at the given position.
 * 
 *        time complexity  - O(N) ; N- node positon to be inserted
 *        space complexity - O(1)
 * 
 * @param linkedlist_t* - reference to linkedlist_t struct
 * @param int - new value insert positon
 * @param etype_t - specify type of data. allowed - INT, FLO, STR
 * @param void* - data as void pointer, will type casted based on etype
 * @return true - if insertion of value is success
 * @return false - insertion failed
 */
bool ll_insert(linkedlist_t *, int, etype_t, void *);

/**
 * @brief Loop though the linked list and retun the node at the index posiiton
 * 
 *        time complexity  - O(N), N is the index position
 *        space complexity - O(1)
 * 
 * @param linkedlist_t* - pointer to linkedlist_t struct
 * @param int - index positon to retrieve the node
 * @return node_t* - return node at the index positon
 *                   NULL is returned for invalid positon
 */
node_t* ll_get(linkedlist_t *, int);

/**
 * @brief Count no of times the value appears.
 * 
 *        time complexity  - O(N) ; in case of int or float
 *                           O(N * M) ; in case of string, M - length of string
 *        space complexity - O(1)
 * 
 * @param linkedlist_t* - reference to linkedlist_t struct
 * @param etype_t - specify type of data. allowed - INT, FLO, STR
 * @param void* - data as void pointer, will type casted based on etype
 * @return int - frequency of the value
 */
int ll_count(linkedlist_t *, etype_t, void *);

/**
 * @brief Identify the first occurance of the value and return the index
 * 
 *        time complexity  - O(N) ; in case of int or float
 *                           O(N * M) ; in case of string, M - length of string
 *        space complexity - O(1)
 * 
 * @param linkedlist_t* - reference to linkedlist_t struct
 * @param etype_t - specify type of data. allowed - INT, FLO, STR
 * @param void* - data as void pointer, will type casted based on etype
 * @return int - returns the first occurance index
 *               returns -1 if not found
 */
int ll_index(linkedlist_t *, etype_t, void *);

/**
 * @brief Removes the last node form the linked list and returns it
 * 
 *        time complexity  - O(N)
 *        space complexity - O(1)
 * 
 * @param linkedlist_t* - reference to linkedlist_t struct 
 * @return node_t* - returns the last node, NULL if not present
 *                   user has to take care of freeing the memeory of popped node
 */
node_t* ll_pop(linkedlist_t *);

/**
 * @brief Remove the first occurance of the element.
 * 
 *        time complexity  - O(N)
 *        space complexity - O(1)
 * 
 * @param linkedlist_t* - reference to linkedlist_t struct
 * @param etype_t - specify type of data. allowed - INT, FLO, STR
 * @param void* - data as void pointer, will type casted based on etype
 * @return true - if value is removed successfully
 * @return false - value removel failed, or value not found
 */
bool ll_remove(linkedlist_t *, etype_t, void *);

/**
 * @brief reverses the linked list in-place by modifing the links.
 *        Done by updating the next pointer of each node to point to the previous
 *        node, thus reversing the order of nodes in list.
 * 
 *        time complexity  - O(N)
 *        space complexity - O(1)
 * 
 * @param linkedlist_t* - pointer to linkedlist_t struct 
 */
void ll_reverse(linkedlist_t *);

/**
 * @brief Get no of nodes in the linked list.
 * 
 *        time complexity - O(N) ; N -  no of nodes in the linked list
 *        space complexiy - O(1)
 * 
 * @param linkedlist_t* - pointer to linkedlist_t struct 
 * @return int - no of nodes
 */
int ll_size(linkedlist_t *);

/**
 * @brief Prints the value in the linked list.
 * 
 *        time complexity  - O(N) ; N - no of nodes in linked list
 *        space complexity - O(1)
 * 
 * @param linkedlist_t* - pointer to linkedlist_t struct 
 */
void ll_print(linkedlist_t *);

/**
 * @brief Release the memory of the entire list
 * 
 *        time complexity  - O(N) ; N - no of nodes in the list
 *        space complexity - O(1)
 * 
 * @param linkedlist_t* - pointer to linkedlist_t struct 
 */
void ll_free(linkedlist_t *);


/* ---------- UTIL FUNCTION PROTOTYPES ---------- */

/**
 * @brief Allocate memory for new node and update it with the value.
 * 
 *        time complexity  - O(1)
 *                           O(N), if etype is string, N is length of string
 *        space complexity - O(1)
 *                           O(N), if etype is string, N is length of string
 * 
 * @param linkedlist_t* - pointer to linkedlist_t struct 
 * @param etype_t - type of the data. allowed - INT, FLO, STR
 * @param void* - data as null pointer, will type casted based on etype
 * @return node_t* - return the note_t struct pointer
 */
node_t* ll_new_node(etype_t, void *);

/**
 * @brief Loop through the linked list and returns the last node
 * 
 *        time complexity  - O(N), N - no of nodes in the list
 *        space complexity - O(1)
 * 
 * @param linkedlist_t* - pointer to linkedlist_t struct  
 * @return node_t* -> reference to the last node of linked list
 */
node_t* ll_last_node(linkedlist_t *);

/**
 * @brief Free the node. if the node's value is string, then free the string too
 * 
 * @param node_t* - pointer to node_t struct
 */
void ll_free_node(node_t *);