#include "stack_arr.h"


stack_arr_t* sa_init() {
  stack_arr_t *sa = malloc(sizeof(stack_arr_t));
  if (!sa) return NULL;

  sa->top = -1;   // set the initial value to top
  return sa;
}



bool sa_is_empty(stack_arr_t *sa) {
  return (sa->top == -1);
}



bool sa_is_full(stack_arr_t *sa) {
  // range of stack is from 0 to size - 1
  return (sa->top == SIZE - 1);
}



bool sa_push(stack_arr_t *sa, etype_t etype, void *val) {
  if (!sa || !val || sa_is_full(sa)) return false;

  // allocate memory for element and update it with the value
  element_t *new_element = sa_new_element(etype, val);
  if (!new_element) return false;

  // increment the top and then add the value
  sa->data[++sa->top] = new_element;
  return true;
}



element_t* sa_pop(stack_arr_t *sa) {
  if (!sa || sa_is_empty(sa)) return NULL;

  element_t *top_element = sa->data[sa->top];
  sa->data[sa->top--] = NULL;  // clear the pointer ref for safety

  return top_element;          // caller should release the memory for the element
}



element_t* sa_peek(stack_arr_t *sa) {
  if (!sa || sa_is_empty(sa)) return NULL;

  return sa->data[sa->top];
}



void sa_free(stack_arr_t **sa) {
  if (!*sa) return;

  while (!sa_is_empty(*sa)) {
    element_t *e = sa_pop(*sa);

    // if the element has STR, then release the memory of it first
    if (e->etype == STR) free(e->value.sval);

    free(e);
  }

  // finally free the stack_arr_t struct
  free(*sa);
  *sa = NULL;  
}



/* ---------- UTIL FUNCTIONS ---------- */

element_t* sa_new_element(etype_t etype, void *val) {
  element_t *new_element = malloc(sizeof(element_t));
  if (!new_element) return NULL;

  switch (etype) {
    case INT:
      // typecast void pointer to int pointer (int *) and then de-reference *
      new_element->value.ival = *(int *)val;
      break;

    case FLO: 
      new_element->value.fval = *(float *)val; 
      break;

    case STR: {
      new_element->value.sval = strdup( (char *)val );
      if (!new_element->value.sval) {
        free(new_element);
        return NULL;
      }
      break;
    }

    default:
      // if we reach here, then invalid etype is passed in
      // release the memory of new node and return
      free(new_element);
      return NULL;
  }
  new_element->etype = etype;  // update the value type
  return new_element;
}



void sa_print(stack_arr_t *sa) {
  if (sa_is_empty(sa)) return;

  printf("\n[");
  for (int i = sa->top; i >= 0; i--) {
    element_t *e = sa->data[sa->top];

    switch(e->etype) {
      case INT: printf("%d", e->value.ival); break;
      case FLO: printf("%f", e->value.fval); break;
      case STR: printf("\"%s\"", e->value.sval); break;
    }

    if (i != 0) printf(", ");
  }

  printf("]\n");
}