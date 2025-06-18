#ifndef __HEADER_LINKED_LIST__
#define __HEADER_LINKED_LIST__

/**
 * @file hlinked_list.c
 * @author thethadikaran
 * @brief Linked List \w Header
 * Comparing with other type of linked list, this type has a header node even
 * the linked list has values or not. This usually hold the meta data of the
 * linked chain like length, last node's address etc.
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

enum element_type { INT, FLO, STR };


/* define an element, used in info part of the node */
struct element {
  enum element_type etype;

  union {
    int ival;
    float fval;
    char *sval;
  } value;
};


/* define a node, building block of a linked list */
struct node {
  struct element ele;    // info part
  struct node *next;     // ref to next node
};


/* define a header node */
struct hnode {
  int len;              // no of nodes in the linked list
  struct node *first;   // ref to first node of the linked list
  struct node *last;    // ref to last node of the linked list
};

typedef struct hnode hlinkedlist;




/* ***** FUNCTION PROTOTYPES ***** */
hlinkedlist* hll_init();

int hll_count(hlinkedlist*);

bool hll_append(hlinkedlist*, enum element_type, void*);

bool hll_insert(hlinkedlist*, int, enum element_type, void*);

bool hll_remove(hlinkedlist*, enum element_type, void*);

struct node* hll_pop(hlinkedlist *);

void hll_free(hlinkedlist *);

void hll_print(hlinkedlist *);


/* UTILS */
struct node* hll_node_create_update(enum element_type, void*);

struct node* hll_get_node(hlinkedlist *hll, int pos);

void hll_free_node(struct node *);

#endif   // __HEADER_LINKED_LIST__