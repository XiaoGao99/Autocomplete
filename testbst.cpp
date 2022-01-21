// /**
//  * Testing BST - Binary Search Tree functions
//  *
//  * This file has series of tests for BST
//  * Each test is independent and uses assert statements
//  * Test functions can only use the public functions from BST
//  * testBSTAll() is called from main in main.cpp
//  * testBSTAll calls all other functions
//  */

#include "bstmap.h"
#include <cassert>
#include <sstream>

using namespace std;

// global value for testing
// NOLINTNEXTLINE
stringstream globalSS;

// need to reset SS before calling this
void printer(const BSTMap::value_type &p) {
  globalSS << "[" << p.first << "=" << p.second << "]";
}

// // Testing == and []
void test01() {
  cout << "Starting test01" << endl;
  cout << "* Testing ==, !=, [] and copy constructor" << endl;
  BSTMap b1;
  auto val = b1["hello"];
  assert(val == 0);
  b1["hello"] = 5;
  val = b1["hello"];
  assert(val == 5);
  b1["world"] = 42;

  BSTMap b2;
  assert(b1 != b2);
  b2["hello"] = 5;
  b2["world"] = 42;
  assert(b1 == b2);

  BSTMap b3(b2);
  assert(b1 == b3);
  cout << "Ending tes01" << endl;
}

// Testing traversal
void test02() {
  cout << "Starting test02" << endl;
  cout << "* Testing traversal" << endl;
  BSTMap b;
  b["x"] = 10;
  b["f"] = 5;
  b["b"] = 3;
  b["e"] = 4;
  b["z"] = 50;
  // cout << b;

  globalSS.str("");
  b.inorder(printer);
  string order = globalSS.str();
  assert(order == "[b=3][e=4][f=5][x=10][z=50]");

  globalSS.str("");
  b.preorder(printer);
  order = globalSS.str();
  assert(order == "[x=10][f=5][b=3][e=4][z=50]");

  globalSS.str("");
  b.postorder(printer);
  order = globalSS.str();
  assert(order == "[e=4][b=3][f=5][z=50][x=10]");
  cout << "Ending test02" << endl;
}

// Testing rebalance
void test03() {
  cout << "Starting test03" << endl;
  cout << "* Testing rebalance" << endl;
  BSTMap b;
  b["1"] = 1;
  b["2"] = 2;
  b["3"] = 3;
  b["4"] = 4;
  b["5"] = 5;
  b["6"] = 6;
  assert(b.height() == 6);
  // cout << b << endl;
  b.rebalance();
  assert(b.height() == 3);
  // cout << b << endl;
  b.clear();
  assert(b.height() == 0);
  cout << "Ending test03" << endl;
}

void test04() {
  cout << "Starting test04" << endl;
  cout << "* Testing size(), contains(), empty(), erase(), count()" << endl;
  BSTMap b;
  assert(b.empty());
  b["1"] = 1;
  b["2"] = 2;
  b["3"] = 3;
  b["4"] = 4;
  b["5"] = 5;
  b["6"] = 6;
  assert(b.contains("2"));
  assert(b.count("2") == 1);
  assert(b.size() == 6);
  assert(b.erase("2"));
  assert(!b.contains("2"));
  assert(b.count("2") == 0);
  assert(b.size() == 5);
  assert(b.count("6") == 1);
  assert(!b.empty());
  assert(b.erase("1"));
  assert(!b.erase("2"));
  assert(b.erase("3"));
  assert(b.erase("4"));
  assert(b.erase("5"));
  assert(b.erase("6"));
  assert(b.empty());
  b["1"] = 1;
  b["2"] = 2;
  b["3"] = 3;
  b["4"] = 4;
  b["5"] = 5;
  b["6"] = 6;
  b.rebalance();
  assert(b.erase("5"));
  assert(b.erase("1"));
  assert(b.erase("6"));
  assert(b.size() == 3);
  cout << "Ending test04" << endl;
}

void test05() {
  cout << "Starting test05" << endl;
  cout << "* Testing for getAll() and construor" << endl;
  BSTMap b;
  b["Hello world"] = 0;
  b["Hello!"] = 1;
  b["Hello"] = 2;
  b["Hell"] = 3;
  b["Haha"] = 4;

  vector<BSTMap::value_type> v;
  v = b.getAll("Hello");
  assert(v.size() == 3);
  BSTMap m(v);
  assert(m.size() == 3);
  v = b.getAll("H");
  assert(v.size() == 5);
  v = b.getAll("Hello!");
  assert(v.size() == 1);
  v = b.getAll("R");
  assert(v.empty());
  cout << "Ending test05" << endl;
}
// // Calling all test functions
void testBSTAll() {
  test01();
  test02();
  test03();
  test04();
  test05();
}