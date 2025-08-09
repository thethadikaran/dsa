#include "cqueue.h"


cqueue_t* cq_init() {
  cqueue_t *cq = malloc(sizeof(cqueue_t));
  if (!cq) return NULL;

  cq->first = 0;
  cq->last = 0;
  return cq;
}


element_t* cq_peek(cqueue_t *cq) {
  if (cq_is_empty(cq)) return NULL;
  return cq->data[cq->first];
}



bool cq_is_empty(cqueue_t *cq) {
  return (cq->first == cq->last);
}



bool cq_is_full(cqueue_t *cq) {
  return ( (cq->last + 1) % SIZE ) == cq->first;
}



bool cq_enqueue(cqueue_t *cq, etype_t etype, void *val) {
  if (!cq || cq_is_full(cq)) return false;

  // allocate memeory for element and update the value
  element_t *new_element = cq_new_element(etype, val);
  if (!new_element) return false;

  cq->data[cq->last] = new_element;
  cq->last = (cq->last + 1) % SIZE;     // update the index circularly
  return true;
}



element_t* cq_dequeue(cqueue_t *cq) {
  if (!cq || cq_is_empty(cq)) return NULL;

  element_t *popped_element = cq->data[cq->first];
  cq->first = (cq->first + 1) % SIZE;  // update the index circularly
  return popped_element;               // caller has to free the memory
}



void cq_free(cqueue_t **cq) {
  if (!cq || !*cq) return;

  while (!cq_is_empty(*cq)) {
    element_t *element = cq_dequeue(*cq);

    if (element->etype == STR) free(element->value.sval);

    free(element);
  }

  free(*cq);
  *cq = NULL;
}


/* ---------- UTIL FUNCTIONS ---------- */

element_t* cq_new_element(etype_t etype, void *val) {
  if (!val) return NULL;

  // allocate memory for new element_t
  element_t *element = malloc(sizeof(element_t));
  if (!element) return NULL;

  switch (etype) {
    case INT: element->value.ival = *(int *)val; break;

    case FLO: element->value.fval = *(float *)val; break;

    case STR: {
      element->value.sval = strdup( (char *)val );
      if (!element->value.sval) {
        free(element);
        return NULL;
      }
      break;
    }

    default:     // invalid element type
      free(element);
      return NULL;
  }

  element->etype = etype;  // update the element type;
  return element;
}