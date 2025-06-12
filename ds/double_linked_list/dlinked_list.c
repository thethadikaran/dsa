#include "dlinked_list.h"



/**
 * @brief Allocate memory for a Node, and mark the element type
 * as special value "NO_VALUE".
 * 
 * @return struct dnode* 
 */
struct dnode* dll_init() {
  struct dnode *dn = dll_create_node();
  if (dn == NULL) return NULL;

  // add marked to denote the node has no value
  dn->ele.etype = NO_VALUE;
  return dn;
}



/**
 * @brief Create a node and set's default value.
 * 
 * @return struct dnode* 
 */
static struct dnode* dll_create_node() {
  struct dnode *dn = malloc( sizeof(struct dnode) );
  if (dn == NULL) {
    fprintf(stderr, "Cannot allocate memory for DNode");
    return NULL;
  }

  dn->prev = NULL;
  dn->next = NULL;

  return dn;
}



/**
 * @brief Insert node at the end of the list.
 * 
 * @param head - reference to start of double linked list
 * @param etype - type of value (either of these - INT, FLO, STR)
 * @param val - value as void pointer (type case based on above etype)
 * @return true 
 * @return false 
 */
bool dll_insert(struct dnode *head, int etype, void *val) {
  if (head == NULL) return false;

  // check for the node with no value marker (initialized node)
  if (head->ele.etype == NO_VALUE) 
    return dll_update_node_value(head, etype, val);

  struct dnode *new = dll_create_node();
  if (new == NULL) return false;

  if (!dll_update_node_value(new, etype, val)) {
    free(new);
    return false;
  }

  // get the last node and update the chain with the new element
  struct dnode *last = dll_get_last_node(head);
  last->next = new;
  new->prev = last;
  return true;
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
static bool dll_update_node_value(struct dnode *n, int etype, void *val) {
  switch (etype) {
    case INT: n->ele.value.ival = *(int *)val; break;
    case FLO: n->ele.value.fval = *(float *)val; break;
    case STR: n->ele.value.sval = strdup( (char *)val ); break;    
    default: return false;
  }  
  n->ele.etype = etype;   // finally update the element type in element struct
  return true;
}



/**
 * @brief Print the values in the linked list (in python's list format).
 * 
 * @param head - reference to the linked list's head node
 */
void dll_print(struct dnode *head) {
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
 * @brief Release the allocated memory for all the Nodes in linked chain.
 * Need to explicitly release the memory occupied by string element.
 * 
 * @param head - pointer to the head of the double linked list
 */
void dll_free(struct dnode *head) {
  while (head != NULL) {
    struct dnode *curr = head;   // mark the current node, need to free the memory

    // if the node contains string data, then release the memory of it
    if (curr->ele.etype == STR)  free(head->ele.value.sval);

    head = head->next;
    free(curr);
  }
}



/**
 * @brief Reverse the elements of the double linked list
 * 
 * @param head 
 */
void dll_reverse(struct dnode **head) {
  struct dnode *tmp = NULL;
  struct dnode *current = *head;

  while (current != NULL) {
    // swap the prev and next pointer reference in a node
    tmp = current->next;
    current->next = current->prev;
    current->prev = tmp;
  
    current = tmp;
  }

  if (tmp != NULL)
    *head = tmp->prev; // update head to the new first node
}



/**
 * @brief Fetch the last node's address.
 * 
 * @param head - pointer to head node of the linked list
 * @return struct node* - the last node's address
 */
struct dnode* dll_get_last_node(struct dnode *head) {
  while (head->next != NULL) 
    head = head->next;
  
  return head;
}



/**
 * @brief Insert element at the specified position
 * 
 * @param head - reference to head of double linked list
 * @param pos - positon to insert
 * @param etype - type of value
 * @param val - value as void pointer (has to type case based on etype)
 * @return true 
 * @return false 
 */
bool dll_insert_at(struct dnode **head, int pos, int etype, void *val) {
  int size = dll_length(*head);
  int count = 0;

  if (pos < 0 || pos > size) {
    fprintf(stderr, "Invalid insert position");
    return false;
  }

  // create a node and update it with the value
  struct dnode *new = dll_create_node();
  if (new == NULL) return false;
  dll_update_node_value(new, etype, val);

  // insertion at start
  if (pos == 0) {
    (*head)->prev = new;   // update the curr head's prev field
    new->next = *head;     // update the new head with then next field
    *head = new;           // finally update the head to ref the new node

    return true;
  }

  // insertion at b/w & end
  struct dnode *node_at_pos = dll_get_node_at(*head, pos);
  if (node_at_pos == NULL) return false;

  node_at_pos->prev->next = new;   // update the previous node to insert position

  new->prev = node_at_pos->prev;   // update the new node to be inserted
  new->next = node_at_pos;

  node_at_pos->prev = new;         // update the node already in insert positon

  return true;
}




/**
 * @brief Calculate no of nodes in the linked chain
 * 
 * @param head - reference to the head node of linked list
 * @return int 
 */
int dll_length(struct dnode *head) {
  int len = 0;

  while (head != NULL) {
    len++;
    head = head->next;
  }
  return len;
}



/**
 * @brief Get the node at the specified position
 * 
 * @param head - reference to start node of linked list
 * @param position - position of node to pick
 * @return struct node* - reference to node at given position
 */
static struct dnode* dll_get_node_at(struct dnode *head, int position) {
  int curr_pos = 0;

  while (head != NULL) {
    if (curr_pos == position) return head;

    head = head->next;
    curr_pos++;
  }

  fprintf(stderr, "Invalid position of Node");
  return NULL;
}



/**
 * @brief Delete node at the specified position
 * 
 * @param head - reference to start node of linked chain
 * @param pos - node's posiiton to remove
 */
void dll_delete_at(struct dnode **head, int pos) {
  if (head == NULL || *head == NULL) return;

  struct dnode *to_del = NULL;

  if (pos == 0) {
    to_del = *head;
    *head = (*head)->next;
    (*head)->prev == NULL;
  }
  else {
    to_del = dll_get_node_at(*head, pos);
    if (to_del == NULL) {
      fprintf(stderr, "Position not valid");
      return;
    }

    // update previous node's next reference
    to_del->prev->next = to_del->next; 

    // update next node's prev reference
    if (to_del->next != NULL) {
      to_del->next->prev = to_del->prev;
    }
  }

  if (to_del->ele.etype == STR) free(to_del->ele.value.sval);
  free(to_del);
}