#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
  O(n) time and space

  using a tmp variable, grow from left to right (0 -> inf)...
  to create product array of numbers to the left of arr[i]

  using a tmp variable 
    and previous left product array grow from right to left (inf -> 0)...
  to create a product array of numbers to the right of arr[i]
*/
int* createProductArr(int* arr, int size) {

  int tmp = 1;

  int *product_arr = (int *)malloc(sizeof(int)*size);
  memset(product_arr, 0, size);

  // handle the numbers to the LEFT of arr[i]
  for(int i = 0; i < size; i++) {
    product_arr[i] = tmp;
    tmp *= arr[i];
  }

  tmp = 1;

  // handle the numbers to the RIGHT if arr[i]
  for(int i = size - 1; i >= 0; i--) {
    product_arr[i] *= tmp;
    tmp *= arr[i];
  }

  return product_arr;
}

int main(int argc, char** argv) {
  printf("Daily Programming, Day-2\n");
  printf("-----------------------------------------------------------------\n");

  printf("Given an array, create new array such that...\n");
  printf("the index i is the product of all numbers except i\n\n");

  int arr[] = {1, 2, 3, 4, 5};
  int size = sizeof(arr)/sizeof(int);
  int *result;

  result = createProductArr(arr, size);

  printf("Initial Array\t");
  printf("[ ");
  for(int i = 0; i < size; i++) {
    printf("%d ", arr[i]);
  }
  printf("]\n");

  printf("Product Array\t");
  printf("[ ");
  for(int i = 0; i < size; i++) {
    printf("%d ", result[i]);
  }
  printf("]\n");
}