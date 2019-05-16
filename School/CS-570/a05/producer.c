#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <pthread.h>
#include <semaphore.h>

#include "conveyorbelt.h"
#include "producer.h"

void Produce(struct candy *curr_candy) {
  int status;

  while(1) {
    usleep(curr_candy->delay);
    
    //if(curr_candy->belt->candies_produced == 100) {
    //	break;
    //}
    
    sem_wait(curr_candy->available);
    sem_wait(curr_candy->mutex);
    //printf("%s has belt\n", curr_candy->name);
    
    if(curr_candy->belt->candies_produced < 100) {
	enqueue(curr_candy->belt, curr_candy);
	PrintBeltProducer(curr_candy);
	/*
	printf("Belt: %d frogs + %d escargots = %d. produced: %d", curr_candy->belt->num_of_frogs, curr_candy->belt->num_of_escargot, curr_candy->belt->size, curr_candy->belt->candies_produced);
	
	if(strcmp(curr_candy->name, "Frog") == 0) {
	    printf("\tAdded crunchy frog bite.\n");
	}
	else {
	    printf("\tAdded escargot sucker.\n");
	}
	*/
    }
    
    sem_post(curr_candy->mutex);
    sem_post(curr_candy->unconsumed);

    if(curr_candy->belt->candies_produced == 100) {
    	break;
    }
  }
}

struct candy* Construct_Curr_Candy(struct queue *q, int delay, char* name, sem_t *mutex, sem_t *available, sem_t *unconsumed) {
  candy *curr_candy = (candy*)malloc(sizeof(candy));
  curr_candy->belt = q;
  curr_candy->delay = delay;
  curr_candy->name = name;
  curr_candy->mutex = mutex;
  curr_candy->available = available;
  curr_candy->unconsumed = unconsumed;
  curr_candy->num_produced = 0;
  return curr_candy;
}

void PrintBeltProducer(struct candy *curr_candy) {
  printf("Belt: %d frogs + %d escargots = %d. produced: %d", curr_candy->belt->num_of_frogs, curr_candy->belt->num_of_escargot, curr_candy->belt->size, curr_candy->belt->candies_produced);
	
	if(strcmp(curr_candy->name, "Frog") == 0) {
	    printf("\tAdded crunchy frog bite.\n");
	}
	else {
	    printf("\tAdded escargot sucker.\n");
	}
}
