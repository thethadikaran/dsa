#include "linked_list.h"

int main() {
  linkedlist *ll = ll_init();
  
  // adding elements
  char *a = "hello world";
  char *b = "this is a new string";
  char *c = "this is other string";
  ll_insert(ll, STR, a);
  ll_insert(ll, STR, b);
  ll_insert(ll, STR, c);

  int x = 44;
  float y = 33.56;

  ll_insert(ll, INT, &x);
  ll_insert(ll, FLO, &y);

  ll_print(ll);
  printf("position of '44': %d\n", ll_search(ll, INT, &x));
  printf("position of '33.56': %d\n", ll_search(ll, FLO, &y));

  printf("no of elements in list: %d\n", ll_length(ll));

  ll_reverse(&ll);
  ll_print(ll);

  printf("position of '44': %d\n", ll_search(ll, INT, &x));
  printf("position of '33.56': %d\n", ll_search(ll, FLO, &y));
  printf("position of 'hello world': %d\n", ll_search(ll, STR, a));

  int z = 400;
  printf("position of '400': %d\n", ll_search(ll, INT, &z));

  ll_insert_at(&ll, 0, INT, &z);
  ll_print(ll);

  ll_insert_at(&ll, ll_length(ll), INT, &z);
  ll_print(ll);

  char *zz = "hmm, will this work";

  ll_insert_at(&ll, 1, STR, zz);
  ll_print(ll);


  

  return 0;
}