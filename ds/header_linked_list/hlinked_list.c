#include "hlinked_list.h"


hlinkedlist *hll_init() {
  hlinkedlist *hll = malloc(sizeof(hlinkedlist));
  if (!hll) {
    fprintf(stderr, "Memory allocation failed for HLinkedList");
    return NULL;
  }

  // initilize with values
  hll->first = NULL;
  hll->last = NULL;
  hll->len = 0;

  return hll;
}



int hll_count(hlinkedlist *hll) {
  return (hll ? hll->len : -1);
}



bool hll_append(hlinkedlist *hll, enum element_type etype, void *val) {
  if (!hll || !val) return false;

  // create a node and update it with the value
  struct node *new = hll_node_create_update(etype, val);
  if (!new) return false;

  // no nodes were present in the linked list
  if (hll->len == 0) {
    hll->first = new;
  }
  else {
    // previous nodes were present in the linked list
    hll->last->next = new;   // add the node to the chain
  }

  hll->last = new;      // update the header parameters
  hll->len++;

  return true;
}



bool hll_insert(hlinkedlist *hll, int pos, enum element_type etype, void *val) {
  if (!hll || pos < 0 || pos > hll->len || !val) {
    fprintf(stderr, "Invalid insert position");
    return false;    
  }

  // if inserting at the end or the list is empty
  if (pos == hll->len) {
    return hll_append(hll, etype, val);
  }

  // create a node and update it with the value
  struct node *new = hll_node_create_update(etype, val);
  if (!new) return false;

  // if insertion at the start of the chain or if it's a first node
  if (pos == 0) {
    new->next = hll->first;     // add the old first node as next element
    hll->first = new;           // update the head node
  }
  else {
    // insertion at intermidiate positon
    struct node *prev = hll_get_node(hll, pos-1);
    new->next = prev->next;
    prev->next = new;
  }

  // update the meta data
  hll->len++;
  return true;
}



bool hll_remove(hlinkedlist *hll, enum element_type etype, void *val) {
  if (!hll || hll->len == 0) return false;

  struct node *curr = hll->first;
  struct node *prev = NULL;

  while (curr != NULL) {
    bool is_value_matched = false;

    switch (etype) {
      case INT:
        is_value_matched = *(int *)val == curr->ele.value.ival;
        break;
      case FLO:
        is_value_matched = *(float *)val == curr->ele.value.fval;
        break;
      case STR:
        is_value_matched = (strcmp(curr->ele.value.sval, (char *)val) == 0);
        break;
    }

    // check if we got the match
    if (is_value_matched) {
      if (!prev) {
        // if prev is null, then it's the first node to remove
        hll->first = curr->next;
      }
      else {
        // if we have prev, then we have two possible situations,
        // either it can be a last node or a intermidiate node
        if (hll->last == curr) {
          hll->last = prev;
          prev->next = NULL;
        }
        else {
          prev->next = curr->next;
        }
      }

      hll_free_node(curr);   // free the removed node
      hll->len--;            // update the node count

      return true;
    }
    // if not a match , then updat the variables to continue the loop
    prev = curr;
    curr = curr->next;
  }

  return false;
}



struct node* hll_pop(hlinkedlist *hll) {
  if (!hll || hll->len == 0) return NULL;

  struct node *popped;

  // special case - only one node present
  if (hll->len == 1) {
    popped = hll->first;

    // update the header node references
    hll->first = NULL;
    hll->last = NULL;
  }
  else {
    // get the node previous to the last node
    struct node *prev_to_last = hll_get_node(hll, hll->len - 2);
    prev_to_last->next = NULL;          // since it's last node, update next ref

    popped = hll->last;                 // make node of curr last node
    hll->last = prev_to_last;           // update new last node in header
  }

  hll->len--;       // decrement the length counter
  return popped;
}



void hll_free(hlinkedlist *hll) {
  // verify if the reference is null
  if (!hll || hll->first == NULL) return;

  struct node *start = hll->first;
  while (start) {
    // take the reference to the node to bel deleted
    struct node *todel = start;

    start = start->next;

    // free the node
    hll_free_node(todel);
  }

  // finally free the hlinked list (head node)
  free(hll);
}



void hll_print(hlinkedlist *hll) {
  if (!hll) return;
  
  printf("\nlength: %d [", hll->len);

  struct node *curr  =  hll->first;
  while (curr) {
    switch (curr->ele.etype) {
      case INT: printf("%d", curr->ele.value.ival); break;
      case FLO: printf("%f", curr->ele.value.fval); break;
      case STR: printf("\"%s\"", curr->ele.value.sval); break;
    }
    // update curr ref to point to next node
    curr = curr->next;

    if (curr) printf(", ");
  }

  printf("]\n");
}



/* ***** UTIL FUNCTION DEFINITIONS ***** */


struct node* hll_node_create_update(enum element_type etype, void *val) {
  // create a node
  struct node *n = malloc(sizeof(struct node));
  if (!n) return NULL;

  // initilize with value
  n->next = NULL;

  // update the node with value
  switch (etype) {
    case INT: n->ele.value.ival = *(int *)val; break;

    case FLO: n->ele.value.fval = *(float *)val; break;

    case STR: 
      n->ele.value.sval = strdup((char *) val);
      if (!n->ele.value.sval) {
        fprintf(stderr, "Cannot duplicate string");
        free(n);
        return NULL;
      }
      break;
 
    default:
      free(n);        // free the node, if type is invalid
      return false;
  }

  n->ele.etype = etype;   // finally update the element type in element struct

  return n;
}



struct node* hll_get_node(hlinkedlist *hll, int pos) {
  if (!hll || pos < 0 || pos >= hll->len) return NULL;

  struct node *curr = hll->first;
  int cpos = 0;

  while (curr) {
    if (cpos == pos) return curr;

    // update to continue the loop
    curr = curr->next;
    cpos++;
  }

  // if we reached here, then something wrong happened
  return NULL;
}



void hll_free_node(struct node *n) {
  if (!n) return;

  // if node contains a string data, then free it 
  if (n->ele.etype == STR) free(n->ele.value.sval);

  free(n);
}