#include "linked_list.h"



/**
 * @brief Create and allocate memory for a new node.
 * 
 * @return struct node* - address of the new node
 * @return NULL - if memory allocation fails
 */
static struct node* ll_create_node() {
  struct node *n = malloc(sizeof(struct node));
  if (n == NULL) {
    fprintf(stderr, "Failed to allocate memory for a Node\n");
    return NULL;
  }
  n->next = NULL;
  return n;
}



/**
 * @brief Creates a node with a marker for no value.
 * This initialized the linked list with one node.
 * 
 * @return struct node* - pointer to a single node
 * @return NULL - if memory allocation fails
 */
struct node* ll_init() {
  struct node *n = ll_create_node();
  if (n == NULL) return NULL;

  // to identify this node don't have any value
  n->ele.etype = NO_VALUE;
  return n;
}



/**
 * @brief Check the value type and update the element with the value
 * 
 * @param n - reference to the node
 * @param etype - value type. either one of these -> INT, FLO, STR
 * @param val - void pointer to the value (type case it to the etype data)
 * @return true - if the node is updated with the value
 * @return false - for wrong element type
 */
static bool ll_update_node_value(struct node *n, int etype, void *val) {
  switch (etype) {
    case INT: n->ele.value.ival = *(int *)val; break;
    case FLO: n->ele.value.fval = *(float *)val; break;
    case STR: n->ele.value.sval = strdup((char *) val); break;    
    default: return false;
  }  
  n->ele.etype = etype;   // finally update the element type in element struct
  return true;
}



/**
 * @brief Create a node and update it with the value.
 * Add this new node at the end of the linked list.
 * 
 * @param head - pointer to head node of the linked list
 * @param etype - value type. either one of these -> INT, FLO, STR
 * @param val - void pointer to the value (type case it to the etype data)
 * 
 * @return true - if the addition of node is successful
 * @return false - if node additon has failed
 */
bool ll_insert(struct node *head, int etype, void *val) { 
  if (head == NULL) return false;

  // verify if it's a first node initialized with NO_VALUE
  if (head->ele.etype == NO_VALUE)
    return ll_update_node_value(head, etype, val);

  struct node *new_node = ll_create_node();
  if (new_node == NULL) return false;

  ll_update_node_value(new_node, etype, val);
  struct node *last = ll_get_last_node(head);   // get the last node in the chain
  last->next = new_node;
  return true;
}



/**
 * @brief Fetch the last node's address.
 * 
 * @param head - pointer to head node of the linked list
 * @return struct node* - the last node's address
 */
struct node* ll_get_last_node(struct node *head) {
  while (head->next != NULL) 
    head = head->next;
  
  return head;
}



/**
 * @brief Release the allocated memory for all the Nodes in linked chain.
 * Need to explicitly release the memory occupied by string element.
 * 
 * @param head - pointer to the head of the linked list
 */
void ll_free(struct node *head) {
  while (head != NULL) {
    struct node *curr = head;   // mark the current node, need to free the memory

    // if the node contains string data, then release the memory of it
    if (curr->ele.etype == STR)  free(head->ele.value.sval);

    head = head->next;
    free(curr);
  }
}



/**
 * @brief Print the values in the linked list (in python's list format).
 * 
 * @param head - reference to the linked list's head node
 */
void ll_print(struct node *head) {
  printf("[");

  while (head != NULL) {
    switch (head->ele.etype) {
      case INT: printf("%d", head->ele.value.ival); break;
      case FLO: printf("%f", head->ele.value.fval); break;
      case STR: printf("\"%s\"", head->ele.value.sval); break;
    }
    head = head->next;
    if (head != NULL) printf(", ");
  }
  printf("]\n");
}



/**
 * @brief Calculate no of nodes in the linked chain
 * 
 * @param head - reference to the head node of linked list
 * @return int 
 */
int ll_length(struct node *head) {
  int len = 0;

  while (head != NULL) {
    len++;
    head = head->next;
  }
  return len;
}



/**
 * @brief Reverse the linked list in-place.
 * 
 * @param head - pointer to current head node
 */
void ll_reverse(struct node **head) {
  struct node *prev = NULL;    // as don't have previous element
  struct node *curr = *head;   // dereference head to get the current head
  struct node *next;

  while (curr != NULL) {
    next = curr->next;   // take a copy of ref to the next node
    curr->next = prev;   // update the curr element to link with previous element
    
    prev = curr;
    curr = next;
  }

  *head = prev;   // update the head to point to the new head
}



/**
 * @brief Search for the element and returns the first position of the value
 * in the linked chain
 * 
 * @param head - reference to start node of linked list
 * @param etype - type of element (INT, FLO, STR)
 * @param val - value to be searched for
 * @return int  - return positon of value in chain or -1
 */
int ll_search(struct node *head, int etype, void *val) {
  int position = 0;

  while (head != NULL) {
    // if element type matches, then check for matching value
    if (head->ele.etype == etype) {
      switch (etype) {
        case INT:
          if (head->ele.value.ival == *(int *)val) return position;
          break;
        case FLO:
          if (head->ele.value.fval == *(float *)val) return position;
          break;
        case STR:
          if ( strcmp(head->ele.value.sval, (char *)val) == 0 ) return position;
          break;
       }
    }

    head = head->next;
    position++;
  }

  return -1;
}



/**
 * @brief Insert a node at any given position
 * 
 * @param head - pointer to reference to start node of linked list
 * @param position - positon at which the new node is inserted
 * @param etype - element type of the new node
 * @param val  - value of the new node
 * @return true - if insertion is success
 * @return false - in insertion fails
 */
bool ll_insert_at(struct node **head, int position, int etype, void *val) {
  int size = ll_length(*head);

  // verify insert position is valid
  if (position < 0 || position > size) {
    fprintf(stderr, "Invalid insert positon");
    return false;
  }

  // create a node and update it with the value
  struct node *n = ll_create_node();
  if (n == NULL) return false;
  ll_update_node_value(n, etype, val);

  // insertion at the start
  if (position == 0) {
    n->next = *head;   // update the next ref to old head
    *head = n;         // update the head to new node
    
    return true;
  }

  // 2. insertion b/w the linked chain and at the end
  struct node *node_one_before_pos = ll_get_node_at(*head, position - 1);
  if (node_one_before_pos == NULL) return false;

  n->next = node_one_before_pos->next;
  node_one_before_pos->next = n;

  return true;
}



/**
 * @brief Get the node at the specified position
 * 
 * @param head - reference to start node of linked list
 * @param position - position of node to pick
 * @return struct node* - reference to node at given position
 */
struct node* ll_get_node_at(struct node *head, int position) {
  int curr_pos = 0;

  while (head != NULL) {
    if (curr_pos == position) return head;

    head = head->next;
    curr_pos++;
  }

  fprintf(stderr, "Invalid position of Node");
  return NULL;
}



bool ll_is_empty(struct node *head) {
  return (head == NULL);
}



void ll_delete_at(struct node **head, int position) {
  if (head == NULL || *head == NULL) return;

  struct node *to_delete = NULL;

  if (position == 0) {
    to_delete = *head;
    *head = (*head)->next;
  }
  else {
    struct node *previous_node = ll_get_node_at(*head, position-1);
    struct node *next_node = previous_node->next->next;

    to_delete = previous_node->next;

    // update the chain to be continuous
    previous_node->next = next_node;
  }

  if (to_delete->ele.etype == STR) free(to_delete->ele.value.sval);
  free(to_delete);
}