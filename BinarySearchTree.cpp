#include "BinarySearchTree.h"
#include <iostream>
#include <vector>
#include <optional>

void BinarySearchTree::destroyTree(TreeNode* node) {
    if (node != nullptr) {
        destroyTree(node->left);
        destroyTree(node->right);
        delete node;
    }
}

void BinarySearchTree::insert(const std::string& regionKey, int period, int count) {
    insert(root, regionKey, period, count);
}

void BinarySearchTree::insert(TreeNode*& node, const std::string& regionKey, int period, int count) {
    if (node == nullptr) {
        node = new TreeNode(regionKey, period, count);
    } else if (regionKey < node->region) {
        insert(node->left, regionKey, period, count);
    } else if (regionKey > node->region) {
        insert(node->right, regionKey, period, count);
    } else {
        node->periods.push_back(period);
        node->counts.push_back(count);
    }
}

void BinarySearchTree::displayInOrder() const {
    inOrderTraversal(root);
}

void BinarySearchTree::inOrderTraversal(TreeNode* node) const {
    if (node != nullptr) {
        inOrderTraversal(node->left);
        std::cout << "Region: " << node->region << std::endl;
        for (size_t i = 0; i < node->periods.size(); ++i) {
            std::cout << "    Period: " << node->periods[i] << ", Births: " << node->counts[i] << std::endl;
        }
        inOrderTraversal(node->right);
    }
}

std::optional<int> BinarySearchTree::searchBirths(const std::string& region, int period) const {
    TreeNode* node = search(region, root);
    if (node != nullptr) {
        for (size_t i = 0; i < node->periods.size(); ++i) {
            if (node->periods[i] == period) {
                return node->counts[i];
            }
        }
    }
    return std::nullopt;
}

bool BinarySearchTree::modifyBirthCount(const std::string& region, int period, int newCount) {
    TreeNode* node = search(region, root);
    if (node != nullptr) {
        for (size_t i = 0; i < node->periods.size(); ++i) {
            if (node->periods[i] == period) {
                node->counts[i] = newCount;
                return true;
            }
        }
    }
    return false;
}

bool BinarySearchTree::deleteRegion(const std::string& region) {
    root = deleteNode(root, region);
    return (root != nullptr);
}

TreeNode* BinarySearchTree::search(const std::string& region, TreeNode* node) const {
    if (node == nullptr || node->region == region) {
        return node;
    }
    if (region < node->region) {
        return search(region, node->left);
    }
    return search(region, node->right);
}

TreeNode* BinarySearchTree::deleteNode(TreeNode* node, const std::string& region) {
    if (node == nullptr) {
        return node;
    }

    if (region < node->region) {
        node->left = deleteNode(node->left, region);
    } else if (region > node->region) {
        node->right = deleteNode(node->right, region);
    } else {
        if (node->left == nullptr) {
            TreeNode* temp = node->right;
            delete node;
            return temp;
        } else if (node->right == nullptr) {
            TreeNode* temp = node->left;
            delete node;
            return temp;
        }

        TreeNode* temp = minValueNode(node->right);
        node->region = temp->region;
        node->periods = temp->periods;
        node->counts = temp->counts;
        node->right = deleteNode(node->right, temp->region);
    }
    return node;
}

TreeNode* BinarySearchTree::minValueNode(TreeNode* node) const {
    TreeNode* current = node;
    while (current && current->left != nullptr) {
        current = current->left;
    }
    return current;
}
