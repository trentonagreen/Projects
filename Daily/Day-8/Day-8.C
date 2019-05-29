#include <stdio.h>

int FindMax(int arr[], int size) {
  int include = arr[0];
  int exclude = 0;
  int new_exclude;


  for(int i = 0; i < size; i++) {
    new_exclude = (include > exclude) ? include:exclude;

    include = exclude + arr[i];
    exclude = new_exclude;
  }
  return ((include > exclude) ? include:exclude);
}
 
int main(int argc, char **argv) {
  printf("Daily Programming, Day-8\n");
  printf("-----------------------------------------------------------------\n");
  
  int arr[] = {5,1,1,5};
  int size = sizeof(arr) / sizeof(int);

  int result = FindMax(arr, size);

  printf("Max sum is:\t%d\n", result);
}