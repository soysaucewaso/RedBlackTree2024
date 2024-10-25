#ifndef NODE_H
#define NODE_H

#include <string>
#include <iomanip> 
#include <stdexcept>
//#include <stdio.h>
class Node
{
public:
  int val;
  Node* parent;
  Node* left;
  Node* right;
  // black or red
  bool red;
  // if root, either
  bool r;
  Node(int v);
  ~Node();
  Node* insert(int v);
  Node* adjust();
  bool remove(int v);
  Node* addL(Node* child);
  Node* addR(Node* child);
  bool removeL();
  bool removeR();
  std::string toString() const;
  std::ostream& printHelp(std::ostream& os, int dashes) const;
  Node* rotate();
  Node* sibling();
};

std::ostream& operator<<(std::ostream& os, const Node& node);

#endif
