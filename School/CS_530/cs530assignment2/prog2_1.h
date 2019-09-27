
typedef struct tsafenode {
  struct tsafenode *next;
  mpz_t number;
} TSAFENODE;

typedef struct tsafelist {
  pthread_mutex_t mutex;
  TSAFENODE *head;
} TSAFELIST;

typedef struct tsafereturndata {
  int isValid;
  mpz_t value;
} TSAFEDATA;

TSAFELIST* tSafeConstruct();
void tSafeDestruct(TSAFELIST *tslist);
void tSafeEnqueue(TSAFELIST *tslist, mpz_t v);
TSAFEDATA* tSafeDequeue(TSAFELIST *tslist);
