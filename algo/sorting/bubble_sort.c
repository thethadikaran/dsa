#include "sorting.h"

void s_bubble_sort(int *arr, int size) {
  bool is_swapped;    // to verify if swapping of elements happens
  int tmp_swp;

  for (int i = 0; i < size - 1; i++) {

    is_swapped = false;

    // size - i     : for every outer loop we reduce the inner loop by one 
    // size - i - 1 : make sure no out of bound idexing happens
    for (int j = 0; j < size - i - 1; j++) {
      if (arr[j] > arr[j + 1]) {
        tmp_swp = arr[j];
        arr[j] = arr[j + 1];
        arr[j + 1] = tmp_swp;

        is_swapped = true;
      }
    }

    // check if swapping of elements happened
    if (!is_swapped) break;
  }
}