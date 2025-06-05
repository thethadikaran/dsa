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