#include <stdio.h>
#include <stdlib.h>

struct Node {
  int data;
  struct Node *both;
};

struct Node *XOR (struct Node *a, struct Node *b) {
  return (struct Node*) ((uintptr_t) (a) ^ (uintptr_t) (b));
}

void add(struct Node **head, int data) {
  struct Node *new_node = (struct Node*)malloc(sizeof(struct Node));
  new_node->data = data;

  new_node->both = XOR(*head, NULL);

  if(*head != NULL) {
    struct Node *next = XOR((*head)->both, NULL);
    (*head)->both = XOR(new_node, next);
  }

  *head = new_node;
}

void printLL(struct Node *head) {
  struct Node *curr = head;
  struct Node *prev = NULL;
  struct Node *next;

  while(curr != NULL) {
    printf("%d ", curr->data);

    next = XOR(prev, curr->both);

    prev = curr;
    curr = next;
  }
}

int main(int argc, char **argv) {
  printf("Daily Programming, Day-5\n");
  printf("-----------------------------------------------------------------\n");

  printf("Create an XOR doubly linked list\n");

  struct Node *head = NULL;
  add(&head, 50);
  add(&head, 40);
  add(&head, 30);
  add(&head, 20);
  add(&head, 10);

  printLL(head);
  printf("\n");
}