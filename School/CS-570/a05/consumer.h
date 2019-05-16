
typedef struct Consumer {
  char* name;
  int delay;
  struct queue* belt;
  sem_t *mutex;
  sem_t *available;
  sem_t *unconsumed;
  int frogs_consumed;
  int escargot_consumed;
} Consumer;

void Consume(struct Consumer *consumer);

struct Consumer* Construct_Consumer(struct queue *q, int delay, char* name, sem_t *mutex, sem_t *available, sem_t *unconsumed);

void PrintBeltConsumer(struct Consumer *consumer, struct node *candy_node);
