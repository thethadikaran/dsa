#include "astack.h"


stack* astack_init() {
  stack *s = malloc(sizeof(stack));
  if (!s) {
    fprintf(stderr, "Cannot allocate memory for stack");
    return NULL;
  }

  s->top = -1;     // initilize to empty
  return s;
}



bool astack_push(stack *s, enum element_type etype, void *val) {
  // check if the stack is full
  if (is_astack_full(s)) {
    fprintf(stderr, "Stack Overflow");
    return false;
  }

  struct element *e = astack_create_element(etype, val);
  if (!e) return false;

  // increment the top and then add push the new element
  s->items[++s->top] = e;
  return true;
}



struct element* astack_pop(stack *s) {
  // check if the stack is empty
  if (is_astack_empty(s)) {
    fprintf(stderr, "Stack Underflow");
    return NULL;
  }

  // isolate the element and then decrement the top
  struct element *e =  s->items[s->top--];
  return e;    // caller has to free the memory for the element
}



struct element* astack_peek(stack *s) {
  // check if the stack is empty
  if (is_astack_empty(s)) {
    fprintf(stderr, "Stack Underflow");
    return NULL;
  }

  // peek at the top element at the stack
  return s->items[s->top];
}



void astack_free(stack *s) {
  while (!is_astack_empty(s)) {
    struct element *ele = astack_pop(s);   // get the top element

    // finally free the element
    astack_free_element(ele);
  }

  free(s);
}



/* ***** UTIL FUNCTION DEFINITIONS ***** */

bool is_astack_full(stack *s) {
  // range of stack is 0 to SIZE - 1
  return (s->top == SIZE - 1);
}



bool is_astack_empty(stack *s) {
  return (s->top == -1);
}



struct element* astack_create_element(enum element_type etype, void *val) {
  if (!val) return NULL;

  struct element *e = malloc(sizeof(struct element));
  if (!e) {
    fprintf(stderr, "Cannot allocate memory for Element");
    return NULL;
  }

  switch (etype) {
    case INT: e->value.ival = *(int *)val; break;

    case FLO: e->value.fval = *(float *)val; break;

    case STR:
      e->value.sval = strdup((char *)val); break;
      if (!e->value.sval) {
        free(e);
        fprintf(stderr, "Cannot allocate memory for string");
        return NULL;
      }

    default: free(e); return NULL;
  }

  return e;
}



void astack_free_element(struct element *ele) {
  if (ele->etype == STR)
    free(ele->value.sval);
  
  free(ele);
}



void astack_print(stack *s) {
  if (is_astack_empty(s)) return;

  printf("\n[");
  for (int i = s->top; i >= 0; i--) {
    struct element *ele = s->items[s->top];

    switch(ele->etype) {
      case INT: printf("%d", ele->value.ival); break;
      case FLO: printf("%f", ele->value.fval); break;
      case STR: printf("\"%s\"", ele->value.sval); break;
    }

    if (i != 0) printf(", ");
  }

  printf("]\n");
}