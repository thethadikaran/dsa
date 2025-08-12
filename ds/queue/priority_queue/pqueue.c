#include "pqueue.h"


priority_queue_t* pq_init() {
  priority_queue_t* pq = malloc(sizeof(priority_queue_t));
  if (!pq) return NULL;

  pq->first = NULL;
  pq->last = NULL;
  pq->size = 0;
  return pq;
}



bool pq_enqueue(priority_queue_t *pq, etype_t etype, void *val, int priority) {
  if (!pq || !val) return false;

  // create a node and update it with values
  node_t *new_node = pq_new_node(etype, val, priority);
  if (!new_node) return false;

  if (pq_is_empty(pq)) {                       // new node
    pq->first = new_node;
    pq->last = new_node;
  } 
  else if (priority < pq->first->priority) {   // insert at first
    new_node->next = pq->first;
    pq->first = new_node;
  }
  else if (priority >= pq->last->priority) {   // insert at last
    pq->last->next = new_node;
    pq->last = new_node;
  } 
  else {                                       // insert at b/w nodes
    node_t* curr = pq->first;
    node_t* prev = NULL;

    // find the positon to insert the new value
    while (curr != NULL && curr->priority <= priority) {
      prev = curr;
      curr = curr->next;
    }

    new_node->next = curr;
    prev->next = new_node;
  }

  pq->size++;   // finally increment the size
  return true;
}



node_t* pq_dequeue(priority_queue_t *pq) {
  if (!pq || pq_is_empty(pq)) return NULL;

  node_t* pop_node = pq->first;
  pq->first = pq->first->next;
  pq->size--;

  return pop_node;    // caller has to free the memeory
}



node_t* pq_peek(priority_queue_t *pq) {
  if (!pq || pq_is_empty(pq)) return NULL;

  return pq->first;
}



bool pq_is_empty(priority_queue_t *pq) {
  if (!pq) return false;

  return pq->first == NULL;
}



int pq_size(priority_queue_t *pq) {
  if (!pq) return -1;

  return pq->size;
}



void pq_free(priority_queue_t **pq) {
  if (!pq || !*pq) return;

  while (!pq_is_empty(*pq)) {
    node_t* todel = pq_dequeue(*pq);

    if (todel->data.etype == STR) free(todel->data.value.sval);

    free(todel);
  }

  free(*pq);
  *pq = NULL;
}


/* ---------- UTIL FUNCTIONS ---------- */

node_t* pq_new_node(etype_t etype, void *val, int priority) {
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
  new_node->priority = priority;
  return new_node;
}

