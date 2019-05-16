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
    while (tmp -> next != NULL) {
      tmp = tmp->next;
    }
    tmp->next = nnode;
  }
  ll->size++;
}

void printList(list* ll) {
  printf("[");
  while (ll->head != NULL) {
    printf("{%s}", ll->head->data);
    if(ll->head->next != NULL){
      printf(",");
    }
    ll->head = ll->head->next;
  }
  printf("]\n");
}
/* END OF LINKED LIST CODE */
