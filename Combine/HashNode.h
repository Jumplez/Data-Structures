#ifndef HASHNODE_H
#define HASHNODE_H

#include <string>
#include <vector>

struct HashNode {
    std::string region;
    std::vector<int> periods;
    std::vector<int> counts;
    HashNode* next;

    HashNode(const std::string& regionKey, int period, int count)
        : region(regionKey), next(nullptr) {
        periods.push_back(period);
        counts.push_back(count);
    }
};

#endif // HASHNODE_H
