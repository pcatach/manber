#ifndef BINARY_SEARCH_TREE_H
#define BINARY_SEARCH_TREE_H

typedef struct Node {
  int value;
  struct Node *left;
  struct Node *right;
} Node;

void printTree(Node *node);
void freeTree(Node *node);
void insertNode(Node **node, int value);
void deleteNode(Node **node, int value);
Node *searchNode(Node *root, int value);
Node *nonRecursiveSearchNode(Node *root, int value);
Node *findNext(Node *root, int value);
Node *findNextK(Node *root, int value, int k);
Node *findSmallest(Node *root, int k);

#endif // BINARY_SEARCH_TREE_H