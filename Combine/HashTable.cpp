#include "HashTable.h"
#include <iostream>
#include <string>
#include <vector>
#include <optional>
#include <algorithm>

// Constructor: Initializes the hash table with a specified number of buckets
HashTable::HashTable(int buckets) : buckets(buckets) {
    table.resize(buckets, nullptr); // Resizes the table to the given number of buckets, in our case 11
}

// Destructor: Clears the table and releases the allocated memory that was dynamically created.
HashTable::~HashTable() {
    clearTable(); 
}

// Insert:
void HashTable::insert(const std::string& regionKey, int period, int count) {
    int index = hashFunction(regionKey); // Get hash index
    HashNode* current = table[index];
    HashNode* prev = nullptr;

    // Traverse the chain at this index to find the region or the end of the chain
    while (current && current->region != regionKey) {
        prev = current;
        current = current->next;
    }

    if (current) {
        // Region found, update count for the given period if real else add new.
        for (auto pc : current->periodCounts) {
            if (pc->period == period) {
                pc->count = count; // Update count
                return;
            }
        }
        current->periodCounts.push_back(new PeriodCount(period, count)); // Add new
    } else {
        HashNode* newNode = new HashNode(regionKey);
        newNode->periodCounts.push_back(new PeriodCount(period, count)); // Add new

        if (prev) {
            prev->next = newNode; // Link to the new node
        } else {
            table[index] = newNode; // Insert at the head of the list
        }
    }
    sortTable(); // Sort the table to maintain order
}

// Search:
std::optional<int> HashTable::search(const std::string& region, int period) const {
    int index = hashFunction(region); // Get hash index
    HashNode* current = table[index];

    // Traverse the chain to find the region
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

// Modify:
bool HashTable::modify(const std::string& region, int period, int newCount) {
    int index = hashFunction(region); // Get hash index
    HashNode* current = table[index];

    // Traverse the chain to find the region
    while (current) {
        if (current->region == region) {
            for (auto pc : current->periodCounts) {
                if (pc->period == period) {
                    pc->count = newCount; // Update count
                    return true;
                }
            }
        }
        current = current->next;
    }
    return false; // Return false if region or period not found
}

// Remove:
bool HashTable::remove(const std::string& region) {
    int index = hashFunction(region); // Get hash index
    HashNode* current = table[index];
    HashNode* prev = nullptr;

    // Traverse the chain to find the region
    while (current) {
        if (current->region == region) {
            if (prev) {
                prev->next = current->next; // Bypass the current node
            } else {
                table[index] = current->next; // Remove from the head
            }
            delete current; // Delete the node
            return true;
        }
        prev = current;
        current = current->next;
    }
    return false; // Return false if region not found
}

// Display:
void HashTable::display() const {
    for (int i = 0; i < buckets; ++i) {
        HashNode* current = table[i];
        // Traverse each chain
        while (current) {
            std::vector<PeriodCount*> births;
            std::vector<PeriodCount*> deaths;

            // Separate births and deaths
            for (auto pc : current->periodCounts) {
                if (current->region.find("(Births)") != std::string::npos) {
                    births.push_back(pc);
                } else if (current->region.find("(Deaths)") != std::string::npos) {
                    deaths.push_back(pc);
                }
            }

            // Display births
            if (!births.empty()) {
                std::cout << "Region: " << current->region << std::endl;
                for (auto pc : births) {
                    std::cout << "    Period: " << pc->period 
                              << "---------->" << pc->count << std::endl;
                }
            }

            // Display deaths
            if (!deaths.empty()) {
                std::cout << "Region: " << current->region << std::endl;
                for (auto pc : deaths) {
                    std::cout << "    Period: " << pc->period 
                              << "---------->" << pc->count << std::endl;
                }
            }

            current = current->next; // Move to the next node in the chain
        }
    }
}

// Hash Function: Computes the hash index for a given key, this key is the sum of the ascii for each region
int HashTable::hashFunction(const std::string& key) const {
    int asciiSum = 0;
    for (char c : key) {
        asciiSum += static_cast<int>(c); // Sum ASCII values of characters
    }
    return asciiSum % buckets; // Return hash index
}

// Clear Table:
void HashTable::clearTable() {
    for (int i = 0; i < buckets; ++i) {
        HashNode* current = table[i];
        while (current) {
            HashNode* toDelete = current;
            current = current->next;
            delete toDelete; // Delete each node
        }
        table[i] = nullptr; // Clear the bucket
    }
}

// Sort Table: Sorts the table based on region names
void HashTable::sortTable() {
    for (auto& head : table) {
        std::vector<HashNode*> nodes;
        HashNode* current = head;
        
        while (current) {
            nodes.push_back(current);
            current = current->next;
        }

        // Sort nodes based on region names
        std::sort(nodes.begin(), nodes.end(), [](HashNode* a, HashNode* b) {
            return a->region < b->region;
        });

        // Rebuild the chain with sorted nodes
        head = nodes.empty() ? nullptr : nodes[0];
        for (size_t i = 0; i < nodes.size(); ++i) {
            nodes[i]->next = (i + 1 < nodes.size()) ? nodes[i + 1] : nullptr;
        }
    }
}
