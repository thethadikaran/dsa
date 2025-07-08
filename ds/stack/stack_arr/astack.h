#ifndef __ARRAY_STACK_HEADER__
#define __ARRAY_STACK_HEADER__

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#define SIZE  1000


enum element_type { INT, FLO, STR };


/* struct representation of a element */
struct element {
  enum element_type etype;

  union {
    int ival;
    float fval;
    char *sval;
  } value;
};


/* struct representation of a stack */
struct stack {
  int top;                      // position of current stack top
  struct element *items[SIZE];  // array of pointer to struct element
};

typedef struct stack stack;




/* ***** FUNCTION PROTOTYPES ***** */
stack* astack_init();

bool astack_push(stack*, enum element_type, void*);

struct element* astack_pop(stack*);

struct element* astack_peek(stack*);

void astack_free(stack*);


/* UTIL */
bool is_astack_full(stack*);

bool is_astack_empty(stack*);

struct element* astack_create_element(enum element_type, void*);

void astack_free_element(struct element*);

void astack_print(stack*);


#endif   // __ARRAY_STACK_HEADER__