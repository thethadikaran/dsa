#include "dlinked_list.h"



dlinkedlist_t* dll_init() {
  dlinkedlist_t *dll = malloc(sizeof(dlinkedlist_t));
  if (!dll) return NULL;

  // initialize the value
  dll->head = NULL;
  return dll;
}



bool dll_append(dlinkedlist_t *dll, etype_t etype, void *val) {
  if (!dll || !val) return false;

  // creat a node and update it with the value
  node_t *new_node = dll_new_node(etype, val);
  if (!new_node) return false;

  // double linked list has no nodes
  if (dll->head == NULL) {
    dll->head = new_node;
    return true;
  }

  // double linked list has nodes
  node_t *last_node = dll_last_node(dll);
  if (!last_node) {
    dll_free_node(new_node);    // free the memory of the new node
    return false;
  }

  last_node->next = new_node;   // update the next node ref in last node
  new_node->prev = last_node;   // update the prev node ref in new last node
  return true;
}



bool dll_insert(dlinkedlist_t *dll, int idx, etype_t etype, void *val) {
  if (!dll || !val || idx < 0) return false;

  // linked list has no nodes
  if (dll->head == NULL) {
    // then idx must be zero, as element can be added at initial position only
    if (idx == 0) 
      return dll_append(dll, etype, val);
    else 
      return false;
  }

  // create a new node and update it with value
  node_t *new_node = dll_new_node(etype, val);
  if (!new_node) return false;

  // insertion at the head position
  if (idx == 0) {
    dll->head->prev = new_node;  // update the second node's prev address
    new_node->next = dll->head;  // update new node with the next node ref

    dll->head = new_node;        // finally update the head node with new node
    return true;
  }

  // get the node, which is at the insert positon
  node_t *idx_node = dll_get(dll, idx);
  if (!idx_node) {
    dll_free_node(new_node);
    return false;
  }

  // insert the new node by moving the idx node right
  new_node->prev = idx_node->prev;      // update the new node's prev ref
  new_node->next = idx_node;            // update the new node's next ref
  idx_node->prev = new_node;            // update the idx node's prev ref
  return true;
}



node_t* dll_get(dlinkedlist_t *dll, int idx) {
  if (!dll || idx < 0) return NULL;

  node_t *curr = dll->head;

  // loop till i equals index and return the node at that position
  for (int i = 0; curr != NULL; i++, curr = curr->next) {
    if (i == idx) return curr;
  }

  // if we reached here, then invalid index is given
  return NULL;
}



int dll_count(dlinkedlist_t *dll, etype_t etype, void *val) {
  if (!dll || !dll->head || !val) return 0;

  node_t *curr = dll->head;
  int freq = 0;

  while (curr) {
    switch (etype) {
      case INT:
        freq += curr->data.value.ival == *(int *)val ? 1 : 0;
        break;

      case FLO:
        freq += curr->data.value.fval == *(float *)val ? 1 : 0;
        break;

      case STR:
        freq += strcmp(curr->data.value.sval, (char *)val) == 0 ? 1 : 0;
        break;

      default:
        return 0;
    }
    curr = curr->next;
  }
  return freq;
}



int dll_index(dlinkedlist_t *dll, etype_t etype, void *val) {
  if (!dll || !dll->head || !val) return -1;

  node_t *curr = dll->head;
  for (int i = 0; curr != NULL; i++, curr = curr->next) {
    switch (etype) {
      case INT: {
        if (curr->data.value.ival == *(int *)val) return i;
        break;
      }

      case FLO: {
        if (curr->data.value.fval == *(float *)val) return i;
        break;
      }

      case STR: {
        if (strcmp(curr->data.value.sval, (char *)val) == 0) return i;
        break;
      }

      default:
        // invalid element type found
        return -1;
    }
  }
  return -1;
}



node_t* dll_pop(dlinkedlist_t *dll) {
  if (!dll || !dll->head) return NULL;

  // only one node present in the linked list
  if (dll->head->next == NULL) {
    node_t* pop_node = dll->head;

    dll->head = NULL;
    return pop_node;   // user has to take care of freeing the node's memory
  }

  node_t *last_node = dll_last_node(dll);  // get the last node
  last_node->prev->next = NULL;            // update the second to last node's next reference 

  return last_node;    // user has to take care of freeing the node's memory
}



int dll_size(dlinkedlist_t *dll) {
  if (!dll || !dll->head) return 0;

  int len = 0;
  node_t *curr = dll->head;

  while (curr != NULL) {
    len++;
    curr = curr->next;
  }

  return len;
}


bool dll_remove(dlinkedlist_t *dll, etype_t etype, void *val) {
  if (!dll || !dll->head || !val) return false;

  node_t *curr = dll->head;
  bool is_match = false;

  while (curr) {
    switch (etype) {
      case INT:
        is_match = ( curr->data.value.ival == *(int *)val );
        break;

      case FLO:
        is_match = ( curr->data.value.fval == *(float *)val );
        break;

      case STR:
        is_match =  ( strcmp(curr->data.value.sval, (char *)val) == 0 );
        break;

      default: return false;    // invalid element type
    }

    // we got a match
    if (is_match) {
      // if it's  head node
      if (curr->prev == NULL) { 
        dll->head = curr->next;   // update the head to point to next node
        if (dll->head) dll->head->prev = NULL;
      }
      else {
        // if it's not a head node
        curr->prev->next = curr->next; // update prev node's next ref to curr's next node
        curr->next->prev = curr->prev; // update next node's prev ref to curr's prev node
      }
      dll_free_node(curr);
      return true;
    }
    curr = curr->next;       // update the pointers to continue the loop
  }
  // if we reach here, then no matching value is found
  return false;
}



void dll_reverse(dlinkedlist_t *dll) {
  node_t *tmp = NULL;
  node_t *curr = dll->head;

  while (curr) {
    // swap the prev and next pointer reference in all the nodes
    node_t *tmp = curr->next;
    curr->next = curr->prev;
    curr->prev = tmp;

    curr = tmp;
  }

  if (tmp) 
    dll->head = tmp->prev; // update head to the new first node
}



void dll_print(dlinkedlist_t *dll) {
  if (!dll) return;

  node_t *curr = dll->head;
  printf("[");

  while (curr != NULL) {
    switch (curr->data.etype) {
      case INT: printf("%d", curr->data.value.ival); break;
      case FLO: printf("%f", curr->data.value.fval); break;
      case STR: printf("\"%s\"", curr->data.value.sval); break;
      default: return;    // invalid element type
    }
    curr = curr->next;

    if (curr) printf(", ");
  }
  printf("]\n");
}



void dll_free(dlinkedlist_t *ll) {
  if (!ll) return;

  node_t *curr = ll->head;

  while (curr) {
    node_t *todel = curr;    // note the reference of the node to be freed
    curr = curr->next;       // update the curr to next node

    dll_free_node(todel);
  }

  // finally free the linkedlist_t struct
  free(ll);
}



/* ---------- UTIL FUNCTIONS ---------- */

node_t* dll_new_node(etype_t etype, void *val) {
  node_t *new_node = malloc(sizeof(node_t));
  if (!new_node) return NULL;

  // initialize with values
  new_node->next = NULL;
  new_node->prev = NULL;

  switch (etype) {
    case INT:
      // typecast void pointer to int pointer (int *) and then de-reference *
      new_node->data.value.ival = *(int *)val;
      break;

    case FLO: 
      new_node->data.value.fval = *(float *)val; 
      break;

    case STR: {
      new_node->data.value.sval = strdup( (char *)val );
      if (!new_node->data.value.sval) {
        dll_free_node(new_node);
        return NULL;
      }
      break;
    }

    default:
      // if we reach here, then invalid etype is passed in
      // release the memory of new node and return
      dll_free_node(new_node);
      return NULL;
  }
  new_node->data.etype = etype;  // update the value type
  return new_node;
}



node_t* dll_last_node(dlinkedlist_t *dll) {
  if (!dll || !dll->head) return NULL;

  node_t *curr = dll->head;

  // loop until the last element is reached
  while (curr->next != NULL) curr = curr->next;

  return curr;
}



void dll_free_node(node_t *n) {
  if (!n) return;

  // if node's value is string, then free it
  if (n->data.etype == STR) free(n->data.value.sval);

  // free the node
  free(n);
}