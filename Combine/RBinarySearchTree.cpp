#include "RBinarySearchTree.h"
#include <iostream>
#include <vector>
#include <optional>

// Destructor helper: useful for the delete function
void RBinarySearchTree::destroyTree(TreeNode* node) {
    if (node != nullptr) {
        destroyTree(node->left);
        destroyTree(node->right);
        delete node;
    }
}

void RBinarySearchTree::insert(const std::string& regionKey, int period, int count) {
    insert(root, regionKey, period, count); // Insert starting from root
}

// Insert helper:
void RBinarySearchTree::insert(TreeNode*& node, const std::string& regionKey, int period, int count) {
    if (node == nullptr) {
        node = new TreeNode(regionKey, period, count); // Create node
    } else if (regionKey < node->region) {
        insert(node->left, regionKey, period, count); // Insert in left subtree
    } else if (regionKey > node->region) {
        insert(node->right, regionKey, period, count); // Insert in right subtree
    } else {
        node->periods.push_back(period);
        node->counts.push_back(count); // Update
    }
}

// Display: In-order traversal
void RBinarySearchTree::displayInOrder() const {
    inOrderTraversal(root); // Start from the root
}

// In-order Traversal:
void RBinarySearchTree::inOrderTraversal(TreeNode* node) const {
    if (node != nullptr) {
        inOrderTraversal(node->left);
        std::cout << "Region: " << node->region << std::endl;
        for (size_t i = 0; i < node->periods.size(); ++i) {
            std::cout << "    Period: " << node->periods[i] << ", Births: " << node->counts[i] << std::endl;
        }
        inOrderTraversal(node->right);
    }
}

// Search Births:
std::optional<int> RBinarySearchTree::searchBirths(const std::string& region, int period) const {
    TreeNode* node = search(region, root);
    if (node != nullptr) {
        for (size_t i = 0; i < node->periods.size(); ++i) {
            if (node->periods[i] == period) {
                return node->counts[i]; // Return count if found
            }
        }
    }
    return std::nullopt; // Return empty if not found
}

// Modify Birth Count:
bool RBinarySearchTree::modifyBirthCount(const std::string& region, int period, int newCount) {
    TreeNode* node = search(region, root);
    if (node != nullptr) {
        for (size_t i = 0; i < node->periods.size(); ++i) {
            if (node->periods[i] == period) {
                node->counts[i] = newCount; // Update count
                return true;
            }
        }
    }
    return false; // Return false if region or period not found
}

// Delete Region:
bool RBinarySearchTree::deleteRegion(const std::string& region) {
    root = deleteNode(root, region); // Delete starting from root
    return (root != nullptr); 
}

// Search:
TreeNode* RBinarySearchTree::search(const std::string& region, TreeNode* node) const {
    if (node == nullptr || node->region == region) {
        return node;
    }
    if (region < node->region) {
        return search(region, node->left); // Search in left subtree
    }
    return search(region, node->right); // Search in right subtree
}

// Delete Node:
TreeNode* RBinarySearchTree::deleteNode(TreeNode* node, const std::string& region) {
    if (node == nullptr) {
        return node;
    }

    if (region < node->region) {
        node->left = deleteNode(node->left, region); // Delete from left subtree
    } else if (region > node->region) {
        node->right = deleteNode(node->right, region); // Delete from right subtree
    } else {
        if (node->left == nullptr) {
            TreeNode* temp = node->right; // Replace with right child
            delete node;
            return temp;
        } else if (node->right == nullptr) {
            TreeNode* temp = node->left; // Replace with left child
            delete node;
            return temp;
        }

        // Replace with smallest node in right subtree
        TreeNode* temp = minValueNode(node->right);
        node->region = temp->region;
        node->periods = temp->periods;
        node->counts = temp->counts;
        node->right = deleteNode(node->right, temp->region);
    }
    return node;
}

// Min Value Node: Finds the node with the smallest key in the subtree
TreeNode* RBinarySearchTree::minValueNode(TreeNode* node) const {
    TreeNode* current = node;
    while (current && current->left != nullptr) {
        current = current->left; // Traverse to the leftmost node
    }
    return current;
}
