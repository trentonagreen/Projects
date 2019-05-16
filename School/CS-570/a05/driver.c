#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>

#include "conveyorbelt.h"
#include "producer.h"
#include "consumer.h"

#define MAX_BELT_SIZE 10

int main(int argc, char** argv) {
  //printf("---------------------------------------------\n");
  
  int ethel_flag = 0;       //number of milliseconds ethel consumes
  int lucy_flag = 0;        //number of milliseconds lucy consumes
  int frog_flag = 0;        //number of milliseconds between frog production
  int escargot_flag = 0;    //number of milliseconds between escargot production

  int ethel_delay = 0;
  int lucy_delay = 0;
  int frog_delay = 0;
  int escargot_delay = 0;
  
  int c;

  while((c = getopt(argc, argv, "E:L:f:e:")) != -1) {
    switch(c) {
      case 'E':
        ethel_flag = 1;
        ethel_delay = atoi(optarg);
        break;
      case 'L':
        lucy_flag = 1;
        lucy_delay = atoi(optarg);
        break;
      case 'f':
        frog_flag = 1;
        frog_delay = atoi(optarg);
        break;
      case 'e':
        escargot_flag = 1;
        escargot_delay = atoi(optarg);
        break;
    }
  }

  int adj_frog_delay = frog_delay * 1000;
  int adj_escargot_delay = escargot_delay * 1000;
  int adj_ethel_delay = ethel_delay * 1000;
  int adj_lucy_delay = lucy_delay * 1000;
  
  /*
    5 threads
      control
      frog producer
      escargot producer
      ethel consumer
      lucy consumer
  */

  pthread_t *control_thread = (pthread_t*)malloc(sizeof(pthread_t));
  pthread_t *frog_thread = (pthread_t*)malloc(sizeof(pthread_t));
  pthread_t *escargot_thread = (pthread_t*)malloc(sizeof(pthread_t));
  pthread_t *ethel_thread = (pthread_t*)malloc(sizeof(pthread_t));
  pthread_t *lucy_thread = (pthread_t*)malloc(sizeof(pthread_t));

  int control_status;
  int frog_status;
  int escargot_status;
  int ethel_status;
  int lucy_status;
        
  /*
    semaphores
    mutex, for critical section initialize to 1
    items in buffer, for barrier initialize to 0
    space in buffer, for size of buff initialize to buffer size
  */
 
 
 sem_t mutex;
 sem_t unconsumed;
 sem_t available;
 
 if(sem_init(&mutex,0, 1) == -1) {
   printf("Unable to init mutex\n");
   return 0;
 }

 if(sem_init(&unconsumed, 0, 0) == -1) {
   printf("Unable to init unconsumed\n");
   return 0;
 }

 if(sem_init(&available, 0, MAX_BELT_SIZE) == -1) {
   printf("Unable to init available\n");
   return 0;
 }

  //create linked list of size MAX_BELT_SIZE
  queue *q = Construct_Queue();
  
  char* frog_char = "Frog";
  char* escargot_char = "Escargot";

  candy *frog = Construct_Curr_Candy(q, adj_frog_delay, frog_char, &mutex, &available, &unconsumed);
  candy *escargot = Construct_Curr_Candy(q, adj_escargot_delay, escargot_char, &mutex, &available, &unconsumed);


  char* ethel_char = "Ethel";
  char* lucy_char = "Lucy";

  Consumer *ethel = Construct_Consumer(q, adj_ethel_delay, ethel_char, &mutex, &available, &unconsumed);
  Consumer *lucy = Construct_Consumer(q, adj_lucy_delay, lucy_char, &mutex, &available, &unconsumed);

  lucy_status = pthread_create(lucy_thread, NULL, (void*)Consume, lucy);
  ethel_status = pthread_create(ethel_thread, NULL, (void*)Consume, ethel);
  frog_status = pthread_create(frog_thread, NULL, (void*)Produce, frog);
  escargot_status = pthread_create(escargot_thread, NULL, (void*)Produce, escargot);

  pthread_join(*frog_thread, NULL);
  pthread_join(*escargot_thread, NULL);
  pthread_join(*ethel_thread, NULL);
  pthread_join(*lucy_thread, NULL);

  //MyBadDebugHabit();
  
  int lucy_total = lucy->frogs_consumed + lucy->escargot_consumed;
  int ethel_total = ethel->frogs_consumed + ethel->escargot_consumed;
  
  printf("\nPRODUCTION REPORT\n");
  printf("----------------------------------------\n");
  printf("crunchy frog bite producer generated %d candies\n", frog->num_produced);
  printf("escargot sucker producer generated %d candies\n", escargot->num_produced);
  printf("Lucy consumed %d crunchy frog bites + %d escargot suckers = %d\n", lucy->frogs_consumed,
  lucy->escargot_consumed, lucy_total);
  printf("Ethel consumed %d crunchy frog bites + %d escargot suckers = %d\n", ethel->frogs_consumed,
  ethel->escargot_consumed, ethel_total);

  free(q);
  free(lucy);
  free(ethel);
  free(frog);
  free(escargot);
}
