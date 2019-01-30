// 1560733
// heyingge@uw.edu
// "Copyright [2018] <Yingge He>"  [legal/copyright]
// This program serves to test struct vector.

#include "Vector.h"
#define N 10  // Test vector length.

// Print the elements in the vector on a line.
static void PrintIntVector(vector_t v);

int main(int argc, char *argv[]) {
  uint32_t i;
  vector_t v = VectorCreate(4);

  if (v == NULL)
    return EXIT_FAILURE;

  for (i = 0; i < N; ++i) {  // Place some elements in the vector.
    int *x = (int*)malloc(sizeof(int));
    *x = i;
    element_t old;
    VectorSet(v, i, x, &old);
  }

  PrintIntVector(v);
  VectorFree(v);
  return EXIT_SUCCESS;
}

static void PrintIntVector(vector_t v) {
  uint32_t i;
  size_t length;

  assert(v != NULL);

  length = VectorLength(v);

  if (length > 0) {
    printf("[%d", *((int*)VectorGet(v, 0)));
    for (i = 1; i < VectorLength(v); ++i)
      printf(",%d", *((int*)VectorGet(v, i)));
    printf("]\n");
  }
}
