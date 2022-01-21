// Autocomplete class 
// read file and store into the BSTMap object
// use std::sort to sort the output by weight desc

#include "autocomplete.h"
#include <algorithm>
#include <fstream>

using namespace std;

void testBSTAll();

// reads a file and stores all objects in the BST
void Autocomplete::readFile(const string &fileName) {
  ifstream ifs(fileName);

  // TODO(student)
  if (!ifs) {
    cout << "Invalid file names!" << endl;
    return;
  }
  // skip the first line and get the number of lines
  int lines;
  ifs >> lines;
  string contents;
  for (int i = 0; i < lines; i++) {
    getline(ifs, contents, '\t');
    uint64_t value = stoi(contents);
    getline(ifs, contents);
    string key = contents;
    phrases[key] = value;
  }
  ifs.close();
  phrases.rebalance();
  // cout << phrases << endl;
}

// sorting rule
bool Autocomplete::sortByWeight(BSTMap::value_type &a, BSTMap::value_type &b) {
  return a.second > b.second;
}

// return the sorted vector of all node starting with prefix(a string)
vector<BSTMap::value_type>
Autocomplete::complete(const BSTMap::key_type &prefix) const {
  vector<BSTMap::value_type> v;
  // TODO(student)
  v = phrases.getAll(prefix);
  sort(v.begin(), v.end(), sortByWeight);
  return v;
}
