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

  printf("no of elements in list: %d\n", ll_length(ll));

  linkedlist *lx = ll_reverse(ll);
  ll_print(lx);

  return 0;
}