#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define NO_VALUE  0
#define INT       1
#define FLO       2
#define STR       3


/**
 * Single Linked list (one way list) 
 *    - as it contains only one link to next node
 *    - can move only in one direction
 */


/* struct used as info part in the node */
struct element {
  int etype;

  union {
    int ival;
    float fval;
    char *sval;
  } value;
};


/* struct defines a single node */
struct node {
  struct element ele;       // info part
  struct node *next;        // ref to next node
};



/* struct to define a linked list */
struct circular_linked_list {
  struct node *last;
};

typedef struct circular_linked_list clinkedlist;



/* ***** FUNCTION PROTOTYPES ***** */
clinkedlist* cll_init();

bool cll_append_front(clinkedlist *, int, void*);

bool cll_append_last(clinkedlist *, int, void*);

void cll_delete(clinkedlist *, int, void*);

void cll_free(clinkedlist *);



/* UTILS */
void cll_print(clinkedlist *);

struct node* cll_create_node();

static bool cll_update_node_value(struct node*, int, void*);

bool cll_is_value_match(struct node*, int, void*);

void cll_free_node(struct node*);