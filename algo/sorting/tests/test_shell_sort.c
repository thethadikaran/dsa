#include "sorting.h"

int main() {
  int a[] = {11, 7, 3, 2, 5, 66, 1, 4, 9, 8};
  s_shell_sort(a, 10);

  for (int i = 0; i < 10; i++) {
    printf("%d, ", a[i]);
  }
  printf("\n\n");
}