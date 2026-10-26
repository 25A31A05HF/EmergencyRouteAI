#include "AVLTree.h"
#include <algorithm>
#include <cmath>

AVLTree::AVLTree() : root(nullptr) {}
AVLTree::~AVLTree() { destroy(root); }
void AVLTree::destroy(Node* n) {
    if (!n) return; destroy(n->left); destroy(n->right); delete n;
}
int AVLTree::nodeHeight(Node* n) { return n ? n->h : 0; }
int AVLTree::balance(Node* n) { return n ? nodeHeight(n->left)-nodeHeight(n->right) : 0; }
AVLTree::Node* AVLTree::rotateRight(Node* y) {
    Node* x=y->left; Node* t=x->right;
    x->right=y; y->left=t;
    y->h=1+std::max(nodeHeight(y->left),nodeHeight(y->right));
    x->h=1+std::max(nodeHeight(x->left),nodeHeight(x->right)); return x;
}
AVLTree::Node* AVLTree::rotateLeft(Node* x) {
    Node* y=x->right; Node* t=y->left;
    y->left=x; x->right=t;
    x->h=1+std::max(nodeHeight(x->left),nodeHeight(x->right));
    y->h=1+std::max(nodeHeight(y->left),nodeHeight(y->right)); return y;
}
AVLTree::Node* AVLTree::insertNode(Node* n, const Hospital& v) {
    if (!n) return new Node(v);
    if (v.id < n->value.id) n->left=insertNode(n->left,v);
    else if (v.id > n->value.id) n->right=insertNode(n->right,v);
    else { n->value=v; return n; }
    n->h=1+std::max(nodeHeight(n->left),nodeHeight(n->right));
    int b=balance(n);
    if (b>1 && v.id<n->left->value.id) return rotateRight(n);
    if (b<-1 && v.id>n->right->value.id) return rotateLeft(n);
    if (b>1 && v.id>n->left->value.id) { n->left=rotateLeft(n->left); return rotateRight(n); }
    if (b<-1 && v.id<n->right->value.id) { n->right=rotateRight(n->right); return rotateLeft(n); }
    return n;
}
void AVLTree::insert(const Hospital& h) { root=insertNode(root,h); }
AVLTree::Node* AVLTree::minNode(Node* n) { while(n && n->left) n=n->left; return n; }
AVLTree::Node* AVLTree::eraseNode(Node* n, int id, bool& erased) {
    if (!n) return nullptr;
    if (id<n->value.id) n->left=eraseNode(n->left,id,erased);
    else if (id>n->value.id) n->right=eraseNode(n->right,id,erased);
    else {
        erased=true;
        if (!n->left || !n->right) {
            Node* child=n->left ? n->left : n->right;
            delete n; return child;
        }
        Node* successor=minNode(n->right);
        n->value=successor->value;
        bool dummy=false; n->right=eraseNode(n->right,successor->value.id,dummy);
    }
    n->h=1+std::max(nodeHeight(n->left),nodeHeight(n->right));
    int b=balance(n);
    if (b>1 && balance(n->left)>=0) return rotateRight(n);
    if (b>1 && balance(n->left)<0) { n->left=rotateLeft(n->left); return rotateRight(n); }
    if (b<-1 && balance(n->right)<=0) return rotateLeft(n);
    if (b<-1 && balance(n->right)>0) { n->right=rotateRight(n->right); return rotateLeft(n); }
    return n;
}
bool AVLTree::erase(int id) { bool erased=false; root=eraseNode(root,id,erased); return erased; }
void AVLTree::collectSpecialty(Node* n, const std::string& s, std::vector<Hospital>& out) {
    if (!n) return;
    collectSpecialty(n->left,s,out);
    if (n->value.specialty==s) out.push_back(n->value);
    collectSpecialty(n->right,s,out);
}
std::vector<Hospital> AVLTree::findSpecialty(const std::string& s) const {
    std::vector<Hospital> out; collectSpecialty(root,s,out); return out;
}
bool AVLTree::contains(int id) const {
    Node* n=root; while(n) { if(id==n->value.id) return true; n=id<n->value.id?n->left:n->right; } return false;
}
int AVLTree::height() const { return nodeHeight(root); }
