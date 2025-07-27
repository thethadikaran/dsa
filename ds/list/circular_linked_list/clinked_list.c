#include "clinked_list.h"


clinkedlist_t* cll_init() {
  clinkedlist_t *cll = malloc(sizeof(clinkedlist_t));
  if (!cll) return NULL;

  cll->head = NULL;
  return cll;
}



bool cll_append(clinkedlist_t *cll, etype_t etype, void *val) {
  if (!cll || !val) return false;

  // create a node and update it with the value
  node_t *new_node = cll_new_node(etype, val);
  if (!new_node) return false;

  // does the circlar linked list is empty?
  if (!cll->head) {
    // in circular linked list, the last node's next points to first node
    // as we have only one node, the next ref points to itself
    new_node->next = new_node;

    cll->head = new_node;
    return true;
  }

  new_node->next = cll->head->next;  // update new node with the first node
  cll->head->next = new_node;        // add the node at the end of the chain
  cll->head = new_node;              // update the head to point the new last node
  return true;
}



node_t* cll_get(clinkedlist_t *cll, int idx) {
  if (!cll || !cll->head || idx < 0) return NULL;

  int pos = 0;
  node_t *curr = cll->head->next;    // as head points to last node

  do {
    if (pos == idx) return curr;

    curr = curr->next;
    pos++;
  } while (curr != cll->head->next);

  // if we reach here, invalid idx is passed in
  return NULL;
}



bool cll_insert(clinkedlist_t *cll, int idx, etype_t etype, void *val) {
  if (!cll || !val || idx < 0) return false;

  // linked list is empty
  if (cll->head == NULL) {
    // then the insert position should be zero, other values are not permitted
    if (idx != 0) return false;

    return cll_append(cll, etype, val);
  }

  // creat a new node and update with value
  node_t *new_node = cll_new_node(etype, val);
  if (!new_node) return false;

  // linked list not empty: insertion at the beginning 
  if (idx == 0) {
    new_node->next = cll->head->next;   // update new node's next ref to prev first node
    cll->head->next = new_node;         // update last node's next ref to new first node
    return true;
  }

  // get the node; one before the idx positon
  node_t *prev_node = cll_get(cll, idx - 1);
  if (!prev_node) {
    cll_free_node(new_node);
    return false;
  }

  // insertion at the last
  if (prev_node == cll->head) {
    new_node->next = cll->head->next;  // update new nodes next ref to first node
    cll->head->next = new_node;        // update prev last node next ref to new last node
    cll->head = new_node;              // update head to point to new last node
    return true;
  }

  // insertion in-between
  new_node->next = prev_node->next;
  prev_node->next = new_node;
  return true;
}



int cll_count(clinkedlist_t *cll, etype_t etype, void *val) {
  if (!cll || !cll->head || !val) return 0;

  node_t *curr = cll->head->next;
  int freq = 0;

  do {
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
  } while (curr != cll->head->next);
  return freq;
}



int cll_index(clinkedlist_t *cll, etype_t etype, void *val) {
  if (!cll || !cll->head || !val) return -1;

  node_t *curr = cll->head->next;
  int idx = 0;

  do {
    switch (etype) {
      case INT: {
        if (curr->data.value.ival == *(int *)val) return idx;
        break;
      }

      case FLO: {
        if (curr->data.value.fval == *(float *)val) return idx;
        break;
      }

      case STR: {
        if (strcmp(curr->data.value.sval, (char *)val) == 0) return idx;
        break;
      }

      default:   // invalid element type found
        return -1;
    }

    idx++;
    curr = curr->next;
  } while (curr != cll->head->next);
  return -1;
}



node_t* cll_pop(clinkedlist_t *cll) {
  if (!cll || !cll->head) return NULL;

  node_t *pop_node = cll->head;

  // if only one node is present
  if (pop_node->next == pop_node) {
    cll->head = NULL;
  } 
  else {
    node_t *curr = cll->head->next;

    // get one node befoe the last node
    while (curr->next != pop_node)
      curr = curr->next;

    curr->next = pop_node->next;   // update prev node to point to first node
    cll->head = curr;              // update head to new prev node
  }            
  return pop_node;
}



bool cll_remove(clinkedlist_t *cll, etype_t etype, void *val) {
  if (!cll || !val || !cll->head) return false;

  node_t *curr = cll->head->next;
  node_t *prev = NULL;

  do {
    bool is_match = false;

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

    if (is_match) {
      if (!prev) {
        // value is present in FIRST NODE

        if (curr == curr->next) cll->head = NULL;   // one node in linked list
        else cll->head->next = curr->next;          // update last node to point to new first node
      }
      else if (curr == cll->head) {
        // value is present in LAST NODE

        prev->next = curr->next;  // update new last node's next ref to first node
        cll->head = prev;         // update head node with new last node
      }
      else {
        // value is present IN-BETWEEN the linked list

        prev->next  = curr->next; // update prev node's next ref with curr next ref
      }

      // free the node to be removed
      cll_free_node(curr);
      return true;
    }

    prev = curr;
    curr = curr->next;
  } while (curr != cll->head->next);

  // if we reach here, then either no node matches the value
  return false;
}



int cll_size(clinkedlist_t *cll) {
  if (!cll || !cll->head) return 0;

  int size = 0;
  node_t* curr = cll->head->next;

  do {
    size++;
    curr = curr->next;
  } while (curr != cll->head->next);

  return size;
}



void cll_free(clinkedlist_t *cll) {
  if (!cll) return;
  if (!cll->head) { free(cll); return; }

  node_t *curr = cll->head->next;
  node_t *start = curr;

  do {
    node_t *todel = curr;
    curr = curr->next;
    cll_free_node(todel);
  } while (curr != start);

  // finally free the linkedlist_t struct
  free(cll);
}


/* ---------- UTIL FUNCTIONS ---------- */

void cll_print(clinkedlist_t *cll) {
  if (!cll || !cll->head) { puts("[]"); return; }

  node_t *curr = cll->head->next;
  printf("[");

  do {
    switch (curr->data.etype) {
      case INT: printf("%d", curr->data.value.ival); break;
      case FLO: printf("%f", curr->data.value.fval); break;
      case STR: printf("\"%s\"", curr->data.value.sval); break;
      default: return;    // invalid element type
    }
    curr = curr->next;

    if (curr != cll->head->next) printf(", ");
  } while (curr != cll->head->next);
  printf("]\n");
}



node_t* cll_new_node(etype_t etype, void *val) {
  if (!val) return NULL;

  node_t *new_node = malloc(sizeof(node_t));
  if (!new_node) return NULL;

  // update the node with the value
  new_node->next = NULL;

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
        cll_free_node(new_node);
        return NULL;
      }
      break;
    }

    default:
      // if we reach here, then invalid etype is passed in
      // release the memory of new node and return
      cll_free_node(new_node);
      return NULL;
  }
  new_node->data.etype = etype;  // update the value type

  return new_node;
}



void cll_free_node(node_t *n) {
  if (!n) return;

  // if node's value is string, then free it
  if (n->data.etype == STR) free(n->data.value.sval);

  // free the node
  free(n);
}