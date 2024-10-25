
#include <iostream>
#include <cstdlib>
#include "Node.h"
#include "Tree.h"
int main(){
  Tree* t = new Tree();
  for (int i=0; i<50; i++) {
    int r = std::rand()%100;
    t->insert(r);
  }
  std::cout<<'\n';
  //std::cout << *(t->root);
  Node* er = new Node(-1);
  Node** err = new Node*;
  *err = er;
  std::cout<<(t->isBalanced(t->root,err))<<"\n\n\n";
  Node* l = t->root;
  while (l->left != NULL){
    l = l->left;
  }
  Node* added = l->addL(new Node(2));
  added->red = false;
  std::cout<<(t->isBalanced(t->root,err))<<"\n\n\n";
  std::cout<<**(err)<<"\n\n\n";

  added->red = true;
  std::cout<<(t->isBalanced(t->root,err))<<"\n\n\n";
  std::cout<<**(err);

  delete t;
  return 0;
}

