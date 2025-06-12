#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define NO_VALUE  0
#define INT       1
#define FLO       2
#define STR       3

/**
 * Double Linked list (two way list) 
 *    - contains two links one to previous & to next node
 *    - can move forward or backward
 */


/* structure of a element in a node */
struct element {
  int etype;

  union {
    int ival;
    float fval;
    char *sval;
  } value;
};


/* structure of a Node in Double linked list */
struct dnode {            // double linked list node   
  struct dnode *prev;     // reference to previous node
  struct element ele;     // info part
  struct dnode *next;     // reference to next node
};

typedef struct dnode dlinkedlist;




/* ***** FUNCTION PROTOTYPES ***** */
struct dnode* dll_init();

void dll_print(struct dnode *);

void dll_free(struct dnode *);

void dll_reverse(struct dnode**);

bool dll_insert(struct dnode*, int , void*);

bool dll_insert_at(struct dnode**, int, int, void*);

void dll_delete_at(struct dnode **,  int);

int dll_length(struct dnode *);


static struct dnode* dll_create_node();

static bool dll_update_node_value(struct dnode*, int, void*);

static struct dnode* dll_get_last_node(struct dnode*);

static struct dnode* dll_get_node_at(struct dnode *, int);