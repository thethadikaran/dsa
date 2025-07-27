#include "sorting.h"


void s_insertion_sort(int arr[], int size) {
  // initially first element is considered to be sorted -> sorted group
  // we start our loop from the second element of array -> unsorted group

  for (int i = 1; i < size; i++) {
    // let's make copy of the current element, that has to inserted at
    // proper positon in the sorted group. since we taken the copy, this 
    // array's position can be used as temp variable
    int curr = arr[i];

    // start the loop from the last element in sorted group and iterate over
    // until either when the start of array is reached or when the curr is
    // lesser than the elements.
    // Till we find the proper position to fit the curr element, on each
    // iteration let's shift the elements to right (using above array's position
    // as temp variable) as these are larger than curr.
    int j = i - 1;
    while (j >= 0 && curr < arr[j]) {
      arr[j + 1] = arr[j];
      j--;
    }

    arr[j + 1] = curr;   // insert curr at the proper position
  }
}