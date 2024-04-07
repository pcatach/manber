/*
Chapter 4, exercises 5 and 6
*/
#include <stdio.h>
#include <stdlib.h>

void printHeap(int *heap, int size) {
  if (heap == NULL || size <= 0) {
    printf("Heap is empty or NULL\n");
    return;
  }

  for (int i = 0; i < size - 1; i++) {
    printf("%d, ", heap[i]);
  }
  printf("%d\n", heap[size - 1]);
}

int insertHeap(int *heap, int size, int value) {
  int current = size;
  while (current > 0) {
    // if parent is at n, children are at 2*n + 1 and 2*n + 2.
    int parent = (current - 1) / 2;
    if (heap[parent] >= value) {
      break;
    }

    // int temp = heap[current];
    // heap[current] = heap[parent];
    // heap[parent] = temp;
    // can save an extra assignment if I just move the parent
    heap[current] = heap[parent];

    current = parent;
  }
  heap[current] = value;
  return size + 1;
}

int main() {
  /*
             15
      /               \
     10                 14
   /    \             /    \
  7      9           11      13
 /  \    /  \       /  \    /  \
1    4  3    8     2    6  5    12

15, 10, 14, 7, 9, 11, 13, 1, 4, 3, 8, 2, 6, 5, 12
*/

  int size = 0;
  int *heap = (int *)malloc(32 * sizeof(int));
  if (heap == NULL) {
    printf("Memory allocation failed\n");
    exit(1);
  }

  for (int i = 1; i < 16; i++) {
    // printHeap(heap, size);
    size = insertHeap(heap, size, i);
  }

  printHeap(heap, size);
  free(heap);

  return 0;
}