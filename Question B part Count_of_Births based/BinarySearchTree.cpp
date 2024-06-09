#include "BinarySearchTree.h"
#include <limits>
#include <algorithm>
#include <unordered_set> // Include unordered_set

void BinarySearchTree::destroyTree(TreeNode* node) {
    if (node != nullptr) {
        destroyTree(node->left);
        destroyTree(node->right);
        delete node;
    }
}

void BinarySearchTree::insert(int totalBirths, int periodValue, const std::string& regionKey) {
    insert(root, totalBirths, periodValue, regionKey);
}

void BinarySearchTree::insert(TreeNode*& node, int totalBirths, int periodValue, const std::string& regionKey) {
    if (node == nullptr) {
        node = new TreeNode(totalBirths, periodValue, regionKey);
    } else if (totalBirths < node->total_births) {
        insert(node->left, totalBirths, periodValue, regionKey);
    } else {
        insert(node->right, totalBirths, periodValue, regionKey);
    }
}

void BinarySearchTree::inOrderTraversal(TreeNode* node) const {
    if (node != nullptr) {
        inOrderTraversal(node->left);
        std::cout << "Births: " << node->total_births << ", Period: " << node->period << ", Region: " << node->region << std::endl;
        inOrderTraversal(node->right);
    }
}

void BinarySearchTree::displayInOrder() const {
    inOrderTraversal(root);
}

void BinarySearchTree::findMinMaxBirths(TreeNode* node, std::vector<std::pair<int, std::string>>& birthCounts) const {
    if (node != nullptr) {
        findMinMaxBirths(node->left, birthCounts);
        birthCounts.push_back(std::make_pair(node->total_births, node->region));
        findMinMaxBirths(node->right, birthCounts);
    }
}

// Find regions with minimum births
std::vector<std::string> BinarySearchTree::findMinBirthsRegions() const {
    std::vector<std::pair<int, std::string>> birthCounts;
    findMinMaxBirths(root, birthCounts);
    std::sort(birthCounts.begin(), birthCounts.end());

    std::vector<std::string> result;
    std::unordered_set<std::string> uniqueRegions; // Use set to track unique regions

    for (const auto& entry : birthCounts) {
        if (uniqueRegions.size() >= 3) break; // Stop when we have enough unique regions
        if (uniqueRegions.find(entry.second) == uniqueRegions.end()) {
            result.push_back(entry.second);
            uniqueRegions.insert(entry.second);
        }
    }

    return result;
}

// Find regions with maximum births
std::vector<std::string> BinarySearchTree::findMaxBirthsRegions() const {
    std::vector<std::pair<int, std::string>> birthCounts;
    findMinMaxBirths(root, birthCounts);
    std::sort(birthCounts.begin(), birthCounts.end(), std::greater<>());

    std::vector<std::string> result;
    std::unordered_set<std::string> uniqueRegions; // Use set to track unique regions

    for (const auto& entry : birthCounts) {
        if (uniqueRegions.size() >= 3) break; // Stop when we have enough unique regions
        if (uniqueRegions.find(entry.second) == uniqueRegions.end()) {
            result.push_back(entry.second);
            uniqueRegions.insert(entry.second);
        }
    }

    return result;
}
