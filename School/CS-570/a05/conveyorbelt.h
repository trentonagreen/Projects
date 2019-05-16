
void ConveyorBeltTest();

typedef struct node {
  int data;
  struct candy *curr_candy;
  struct node *next;
} node;

typedef struct queue {
  struct node *head, *tail;
  int size;
  int num_of_frogs;
  int num_of_escargot;
  int candies_produced;
  int candies_consumed;
  int num_frogs_produced;
  int num_escargot_produced;
} queue;

struct queue* Construct_Queue();
//struct node* Create_Node(int data);
struct node* Create_Node(struct candy *curr_candy);

//void enqueue(struct queue *q, int data);
int enqueue(struct queue *q, struct candy *curr_candy);
struct node* dequeue(struct queue *q);

void candy_check(struct queue *q);

void print_queue(struct queue *q);
