#ifndef __CIRCULAR_LINKED_LIST__
#define __CIRCULAR_LINKED_LIST__

/**
 * @file clinked_list.h
 * @author thethadikaran
 * @brief Circular Linked List
 * Here the last node's next reference points to the head node of the linked list.
 * We keep track of the last node to do all operations. Tracking last node helps
 * to insert elements either in front and in last with O(1) complexity.
 * @version 0.1
 * @date 2025-06-16
 * 
 * @copyright Copyright (c) 2025
 * 
 */
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


#endif   // __CIRCULAR_LINKED_LIST__