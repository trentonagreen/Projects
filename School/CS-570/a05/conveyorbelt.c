#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <semaphore.h>
#include "conveyorbelt.h"
#include "producer.h"

#define MAX_FROGS 3

void ConveyorBeltTest() {
  printf("----Conveyor Belt Test----\n");
}

struct queue* Construct_Queue() {
  queue *q = (queue*)malloc(sizeof(queue));
  q->head = NULL;
  q->tail = NULL;
  q->size = 0;
  q->num_of_frogs = 0;
  q->num_of_escargot = 0;
  q->candies_produced = 0;
  q->candies_consumed = 0;
  return q;
}

struct node* Create_Node(struct candy *curr_candy) {
  node *tmp = (node*)malloc(sizeof(node));
  //tmp->data = data;
  tmp->curr_candy = curr_candy;
  tmp->next = NULL;
  return tmp;
}

int enqueue(queue *q, struct candy *curr_candy) {

  //printf("adding %s to belt\n", curr_candy->name);

  if(q->num_of_frogs == MAX_FROGS && strcmp(curr_candy->name, "Frog") == 0) {
    //printf("TOO MANY FROGS ON BELT\n");
    return -1;
  }
  
  if(strcmp(curr_candy->name, "Frog") == 0) {
    //printf("adding frogs to belt\n");
    q->num_of_frogs = q->num_of_frogs + 1;
  }
  else {
    q->num_of_escargot = q->num_of_escargot + 1;
  }

  node* tmp = Create_Node(curr_candy);
  
  q->size = q->size + 1;
  q->candies_produced = q->candies_produced + 1;
  curr_candy->num_produced = curr_candy->num_produced + 1;

  if(q->tail == NULL) {
    q->head = tmp;
    q->tail = tmp;
    
    //printf("added %s to belt\n", curr_candy->name);
    
    return 1;
  }

  q->tail->next = tmp;
  q->tail = tmp;
  return 1;
}
struct node* dequeue(struct queue *q) {
  if(q->head == NULL) {
    printf("queue is empty...\n");
    return NULL;
  }

  node *tmp = q->head;
  q->head = q->head->next;

  if(q->head == NULL) {
    q->tail = NULL;
  }

  if(strcmp(tmp->curr_candy->name, "Frog") == 0) {
    q->num_of_frogs = q->num_of_frogs - 1;
  }
  else {
    q->num_of_escargot = q->num_of_escargot - 1;
  }

  //decrement type of candy
  q->size = q->size - 1;
  q->candies_consumed = q->candies_consumed + 1;
  return tmp;
}

void print_queue(queue *q) {
  node *tmp = q->head;

  if(tmp == NULL) {
    return;
  }

  while(tmp != NULL) {
    printf("Type: %s --- Delay: %d\n", tmp->curr_candy->name, tmp->curr_candy->delay);
    tmp = tmp->next;
  }
}
