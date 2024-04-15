/*
Chapter 4, exercises 5, 6, 13
*/
#include <stdio.h>
#include <stdlib.h>

int *buildHeap() {
  int *heap = (int *)malloc(32 * sizeof(int));
  if (heap == NULL) {
    printf("Memory allocation failed\n");
    exit(1);
  }
  return heap;
}

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

void swap(int *heap, int first, int second) {
  int temp = heap[first];
  heap[first] = heap[second];
  heap[second] = temp;
}

int insertHeap(int *heap, int size, int value) {
  // O(log n)
  int current = size;
  // bubble up
  while (current > 0) {
    // if parent is at n, children are at 2*n + 1 and 2*n + 2.
    int parent = (current - 1) / 2;
    if (heap[parent] >= value) {
      break;
    }

    // swap(heap, current, parent);
    // can save an extra assignment if I just move the parent
    heap[current] = heap[parent];

    current = parent;
  }
  heap[current] = value;
  return size + 1;
}

int removeHeap(int *heap, int size, int *dest) {
  // O(log n)
  // pop out max of heap
  *dest = heap[0];
  // replace with last leaf
  heap[0] = heap[size - 1];
  size -= 1;

  int parent = 0;
  int child = 1;

  // flow down
  while (child < size) {
    // use max(child1, chil2)
    if (heap[child] < heap[child + 1]) {
      child = child + 1;
    }

    if (heap[parent] < heap[child]) {
      swap(heap, parent, child);
      parent = child;
      child = 2 * child + 1;
    } else {
      break;
    }
  }

  return size;
}

void mergeHeaps(int *heap1, int *size1, int *heap2, int *size2) {
  // NOTE: will change heap1 and destroy heap2!
  // O(m * log(n + m))
  int current;
  while (*size2 > 0) {
    *size2 = removeHeap(heap2, *size2, &current);
    *size1 = insertHeap(heap1, *size1, current);
  }
}

int main() {
  int size1 = 0;
  int *heap1 = buildHeap();
  int size2 = 0;
  int *heap2 = buildHeap();

  for (int i = 1; i < 6; i++) {
    size1 = insertHeap(heap1, size1, 2 * i - 1);
    size2 = insertHeap(heap2, size2, 2 * i);
  }

  printHeap(heap1, size1);
  printHeap(heap2, size2);

  mergeHeaps(heap1, &size1, heap2, &size2);
  printHeap(heap1, size1);

  free(heap1);
  free(heap2);

  return 0;
}