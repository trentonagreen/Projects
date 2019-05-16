#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdint.h>

#include "linkedlist.h"
#include "DirEntry.h"

struct list* Construct_List() {
  list *ll = (list*)malloc(sizeof(list)); 
  ll->head = NULL;                           
  ll->tail = NULL;
  ll->size = 0;
  return ll;
}

struct node* Create_Node() {
  node *tmp = (node*)malloc(sizeof(node));
  tmp->next = NULL;
  tmp->entry = NULL;
  tmp->nextentry = NULL;
  tmp->superblock = NULL;
  tmp->block = -1;      
  tmp->freebit = -1;    
  tmp->freemap = NULL;
  return tmp;
}

void enqueue(list *ll, struct DirEntry *entry) {
  
  node* tmp = Create_Node();
  tmp->block = ll->size;

  if(ll->tail == NULL) {
    ll->head = tmp;
    ll->tail = tmp;

    ll->size++;
    
    return;
  }

  ll->tail->next = tmp;
  ll->tail = tmp;

  ll->size++;

  return;
}

struct node* dequeue(struct list *ll) {

  if(ll->head == NULL) {
    printf("list is empty...\n");
    return NULL;
  }

  node *tmp = ll->head;
  ll->head = ll->head->next;

  if(ll->head == NULL) {
    ll->tail = NULL;
  }

  ll->size--;

  return tmp;
}

void printlist(struct list *ll) {
  node *tmp = ll->head;

  while(tmp != NULL){
    printf("block:\t%d", tmp->block);

    if(tmp->entry != NULL) {
      printf("\tfile:\t%s\n", tmp->entry->fname);
    }
    else if(tmp->freemap != NULL) {
      printf("\tfile:\tFREEMAP\n");
    }
    else {
      printf("\tfile:\tNULL\n");
    }

    tmp = tmp->next;
  }
}

