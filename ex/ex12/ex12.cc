// 1560733
// heyingge@uw.edu
// "Copyright [2018] <Yingge He>"  [legal/copyright]
// This program prompts the user to type in 10 doubles,
// reads those doubles into a vector of doubles,
// sorts the vector, and then prints out the sorted vector.

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

// Read the type T object from input stream.
// exit(EXIT_FAILURE) after printing out a helpful error message
// if detects conversion or EOF conditions.
template <typename T> T ReadValue(istream& in);

// Print the type T object to stdout.
template <typename T>
void PrintOut(const T& p) {
  cout << p << endl;
}

int main(int argc, char **argv) {
  vector<double> v;
  cout << "Input 10 doubles:" << endl;

  // add new stdin double to the end of vector, repeat 10 times
  for (int i = 0; i < 10; i++)
    v.push_back(ReadValue<double>(cin));

  // do the sorting in ascending order
  sort(v.begin(), v.end());
  cout << "Your sorted doubles are:" << endl;

  // print out each element in the vector
  for_each(v.begin(), v.end(), &PrintOut<double>);

  return EXIT_SUCCESS;  // success
}

template <typename T> T ReadValue(istream& in) {
  T value;
  in >> value;  // read from input stream

  // detects conversion or EOF conditions
  if (in.fail()) {
    cout << "Terminating...Either because of conversion or EOF." << endl;
    exit(EXIT_FAILURE);
  }

  return value;
}
