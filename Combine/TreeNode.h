#ifndef TREENODE_H
#define TREENODE_H

#include <string>
#include <vector>

class TreeNode {
public:
    std::string region;
    std::vector<int> periods;
    std::vector<int> counts;
    TreeNode* left;
    TreeNode* right;

    TreeNode(const std::string& reg, int period, int count)
        : region(reg), left(nullptr), right(nullptr) {
        periods.push_back(period);
        counts.push_back(count);
    }
};

#endif // TREENODE_H
