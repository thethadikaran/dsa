#include "hlinked_list.h"



dhlinkedlist_t* dhll_init() {
  dhlinkedlist_t *dhll = malloc(sizeof(dhlinkedlist_t));
  if (!dhll) return NULL;

  // initialize with values
  dhll->size = 0;
  dhll->head = NULL;
  dhll->tail = NULL;
  return dhll;
}



bool dhll_append(dhlinkedlist_t *dhll, etype_t etype, void *val) {
  if (!dhll || !val) return false;

  // create a node and update it with the value
  node_t *new_node = dhll_new_node(etype, val);
  if (!new_node) return false;

  // linked list has no nodes
  if (dhll->head == NULL) {
    dhll->head = new_node;  // since we have single node, both tail and
    dhll->tail = new_node;  // head point to the same node
  }
  else {
    // linked list has nodes - then add the new node at the end
    new_node->prev = dhll->tail;  // update new node's prev ref to previous last node
    dhll->tail->next = new_node;  // update previous last node's next ref to point new node
    dhll->tail = new_node;        // finally update the header node to point to new last node
  }

  dhll->size++;      // update the node count
  return true;
}



bool dhll_insert(dhlinkedlist_t *dhll, int idx, etype_t etype, void *val) {
  if (!dhll || !val || idx < 0 || idx > dhll->size) return false;

  // linked list has no nodes or linked list has node, and we need to insert 
  // at the tail of linked list
  if (dhll->head == NULL || idx == dhll->size)
    return dhll_append(dhll, etype, val);

  // create node and update it with the value
  node_t *new_node = dhll_new_node(etype, val);
  if (!new_node) return false;

  if (idx == 0) {
    // if insertion is at beginning of linked list
    new_node->next = dhll->head;
    if (dhll->head) dhll->head->prev = new_node;
    dhll->head = new_node;
  }
  else if (idx == dhll->size) {
    // insertion is at the end of the linked list
    new_node->prev = dhll->tail;  // update new node's prev ref to previous last node
    dhll->tail->next = new_node;  // update previous last node's next ref to point new node
    dhll->tail = new_node;        // finally update the header node to point to new last node
  }
  else {
    // get the node at the insert positon
    node_t *idx_node = dhll_get(dhll, idx);
    if (!idx_node) {
      dhll_free_node(new_node);
      return false;
    }

    // insert the new node by moving the idx_node to right
    new_node->prev = idx_node->prev;   // update new node's prev and next ref
    new_node->next = idx_node;

    if (idx_node->prev) idx_node->prev->next = new_node;

    idx_node->prev = new_node;
  }

  dhll->size++;
  return true;
}



node_t* dhll_get(dhlinkedlist_t *dhll, int idx) {
  if (!dhll || idx < 0 || idx > dhll->size) return NULL;

  node_t *curr = dhll->head;

  // loop till i equals index and return the node at that position
  for (int i = 0; curr != NULL; i++, curr = curr->next) {
    if (i == idx) return curr;
  }

  // if we reached here, then invalid index is given
  return NULL;
}



int dhll_count(dhlinkedlist_t *dhll, etype_t etype, void *val) {
  if (!dhll || dhll->size == 0 || !val) return 0;

  node_t *curr = dhll->head;
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



int dhll_index(dhlinkedlist_t *dhll, etype_t etype, void *val) {
  if (!dhll || dhll->size == 0 || !val) return -1;

  node_t *curr = dhll->head;
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



node_t* dhll_pop(dhlinkedlist_t *dhll) {
  if (!dhll || dhll->size <= 0) return NULL;

  node_t *popped_node = NULL;

  if (dhll->size == 1) {
    // linked list has only one node
    popped_node = dhll->head;

    dhll->head = NULL;
    dhll->tail = NULL;
  }
  else {
    // linked list has many nodes
    popped_node = dhll->tail;

    dhll->tail = dhll->tail->prev;    // update tail to point to previous node
    dhll->tail->next = NULL;          // update prev node's next ref to NULL
  }

  dhll->size--;
  return popped_node;  // user has to take care of freeing the node's memory
}



bool dhll_remove(dhlinkedlist_t *dhll, etype_t etype, void *val) {
  if (!dhll || dhll->size <= 0 || !val) return false;

  node_t *curr = dhll->head;
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
      if (curr == dhll->head) {
        // it's a head node
        dhll->head = curr->next;                   // update head to point to next node   
        if (dhll->head) dhll->head->prev = NULL;   // update the next node's prev ref to NULL
        else dhll->tail = NULL;                    // linked list is empty
      }
      else if (curr == dhll->tail) {
        // it's a tail node
        dhll->tail = curr->prev;                   // update tail to point to one before last node
        if (dhll->tail) dhll->tail->next = NULL;   // update new last node's next ref
        else dhll->head = NULL;                    // linked list is empty
      }
      else {
        // it's a intermittent node
        curr->prev->next = curr->next;  // update prev node's next ref
        curr->next->prev = curr->prev;  // update next node's prev ref
      }
      dhll_free_node(curr);   // finally, free the removed node
      dhll->size--;           // decrement the node's count
      return true;
    }
    curr = curr->next;   // update pointer to continue the loop
  }
  // if we reach here, then no matching element is found
  return false;  
}



void dhll_reverse(dhlinkedlist_t *dhll) {
  if (!dhll || dhll->size <= 0) return;

  node_t *tmp = NULL;
  node_t *curr = dhll->head;

  while (curr) {
    // swap the prev and next pointer reference in all the nodes
    node_t *tmp = curr->next;
    curr->next = curr->prev;
    curr->prev = tmp;

    curr = tmp;
  }

  // swap the head and tail references
  node_t *swp = dhll->head;
  dhll->head = dhll->tail;
  dhll->tail = swp;
}



int dhll_size(dhlinkedlist_t *dhll) {
  return dhll->size;
}



void dhll_print(dhlinkedlist_t *dhll) {
  if (!dhll) return;

  node_t *curr = dhll->head;
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



void dhll_free(dhlinkedlist_t *dhll) {
  if (!dhll) return;

  node_t *curr = dhll->head;

  while (curr) {
    node_t *todel = curr;    // note the reference of the node to be freed
    curr = curr->next;       // update the curr to next node

    dhll_free_node(todel);
  }

  // finally free the linkedlist_t struct
  free(dhll);
}



/* ---------- UTIL FUNCTIONS ---------- */

node_t* dhll_new_node(etype_t etype, void *val) {
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
        dhll_free_node(new_node);
        return NULL;
      }
      break;
    }

    default:
      // if we reach here, then invalid etype is passed in
      // release the memory of new node and return
      dhll_free_node(new_node);
      return NULL;
  }
  new_node->data.etype = etype;  // update the value type
  return new_node;
}



void dhll_free_node(node_t *n) {
  if (!n) return;

  // if node's value is string, then free it
  if (n->data.etype == STR) free(n->data.value.sval);

  // free the node
  free(n);
}

