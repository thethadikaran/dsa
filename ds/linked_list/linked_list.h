#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define NO_VALUE  0
#define INT       1
#define FLO       2
#define STR       3



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

bool ll_insert_at(struct node*, int, void*, int); // TODO

void ll_delete_val(struct node*, int);   // TODO

void ll_delete_at(struct node*, int);   // TODO

struct node* ll_reverse(struct node*);

struct node* ll_search(struct node*, int, int);    // TODO

void ll_free(struct node*);



void ll_print(struct node*);

struct node* ll_get_last_node(struct node*);

struct node* ll_create_node();

bool ll_update_node_value(struct node *, int, void*);