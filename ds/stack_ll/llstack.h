#ifndef __LINKEDLIST_STACK_HEADER__
#define __LINKEDLIST_STACK_HEADER__


#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>


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


/* struct representation of a node */
struct node {
  struct element *data;
  struct node *next;
};


/* struct representation of a stack */
struct llstack {
  int count;         // no of nodes in stack
  struct node *top;  // hold ref to head of the linked list
};

typedef struct llstack llstack;



/* ***** FUNCTION PROTOTYPES ***** */
llstack* llstack_init();

bool llstack_push(llstack*, enum element_type, void*);

struct node* llstack_pop(llstack*);

struct node* llstack_peek(llstack*);

void llstack_free(llstack*);


/* UTIL */
bool is_llstack_empty(llstack*);

struct node* llstack_create_node(enum element_type, void*);

void llstack_free_node(struct node *);

void llstack_print(llstack*);


#endif   // __LINKEDLIST_STACK_HEADER__