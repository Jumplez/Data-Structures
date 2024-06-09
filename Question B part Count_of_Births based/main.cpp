#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>
#include "BinarySearchTree.h"

void trim(std::string &str) {
    str.erase(0, str.find_first_not_of(" \t"));
    str.erase(str.find_last_not_of(" \t") + 1);
}

void readDataFromFile(const std::string& filename, BinarySearchTree& bst) {
    std::ifstream infile(filename);
    if (!infile.is_open()) {
        std::cerr << "Error opening file: " << filename << std::endl;
        return;
    }

    std::string line;
    while (std::getline(infile, line)) {
        std::istringstream iss(line);
        std::string period_str, eventType, region, count_str;

        std::getline(iss, period_str, '\t');
        std::getline(iss, eventType, '\t');

        if (eventType != "Births") continue;

        if (line.find('\"') != std::string::npos) {
            std::getline(iss, region, '\"');
            std::getline(iss, region, '\"');
            std::getline(iss, count_str);
            count_str.erase(0, count_str.find_first_not_of("\t"));
        } else {
            std::getline(iss, region, '\t');
            std::getline(iss, count_str);
        }

        trim(period_str);
        trim(eventType);
        trim(region);
        trim(count_str);

        try {
            int period = std::stoi(period_str);
            int count = std::stoi(count_str);

            if (eventType == "Births") {
                bst.insert(count, period, region);
            }
        } catch (const std::invalid_argument& e) {
            continue;
        } catch (const std::out_of_range& e) {
            continue;
        }
    }

    infile.close();
}

int main() {
    std::cout << "Program started!" << std::endl;

    int select_option = -1;

    BinarySearchTree bst;

    readDataFromFile("Deaths_Births.txt", bst);

    while (select_option != 4) {
        std::cout << "1. Find Regions with the MINIMUM Number of Births\n";
        std::cout << "2. Find Regions with the MAXIMUM Number of Births\n";
        std::cout << "3. Display Binary Search Tree\n";
        std::cout << "4. Exit\n";
        std::cin >> select_option;

        switch (select_option) {
            case 1: {
                auto minRegions = bst.findMinBirthsRegions();
                std::cout << "Regions with the minimum number of births:\n";
                for (const auto& region : minRegions) {
                    std::cout << region << "\n";
                }
                break;
            }
            case 2: {
                auto maxRegions = bst.findMaxBirthsRegions();
                std::cout << "Regions with the maximum number of births:\n";
                for (const auto& region : maxRegions) {
                    std::cout << region << "\n";
                }
                break;
            }
            case 3: {
                bst.displayInOrder();
                break;
            }
            case 4: {
                std::cout << "Exiting...\n";
                return 0;
            }
            default:
                std::cout << "Invalid choice!\n";
        }
    }

    return 0;
}
