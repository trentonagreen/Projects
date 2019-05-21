
#include <stdio.h>
#include <stdlib.h>

/*
  swap the given values
*/
void swap(int *a, int *b) {
  int tmp;
  tmp = *a;
  *a = *b;
  *b = tmp;
}

/*
  Function that pulls all non-positive numbers and zero to the left side of arr
*/
int seperate(int *arr, int size) {
  int tmp = 0;
  for(int i = 0; i < size; i++) {
    if(arr[i] <= 0) {
      swap(&arr[i], &arr[tmp]);
      tmp++;
    }
  }

  return tmp;
}

/*
  Function that looks at the positive side of the array
*/
int findFirstMissingPos(int *arr, int size) {

  // while checking array, mark an index checked by making it's previous negative
  // since we are looking at the positive section of array
  //  index starts at zero and positive nums start at index 1
  for(int i = 0; i < size; i++) {
    if(abs(arr[i]) - 1 < size && arr[abs(arr[i]) - 1] > 0) {
      arr[ abs(arr[i]) - 1 ]= -arr[ abs(arr[i]) - 1];
    }
  }

  // return the first index value that is positive
  for(int i = 0; i < size; i++) {
    if(arr[i] > 0) {
      return i + 1;
    }
  }

  return size + 1;
}

/*
  Function that calls two others to seperate array and find the missing number
*/
int findMissing(int *arr, int size) {

  // seperate array from negatives and positives
  int sep = seperate(arr, size);

  // shift array to only look at the positive part
  int result = findFirstMissingPos(arr + sep, size - sep);
  return result;
}

int main(int argc, char **argv) {
  printf("Daily Programming, Day-3\n");
  printf("-----------------------------------------------------------------\n");

  printf("Given an unsorted array...\n");
  printf("Find the first missing positive integer.\n");

  int arr[] = {3, 4, -1, 1};
  int size = sizeof(arr) / sizeof(int);

  int missingNum = findMissing(arr, size);

  printf("The missing positive number is:\t%d\n", missingNum);
}
