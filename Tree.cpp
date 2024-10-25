#include "Tree.h"
#include <cstddef>

Tree::Tree(){
  root = NULL;
}
Tree::~Tree(){
  delete root;
}
Node* Tree::insert(int v){
  if (root == NULL){
    root = new Node(v);
    return root;
  }
  Node* newNode = root->insert(v);
  adjust(newNode);
  return newNode;
}
void Tree::adjust(Node* newNode){
  Node* parent = newNode -> parent;
  if (parent == NULL){
    newNode -> red = false;
    return;
  }
  if (!parent->red){
    newNode->red = true;
    return;
  }
  Node* gp = newNode -> parent -> parent;
  if(gp == NULL){
    throw std::invalid_argument("Root is red");
  }
  Node* unc = parent->sibling();
  if (unc == NULL){
    // only possible if parent, node, and gp have no other kids
    if(parent->left != NULL && parent->right != NULL || newNode->left != NULL || newNode->right !=NULL)
      throw std::invalid_argument("UNC is null, yet there are other kids");
    Node* newRoot = newNode->rotate();
    newRoot->red = false;
    newRoot->left->red = true;
    newRoot->right->red = true;
    if(newRoot->parent== NULL){
      root = newRoot;
    }
  }
  else if(unc->red){
    parent->red = false;
    unc->red = false;
    // if gp is root, will fix with recursive call
    gp->red = true;
    newNode->red = true;
    adjust(gp);
  }
  else{
    // unc is black
    Node* newRoot = newNode->rotate();
    newRoot->red = false;
    newRoot->left->red = true;
    newRoot->right->red = true;
    if(newRoot->parent == NULL){
      root = newRoot;
    }
  }
}
bool remove(int v){

}



int Tree::isBalanced(Node* n,Node** errNode){
  if (n == NULL)
    return 0;
  if (n->parent != NULL and n->red and n->parent->red){
    *errNode = n->parent;
    return -1;
  }
  int le = isBalanced(n->left, errNode);
  int ri = isBalanced(n->right, errNode);
  if (le == -1 or ri == -1)
    return -1;
  else if (le == -2 or ri == -2){
    return -2;
  }
  else if (le != ri){
    *errNode = n;
    return -2;
  }
  return le + (n->red ? 0 : 1);
}
