#ifndef TREE_H
#define TREE_H
#include <stdexcept>
#include "Node.h"
#include <iostream>
class Tree{
  public:
Node* root;
Tree();
  ~Tree();
  Node* insert(int v);
  void adjust(Node* newNode);
  bool remove(int v);
  int isBalanced(Node* curr, Node** errNode);
  void fixMissingBlack(Node* n);
};
#endif // !TREE_H

