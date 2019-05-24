#include <stdio.h>
#include <stdlib.h>

struct Node {
  int data;
  struct Node *left;
  struct Node *right;
};

struct Node *newNode(int data) {
  struct Node *node = (struct Node *)malloc(sizeof(struct Node));
  node->data = data;
  node->left = NULL;
  node->right = NULL;
  return node;
}

bool countUnivalTreeHelper(struct Node *root, int *counter) {
  if(!root) {
    return true;
  }

  bool left = countUnivalTreeHelper(root->left, counter);
  bool right = countUnivalTreeHelper(root->right, counter);

  if(left && right) {
    struct Node *rootLeft = root->left;
    struct Node *rootRight = root->right;

    // if leaf  
    if(!rootLeft && !rootRight) {
      (*counter)++;
      return true;
    }

    // left and right child exist and their data matches root
    else if(rootLeft && rootRight && rootLeft->data == root->data && rootRight->data == root->data) {
      (*counter)++;
      return true;
    }

    // only left child data matches root
    else if(rootLeft && rootLeft->data == root->data) {
      (*counter)++;
      return true;
    }

    // only right child data matches root
    else if(rootRight && rootRight->data == root->data) {
      (*counter)++;
      return true;
    }
  
  }
  return false;
}

int countUnivalTree(struct Node *root) {
  int counter = 0;
  countUnivalTreeHelper(root, &counter);
  return counter;
}

int main(int argc, char **argv) {
  printf("Daily Programming, Day-7\n");
  printf("-----------------------------------------------------------------\n");

  struct Node *root = newNode(0);
  root->left = newNode(1);
  root->right = newNode(0);
  root->right->left = newNode(1);
  root->right->right = newNode(0);
  root->right->left->left = newNode(1);
  root->right->left->right = newNode(1);

  int result = countUnivalTree(root);
  printf("%d\n", result);
}