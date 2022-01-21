// BST class
// Creates a BST to store values
// Uses Node which holds the data
// Uses templates to store any type of data
// binarysearchtreee.cpp file is included at the bottom of the .h file
// binarysearchtreee.cpp is part of the template, cannot be compiled separately

#ifndef BSTMAP_H
#define BSTMAP_H

#include <algorithm>
#include <cstdint>
#include <iostream>
#include <queue>
#include <string>
#include <vector>
using namespace std;

class BSTMap {

  // display BST tree in a human-readable format
  // comment out printSideways or printVertical
  friend ostream &operator<<(ostream &out, const BSTMap &bst);

public:
  using key_type = string;
  using mapped_type = uint64_t;
  using value_type = pair<key_type, mapped_type>;

  // constructor, empty tree
  BSTMap() = default;

  // copy constructor
  BSTMap(const BSTMap &bst);

  // given an array of length n
  // create a tree to have all items in that array
  // with the minimum height (uses same helper as rebalance)
  explicit BSTMap(const vector<value_type> &v);

  // destructor
  virtual ~BSTMap();

  // move not allowed
  BSTMap(BSTMap &&other) = delete;

  // assignment not allowed
  BSTMap &operator=(const BSTMap &other) = delete;

  // move assignment not allowed
  BSTMap &operator=(BSTMap &&other) = delete;

  // true if no nodes in BST
  bool empty() const;

  // Number of nodes in BST
  int size() const;

  // 0 if empty, 1 if only root, otherwise
  // height of root is max height of subtrees + 1
  int height() const;

  // delete all nodes in tree
  void clear();

  // true if item is in BST
  bool contains(const key_type &key) const;

  // same as contains, but returns 1 or 0
  // compatibility with std::map
  size_t count(const key_type &k) const;

  // If k matches the key returns a reference to its value
  // If k does not match any key, inserts a new element
  // with that key and returns a reference to its mapped value.
  mapped_type &operator[](const key_type &k);

  // inorder traversal: left-root-right
  // takes a function that takes a single parameter of type T
  void inorder(void visit(const value_type &item)) const;

  // preorder traversal: root-left-right
  void preorder(void visit(const value_type &item)) const;

  // postorder traversal: left-right-root
  void postorder(void visit(const value_type &item)) const;

  // balance the BST by saving all nodes to a vector inorder
  // and then recreating the BST from the vector
  void rebalance();

  // returns true if item successfully erased - BONUS
  bool erase(const key_type &k);

  // return a vector which contains all nodes staring with k (a string)
  vector<value_type> getAll(const key_type &k) const;

  // trees are equal if they have the same structure
  // AND the same item values at all the nodes
  bool operator==(const BSTMap &other) const;

  // not == to each other
  bool operator!=(const BSTMap &other) const;

private:
  // Node for BST
  struct Node {

    // constructor, for easy insertion
    explicit Node(value_type item)
            : data(std::move(std::move(std::move(std::move(std::move(std::move(item))))))), left(nullptr), right(nullptr) {};
    // key-value pair
    value_type data;
    // children
    struct Node *left;
    struct Node *right;
  };

  // refer to data type "struct Node" as Node
  using Node = struct Node;

  // print Node
  friend ostream &operator<<(ostream &out, const Node &n);

  // root of the tree
  Node *root{nullptr};

  // print tree sideways with root on left
  static ostream &printSideways(ostream &out, const Node *curr, int level = 0);

  // helper for printVertical
  static ostream &centeredPrint(ostream &out, int space, const string &str,
                                char fillChar = ' ');

  // print tree with the root at top
  static ostream &printTreeLevel(ostream &out, queue<const Node *> &q,
                                 int width, int depth, int maxDepth);

  // helper function for displaying tree sideways, works recursively
  static ostream &printVertical(ostream &out, Node *curr);

  // height of a Node, nullptr is 0, root is 1, static, no access to 'this'
  // helper function to height(), used by printVertical
  static int getHeight(const Node *n);

  // size of the tree, static, no access to 'this'
  // helper function to size(). 
  // works recursively
  static int getSize(const Node *node);

  // check if the tree contains a node or not, static, no access to 'this'
  // helper function to contains().
  static bool containsHelper(const Node *node, const key_type &key);

  // check weather two trees are equal, static, no access to 'this'
  // helper function to == and !=, works recursively.
  static bool isEqual (const Node *p, const Node *q);

  // convert the tree to vector inorder.
  // helper function to rebalance() and constructor;
  void toVector(Node *node, vector<value_type> &v) const;

  // build the tree with the sorted(inorder) vector
  // helper function to rebalance() and constructor;
  void build(const vector<value_type> &v, int lo, int hi);

  // inorder traversal: left-root-right
  // helper function to inorder(void visit(const value_type &item))
  // works recursively
  void inorderHelper(Node *node, void visit(const value_type &item)) const;

  // postorder traversal: left-right-root
  // helper function to postorder(void visit(const value_type &item))
  // works recursively
  void postorderHelper(Node *node, void visit(const value_type &item)) const;

  // preorder traversal: root-left-right
  // helper function to preorder(void visit(const value_type &item))
  // works recursively
  void preorderHelper(Node *node, void visit(const value_type &item)) const;

  // insert a new node with given input value 
  mapped_type &insert(const value_type &item);

  // delete all the nodes
  // helper function to clear()
  // works recursively
  void clearHelper(Node *node);

  // copy another tree
  // helper function to copy constructor 
  // works recursively 
  void copy(Node *node);

  // search a given target
  // return the mapped_value
  // helper function to [] 
  // pre: item exists.
  mapped_type &search(Node *node, const key_type &key);

  // check if a node is leaf 
  // helper function to erase()
  bool isLeaf(Node *node) const;

  // find the smallest value in the right subtree of a given node 
  // helper function to erase()
  Node *getSuccessor (Node *node) const;

  // add all nodes staring with k (a string)
  // helper function to getAll()
  void getAllHelper (Node *node, const key_type &k, vector<value_type> &v) const;
};

#endif // BSTMAP_H
