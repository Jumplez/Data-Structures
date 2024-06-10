#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <string>
#include <vector>
#include <optional>

struct PeriodCount {
    int period;
    int count;

    PeriodCount(int period, int count) : period(period), count(count) {}
};

struct HashNode {
    std::string region;
    std::vector<PeriodCount*> periodCounts;
    HashNode* next;

    HashNode(const std::string& regionKey) : region(regionKey), next(nullptr) {}

    ~HashNode() {
        for (auto pc : periodCounts) {
            delete pc;
        }
    }
};

class HashTable {
public:
    HashTable(int buckets);
    ~HashTable();

    void insert(const std::string& regionKey, int period, int count);
    std::optional<int> search(const std::string& region, int period) const;
    bool modify(const std::string& region, int period, int newCount);
    bool remove(const std::string& region);
    void display() const;

private:
    std::vector<HashNode*> table;
    int buckets;

    int hashFunction(const std::string& key) const;
    void clearTable();
    void sortTable();
};

#endif // HASHTABLE_H
