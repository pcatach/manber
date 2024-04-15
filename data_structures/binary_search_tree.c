/*
Chapter 4, exercises 3 and 4

To compile: gcc binary_search.c
*/

#include "binary_search_tree.h"
#include <stdio.h>
#include <stdlib.h>

void printTree(Node **node) {
  // prints binary tree in the implicit representation
  if (!*node) {
    return;
  }
  printf("%d ", (*node)->value);
  printTree(&(*node)->left);
  printTree(&(*node)->right);
}

void freeNode(Node **node) {
  if (!*node) {
    return;
  }
  Node *left = (*node)->left;
  Node *right = (*node)->right;
  free(*node);
  freeNode(&left);
  freeNode(&right);
}

void insertNode(Node **node, int value) {
  // O(log n)
  if (!*node) {
    Node *new_node = (Node *)malloc(sizeof(Node));
    if (!node) {
      printf("Failed to allocate memory.\n");
      exit(1);
    }
    new_node->value = value;
    new_node->left = NULL;
    new_node->right = NULL;
    *node = new_node;
    return;
  }

  if (value <= (*node)->value) {
    insertNode(&(*node)->left, value);
  } else {
    insertNode(&(*node)->right, value);
  }
}

Node *search(Node **node, int value) {
  // O(log n)
  if (value == (*node)->value) {
    return *node;
  } else if (value <= (*node)->value) {
    return search(&(*node)->left, value);
  } else {
    return search(&(*node)->right, value);
  }
}

Node *nonRecursiveSearch(Node **root, int value) {
  // O(log n)
  Node *current = *root;
  while (current) {
    if (value == current->value) {
      return current;
    } else if (value <= current->value) {
      current = current->left;
    } else {
      current = current->right;
    }
  }
  return NULL;
}

int main() {
  /*
          4
        /   \
      2       5
     / \       \
    1   3       6
  */
  Node *root = NULL;
  insertNode(&root, 4);
  insertNode(&root, 2);
  insertNode(&root, 5);
  insertNode(&root, 6);
  insertNode(&root, 3);
  insertNode(&root, 1);

  printTree(&root);
  printf("\n");

  printf("Search for 2\n");
  Node *nodeTwo = search(&root, 2);
  printTree(&nodeTwo);
  printf("\n");

  printf("Nonrecursive search for 5\n");
  Node *nodeFive = search(&root, 5);
  printTree(&nodeFive);
  printf("\n");

  freeNode(&root);
  return 0;
}