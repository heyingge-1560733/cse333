// Yingge He
// 1560733
// heyingge@uw.edu
// "Copyright [2018] <Yingge He>"  [legal/copyright]

#include <inttypes.h>
#include <stdlib.h>
#include <stdio.h>

typedef struct {
  int32_t x;
  int32_t y;
  int32_t z;
} Point3d;

Point3d* AllocatedPoint3d(int32_t x, int32_t y, int32_t z) {
  Point3d* ptr = (Point3d*)malloc(sizeof(Point3d));
  ptr->x = x;
  ptr->y = y;
  ptr->z = z;
  if (ptr == NULL) {
    printf("Error: Fail to Allocate Memory Space for Point3d.\n");
  }
  return ptr;
}

int main() {
  int32_t x = 0;
  int32_t y = 1;
  int32_t z = 2;
  int32_t* ptr = (int32_t*)AllocatedPoint3d(x, y, z);
  if (ptr != NULL) {
    if (ptr[0] == x && ptr[1] == y && ptr[2] == z) {
      printf("Pass Test: All fields are in their allocated memory.\n");
    } else {
      printf("Fail To Pass Test: Fields are not in their allocated memory.\n");
    }
  free(ptr);
  }
}
