
#include <iostream>
#include <cstdlib>
#include "Node.h"
#include "Tree.h"
int main(){
  Tree* t = new Tree();
  for (int i=0; i<100; i++) {
    int r = std::rand()%5;
    t->insert(r);
  }

  std::cout<<'\n';
  //std::cout << *(t->root);
  Node* er = new Node(-1);
  Node** err = new Node*;
  *err = er;

  std::cout<<(t->isBalanced(t->root,err))<<"\n\n\n";
  int count = 0;
  for (int i = 0; i < 110; i++) {
  if(t->remove(std::rand()%5))
      count += 1;
  //std::cout<<(t->isBalanced(t->root,err))<<"\n\n\n";
  //std::cout<<**(err)<<"\n\n\n";
    //std::cout<<*(t->root);
  
  }
  std::cout<<(t->isBalanced(t->root,err))<<"\n\n\n";
  std::cout<<count<<'\n';
  std::cout << *(t->root);

  delete t;
  return 0;
}

