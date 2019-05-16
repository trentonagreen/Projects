#define ENQUEUE enqueue(ll, str); str[0] = '\0';

struct list* construct();
void enqueue(struct list *ll, void *data);
void printList(struct list* ll);
void append(char *str, char c);
int tokenize(struct list* ll, char* input, char* str);

typedef struct node {
  void *data;
  struct node *next;
} node;

typedef struct list {
  struct node *head;
  int size;
} list;
