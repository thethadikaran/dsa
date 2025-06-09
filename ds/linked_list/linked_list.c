#include "linked_list.h"


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
  // check if the node has a value (is it a initial node?)
  if (head->ele.etype == NO_VALUE) {
    ll_update_node_value(head, etype, val);
    return true;
  }

  // first: create a new node
  struct node *new_node = ll_create_node();
  if (new_node == NULL) return true;

  // add the value to the new node
  ll_update_node_value(new_node, etype, val);

  // now get the last node in the linked chain
  struct node *last = ll_get_last_node(head);

  // finally add the new node as the last one
  last->next = new_node;
  return true;
}


/**
 * @brief Fetch the last node's address.
 * 
 * @param head - pointer to head node of the linked list
 * 
 * @return struct node* - the last node's address
 */
struct node* ll_get_last_node(struct node *head) {
  while (head->next != NULL) 
    head = head->next;
  
  return head;
}


/**
 * @brief Create and allocate memory for a new node.
 * 
 * @return struct node* - address of the new node
 * @return NULL - if memory allocation fails
 */
struct node* ll_create_node() {
  struct node *n = malloc(sizeof(struct node));
  if (n == NULL) {
    perror("Cant allocate memory for Node");
    return NULL;
  }

  n->next = NULL;
  return n;
}


/**
 * @brief Check the value type and update the Element's union accordingly.
 * 
 * @param n - reference to the node
 * @param etype - value type. either one of these -> INT, FLO, STR
 * @param val - void pointer to the value (type case it to the etype data)
 * @return true - if the node is updated with the value
 * @return false - for wrong element type
 */
bool ll_update_node_value(struct node *n, int etype, void *val) {
  switch (etype) {
    case INT:
      n->ele.value.ival = *(int *)val;
      break;

    case FLO:
      n->ele.value.fval = *(float *)val;
      break;

    case STR:
      n->ele.value.sval = strdup((char *) val);
      break;
    
    default:
      perror("Invalid element type");
      return false;
  }
  // finally update the element type in element struct
  n->ele.etype = etype;
  return true;
}


/**
 * @brief Release the allocated memory for all the Nodes in linked chain.
 * Need to explicitly release the memory occupied by string element.
 * 
 * @param head - pointer to the head of the linked list
 */
void ll_free(struct node *head) {
  while (head != NULL) {
    // in case the node contain string data, then release memeory for it
    if (head->ele.etype == STR)
      free(head->ele.value.sval);
    
    // mark the location of current node, we need to free the memory
    struct node *curr = head;

    // update the next node's address to continue the loop
    head = head->next;

    // finally, free the current node
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
    // update the next node
    head = head->next;

    if (head != NULL) printf(", ");
  }
  printf("]\n");
}


/**
 * @brief Calculate no of nodes in the linked chain
 * 
 * @param head - reference to the head node of linked list
 * 
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
 * 
 * @return struct node* - pointer to new head node after reverse
 */
void ll_reverse(struct node **head) {
  struct node *prev = NULL;    // as don't have previous element
  struct node *curr = *head;    // dereference head to get the current head
  struct node *next;

  while (curr != NULL) {
    // take a copy of ref to the next node
    next = curr->next;

    // update the curr element to link with previous element
    curr->next = prev;

    // update the other pointers to continue the loop
    prev = curr;
    curr = next;
  }

  // update the head to point to the new head
  *head = prev;
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
       }
    }

    // update the next element & positon
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
    perror("Invalid insert positon");
    return false;
  }

  // create a node and update it with the value
  struct node *n = ll_create_node();
  ll_update_node_value(n, etype, val);

  // 1. insertion at the start
  if (position == 0) {
    n->next = *head;   // update the next ref to old head
    *head = n;         // update the head to new node
    
    return true;
  }

  // 2. insertion at the end
  if (position == size) {
    struct node *last = ll_get_last_node(*head);    // get the last node
    last->next = n;                                 // update last node's next ref

    return true;
  }

  // 3. insertion b/w the linked chain
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

  perror("Invalid position of Node");
  return NULL;
}