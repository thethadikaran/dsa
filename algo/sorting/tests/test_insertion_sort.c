#include "sorting.h"

int main() {
  int a[] = {11,7};
  s_insertion_sort(a, 2);

  for (int i = 0; i < 2; i++) {
    printf("%d, ", a[i]);
  }
  printf("\n\n");
}