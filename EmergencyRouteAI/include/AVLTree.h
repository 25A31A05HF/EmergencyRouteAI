#pragma once
#include "Hospital.h"
#include <string>
#include <vector>
#include <memory>

class AVLTree {
public:
    AVLTree();
    ~AVLTree();
    void insert(const Hospital& h);
    bool erase(int id);
    std::vector<Hospital> findSpecialty(const std::string& specialty) const;
    bool contains(int id) const;
    int height() const;
private:
    struct Node {
        Hospital value;
        int h = 1;
        Node* left = nullptr;
        Node* right = nullptr;
        explicit Node(const Hospital& v) : value(v) {}
    };
    Node* root;
    static int nodeHeight(Node*);
    static int balance(Node*);
    static Node* rotateLeft(Node*);
    static Node* rotateRight(Node*);
    static Node* insertNode(Node*, const Hospital&);
    static Node* eraseNode(Node*, int, bool&);
    static Node* minNode(Node*);
    static void collectSpecialty(Node*, const std::string&, std::vector<Hospital>&);
    static void destroy(Node*);
};
