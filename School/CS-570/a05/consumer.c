#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <pthread.h>
#include <semaphore.h>

#include "conveyorbelt.h"
#include "producer.h"
#include "consumer.h"

void Consume(struct Consumer *consumer) {
  node *candy_node;

  while(1) {
    usleep(consumer->delay);

    sem_wait(consumer->unconsumed);
    sem_wait(consumer->mutex);
    
    if(consumer->belt->candies_consumed < 100) {
    	candy_node = dequeue(consumer->belt);
	PrintBeltConsumer(consumer, candy_node);
	
	/*
	if(candy_node != NULL) {
	    printf("Belt: %d frogs + %d escargots = %d. produced: %d", candy_node->curr_candy->belt->num_of_frogs, candy_node->curr_candy->belt->num_of_escargot, candy_node->curr_candy->belt->size, candy_node->curr_candy->belt->candies_produced);
	
	    if(strcmp(candy_node->curr_candy->name, "Frog") == 0) {
	        consumer->frogs_consumed = consumer->frogs_consumed + 1;
	        printf("\t%s consumed crunchy frog bite.\n", consumer->name);
	    }
	    else {
	        consumer->escargot_consumed = consumer->escargot_consumed + 1;
	        printf("\t%s consumed escargot sucker.\n", consumer->name);
	    }
	}
	*/
    }
    
    
    sem_post(consumer->mutex);
    sem_post(consumer->available);
    
    if(consumer->belt->candies_consumed == 100) {
    	break;
    }
    
    free(candy_node);
  }
}

struct Consumer* Construct_Consumer(struct queue *q, int delay, char* name, sem_t *mutex, sem_t *available, sem_t *unconsumed) {
  Consumer *consumer = (Consumer*)malloc(sizeof(Consumer));
  consumer->belt = q;
  consumer->delay = delay;
  consumer->name = name;
  consumer->mutex = mutex;
  consumer->available = available;
  consumer->unconsumed = unconsumed;
  consumer->frogs_consumed = 0;
  consumer->escargot_consumed = 0;
  return consumer;
}

void PrintBeltConsumer(struct Consumer *consumer, struct node *candy_node) {
  if(candy_node != NULL) {
	    printf("Belt: %d frogs + %d escargots = %d. produced: %d", candy_node->curr_candy->belt->num_of_frogs, candy_node->curr_candy->belt->num_of_escargot, candy_node->curr_candy->belt->size, candy_node->curr_candy->belt->candies_produced);
	
	    if(strcmp(candy_node->curr_candy->name, "Frog") == 0) {
	        consumer->frogs_consumed = consumer->frogs_consumed + 1;
	        printf("\t%s consumed crunchy frog bite.\n", consumer->name);
	    }
	    else {
	        consumer->escargot_consumed = consumer->escargot_consumed + 1;
	        printf("\t%s consumed escargot sucker.\n", consumer->name);
	    }
	}
}
