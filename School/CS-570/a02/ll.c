#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ll.h"

struct list* construct() {
  list *ll = (list*)malloc(sizeof(list));
  ll->head = NULL;
  ll->size = 0;
  return ll;
}

void destruct(list* ll) {
  node *current = ll->head;
  node *tmp;

  while (current != NULL) {
    tmp = current->next;
    free(current);
    current = tmp;
  }
  free(ll);
}

void enqueue(list *ll, void *data) {
  node *nnode = (node*)malloc(sizeof(node));
  nnode->next = NULL;
  nnode->data = malloc(strlen(data));
  strcpy(nnode->data, data);

  if(ll->head == NULL) {
    ll->head = nnode;
  }
  else {
    node* tmp = ll->head;
    while (tmp->next != NULL) {
      tmp = tmp->next;
    }
    tmp->next = nnode;
  }
  ll->size++;
}

void printList(list* ll) {
  node* tmp = ll->head;

  if(tmp == NULL) {
    return;
  }

  printf("[");
  while (tmp != NULL) {
    printf("{%s}", tmp->data);
    if(tmp->next != NULL){
      printf(",");
    }
    tmp = tmp->next;
  }
  printf("]\n");
}

/*
  Added to ASSIGNMENT 2
*/

/*
  Given a specific location, delete node in linked list
*/
void delete(list* ll, int index) {
  node* tmp = ll->head;

  if(tmp == NULL) {
    return;
  }
  if(index == 0) {
    ll->head = tmp->next;
    free(tmp);
    ll->size--;
    return;
  }
  for(int i = 0; tmp!= NULL && i < index - 1; i++) {
    tmp = tmp->next;
  }
  if(tmp == NULL || tmp->next == NULL) {
    return;
  }
  node* next = tmp->next->next;
  free(tmp->next);
  tmp->next = next;

  ll->size--;
}

/*
  Clears the Linked List
*/
void clear(list* ll) {
  while(ll->size > 0) {
    delete(ll, ll->size-1);
  }
}

/* END OF LINKED LIST CODE */
