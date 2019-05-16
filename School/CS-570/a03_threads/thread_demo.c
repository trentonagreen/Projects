#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include "worker.h"

int main(int argc, char* argv[]) {
  int status;
  int Nthreads = 5;

  pthread_t *t = (pthread_t*)malloc(sizeof(pthread_t)*Nthreads);

  for(long i = 0; i < Nthreads; i++) {
    status = pthread_create(t+i, NULL, &square, (void *) i);
    usleep(1);
    if(status != 0) {
      printf("Error creating thread %ld\n", i);
      return 2;
    }
  }

  for(int i = 0; i < Nthreads; i++) {
    status = pthread_join(t[i], NULL);
    if(status != 0) {
      printf("Error joining thread %d\n", i);
      return 3;
    }
  }
  printf("work complete.\n");

  return 0;
}
