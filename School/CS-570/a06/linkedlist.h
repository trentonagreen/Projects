
/*
typedef struct node {
  struct node *next;
  struct list *freemap;
  char *filename;
  //DirEntry *directory;
  uint32_t block;     // "block" (idx) number
  uint32_t data;      // data for this block 
  int free;           // 0 is free, 1 is used 
} node;
*/

typedef struct node {
  struct node *next;
  struct DirEntry *entry;
  struct DirEntry *nextentry;
  struct SuperBlock *superblock;
  uint32_t block;
  uint32_t freebit;    //0 free : 1 used
  uint32_t *freemap;
} node;

typedef struct list {
  struct node *head, *tail;   
  int size;                   
} list;

struct list* Construct_List();

struct node* Create_Node();

void enqueue(struct list *ll, struct DirEntry *entry);

struct node* dequeue(struct list *ll);

void printlist(struct list *ll);

//struct node* search(struct node *head, int idx);

//void modifylist(struct node *head);
