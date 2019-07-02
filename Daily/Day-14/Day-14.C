#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int selectRand(int x) {
  int result;
  int count = 0;

  count++;

  if(count == 1) {
    result = x;
  }
  else {
    int i = rand() % count;

    if(i == count - 1) {
      result = x;
    }
  }

  return result;
}

int main(int argc, char **argv) {
  printf("Daily Programming, Day-14\n");
  printf("-----------------------------------------------------------------\n");

  int stream[] = {1,2,3,4,5,6,7};
  int len = sizeof(stream) / sizeof(int);

  srand(time(NULL));
  for(int i = 0; i < len; ++i) {
    printf("Rand num from first %d is:\t%d\n", i+1, selectRand(stream[i]));
  }
}