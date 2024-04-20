/*
Chapter 4, exercises 3, 4, 15
*/

#include "binary_search_tree.h"
#include <stdio.h>
#include <stdlib.h>

void printTree(Node *node) {
  // prints binary tree in the implicit representation
  if (!node) {
    return;
  }
  printf("%d ", node->value);
  printTree(node->left);
  printTree(node->right);
}

void freeTree(Node *node) {
  if (!node) {
    return;
  }
  Node *left = node->left;
  Node *right = node->right;
  free(node);
  freeTree(left);
  freeTree(right);
}

void insertNode(Node **root, int value) {
  // insertNode needs to take a Node** (pointer to a pointer to Node) instead of
  // Node* because it potentially modifies the root pointer itself
  // O(log n)
  Node *new_node = (Node *)malloc(sizeof(Node));
  if (!new_node) {
    printf("Failed to allocate memory.\n");
    exit(1);
  }
  new_node->value = value;
  new_node->left = NULL;
  new_node->right = NULL;

  if (!*root) {
    *root = new_node;
    return;
  }

  Node *current = *root;
  while (current) {
    if (value == current->value) {
      // repeated value, ignore
      return;
    }

    if (value > current->value) {
      if (!current->right) {
        current->right = new_node;
        return;
      } else {
        current = current->right;
      }
    } else if (value < current->value) {
      if (!current->left) {
        current->left = new_node;
        return;
      } else {
        current = current->left;
      }
    }
  }
}

Node *searchNode(Node *node, int value) {
  // O(log n)
  if (!node || value == node->value) {
    return node;
  } else if (value < node->value) {
    return searchNode(node->left, value);
  } else {
    return searchNode(node->right, value);
  }
}

Node *nonRecursiveSearchNode(Node *root, int value) {
  // O(log n)
  Node *current = root;
  while (current) {
    if (value == current->value) {
      return current;
    } else if (value < current->value) {
      current = current->left;
    } else {
      current = current->right;
    }
  }
  return NULL;
}

void deleteNode(Node **root, int value) {
  // O(log n)
  // if (!*root) {
  //   return;
  // }
}

int main() {
  /*
          4
        /   \
      2       5
     / \       \
    0   3       6
     \
      1
  */
  Node *root = NULL;
  insertNode(&root, 4);
  insertNode(&root, 2);
  insertNode(&root, 5);
  insertNode(&root, 6);
  insertNode(&root, 3);
  insertNode(&root, 0);
  insertNode(&root, 1);

  printTree(root);
  printf("\n");

  printf("Search for 2\n");
  Node *node_two = searchNode(root, 2);
  printTree(node_two);
  printf("\n");

  printf("Nonrecursive search for 5\n");
  Node *node_five = nonRecursiveSearchNode(root, 5);
  printTree(node_five);
  printf("\n");

  printf("Search for 7\n");
  Node *node_seven = searchNode(root, 7);
  printTree(node_seven);
  printf("\n");

  printf("Nonrecursive search for 8\n");
  Node *node_eight = nonRecursiveSearchNode(root, 8);
  printTree(node_eight);
  printf("\n");

  printf("Insert repeated 6\n");
  insertNode(&root, 6);
  printTree(root);
  printf("\n");

  printf("Delete 7\n");
  deleteNode(&root, 7);
  printTree(root);
  printf("\n");

  printf("Delete 5\n");
  deleteNode(&root, 5);
  printTree(root);
  printf("\n");
  /*
          4
        /   \
      2       6
     / \
    0   3
     \
      1
  */

  printf("Delete 6\n");
  deleteNode(&root, 6);
  printTree(root);
  printf("\n");
  /*
          4
        /
      2
     / \
    0   3
     \
      1
  */

  printf("Delete 2\n");
  deleteNode(&root, 2);
  printTree(root);
  printf("\n");
  /*
          4
        /
      1
     / \
    0   3
  */

  printf("Delete 1\n");
  deleteNode(&root, 1);
  printTree(root);
  printf("\n");
  /*
          4
        /
      0
       \
        3
  */

  freeTree(root);
  return 0;
}