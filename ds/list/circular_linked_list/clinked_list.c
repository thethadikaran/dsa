#include "clinked_list.h"

struct node* cll_create_node() {
  struct node *n = malloc(sizeof(struct node));
  if (!n) return NULL;

  n->next = NULL;
  return n;
}



clinkedlist* cll_init() {
  clinkedlist *cll = malloc(sizeof(clinkedlist));
  if (!cll) return NULL;

  cll->last = NULL;
  return cll;
}



bool cll_append_front(clinkedlist *cll, int etype, void *val) {
  // create a node and update with the value
  struct node *new = cll_create_node();
  if (new == NULL) return false;

  if (!cll_update_node_value(new, etype, val)) return false;

  // check if any nodes were present
  if (cll->last == NULL) {
    cll->last = new;
    new->next = new;    // point the node to itself
  }
  else {
    // update new node's next ref with the previous first node
    new->next = cll->last->next;

    // update the last node's next ref to point to new first node
    cll->last->next = new;
  }
  return true;
}



bool cll_append_last(clinkedlist *cll, int etype, void *val) {
  // create a node and update with the value
  struct node *new = cll_create_node();
  if (new == NULL) return false;

  if (!cll_update_node_value(new, etype, val)) return false;

  // check if any nodes were present
  if (cll->last == NULL) {
    cll->last = new;
    new->next = new;    // point the node to itself
  }
  else {
    // update new nodes next ref to point to first node
    new->next = cll->last->next;

    // update the previous last node's next ref to point to new node
    cll->last->next = new;

    // update the last refernce in the circular_linked_list struct
    cll->last = new;
  }

  return true;
}



void cll_delete(clinkedlist *cll, int etype, void *val) {
  if (!cll || !cll->last) return;

  struct node *curr = cll->last->next;    // get the head node
  struct node *prev = cll->last;

  // check if the first node has the value to be removed
  if (cll_is_value_match(curr, etype, val)) {
    // check if it's the only node
    if (curr == cll->last) {
      cll->last = NULL;
      cll_free_node(curr);
    }
    else {
      // update the last node with next first node
      cll->last->next = curr->next;
      cll_free_node(curr);
    }
  
  return;    
  }

  // loop through to identify the element to remove
  curr = curr->next;

  while (curr != cll->last && !cll_is_value_match(curr, etype, val)) {
    prev = curr;
    curr = curr->next;
  }

  if (cll_is_value_match(curr, etype, val)) {
    // update the prev node's next ref to the curr node's next
    prev->next = curr->next;

    // check if the curr node is the last node
    if (curr == cll->last) cll->last = prev;

    cll_free_node(curr);
  }
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
static bool cll_update_node_value(struct node *n, int etype, void *val) {
  switch (etype) {
    case INT: n->ele.value.ival = *(int *)val; break;
    case FLO: n->ele.value.fval = *(float *)val; break;
    case STR: n->ele.value.sval = strdup((char *) val); break;    
    default: return false;
  }  
  n->ele.etype = etype;   // finally update the element type in element struct
  return true;
}



bool cll_is_value_match(struct node *n, int etype, void *val) {
  if (n->ele.etype == etype) {
    switch (etype) {
      case INT: return ( *(int *)val == n->ele.value.ival );
      case FLO: return ( *(float *)val == n->ele.value.fval );
      case STR: return ( strcmp( (char *)val, n->ele.value.sval) == 0);
      default: return false;
    }
  }
  return false;
}



void cll_free_node(struct node *n) {
  if (n->ele.etype == STR) 
    free(n->ele.value.sval);
  
  free(n);
}



void cll_free(clinkedlist *cll) {
  // check the linked list is empty?
  if (cll->last == NULL) {
    free(cll);
    return;
  }

  // start from the first node
  struct node *curr = cll->last->next;

  do {
    struct node *to_del = curr;
    curr = curr->next;                // move to next node
    cll_free_node(to_del);            // free curr node
  } while (curr != cll->last->next);  // loop until the curr node reach head again

  free(cll);
}



void cll_print(clinkedlist *cll) {
  printf("\n[");

  if (cll->last == NULL) {
    printf("]\n");
    return;
  }

  struct node *curr = cll->last->next;

  do {
    switch (curr->ele.etype) {
      case INT: printf("%d", curr->ele.value.ival); break;
      case FLO: printf("%f", curr->ele.value.fval); break;
      case STR: printf("\"%s\"", curr->ele.value.sval); break;
    }
    curr = curr->next;

    if (curr != cll->last->next) printf(", ");  // to avoid printing extra comma
  } while (curr != cll->last->next);

  printf("]\n");
}