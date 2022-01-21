// BST class
// Creates a BST to store values
// Uses Node which holds the data

#include "bstmap.h"
#include <cassert>

using namespace std;

// copy constructor
BSTMap::BSTMap(const BSTMap &bst) {
  // clear this tree first
  this->clear();

  // then add each node
  if (bst.root == nullptr) {
    this->root = nullptr;
  } else {
    copy(bst.root);
  }
}

// given an array of length n
// create a tree to have all items in that array
// with the minimum height (uses same helper as rebalance)
BSTMap::BSTMap(const vector<value_type> &v) {
  for (const auto &i : v) {
    this->insert(i);
  }
  this->rebalance();
}

// destructor
BSTMap::~BSTMap() { clear(); }

// delete all nodes in tree
void BSTMap::clear() {
  clearHelper(this->root);
  this->root = nullptr;
}

// delete all the nodes in the tree
// helper function to clear()
// works recursively
void BSTMap::clearHelper(Node *node) {

  // if null, just return
  if (node == nullptr) {
    return;
  }

  // traversal
  clearHelper(node->left);
  clearHelper(node->right);

  // action
  delete node;
  node = nullptr;
}

// copy another tree
// helper function to copy constructor
// works recursively
void BSTMap::copy(Node *node) {
  // add root
  this->insert(node->data);

  // add left and right children
  if (node->left != nullptr) {
    copy(node->left);
  }
  if (node->right != nullptr) {
    copy(node->right);
  }
}

// true if no nodes in BST
bool BSTMap::empty() const { return this->root == nullptr; }

// insert a new node into BST
BSTMap::mapped_type &BSTMap::insert(const value_type &item) {

  // if root is null, just add to root
  if (this->root == nullptr) {
    this->root = new Node(item);
    return this->root->data.second;
  }

  // else, create the new node first
  Node *newNode = new Node(item);
  Node *curr = this->root;
  Node *parent = nullptr;

  // iter to the corret position and insert
  while (true) {
    parent = curr;
    if (item.first < parent->data.first) {
      curr = parent->left;
      if (curr == nullptr) {
        parent->left = newNode;
        return parent->left->data.second;
      }
    } else {
      curr = parent->right;
      if (curr == nullptr) {
        parent->right = newNode;
        return parent->right->data.second;
      }
    }
  }
}
// Number of nodes in BST
int BSTMap::size() const { return getSize(this->root); }

// size of the tree, static, no access to 'this'
// helper function to size().
// works recursively
int BSTMap::getSize(const Node *node) {
  if (node == nullptr) {
    return 0;
  }
  int size = 1;
  size += getSize(node->left);
  size += getSize(node->right);
  return size;
}

// true if item is in BST
bool BSTMap::contains(const key_type &key) const {
  return containsHelper(this->root, key);
}

bool BSTMap::containsHelper(const Node *node, const key_type &key) {
  if (node == nullptr) {
    return false;
  }

  if (node->data.first == key) {
    return true;
  }

  if (node->data.first > key) {
    return containsHelper(node->left, key);
  }
  return containsHelper(node->right, key);
}

// If k matches the key returns a reference to its value
// If k does not match any key, inserts a new element
// with that key and returns a reference to its mapped value.
BSTMap::mapped_type &BSTMap::operator[](const key_type &k) {
  if (this->contains(k)) {
    return this->search(this->root, k);
  }
  value_type item = value_type(k, 0);
  return this->insert(item);
}

// search a given target
// return the mapped_value
// helper function to []
// pre: item exists.
BSTMap::mapped_type &BSTMap::search(Node *node, const key_type &key) {
  if (node->data.first == key) {
    return node->data.second;
  }

  if (node->data.first > key) {
    return search(node->left, key);
  }
  return search(node->right, key);
}

// return a vector which contains all nodes staring with k (a string)
vector<BSTMap::value_type> BSTMap::getAll(const key_type &k) const {
  vector<value_type> v;
  getAllHelper(this->root, k, v);
  return v;
}

// add all nodes staring with k (a string)
// helper function to getAll()
void BSTMap::getAllHelper(Node *node, const key_type &k,
                          vector<value_type> &v) const {
  if (node == nullptr) {
    return;
  }
  string target = node->data.first.substr(0, k.length());
  if (target >= k) {
    getAllHelper(node->left, k, v);
  }

  if (target == k) {
    v.push_back(node->data);
  }

  if (target <= k) {
    getAllHelper(node->right, k, v);
  }
}

// 0 if empty, 1 if only root, otherwise
// height of root is max height of subtrees + 1
int BSTMap::height() const { return getHeight(this->root); }

// height of a Node, nullptr is 0, root is 1, static, no access to 'this'
// helper function to height(), used by printVertical
int BSTMap::getHeight(const Node *n) {
  if (n == nullptr) {
    return 0;
  }
  int left = getHeight(n->left) + 1;
  int right = getHeight(n->right) + 1;
  return left > right ? left : right;
}

// same as contains, but returns 1 or 0
// compatibility with std::map
size_t BSTMap::count(const string &k) const { return contains(k) ? 1 : 0; }

// inorder traversal: left-root-right
// takes a function that takes a single parameter of type T
void BSTMap::inorder(void visit(const value_type &item)) const {
  inorderHelper(this->root, visit);
}

// inorder traversal: left-root-right
// helper function to inorder(void visit(const value_type &item))
// works recursively
void BSTMap::inorderHelper(Node *node,
                           void visit(const value_type &item)) const {
  if (node == nullptr) {
    return;
  }
  inorderHelper(node->left, visit);
  visit(node->data);
  inorderHelper(node->right, visit);
}

// preorder traversal: root-left-right
void BSTMap::preorder(void visit(const value_type &item)) const {
  return preorderHelper(this->root, visit);
}

// preorder traversal: root-left-right
// helper function to preorder(void visit(const value_type &item))
// works recursively
void BSTMap::preorderHelper(Node *node,
                            void visit(const value_type &item)) const {
  if (node == nullptr) {
    return;
  }
  visit(node->data);
  preorderHelper(node->left, visit);
  preorderHelper(node->right, visit);
}
// postorder traversal: left-right-root
void BSTMap::postorder(void visit(const value_type &item)) const {
  return postorderHelper(this->root, visit);
}

// postorder traversal: left-right-root
// helper function to postorder(void visit(const value_type &item))
// works recursively
void BSTMap::postorderHelper(Node *node,
                             void visit(const value_type &item)) const {
  if (node == nullptr) {
    return;
  }
  postorderHelper(node->left, visit);
  postorderHelper(node->right, visit);
  visit(node->data);
}
// balance the BST by saving all nodes to a vector inorder
// and then recreating the BST from the vector
void BSTMap::rebalance() {
  vector<value_type> v;
  this->toVector(this->root, v);
  this->clear();
  this->build(v, 0, v.size() - 1);
}

// convert the tree to vector inorder.
// helper function to rebalance;
void BSTMap::toVector(Node *node, vector<value_type> &v) const {
  if (node == nullptr) {
    return;
  }
  toVector(node->left, v);
  v.push_back(node->data);
  toVector(node->right, v);
}

// build the tree with the sorted(inorder) vector
// helper function to rebalance() and constructor;
void BSTMap::build(const vector<value_type> &v, int lo, int hi) {
  if (lo > hi) {
    return;
  }
  int mid = (lo + hi) / 2;
  this->insert(v[mid]);
  build(v, lo, mid - 1);
  build(v, mid + 1, hi);
}

// trees are equal if they have the same structure
// AND the same item values at all the nodes
bool BSTMap::operator==(const BSTMap &other) const {
  return isEqual(this->root, other.root);
}

// not == to each other
bool BSTMap::operator!=(const BSTMap &other) const {
  return !isEqual(this->root, other.root);
}

// check weather two trees are equal, static, no access to 'this'
// helper function to == and !=, works recursively.
bool BSTMap::isEqual(const Node *p, const Node *q) {
  if (p == nullptr && q == nullptr) {
    return true;
  }

  if (p == nullptr || q == nullptr) {
    return false;
  }

  return (p->data.first == q->data.first) &&
         (p->data.second == q->data.second) && isEqual(p->left, q->left) &&
         isEqual(p->right, q->right);
}

// check if a node is leaf
// helper function to erase()
bool BSTMap::isLeaf(Node *node) const {
  return node->left == nullptr && node->right == nullptr;
}

// find the smallest value in the right subtree of a given node
// which is the leftmost child in the righht subtree of the given node
// helper function to erase()
BSTMap::Node *BSTMap::getSuccessor(Node *node) const {
  Node *successor = nullptr;
  Node *parent = nullptr;
  Node *curr = node->right;

  while (curr != nullptr) {
    parent = successor;
    successor = curr;
    curr = curr->left;
  }

  // if successor is not the right child of deleted node
  // then we also need to set up the value
  if (successor != node->right) {
    parent->left = successor->right;
    successor->right = node->right;
  }
  return successor;
}

// detele a node
// return true if delete successfully
bool BSTMap::erase(const key_type &k) {

  // There will be four cases:
  // case 1 : the target node does not exist in the tree
  // case 2 : the target node is a leaf node
  // case 3 : the target node has one child
  // case 4 : the target node has two children

  Node *parent = this->root;
  Node *curr = this->root;
  bool isLeft = false;

  // move to the postion
  while (curr != nullptr && curr->data.first != k) {
    parent = curr;
    if (curr->data.first > k) {
      curr = curr->left;
      isLeft = true;
    } else {
      curr = curr->right;
      isLeft = false;
    }
  }

  // case 1 : the target node does not exist in the tree
  if (curr == nullptr) {
    return false;
  }

  // case 2: the target node is a leaf node
  if (isLeaf(curr)) {
    if (curr == this->root) {
      this->root = nullptr;
    } else if (isLeft) {
      parent->left = nullptr;
    } else {
      parent->right = nullptr;
    }
    // case 3: the target node has and only has one child
  } else if (curr->right == nullptr) {
    if (curr == this->root) {
      this->root = curr->left;
    } else if (isLeft) {
      parent->left = curr->left;
    } else {
      parent->right = curr->left;
    }
  } else if (curr->left == nullptr) {
    if (curr == this->root) {
      this->root = curr->right;
    } else if (isLeft) {
      parent->left = curr->right;
    } else {
      parent->right = curr->right;
    }
    // case 4: the target node has two children
  } else {
    Node *successor = getSuccessor(curr);
    if (curr == this->root) {
      this->root = successor;
    } else if (isLeft) {
      parent->left = successor;
    } else {
      parent->right = successor;
    }
    successor->left = curr->left;
  }
  delete curr;
  curr = nullptr;
  return true;
}