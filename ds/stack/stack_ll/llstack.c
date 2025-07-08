#include "llstack.h"


llstack* llstack_init() {
  llstack *lls = malloc(sizeof(llstack));
  if (!lls) {
    fprintf(stderr, "Cannot allocate memory");
    return NULL;
  }

  // initililze with values
  lls->count = 0;
  lls->top = NULL;
  return lls;
}



bool llstack_push(llstack *lls, enum element_type etype, void *val) {
  if (!val) return false;

  // create a node and update it with the value
  struct node *new_node = llstack_create_node(etype, val);
  if (!new_node) return false;

  // each new nodes will be added at the first element of the
  // linked chain (which will be denoted as top)
  new_node->next = lls->top;    // update next ref in new node
  lls->top = new_node;          // update top with new node
  lls->count++;                 // update node's count
  return true;
}



struct node* llstack_pop(llstack *lls) {
  if (is_llstack_empty(lls)) {
    fprintf(stderr, "Stack Underflow");
    return NULL;
  }

  struct node *popped = lls->top;   // mark the top element to be popped

  lls->top = popped->next;          // update the next node as top node
  lls->count--;

  return popped;    // caller is expected to free the memeory
}



struct node* llstack_peek(llstack *lls) {
  if (is_llstack_empty(lls)) {
    fprintf(stderr, "Stack Underflow");
    return NULL;
  }

  return lls->top;
}



void llstack_free(llstack *lls) {
  if (!lls | is_llstack_empty(lls)) return;

  while (!is_llstack_empty(lls)) {
    struct node *tmp = llstack_pop(lls);
    llstack_free_node(tmp);
  }

  // finally free the llstack memory
  free(lls);
}


/* ***** UTIL FUNCTION DEFINITIONS ***** */

bool is_llstack_empty(llstack *lls) {
  return (lls->top == NULL);
}



struct node* llstack_create_node(enum element_type etype, void *val) {
  if (!val) return NULL;

  // allocate memory for a Node
  struct node *new = malloc(sizeof(struct node));
  if (!new) return NULL;

  new->next = NULL;          // initilize next to NULL

  // allocate memory for a Element
  new->data = malloc(sizeof(struct element));
  if (!new->data) {
    free(new);
    return NULL;
  }

  // update the element with the value
  switch (etype) {
    case INT: new->data->value.ival = *(int *)val; break;

    case FLO: new->data->value.fval = *(float *)val; break;

    case STR: {
      new->data->value.sval = strdup( (char *)val );
      if (!new->data->value.sval) {
        llstack_free_node(new);
        return NULL;
      }
      break;
    }

    default: {
      // for invalid value type, release the node & element memory
      // allocation and return
      llstack_free_node(new);
      return NULL;
    }
  }

  return new;
}



void llstack_free_node(struct node *n) {
  if (n) {
    if (n->data) {
      if (n->data->etype == STR) 
        free(n->data->value.sval); // Free string value if it's a string

      free(n->data); // Free the element
    }
    free(n); // Free the node
  }
}



void llstack_print(llstack *lls) {
  if (is_llstack_empty(lls)) {
      printf("Stack is empty\n");
      return;
  }

  struct node *current = lls->top;
  printf("Stack contents:\n");
  while (current) {
    switch (current->data->etype) {
      case INT:
          printf("%d\n", current->data->value.ival);
          break;
      case FLO:
          printf("%f\n", current->data->value.fval);
          break;
      case STR:
          printf("%s\n", current->data->value.sval);
          break;
    }
      current = current->next; // Move to the next node
  }
}