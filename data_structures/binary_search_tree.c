/*
Chapter 4, exercises 3, 4, 15, 16, 17

Obs: many of these data structures could be implemented as AVL trees
to keep worst case O(log n), but that would make this code much harder
to follow.
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
      free(new_node);
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

Node *findNext(Node *root, int value) {
  // O(log n)
  // find the smallest value in the BST that is greater than value
  Node *current = root;
  Node *next = NULL;
  while (current) {
    if (current->value <= value) {
      // no node in the left subtree will be > value
      // so we can trim here
      current = current->right;
    } else {
      // check if it's the smallest we found so far
      if (!next || (current->value < next->value)) {
        next = current;
      }
      current = current->left;
    }
  }
  return next;
}

Node *findNextK(Node *root, int value, int k) {
  // O(k *log n)
  // find the kth smallest value after value
  Node *current = nonRecursiveSearchNode(root, value);
  if (!current) {
    return NULL;
  }
  // find kth next node
  for (int i = 0; i < k; i++) {
    current = findNext(root, current->value);
    if (!current)
      return NULL;
  }
  return current;
}

Node *findSmallest(Node *root, int k) {
  // O(k*log n)
  // find the (k-1)th smallest value in the tree

  if (k < 1 || !root) {
    return NULL;
  }

  // first find the smallest
  Node *smallest = root;
  while (smallest->left)
    smallest = smallest->left;

  // find kth next node
  Node *ith_smallest = smallest;
  for (int i = 0; i < k - 1; i++) {
    ith_smallest = findNext(root, ith_smallest->value);
  }
  return ith_smallest;
}

void deleteNode(Node **root, int value) {
  // Note: we assume the root is never deleted
  // O(log n)
  if (!*root) {
    return;
  }

  Node *parent = NULL;
  Node *current = *root;
  // find node
  while (current) {
    if (value == current->value) {
      break;
    } else if (value > current->value) {
      parent = current;
      current = current->right;
    } else {
      parent = current;
      current = current->left;
    }
  }
  // if couldn't find, return
  if (!current)
    return;

  // cases for 0, 1 or 2 children
  if (!current->left) {
    if (value < parent->value) {
      parent->left = current->right;
    } else {
      parent->right = current->right;
    }
  } else if (!current->right) {
    if (value < parent->value) {
      parent->left = current->left;
    } else {
      parent->right = current->left;
    }
  } else {
    // two children case
    // set node's value to the rightmost node in the node's left subtree
    Node *rightmost_parent = current;
    Node *rightmost = current->left;
    while (rightmost->right) {
      rightmost_parent = rightmost;
      rightmost = rightmost->right;
    }

    current->value = rightmost->value;
    if (rightmost_parent == current) {
      rightmost_parent->left = rightmost->left;
    } else {
      rightmost_parent->right = rightmost->right;
    }
    free(rightmost);
    return;
  }
  free(current);
}

int main() {
  /*
          4
        /   \
      2       5
     / \       \
    0   3       6
   / \
 -1   1
  */
  Node *root = NULL;
  int values[] = {4, 2, 5, 6, 3, 0, 1, -1};
  for (int i = 0; i < 8; i++) {
    insertNode(&root, values[i]);
  }

  printTree(root);
  printf("\n");

  int search_values[] = {2, 7};
  for (int i = 0; i < 2; i++) {
    printf("Search for %d\n", search_values[i]);
    Node *found = searchNode(root, search_values[i]);
    printTree(found);
    printf("\n");
  }

  int non_recursive_search_values[] = {5, 8};
  for (int i = 0; i < 2; i++) {
    printf("Non-recursive search for %d\n", non_recursive_search_values[i]);
    Node *found = nonRecursiveSearchNode(root, non_recursive_search_values[i]);
    printTree(found);
    printf("\n");
  }

  printf("Insert repeated 6\n");
  insertNode(&root, 6);
  printTree(root);
  printf("\n");

  printf("Find next to 1\n");
  Node *next = findNext(root, 1);
  printTree(next);
  printf("\n");

  printf("Find 3rd next to 2\n");
  Node *thirdNextToTwo = findNextK(root, 2, 3);
  printTree(thirdNextToTwo);
  printf("\n");

  printf("Find the 4th smallest value\n");
  Node *fourthSmallest = findSmallest(root, 4);
  printTree(fourthSmallest);
  printf("\n");

  int delete_values[] = {7, 5, 6, 2, 1};
  for (int i = 0; i < 5; i++) {
    printf("Delete %d\n", delete_values[i]);
    deleteNode(&root, delete_values[i]);
    printTree(root);
    printf("\n");
  }

  /*
  Delete 5
          4
        /   \
      2       6
     / \
    0   3
   / \
  -1  1
  Delete 6
          4
        /
      2
     / \
    0   3
   / \
  -1  1
  Delete 2
          4
        /
      1
     / \
    0   3
   /
  -1
  Delete 1
           4
        /
      0
     / \
   -1   3
  */

  freeTree(root);
  return 0;
}