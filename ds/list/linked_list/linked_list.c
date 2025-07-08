#include "linked_list.h"


linkedlist_t* ll_init() {
  linkedlist_t *ll = malloc(sizeof(linkedlist_t));
  if (!ll) return NULL;

  // initialize the linkedlist
  ll->head = NULL;

  return ll;
}



bool ll_append(linkedlist_t *ll, etype_t etype, void *val) {
  if (!ll || !val) return false;

  // create node and update it with the value
  node_t *new_node = ll_new_node(etype, val);
  if (!new_node) return false;

  // linked list has no nodes
  if (ll->head == NULL) {
    ll->head = new_node;
    return true;
  }

  // linked list has nodes
  node_t *last_node = ll_last_node(ll);
  if (!last_node) {
    ll_free_node(new_node);      // release the memory of new node
    return false;
  }

  last_node->next = new_node;
  return true;
}



bool ll_insert(linkedlist_t *ll, int idx, etype_t etype, void *val) {
  if (!ll || !val || idx < 0) return false;

  // linked list has no nodes
  if (ll->head == NULL) {
    // then idx must be zero, as element can be added at initial position only
    if (idx == 0) 
      return ll_append(ll, etype, val);
    else 
      return false;
  }

  // create a new node and update it with value
  node_t *new_node = ll_new_node(etype, val);
  if (!new_node) return false;

  // insertion at the head position
  if (idx == 0) {
    new_node->next = ll->head;
    ll->head = new_node;
    return true;
  }

  // get the node; one before the idx position
  node_t *idx_node = ll_get(ll, idx - 1);
  if (!idx_node) return false;

  // link the new node after the idx node
  new_node->next = idx_node->next;
  idx_node->next = new_node;
  return true;
}



node_t* ll_get(linkedlist_t *ll, int idx) {
  if (!ll || idx < 0) return NULL;

  node_t *head = ll->head;

  // loop till i equals index and return the node at that position
  for (int i = 0; head != NULL; i++, head = head->next) {
    if (i == idx) return head;
  }

  // if we reached here, then invalid index is given
  return NULL;
}



int ll_count(linkedlist_t *ll, etype_t etype, void *val) {
  if (!ll || !ll->head || !val) return 0;

  node_t *head = ll->head;
  int freq = 0;

  while (head) {
    switch (etype) {
      case INT:
        freq += head->data.value.ival == *(int *)val ? 1 : 0;
        break;

      case FLO:
        freq += head->data.value.fval == *(float *)val ? 1 : 0;
        break;

      case STR:
        freq += strcmp(head->data.value.sval, (char *)val) == 0 ? 1 : 0;
        break;

      default:
        return 0;
    }

    head  = head->next;
  }
  return freq;
}



int ll_index(linkedlist_t *ll, etype_t etype, void *val) {
  if (!ll || !ll->head || !val) return -1;

  node_t *head = ll->head;
  for (int i = 0; head != NULL; i++, head = head->next) {
    switch (etype) {
      case INT: {
        if (head->data.value.ival == *(int *)val) return i;
        break;
      }

      case FLO: {
        if (head->data.value.fval == *(float *)val) return i;
        break;
      }

      case STR: {
        if (strcmp(head->data.value.sval, (char *)val) == 0) return i;
        break;
      }

      default:
        // invalid element type found
        return -1;
    }
  }
  return -1;
}



node_t* ll_pop(linkedlist_t *ll) {
  if (!ll || !ll->head) return NULL;

  // only one node present in the linked list
  if (ll->head->next == NULL) {
    node_t* pop_node = ll->head;

    ll->head = NULL;
    return pop_node;   // user has to take care of freeing the node's memory
  }

  node_t *head = ll->head;
  // get one node before the last node
  while (head->next->next != NULL) 
    head = head->next;

  // update the second to last node's next reference 
  node_t *pop_node = head->next;
  head->next = NULL;
  return pop_node;    // user has to take care of freeing the node's memory
}



bool ll_remove(linkedlist_t *ll, etype_t etype, void *val) {
  if (!ll || !ll->head || !val) return false;

  node_t *curr = ll->head;
  node_t *prev = NULL;
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
      if (prev) {
        // value is in the middle or end
        prev->next = curr->next;
      }
      else {
        // value is at the head position
        ll->head = curr->next;
      }

      ll_free_node(curr);
      return true;      
    }

    // update the pointers to continue the loop
    prev = curr;
    curr = curr->next;
  }
  return false;
}



void ll_reverse(linkedlist_t *ll) {
  if (!ll || !ll->head) return;

  node_t *prev = NULL;
  node_t *curr = ll->head;
  node_t *next = NULL;

  while (curr) {
    next = curr->next;    // take a copy of the next node
    curr->next = prev;    // update the curr node's next to prev node

    prev = curr;
    curr = next;
  }

  // finally update the head with the new node
  ll->head = prev;
}



int ll_size(linkedlist_t *ll) {
  if (!ll || !ll->head) return 0;

  int len = 0;
  node_t *head = ll->head;

  while (head != NULL) {
    len++;
    head = head->next;
  }

  return len;
}



void ll_print(linkedlist_t *ll) {
  if (!ll) return;

  node_t *curr = ll->head;
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



void ll_free(linkedlist_t *ll) {
  if (!ll) return;

  node_t *head = ll->head;

  while (head) {
    node_t *todel = head;    // note the reference of the node to be freed
    head = head->next;       // update the head to next node

    ll_free_node(todel);
  }

  // finally free the linkedlist_t struct
  free(ll);
}


/* ---------- UTIL FUNCTIONS ---------- */

node_t* ll_new_node(etype_t etype, void *val) {
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
        ll_free_node(new_node);
        return NULL;
      }
      break;
    }

    default:
      // if we reach here, then invalid etype is passed in
      // release the memory of new node and return
      ll_free_node(new_node);
      return NULL;
  }
  new_node->data.etype = etype;  // update the value type

  return new_node;
}



node_t* ll_last_node(linkedlist_t *ll) {
  if (!ll || !ll->head) return NULL;

  node_t *head = ll->head;

  // loop until the last element is reached
  while (head->next != NULL) head = head->next;

  return head;
}



void ll_free_node(node_t *n) {
  if (!n) return;

  // if node's value is string, then free it
  if (n->data.etype == STR) free(n->data.value.sval);

  // free the node
  free(n);
}