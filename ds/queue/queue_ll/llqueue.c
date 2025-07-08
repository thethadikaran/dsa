#include "llqueue.h"


llqueue* llq_init() {
  struct llqueue *llq = malloc(sizeof(struct llqueue));
  if (!llq) return NULL;

  // initialize the memebers with the values
  llq->front = NULL;
  llq->rear = NULL;
  llq->size = 0;

  return llq;
}



bool llq_enqueue(llqueue *llq, enum element_type etype, void *val) {
  // create an element and update it with value
  struct node *new_node = llq_create_node(etype, val);
  if (!new_node) return false;

  // if the queue contains no element
  if (llq_is_empty(llq)) {
    llq->front = new_node;   // update new node in both front and rear reference
    llq->rear = new_node;
  } 
  else {
    // if queue already contain elelemts, then udpate the rear part
    llq->rear->next = new_node;  // add new node to prev rear node's next ref
    llq->rear = new_node;        // update new node as rear node
  }

  llq->size++;   // update the node's count
  return true;
}



struct node* llq_dequeue(llqueue *llq) {
  if (llq_is_empty(llq)) return NULL;

  struct node *popped = llq->front; // make reference of the front element
  llq->front = popped->next;        // update the next element as first node;

  llq->size--;

  if (llq->size == 0)
    llq->rear == NULL;   // update the rear if the queue is empty

  return popped;         // caller is expected to free the memeory
}



struct node* llq_peek(llqueue *llq) {
  if (llq_is_empty(llq)) return NULL;

  return llq->front;
}



bool llq_is_empty(llqueue *llq) {
  return (!llq || llq->front == NULL);
}



int llq_size(llqueue *llq) {
  return llq->size;
}



void llq_free(llqueue *llq) {
  if (!llq) return;

  while (!llq_is_empty(llq)) {
    struct node *todel = llq_dequeue(llq);
    free(todel);
  }

  // finally free the memeory of llqueue
  free(llq);
}



/* ===================================== */
/* ***** UTIL FUNCTION DEFINITIONS ***** */
/* ===================================== */

struct node* llq_create_node(enum element_type etype, void *val) {
  if (!val) return NULL;

  // allocate memory for a Node
  struct node *new_node = malloc(sizeof(struct node));
  if (!new_node) return NULL;

  new_node->next = NULL;          // initilize next to NULL

  // allocate memory for a Element
  new_node->data = malloc(sizeof(struct element));
  if (!new_node->data) {
    free(new_node);
    return NULL;
  }

  // update the element with the value
  switch (etype) {
    case INT: new_node->data->value.ival = *(int *)val; break;

    case FLO: new_node->data->value.fval = *(float *)val; break;

    case STR: {
      new_node->data->value.sval = strdup( (char *)val );
      if (!new_node->data->value.sval) {
        llq_free_node(new_node);
        return NULL;
      }
      break;
    }

    default: {
      // for invalid value type, release the node & element memory
      // allocation and return
      llq_free_node(new_node);
      return NULL;
    }
  }

  return new_node;
}



void llq_free_node(struct node *n) {
  if (n) {
    if (n->data) {
      if (n->data->etype == STR) 
        free(n->data->value.sval); // free string value if it's a string

      free(n->data); // free the element
    }
    free(n); // free the node
  }
}



void llq_print(llqueue *llq) {
  if (llq_is_empty(llq)) {
    printf("[]");
    return;
  }

  struct node *current = llq->front; // Start from the front of the queue
  printf("Queue contents:\n");

  while (current != NULL) {
    switch (current->data->etype) {
      case INT:
          printf("INT: %d\n", current->data->value.ival);
          break;
      case FLO:
          printf("FLOAT: %.2f\n", current->data->value.fval);
          break;
      case STR:
          printf("STRING: %s\n", current->data->value.sval);
          break;
      default:
          printf("UNKNOWN TYPE\n");
          break;
    }
    current = current->next; // Move to the next node
  }
}