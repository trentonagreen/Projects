#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

void *square(void *num) {
  int number = (int)num;
  long squared = number*number;//(int)num * (int)num;
  printf("%ld\n", squared);
  return (void *) squared;
}

