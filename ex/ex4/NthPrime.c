// Yingge He
// 1560733
// heyingge@uw.edu
// "Copyright [2018] <Yingge He>"  [legal/copyright]
// This file calculates the nth prime number, where n is the input parameter.
#include "NthPrime.h"

// this function returns 1 if the input integer is
// a prime number and 0 otherwise
int IsPrime(uint64_t n);

// specified in NthPrime.h
uint64_t NthPrime(uint16_t n) {
  uint16_t count = 0;
  uint64_t curr = 2;
  while (count < n) {
    if (IsPrime(curr)) {
      count++;
    }
    curr++;
  }
  return curr - 1;
}

int IsPrime(uint64_t n) {
  for (int i = 2; i < n; i++) {
    if (n % i == 0) {
      return 0;
    }
  }
  return 1;
}
