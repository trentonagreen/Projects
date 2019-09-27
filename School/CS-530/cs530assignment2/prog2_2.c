#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <gmp.h>
#include "prog2_1.h"

mpz_t globalCounter;
pthread_mutex_t counterguard = PTHREAD_MUTEX_INITIALIZER;
TSAFELIST *numberList;

mpz_t inc; //used to increment globalCounter

unsigned int getBitLength(mpz_t n);

void getNextNum(mpz_t num) {

  pthread_mutex_lock(&(numberList->mutex));
  mpz_add(num, num, inc);
  pthread_mutex_unlock(&(numberList->mutex));

}

static void *generatePrimes(void *amount) {

  int isPrime;
  int K = (int)amount;
  int count = 0;

  pthread_mutex_lock(&counterguard);

    for (int i = 0; i < 100000; i++) { //100000

      if(count == K) {
        break;
      }

      isPrime = mpz_probab_prime_p(globalCounter, 15);
      if(isPrime == 2 || isPrime == 1) {
        tSafeEnqueue(numberList, globalCounter);
        count++;
      }
      getNextNum(globalCounter);
    }

  pthread_mutex_unlock(&counterguard);

  return 0;
}

unsigned int getBitLength(mpz_t n) {
  unsigned int count = 0;
  int x = mpz_get_ui(n);

  while (x) {
    count++;
    x >>= 1;
  }

  return count;
}

int main(int argc, char* argv[]) {
  printf("Assignment #2-2, Trenton Green, trenton.green@sbcglobal.net\n");

  if(argc < 3) {
    printf("Needs a K and B input values\n");
    return 0;
  }

  int Nthreads = 4;
  int bitLength = 0;
  long K = atoi(argv[1]);
  int B = atoi(argv[2]);
  int status;

  if(B == 2) {
    printf("2\n");
    printf("3\n");
    printf("No more numbers of bit length %d\n", B);
    return 1;
  }

  mpz_init(globalCounter);
  mpz_set_ui(globalCounter, 1);

  mpz_init(inc);
  mpz_set_ui(inc, 1);

  numberList = tSafeConstruct();

  mpz_ui_pow_ui(globalCounter, 2, B-1);

  if(bitLength < B) {
    while(bitLength < B) {
      getNextNum(globalCounter);
      bitLength = getBitLength(globalCounter);
    }
  }

  pthread_t *t = (pthread_t*)malloc(sizeof(pthread_t)*Nthreads);

  for(int i=0;i<Nthreads;i++){
      status = pthread_create(t+i,NULL,generatePrimes,(void*)K); //num
      usleep(100000);
      if(status != 0){
          printf("Error creating thread %d\n",i);
          return 2;
      }
  }
  for(int i=0;i<Nthreads;i++){
      status = pthread_join(t[i],NULL);
      if(status != 0){
          printf("Error joining thread %d\n",i);
          return 3;
      }
  }
  TSAFEDATA *data;
  for(int x = 0; x < K; x++) {
    bitLength = getBitLength(numberList->head->number);
    data = tSafeDequeue(numberList);
    if(bitLength == B && data->isValid == 1)  {
      mpz_out_str(stdout, 10, data->value);
      printf("\n");
    }
    else {
      printf("No more numbers of bit length %d\n", B);
      break;
    }
  }

  tSafeDestruct(numberList);

  return 1;
}
