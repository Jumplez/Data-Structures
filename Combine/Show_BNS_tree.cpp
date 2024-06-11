#include "Show_BNS_tree.h"

void Show_BNS_tree::display(const RBinarySearchTree& bst) {
    TreeNode* root = getRoot(bst);
    inOrderTraversal(root);
}

void Show_BNS_tree::inOrderTraversal(TreeNode* node) const {
    if (node != nullptr) {
        inOrderTraversal(node->left);
        std::cout << "Region: " << node->region << std::endl;
        for (size_t i = 0; i < node->periods.size(); ++i) {
            std::cout << "    Period: " << node->periods[i] << "---------->" << node->counts[i] << std::endl;
        }
        inOrderTraversal(node->right);
    }
}

TreeNode* Show_BNS_tree::getRoot(const RBinarySearchTree& bst) const {
    return bst.getRoot();
}
