#ifndef SHOW_BNS_TREE_H
#define SHOW_BNS_TREE_H

#include "RBinarySearchTree.h"
#include <iostream>

class Show_BNS_tree {
public:
    void display(const RBinarySearchTree& bst);
private:
    void inOrderTraversal(TreeNode* node) const;
    TreeNode* getRoot(const RBinarySearchTree& bst) const;
};

#endif // SHOW_BNS_TREE_H
