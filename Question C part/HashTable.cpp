#include "HashTable.h"
#include <iostream>
#include <string>
#include <vector>
#include <optional>
#include <algorithm>

HashTable::HashTable(int buckets) : buckets(buckets) {
    table.resize(buckets, nullptr);
}

HashTable::~HashTable() {
    clearTable();
}

void HashTable::insert(const std::string& regionKey, int period, int count) {
    int index = hashFunction(regionKey);
    HashNode* current = table[index];
    HashNode* prev = nullptr;

    while (current && current->region != regionKey) {
        prev = current;
        current = current->next;
    }

    if (current) {
        for (auto pc : current->periodCounts) {
            if (pc->period == period) {
                pc->count = count;
                return;
            }
        }
        current->periodCounts.push_back(new PeriodCount(period, count));
    } else {
        HashNode* newNode = new HashNode(regionKey);
        newNode->periodCounts.push_back(new PeriodCount(period, count));

        if (prev) {
            prev->next = newNode;
        } else {
            table[index] = newNode;
        }
    }
    sortTable();
}

std::optional<int> HashTable::search(const std::string& region, int period) const {
    int index = hashFunction(region);
    HashNode* current = table[index];

    while (current) {
        if (current->region == region) {
            for (auto pc : current->periodCounts) {
                if (pc->period == period) {
                    return pc->count;
                }
            }
        }
        current = current->next;
    }
    return std::nullopt;
}

bool HashTable::modify(const std::string& region, int period, int newCount) {
    int index = hashFunction(region);
    HashNode* current = table[index];

    while (current) {
        if (current->region == region) {
            for (auto pc : current->periodCounts) {
                if (pc->period == period) {
                    pc->count = newCount;
                    return true;
                }
            }
        }
        current = current->next;
    }
    return false;
}

bool HashTable::remove(const std::string& region) {
    int index = hashFunction(region);
    HashNode* current = table[index];
    HashNode* prev = nullptr;

    while (current) {
        if (current->region == region) {
            if (prev) {
                prev->next = current->next;
            } else {
                table[index] = current->next;
            }
            delete current;
            return true;
        }
        prev = current;
        current = current->next;
    }
    return false;
}

void HashTable::display() const {
    for (int i = 0; i < buckets; ++i) {
        HashNode* current = table[i];
        while (current) {
            std::vector<PeriodCount*> births;
            std::vector<PeriodCount*> deaths;

            for (auto pc : current->periodCounts) {
                if (current->region.find("(Births)") != std::string::npos) {
                    births.push_back(pc);
                } else if (current->region.find("(Deaths)") != std::string::npos) {
                    deaths.push_back(pc);
                }
            }

            if (!births.empty()) {
                std::cout << "Region: " << current->region << std::endl;
                for (auto pc : births) {
                    std::cout << "    Period: " << pc->period 
                              << ", Births|Deaths: " << pc->count << std::endl;
                }
            }

            if (!deaths.empty()) {
                std::cout << "Region: " << current->region << std::endl;
                for (auto pc : deaths) {
                    std::cout << "    Period: " << pc->period 
                              << ", Births|Deaths: " << pc->count << std::endl;
                }
            }

            current = current->next;
        }
    }
}

int HashTable::hashFunction(const std::string& key) const {
    int asciiSum = 0;
    for (char c : key) {
        asciiSum += static_cast<int>(c);
    }
    return asciiSum % buckets;
}

void HashTable::clearTable() {
    for (int i = 0; i < buckets; ++i) {
        HashNode* current = table[i];
        while (current) {
            HashNode* toDelete = current;
            current = current->next;
            delete toDelete;
        }
        table[i] = nullptr;
    }
}

void HashTable::sortTable() {
    for (auto& head : table) {
        std::vector<HashNode*> nodes;
        HashNode* current = head;
        while (current) {
            nodes.push_back(current);
            current = current->next;
        }

        std::sort(nodes.begin(), nodes.end(), [](HashNode* a, HashNode* b) {
            return a->region < b->region;
        });

        head = nodes.empty() ? nullptr : nodes[0];
        for (size_t i = 0; i < nodes.size(); ++i) {
            nodes[i]->next = (i + 1 < nodes.size()) ? nodes[i + 1] : nullptr;
        }
    }
}
