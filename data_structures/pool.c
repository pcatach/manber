/*
Chapter 4, exercises 10 to 12
*/
#include <stdio.h>
#include <stdlib.h>

#define MAX_JOB 32

typedef int Pool;

void printPool(Pool *pool) {
  for (int i = 0; i < MAX_JOB - 1; i++) {
    printf("%d, ", pool[i]);
  }
  printf("%d\n", pool[MAX_JOB - 1]);
}

void addJob(Pool *pool, int job) {
  int hashed_job = job % MAX_JOB;
  // printf("Hash of %d is %d\n", job, hashed_job);
  pool[hashed_job] = job;
}

void removeJob(Pool *pool, int *job) {
  for (int i = 0; i < MAX_JOB; i++) {
    if (pool[i] != 0) {
      *job = pool[i];
      pool[i] = 0;
      return;
    }
  }
}

int main() {
  Pool *pool = (Pool *)malloc(MAX_JOB * sizeof(Pool));
  if (pool == NULL) {
    printf("Memory allocation failed\n");
    exit(1);
  }
  for (int i = 0; i < MAX_JOB; i++) {
    // initialise pool to 0
    pool[i] = 0;
  }

  printPool(pool);
  addJob(pool, 1);
  addJob(pool, 2);
  addJob(pool, 3);
  addJob(pool, 3);
  addJob(pool, 3);
  addJob(pool, 31);
  addJob(pool, 30);
  addJob(pool, 12);
  addJob(pool, 15);
  printPool(pool);

  int next_job;
  removeJob(pool, &next_job);
  printf("Next job is %d\n", next_job);
  removeJob(pool, &next_job);
  printf("Next job is %d\n", next_job);
  removeJob(pool, &next_job);
  printf("Next job is %d\n", next_job);
  printPool(pool);

  free(pool);
  return 0;
}