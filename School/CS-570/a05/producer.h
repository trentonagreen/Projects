
typedef struct candy {
  int delay;
  char* name;
  struct queue* belt; 
  sem_t *mutex;
  sem_t *available;
  sem_t *unconsumed;
  int num_produced;
} candy;

void Produce(struct candy *curr_candy);

struct candy* Construct_Curr_Candy(struct queue *q, int delay, char* name, sem_t *mutex, sem_t *available, sem_t *unconsumed);

void PrintBeltProducer(struct candy *curr_candy);
