#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX 100

/*
  O(n) time and space

  find if two numbers add up to k using a hash

  if there are multiple pairs that add up to k
  it will only find the first pair in the arr
*/
bool findK(int arr[], int k, int size) {
  int tmp;

  // init empty hash
  bool s[MAX];
  memset(s, 0, size * sizeof(bool));

  // for each element in arr
  //    if k - arr[i] is in s, Pair is found, print and return
  //    else set arr[i] in s
  for(int i = 0; i < size; i++) {
    tmp = k - arr[i];
    
    if(tmp >= 0 && s[tmp] == 1) {
      printf("Pair that adds up to %d: (%d, %d)\n", k, tmp, arr[i]);
      return true;
    }

    s[arr[i]] = 1;
  }

  printf("No pair that adds up to k\n");
  return false;
}

int main(int argc, char** argv) {
  printf("Daily Programming, Day-1\n");
  printf("-----------------------------------------------------------------\n");
  printf("Find two numbers in array that add up to k\n");

  int arr[] = {10, 15, 3, 6, 2, 22, 37, 8};
  int k = 18;
  int size = sizeof(arr)/sizeof(int);

  printf("arr -> [ ");
  for(int i = 0; i < size; i++) {
    printf("%d ", arr[i]);
  }
  printf("]\n");
  printf("k: %d\n", k);

  bool result = findK(arr, k, size);

  if(result) {
    printf("Success\n");
  }
  else {
    printf("Failed\n");
  }

  return 0;
}