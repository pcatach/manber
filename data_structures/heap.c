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
  printf("Inserting %d\n", value);
  heap[size] = value;
  if (size == 0) {
    return size + 1;
  }

  int current = size;
  int parent = (current - 1) / 2;

  // bubble up
  while (heap[parent] < heap[current]) {
    printf("Exchanging %d with %d\n", heap[current], heap[parent]);
    int temp = heap[current];
    heap[current] = heap[parent];
    heap[parent] = temp;

    current = parent;
    parent = (current - 1) / 2;
  }
  return size + 1;
}

int main() {
  /*
             15
      /               \
     14                 13
   /    \             /    \
  12      11         10      9
 /  \    /  \       /  \    /  \
8    7  6    5     4    3  2    1
  */

  int size = 0;
  int *heap = (int *)malloc(32 * sizeof(int));
  if (heap == NULL) {
    printf("Memory allocation failed\n");
    exit(1);
  }

  for (int i = 1; i < 16; i++) {
    printHeap(heap, size);
    size = insertHeap(heap, size, i);
  }

  printHeap(heap, size);
  free(heap);

  return 0;
}