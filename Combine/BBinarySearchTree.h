#ifndef BBinarySearchTree_H
#define BBinarySearchTree_H

#include <iostream>
#include <vector>
#include <string>
#include <limits>

// BTreeNode struct definition
struct BTreeNode {
    int total_births;
    int period;
    std::string region;
    BTreeNode* left;
    BTreeNode* right;

    BTreeNode(int totalBirths, int periodValue, const std::string& regionKey) 
        : total_births(totalBirths), period(periodValue), region(regionKey), left(nullptr), right(nullptr) {}
};

// BBinarySearchTree class definition
class BBinarySearchTree {
public:
    BBinarySearchTree() : root(nullptr) {}
    ~BBinarySearchTree() { destroyTree(root); }

    void insert(int totalBirths, int periodValue, const std::string& regionKey);
    std::vector<std::string> findMinBirthsRegions() const;
    std::vector<std::string> findMaxBirthsRegions() const;
    void displayInOrder() const;

private:
    BTreeNode* root;

    void insert(BTreeNode*& node, int totalBirths, int periodValue, const std::string& regionKey);
    void destroyTree(BTreeNode* node);
    void inOrderTraversal(BTreeNode* node) const;
    void findMinMaxBirths(BTreeNode* node, std::vector<std::pair<int, std::string>>& birthCounts) const;
};

#endif // BBinarySearchTree_H
