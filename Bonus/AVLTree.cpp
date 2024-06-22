#include "AVLTree.h"
#include <algorithm>
#include <unordered_set>

void AVLTree::destroyTree(AVLNode* node) {
    if (node != nullptr) {
        destroyTree(node->left);
        destroyTree(node->right);
        delete node;
    }
}

void AVLTree::insert(int totalBirths, int periodValue, const std::string& regionKey) {
    root = insert(root, totalBirths, periodValue, regionKey);
}

AVLNode* AVLTree::insert(AVLNode* node, int totalBirths, int periodValue, const std::string& regionKey) {
    if (node == nullptr) {
        return new AVLNode(totalBirths, periodValue, regionKey);
    }

    if (totalBirths < node->total_births) {
        node->left = insert(node->left, totalBirths, periodValue, regionKey);
    } else if (totalBirths > node->total_births) {
        node->right = insert(node->right, totalBirths, periodValue, regionKey);
    } else {
        return node; // Duplicate births are not allowed
    }

    node->height = 1 + std::max(height(node->left), height(node->right));

    int balance = getBalance(node);

    if (balance > 1 && totalBirths < node->left->total_births) {
        return rotateRight(node);
    }

    if (balance < -1 && totalBirths > node->right->total_births) {
        return rotateLeft(node);
    }

    if (balance > 1 && totalBirths > node->left->total_births) {
        node->left = rotateLeft(node->left);
        return rotateRight(node);
    }

    if (balance < -1 && totalBirths < node->right->total_births) {
        node->right = rotateRight(node->right);
        return rotateLeft(node);
    }

    return node;
}

void AVLTree::inOrderTraversal(AVLNode* node) const {
    if (node != nullptr) {
        inOrderTraversal(node->left);
        std::cout << "Births: " << node->total_births << ", Period: " << node->period << ", Region: " << node->region << std::endl;
        inOrderTraversal(node->right);
    }
}

void AVLTree::displayInOrder() const {
    inOrderTraversal(root);
}

void AVLTree::findMinMaxBirths(AVLNode* node, std::vector<std::pair<int, std::string>>& birthCounts) const {
    if (node != nullptr) {
        findMinMaxBirths(node->left, birthCounts);
        birthCounts.push_back(std::make_pair(node->total_births, node->region));
        findMinMaxBirths(node->right, birthCounts);
    }
}

std::vector<std::string> AVLTree::findMinBirthsRegions() const {
    std::vector<std::pair<int, std::string>> birthCounts;
    findMinMaxBirths(root, birthCounts);
    std::sort(birthCounts.begin(), birthCounts.end());

    std::vector<std::string> result;
    std::unordered_set<std::string> uniqueRegions;

    for (const auto& entry : birthCounts) {
        if (uniqueRegions.size() >= 3) break;
        if (uniqueRegions.find(entry.second) == uniqueRegions.end()) {
            result.push_back(entry.second);
            uniqueRegions.insert(entry.second);
        }
    }

    return result;
}

std::vector<std::string> AVLTree::findMaxBirthsRegions() const {
    std::vector<std::pair<int, std::string>> birthCounts;
    findMinMaxBirths(root, birthCounts);
    std::sort(birthCounts.begin(), birthCounts.end(), std::greater<>());

    std::vector<std::string> result;
    std::unordered_set<std::string> uniqueRegions;

    for (const auto& entry : birthCounts) {
        if (uniqueRegions.size() >= 3) break;
        if (uniqueRegions.find(entry.second) == uniqueRegions.end()) {
            result.push_back(entry.second);
            uniqueRegions.insert(entry.second);
        }
    }

    return result;
}

int AVLTree::height(AVLNode* node) {
    return node ? node->height : 0;
}

int AVLTree::getBalance(AVLNode* node) {
    return node ? height(node->left) - height(node->right) : 0;
}

AVLNode* AVLTree::rotateRight(AVLNode* y) {
    AVLNode* x = y->left;
    AVLNode* T2 = x->right;

    x->right = y;
    y->left = T2;

    y->height = std::max(height(y->left), height(y->right)) + 1;
    x->height = std::max(height(x->left), height(x->right)) + 1;

    return x;
}

AVLNode* AVLTree::rotateLeft(AVLNode* x) {
    AVLNode* y = x->right;
    AVLNode* T2 = y->left;

    y->left = x;
    x->right = T2;

    x->height = std::max(height(x->left), height(x->right)) + 1;
    y->height = std::max(height(y->left), height(y->right)) + 1;

    return y;
}
