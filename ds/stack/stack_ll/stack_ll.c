#include "stack_ll.h"


stack_ll_t* sll_init() {
  stack_ll_t *sll = malloc(sizeof(stack_ll_t));
  if (!sll) return NULL;

  // set the initializer values
  sll->size = 0;
  sll->top = NULL;
  return sll;
}



bool sll_push(stack_ll_t *sll, etype_t etype, void *val) {
  if (!sll || !val) return false;

  // let's create a new node and update it with the value
  node_t *new_node = sll_new_node(etype, val);
  if (!new_node) return false;

  new_node->next = sll->top;  // update new first node's next ref to old first node
  sll->top = new_node;        // update top to the new first node
  sll->size++;
  return true;
}



node_t* sll_pop(stack_ll_t *sll) {
  if (!sll || sll_is_empty(sll)) return NULL;

  node_t *pop_node = sll->top;   // take a ref of the first node to be removed
  sll->top = pop_node->next;     // update the top with the next element in the list
  sll->size--;                   // finally decrement the node count

  return pop_node;   // caller must release the memory of the node
}



node_t* sll_peek(stack_ll_t *sll) {
  if (!sll || sll_is_empty(sll)) return NULL;
  return sll->top;
}



bool sll_is_empty(stack_ll_t *sll) {
  return (sll->top == NULL);
}



void sll_free(stack_ll_t **sll) {
  if (!sll || !*sll) return;

  while (!sll_is_empty(*sll)) {
    node_t *todel = sll_pop(*sll);

    // for string data, release memory explicitly
    if (todel->data.etype == STR) free(todel->data.value.sval);

    free(todel);
  }

  // finallly release the stack 
  free(*sll);
  *sll = NULL;
}


/* ---------- UTIL FUNCTIONS ---------- */


node_t* sll_new_node(etype_t etype, void *val) {
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



void sll_print(stack_ll_t *sll) {
  if (!sll || sll_is_empty(sll)) {
    puts("[]");
    return;
  }

  printf("\n[");
  node_t *curr = sll->top;
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