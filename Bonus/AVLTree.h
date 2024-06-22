#ifndef AVL_TREE_H
#define AVL_TREE_H

#include <iostream>
#include <vector>
#include <string>
#include <limits>

struct AVLNode {
    int total_births;
    int period;
    std::string region;
    AVLNode* left;
    AVLNode* right;
    int height;

    AVLNode(int totalBirths, int periodValue, const std::string& regionKey)
        : total_births(totalBirths), period(periodValue), region(regionKey), left(nullptr), right(nullptr), height(1) {}
};

class AVLTree {
public:
    AVLTree() : root(nullptr) {}
    ~AVLTree() { destroyTree(root); }

    void insert(int totalBirths, int periodValue, const std::string& regionKey);
    std::vector<std::string> findMinBirthsRegions() const;
    std::vector<std::string> findMaxBirthsRegions() const;
    void displayInOrder() const;

private:
    AVLNode* root;

    AVLNode* insert(AVLNode* node, int totalBirths, int periodValue, const std::string& regionKey);
    void destroyTree(AVLNode* node);
    void inOrderTraversal(AVLNode* node) const;
    void findMinMaxBirths(AVLNode* node, std::vector<std::pair<int, std::string>>& birthCounts) const;
    int height(AVLNode* node);
    int getBalance(AVLNode* node);
    AVLNode* rotateRight(AVLNode* y);
    AVLNode* rotateLeft(AVLNode* x);
};

#endif // AVL_TREE_H
