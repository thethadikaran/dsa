#include "sorting.h"


void s_selection_sort(int *arr, int size) {
  int min_idx;    // hold the index of smallest value
  int tmp;        // to use for swapping

  // since selection sort needs size - 1 iteration to sort the array
  for (int i = 0; i < size - 1; i++) {
    min_idx = i;

    // find the smallest value in range (i to size)
    for (int j = i; j < size; j++) {
      if (arr[j] < arr[min_idx])
        min_idx = j;
    }

    // let's swap the values b/w i and the min_idx position
    if (i != min_idx) {
      tmp = arr[i];
      arr[i] = arr[min_idx];
      arr[min_idx] = tmp;
    }
  }
}