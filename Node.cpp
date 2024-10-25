#include "Node.h"


Node::Node(int v){
  val = v;
  left = NULL;
  right = NULL;
  parent = NULL;
  red = false;
  r = false;
}
Node::~Node(){
  delete left;
  delete right;
}

std::string Node::toString() const{
  char col = red ? 'r': 'b';
  return std::to_string(val) + col;
}
Node* Node::insert(int v){
  if (v <= val){
    if (left == NULL)
      return addL(new Node(v));
    else 
      return left->insert(v);
  }
  else {
    if (right == NULL)
      return addR(new Node(v));
    else 
      return right->insert(v);
  }
}

Node* Node::addL(Node* child){
  left = child;
  if(child != NULL){
  child->parent = this;
  child->r= false;
  }
  return child;
} 
Node* Node::addR(Node* child){
  right = child;
  if(child != NULL){
  child->parent = this;
  child->r= true;
  }
  return child;
}
bool Node::removeL(){
  
}
bool Node::removeR(){

}
std::ostream& Node::printHelp(std::ostream& os, int dashes) const{
  int mult = 4;
  if (left != NULL){
    left->printHelp(os,dashes + mult);
      os << std::setw(dashes + mult / 2) << '/' << '\n';
  } 
  os << std::setw(dashes) << toString() << '\n';
  if (right != NULL){
    os << std::setw(dashes + mult / 2) << '\\' << '\n';
    right->printHelp(os,dashes+mult);
  }
  return os;
}
std::ostream& operator<<(std::ostream& os, const Node& node){
  node.printHelp(os,0);
  return os;
}
Node* Node::rotate(){
  Node* n = this;
  Node* parent = n->parent;
  Node* gp = parent->parent;
  if (gp == NULL)
    throw std::invalid_argument("grandparent can't be NULL");
  if (n->r != parent->r){
    bool dir = n->r;
    if (!dir){
      gp->addR(n);
      parent->addL(n->right);
      n->addR(parent);
    }
    else{
      gp->addL(n);
      parent->addR(n->left);
      n->addL(parent);
    }
    Node* save = n;
    n = parent;
    parent = save;
  }
  if(n->r != parent->r){
    throw std::invalid_argument("earlier rotation failed");
  }
  bool dir = parent->r;
  Node* gpp = gp->parent;
  if (gpp != NULL && !gp->r){
    gpp->addL(parent);
  }
  else if(gpp != NULL){
    gpp->addR(parent);
  }else{
    parent->parent = NULL;
  }
  if(!dir){
    gp->addL(parent->right);
    parent->addR(gp);
  }
  else{
    gp->addR(parent->left);
    parent->addL(gp);
  }
  return parent;
}
Node* Node::sibling(){
  if (r)
    return parent->left;
  else 
    return parent->right;
}
