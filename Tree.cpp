#include "Tree.h"
#include <cstddef>
#include <stdexcept>

Tree::Tree() { root = NULL; }
Tree::~Tree() { delete root; }
Node *Tree::insert(int v) {
  if (root == NULL) {
    root = new Node(v);
    return root;
  }
  Node *newNode = root->insert(v);
  adjust(newNode);
  return newNode;
}
void Tree::adjust(Node *newNode) {
  Node *parent = newNode->parent;
  if (parent == NULL) {
    newNode->red = false;
    return;
  }
  if (!parent->red) {
    newNode->red = true;
    return;
  }
  Node *gp = newNode->parent->parent;
  if (gp == NULL) {
    throw std::invalid_argument("Root is red");
  }
  Node *unc = parent->sibling();
  if (unc == NULL) {
    // only possible if parent, node, and gp have no other kids
    if (parent->left != NULL && parent->right != NULL ||
        newNode->left != NULL || newNode->right != NULL)
      throw std::invalid_argument("UNC is null, yet there are other kids");
    Node *newRoot = newNode->rotate();
    newRoot->red = false;
    newRoot->left->red = true;
    newRoot->right->red = true;
    if (newRoot->parent == NULL) {
      root = newRoot;
    }
  } else if (unc->red) {
    parent->red = false;
    unc->red = false;
    // if gp is root, will fix with recursive call
    gp->red = true;
    newNode->red = true;
    adjust(gp);
  } else {
    // unc is black
    Node *newRoot = newNode->rotate();
    newRoot->red = false;
    newRoot->left->red = true;
    newRoot->right->red = true;
    if (newRoot->parent == NULL) {
      root = newRoot;
    }
  }
}
bool Tree::remove(int v) {
  // find
  Node *curr = root;
  while (curr != NULL) {
    if (curr->val == v)
      break;
    else if (v < curr->val) {
      curr = curr->left;
    } else {
      curr = curr->right;
    }
  }
  if (curr == NULL)
    return false;
  // get biggest smaller node
  Node *pre = curr->left;
  if (pre == NULL) {
    // swap with itself
    pre = curr;
  } else {
    while (pre->right != NULL) {
      pre = pre->right;
    }
  }
  // no need to fixup if child
  // just replace pre with child and color black
  Node *child = pre->left;
  if (curr == pre) {
    child = pre->right;
  }
  if (pre->parent == NULL) {
    root = child;
    if (child!=NULL)
      child->parent = NULL;
  } else if (!pre->r) {
    pre->parent->addL(child);
  } else {
    pre->parent->addR(child);
  }
  if (child != NULL) {
    child->red = false;
  } else if (!pre->red) {
    pre->red = true;
    fixMissingBlack(pre);
  }
  // if pre is red, can be deleted without consequence

  // if curr is pre, return
  if (curr != pre) {
    // replace curr with pre
    // put pre in new location
    if (curr->parent == NULL) {
      root = pre;
      root->parent = NULL;
    } else if (!curr->r) {
      curr->parent->addL(pre);
    } else {
      curr->parent->addR(pre);
    }
    pre->addL(curr->left);
    pre->addR(curr->right);
    pre->red = curr->red;
    pre->val = curr->val;
  }

  curr->left = NULL;
  curr->right = NULL;
  curr->parent = NULL;
  delete curr;
  return true;
}

void Tree::fixMissingBlack(Node *n) {
  Node *p = n->parent;
  if (p == NULL) {
    n->red = false;
    return;
  }
  Node *w = n->sibling();

  if (w == NULL) {
    throw std::invalid_argument("N should have a sibling");
  }

  if (w->red) {
    w->red = false;
    p->red = true;
    Node *farneph = (!w->r) ? (w->left) : (w->right);
    farneph->rotate();
    if (w->parent == NULL) {
      root = w;
    }
    if(n->parent == NULL){

    throw std::invalid_argument("N should have a parent");
    }
    w = n->sibling();
  }
  if ((w->left == NULL || !w->left->red) &&
      (w->right == NULL || !w->right->red)) {
    w->red = true;
    if (p->red == true) {
      p->red = false;
      std::cout << "Better be false!";
      std::cout << p->red << "\n\n\n";
    } else {
      fixMissingBlack(p);
    }
    return;
  }
  // can lead to other cases
  Node *closeneph = NULL;
  Node *farneph = NULL;
  if (!n->r) {
    closeneph = w->left;
    farneph = w->right;
  } else {
    closeneph = w->right;
    farneph = w->left;
  }
  if (closeneph != NULL && closeneph->red &&
      (farneph == NULL || !farneph->red)) {
    Node *newRoot = closeneph->rotate();
    if (newRoot->parent == NULL) {
      root = newRoot;
    }
    newRoot->red = p->red;
    newRoot->left->red = false;
    newRoot->right->red = false;
  } else if (farneph != NULL && farneph->red) {
    farneph->red = false;
    w->red = p->red;
    p->red = false;
    farneph->rotate();
    if (w->parent == NULL) {
      root = w;
    }
  } else {
    throw std::invalid_argument("Should've been caught by a case");
  }
}

int Tree::isBalanced(Node *n, Node **errNode) {
  if (n == NULL)
    return 0;
  if (n->parent != NULL and n->red and n->parent->red) {
    *errNode = n->parent;
    return -1;
  }
  int le = isBalanced(n->left, errNode);
  int ri = isBalanced(n->right, errNode);
  if (le == -1 or ri == -1)
    return -1;
  else if (le == -2 or ri == -2) {
    return -2;
  } else if (le != ri) {
    *errNode = n;
    return -2;
  }
  return le + (n->red ? 0 : 1);
}
