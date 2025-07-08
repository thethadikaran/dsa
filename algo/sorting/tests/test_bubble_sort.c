#include "sorting.h"

int main() {
  int a[] = {11,7,1,9,3,5,1};
  s_bubble_sort(a, 7);

  for (int i = 0; i < 7; i++) {
    printf("%d, ", a[i]);
  }
  printf("\n\n");
}