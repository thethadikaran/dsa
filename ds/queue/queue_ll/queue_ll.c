#include "queue_ll.h"


queue_ll_t* qll_init() {
  queue_ll_t *qll = malloc(sizeof(queue_ll_t));
  if (!qll) return NULL;

  // initilize with default values
  qll->size = 0;
  qll->first = NULL;
  qll->last = NULL;
  return qll;
}



bool qll_enqueue(queue_ll_t *qll, etype_t etype, void *val) {
  if (!qll || !val) return false;

  // create a node and update it with the value
  node_t *new_node = qll_new_node(etype, val);
  if (!new_node) return false;

  // the queue is empty
  if (qll_is_empty(qll)) {
    qll->first = new_node;
    qll->last = new_node;
  } else {
    // queue is not empty, then update the last pointer alone
    qll->last->next = new_node;   // update old last node next ref to new last node
    qll->last = new_node;         // update the new last node
  }

  // finally increment the size and return
  qll->size++;
  return true;
}



node_t* qll_dequeue(queue_ll_t *qll) {
  if (!qll || qll_is_empty(qll)) return NULL;

  node_t *popped_node = qll->first;  // copy the ref of node to be removed
  qll->first = popped_node->next;    // update first with next node in list

  qll->size--;

  // check if the queue is empty, if so, update the last pointer too
  if (qll->size == 0) qll->last = NULL;

  return popped_node;
}



node_t* qll_peek(queue_ll_t *qll) {
  if (!qll || qll_is_empty(qll)) return NULL;

  return qll->first;
}



bool qll_is_empty(queue_ll_t *qll) {
  return (!qll || qll->first == NULL);
}



int qll_size(queue_ll_t *qll) {
  return qll->size;
}



void qll_free(queue_ll_t **qll) {
  if (!qll || !*qll) return;

  while (!qll_is_empty(*qll)) {
    node_t *todel = qll_dequeue(*qll);
    
    if (todel->data.etype == STR) free(todel->data.value.sval);

    free(todel);
  }

  // finally free the queue_ll_t struct and make it as NULL
  free(*qll);
  *qll = NULL;
}


/* ---------- UTIL FUNCTIONS ---------- */

node_t* qll_new_node(etype_t etype, void *val) {
  if (!val) return NULL;

  // allocate memory for a Node
  node_t *new_node = malloc(sizeof(node_t));
  if (!new_node) return NULL;

  new_node->next = NULL;          // initilize next to NULL

  // update the element with the value
  switch (etype) {
    case INT: new_node->data.value.ival = *(int *)val; break;

    case FLO: new_node->data.value.fval = *(float *)val; break;

    case STR: {
      new_node->data.value.sval = strdup( (char *)val );
      if (!new_node->data.value.sval) {
        free(new_node);
        return NULL;
      }
      break;
    }

    default: {    // invalid value type
      free(new_node);
      return NULL;
    }
  }

  new_node->data.etype = etype;  // update the element type
  return new_node;
}



void qll_print(queue_ll_t *qll) {
  if (!qll || qll_is_empty(qll)) {
    puts("[]");
    return;
  }

  printf("\n[");
  node_t *curr = qll->first;
  while (curr) {
    switch(curr->data.etype) {
      case INT: printf("%d", curr->data.value.ival); break;
      case FLO: printf("%f", curr->data.value.fval); break;
      case STR: printf("\"%s\"", curr->data.value.sval); break;
    }

    curr = curr->next;
    if (curr) printf(", ");
  }

  printf("]\n");
}