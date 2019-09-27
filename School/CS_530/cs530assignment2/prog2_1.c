#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <gmp.h>
#include "prog2_1.h"

TSAFELIST* tSafeConstruct() {
  TSAFELIST *tslist = (TSAFELIST*)malloc(sizeof(TSAFELIST));
  tslist->head = NULL;
  pthread_mutex_init(&(tslist->mutex), NULL);
  return tslist;
}

void tSafeDestruct(TSAFELIST *tslist) {
  pthread_mutex_lock(&(tslist->mutex));
  TSAFENODE *node = tslist->head;
  TSAFENODE *next;

  while(node != NULL) {
    next = node->next;
    free(node);
    node = next;
  }

  pthread_mutex_unlock(&(tslist->mutex));
  pthread_mutex_destroy(&(tslist->mutex));
  free(tslist);
}

void tSafeEnqueue(TSAFELIST *tslist, mpz_t n) {
  TSAFENODE *node = (TSAFENODE*)malloc(sizeof(TSAFENODE));

  pthread_mutex_lock(&(tslist->mutex));

  node->next = NULL;

  mpz_init(node->number);
  mpz_set(node->number, n);

  if(tslist->head == NULL) {
    tslist->head = node;
  }
  else {
    TSAFENODE *tmp = tslist->head;
    while (tmp->next != NULL) {
      tmp = tmp->next;
    }
    tmp->next = node;
  }

  pthread_mutex_unlock(&(tslist->mutex));
}

TSAFEDATA* tSafeDequeue(TSAFELIST *tslist) {
  TSAFEDATA *data;
  TSAFENODE *delete;

  if(tslist->head == NULL) {
    printf("---- queue is already empty ----\n");
    data->isValid = 0;
    return data;
  }

  pthread_mutex_lock(&(tslist->mutex));

  data = (TSAFEDATA*)malloc(sizeof(TSAFEDATA));

  mpz_set(data->value, tslist->head->number);

  if(tslist->head == NULL)
    printf("---- queue is empty ----\n");
  else {
    delete = tslist->head;
    tslist->head = tslist->head->next;
    data->isValid = 1;
  }

  //mpz_out_str(stdout, 10, data->value);
  //printf("\n");

  free(delete);

  pthread_mutex_unlock(&(tslist->mutex));

  return data;
}
