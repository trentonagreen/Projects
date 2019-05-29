#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <bits/stdc++.h>

#define ALPHABET_SIZE 26
#define CHAR_TO_IDX(c) ((int)c - (int)'a')

typedef struct TrieNode {
  struct TrieNode *children[ALPHABET_SIZE];

  bool isEndWord;
} TrieNode;

struct TrieNode *CreateNode() {
  struct TrieNode *node = (TrieNode *)malloc(sizeof(TrieNode));
  node->isEndWord = false;

  for(int i = 0; i < ALPHABET_SIZE; i++) {
    node->children[i] = NULL;
  }
  return node;
}

void insert(struct TrieNode *root, const char* key) {
  struct TrieNode *crawl = root;

  for(int i = 0; i < strlen(key); i++) {
    int idx = CHAR_TO_IDX(key[i]);

    if(!crawl->children[i]) {
      crawl->children[i] = CreateNode();
    }

    crawl = crawl->children[i];
  }

  crawl->isEndWord = true;
}

bool search(struct TrieNode *root, const char *key) {
  struct TrieNode *crawl = root;

  for(int i = 0; i < strlen(key); i++) {
    int idx = CHAR_TO_IDX(key[i]);

    if(!crawl->children[i]) {
      return false;
    }

    crawl = crawl->children[i];
  }

  return (crawl != NULL && crawl->isEndWord);
}

bool isLast(struct TrieNode *root) {
  for(int i = 0; i <ALPHABET_SIZE; i++) {
    if(root->children[i]) {
      return 0;
    }
  }
  return 1;
}

void SuggestRecur(struct TrieNode *root, string currPrefix) {
  if(root->isEndWord) {
    printf("%s\n", currPrefix);
  }

  if(isLast(root)) {
    return;
  }

}

int main(int argc, char **argv) {
  printf("Daily Programming, Day-9\n");
  printf("-----------------------------------------------------------------\n");
  
}