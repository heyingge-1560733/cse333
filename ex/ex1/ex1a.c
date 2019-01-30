// Yingge He
// 1560733
// heyingge@uw.edu
// "Copyright [2018] <Yingge He>"  [legal/copyright]
#include <stdio.h>

void CheckDouble(double d);
void CheckArray(int n[]);

int main() {
  double m = 8;
  int n[5] = {0, 1, 2, 3, 4};

  double old_m = m;
  CheckDouble(m);
  printf("double: pass-by-");
  if (old_m == m)
    printf("value\n");
  else
    printf("reference\n");

  int* ptr = n;
  CheckArray(n);
  printf("array of ints: pass-by-");
  if (ptr == n)
    printf("value\n");
  else
    printf("reference\n");
  return 0;
}

void CheckDouble(double d) {
  d = d + 1;
}

void CheckArray(int n[]) {
  n = n + 1;
}
