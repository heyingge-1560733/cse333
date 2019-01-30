// 1560733
// heyingge@uw.edu
// "Copyright [2018] <Yingge He>"  [legal/copyright]
// This program prints out all integers that are factors
// of the input positive integer.

#include <iostream>
#include <cstdlib>
#include <cinttypes>

using namespace std;

int main(int argc, char** argv) {
  int64_t num;
  cout << "Which positive integer would you like me to factorize? ";
  cin >> num;  // read from stdin

  if (num < 1) {
    cout << "A non-positive integer was passed in." << endl;
    return EXIT_FAILURE;  // exit safely
  }

  cout << 1;  // 1 is always the factor of any integer itself
  for (int64_t i = 2; i <= num; i++) {
    if (num % i == 0) {  // i is the factor if num mod i is 0
      cout << " " << i;
    }
  }
  cout << endl;
  return EXIT_SUCCESS;  // success
}
