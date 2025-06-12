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

typedef struct node linkedlist;





/* ***** FUNCTION PROTOTYPES ***** */
struct node* ll_init();

int ll_length(struct node*); 

bool ll_insert(struct node*, int, void*);

bool ll_insert_at(struct node**, int, int, void*);

void ll_delete_at(struct node**, int);

void ll_reverse(struct node**);

int ll_search(struct node*, int, void*);

void ll_free(struct node*);

void ll_print(struct node*);

struct node* ll_get_last_node(struct node*);

struct node* ll_get_node_at(struct node*, int);

static struct node* ll_create_node();

static bool ll_update_node_value(struct node *, int, void*);