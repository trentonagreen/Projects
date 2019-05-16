/*

ASSIGNMENT 1

*/

#define ENQUEUE enqueue(ll, str); str[0] = '\0';
#define TRUE 1
#define FALSE 0
#define LIMIT 100

static const char* special = "|;<>&";
static const char* rcarrot = ">";
static const char* lcarrot = "<";
static const char* ampersand = "&";
static const char* semicolon = ";";
static const char* piper = "|";
static const char* escape = "\\";
static const char* squote = "\'";
static const char* dquote = "\"";

typedef struct node {
  void *data;
  struct node *next;
} node;

typedef struct list {
  struct node *head;
  int size;
} list;

struct list* construct();
void destruct(struct list *ll);
void enqueue(struct list *ll, void *data);
void printList(struct list* ll);

void append(char *str, char c);
void tokenize(struct list* ll, char* input, char* str);

/*
  ASSIGNMENT 2
*/
void delete(struct list* ll, int index);
void clear(struct list* ll);
void launch(char *argv[LIMIT]);
void execute_commands(struct list* ll);
