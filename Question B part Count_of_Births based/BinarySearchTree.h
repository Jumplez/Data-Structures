#ifndef BINARYSEARCHTREE_H
#define BINARYSEARCHTREE_H

#include <iostream>
#include <vector>
#include <string>
#include <limits>

// TreeNode struct definition
struct TreeNode {
    int total_births;
    int period;
    std::string region;
    TreeNode* left;
    TreeNode* right;

    TreeNode(int totalBirths, int periodValue, const std::string& regionKey) 
        : total_births(totalBirths), period(periodValue), region(regionKey), left(nullptr), right(nullptr) {}
};

// BinarySearchTree class definition
class BinarySearchTree {
public:
    BinarySearchTree() : root(nullptr) {}
    ~BinarySearchTree() { destroyTree(root); }

    void insert(int totalBirths, int periodValue, const std::string& regionKey);
    std::vector<std::string> findMinBirthsRegions() const;
    std::vector<std::string> findMaxBirthsRegions() const;
    void displayInOrder() const;

private:
    TreeNode* root;

    void insert(TreeNode*& node, int totalBirths, int periodValue, const std::string& regionKey);
    void destroyTree(TreeNode* node);
    void inOrderTraversal(TreeNode* node) const;
    void findMinMaxBirths(TreeNode* node, std::vector<std::pair<int, std::string>>& birthCounts) const;
};

#endif // BINARYSEARCHTREE_H
