#ifndef TREE_H
#define TREE_H
#include <stdexcept>
#include "Node.h"
class Tree{
  public:
Node* root;
Tree();
  ~Tree();
  Node* insert(int v);
  void adjust(Node* newNode);
  bool remove(int v);
  int isBalanced(Node* curr, Node** errNode);
};
#endif // !TREE_H

