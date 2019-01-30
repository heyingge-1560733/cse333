// Yingge He
// 1560733
// heyingge@uw.edu
// "Copyright [2018] <Yingge He>"  [legal/copyright]
// This program reads and counts the individual words in the file.
// Then it prints a sorted list of the words and the number of times
// each word appears in the file.
#include <fstream>
#include <string>
#include <iostream>
#include <map>
#include <algorithm>

using namespace std;

// Print the key and value pair to stdout
void PrintOut(const pair<string, int>& p) {
  cout << p.first << " " << p.second << endl;
}

int main(int argc, char **argv) {
  // check the validity of the input
  if (argc != 2) {
    cout << "Invalid input file name." << endl;
    exit(EXIT_FAILURE);  // exit if invalid argument
  }

  string word, filename;
  map<string, int> wordcount;

  filename = argv[1];
  ifstream file(filename.c_str());  // open file

  if (!file.is_open()) {
    cout << "Fail to open " << filename << endl;
    exit(EXIT_FAILURE);  // exit if can't open the file
  }

  while (file >> word) {  // read words from file
    if (wordcount.count(word))
      wordcount[word]++;  // increment value if key already exists
    else
      // insert a new pair if key does not exit
      wordcount.insert(pair<string, int>(word, 1));
  }

  file.close();  // we are done, close the file
  for_each(wordcount.begin(), wordcount.end(), &PrintOut);  // print result

  return 0;  // succcess
}
