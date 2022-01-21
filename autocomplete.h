// Autocomplete class 
// read file and store into the BSTMap object
// use std::sort to sort the output by weight desc
#ifndef AUTOCOMPLETE_H
#define AUTOCOMPLETE_H

#include "bstmap.h"
using namespace std;

class Autocomplete {
public:
  Autocomplete() = default;
  
  // reads a file and stores all objects in the BST
  void readFile(const string &fileName);

  // return the sorted vector of all node starting with prefix(a string)
  vector<BSTMap::value_type> complete(const string &prefix) const;

private:
  // BST of phrases and their frequency
  BSTMap phrases;

  // sorter
  bool static sortByWeight(BSTMap::value_type &a, BSTMap::value_type &b);
};

#endif // AUTOCOMPLETE_H
