#include "sorting.h"

int increment_factor(int size) {
  // let's take the increment factor to be half the size of array + 1
  // + 1 is to make the factor to be odd.
  // And on each iteration, we decrement the factor by 2 until we reach 1
  return (size % 2 == 0 ? (size / 2) + 1 : size / 2); 
}




void s_shell_sort(int arr[], int size) {
  // increment - is the interval range, distance b/w elements that were compared
  int increment = increment_factor(size);

  while (increment >= 1) {
    // starting from the increment, loop through till the end of the loop
    // do this for every new increment value
    for (int i = increment; i < size; i++) {
      int curr = arr[i];

      // starting from the current i positon, let's hop elements with the
      // 'increment' as intervel and continue it till :- either we reach 0 or
      // we find a proper position for the current element
      int j = i - increment;
      while (j >= 0 && curr < arr[j]) {
        arr[j + increment] = arr[j];

        j -= increment;
      }

       // insert curr at proper position
      arr[j + increment] = curr;
    }

    // decrement the increment factor by 2 on every  iteration
    increment -= 2;
  }
}