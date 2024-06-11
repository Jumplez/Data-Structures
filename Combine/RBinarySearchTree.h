#ifndef RBinarySearchTree_H
#define RBinarySearchTree_H

#include <iostream>
#include <vector>
#include <string>
#include <optional>

struct TreeNode {
    std::string region;
    std::vector<int> periods;
    std::vector<int> counts;
    TreeNode* left;
    TreeNode* right;

    TreeNode(const std::string& regionKey, int period, int count) 
        : region(regionKey), left(nullptr), right(nullptr) {
        periods.push_back(period);
        counts.push_back(count);
    }
};

class RBinarySearchTree {
public:
    RBinarySearchTree() : root(nullptr) {}
    ~RBinarySearchTree() { destroyTree(root); }

    void insert(const std::string& regionKey, int period, int count);
    void displayInOrder() const;
    bool modifyBirthCount(const std::string& region, int period, int newCount);
    bool deleteRegion(const std::string& region);
    std::optional<int> searchBirths(const std::string& region, int period) const;

    TreeNode* getRoot() const { return root; } // Make getRoot public

private:
    TreeNode* root;

    void insert(TreeNode*& node, const std::string& regionKey, int period, int count);
    void inOrderTraversal(TreeNode* node) const;
    void destroyTree(TreeNode* node);

    TreeNode* search(const std::string& region, TreeNode* node) const;
    TreeNode* deleteNode(TreeNode* node, const std::string& region);
    TreeNode* minValueNode(TreeNode* node) const;
};

#endif // RBinarySearchTree_H
