#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node {
  const char *name;
  int data;
  struct Node *left;
  struct Node *right;
} Node;

Node *initNode(const char *name, int data) {
  Node *node = (Node*)malloc(sizeof(Node));
  node->name = name;
  node->data = data;
  node->left = NULL;
  node->right = NULL;
  return node;
}

void serialization(Node *node) {

  if(node == NULL) {
    return;
  }

  serialization(node->left);

  printf("%d ", node->data);
  
  serialization(node->right);
}

Node *deserialization(char *string_tree, int data) {

  int size = strlen(string_tree);
  if(data == size) { 
    printf("reached end\n");
    return NULL;
  }

  char s = string_tree[data];

  if(s == 45) {
    printf("found a negative\n");
    return NULL;
  }

  Node *node = initNode("node", string_tree[data]);

  data++;
  deserialization(string_tree, data);
  
  return node;
}

int main(int argc, char** argv) {
  printf("Daily Programming, Day-3\n");
  printf("-----------------------------------------------------------------\n");

  printf("Given a root to a binary tree...\n");
  printf("Implement serialize, which serializes tree into a string...\n");
  printf("And deserialize, which deserializes string to tree\n\n");

  printf("Serialization of tree to string\n");
  Node *root = initNode("root", 0);

  root->left = initNode("root left", 1);
  Node *rootLeft = root->left;
  root->right = initNode("root left", 2);
  Node *rootRight = root->right;


  rootLeft->left = initNode("left left", 3);
  Node *rootLeftLeft = rootLeft->left;
  rootLeft->right = initNode("left right", 4);
  Node *rootLeftRight = rootLeft->right;

  rootRight->left = initNode("right left", 5);
  Node *rootRightLeft = rootRight->left;

  rootLeftLeft->left = initNode("left left left", 6);
  Node *rootLeftLeftLeft = rootLeftLeft->left;

  serialization(root);
  printf("\n");

  printf("Deserialization of string to tree\n");
  char tree[] = "123-1";

  Node *deserialTree = deserialization(tree, 0);
}