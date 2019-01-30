// Yingge He
// 1560733
// heyingge@uw.edu
// "Copyright [2018] <Yingge He>"  [legal/copyright]
// This file is for testing NthPrime().

#include "NthPrime.h"
#define MAX 65535  // the maximum number that uint16_t can represent

// a helper function that tests if input is valid or not and print the result
int Test(int n);

int main() {
  Test(-1);
  Test(0);
  Test(1);
  Test(2);
  Test(3);
  Test(99);
  return 1;
}

int Test(int n) {
  if (n > 0 && n <= MAX) {
    printf("%"PRIu16"th prime number is %"PRIu64".\n",
           n, NthPrime((uint16_t)n));
  } else {
    printf("Invalid Input.\n");
  }
  return 1;
}
