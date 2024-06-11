#include "Modify.h"
#include <iostream>

void Modify::modify(RBinarySearchTree& bst) {
    std::string region;
    int period, newCount;

    std::cout << "Enter the region (e.g., 'Athens (Births)'): ";
    std::cin.ignore(); // To ignore the newline character
    std::getline(std::cin, region);

    std::cout << "Enter the period (e.g., 2020): ";
    std::cin >> period;

    std::cout << "Enter the new number of births: ";
    std::cin >> newCount;

    bool modified = bst.modifyBirthCount(region, period, newCount);

    if (modified) {
        std::cout << "The number of births has been updated successfully.\n";
    } else {
        std::cout << "No data found for the given region and period.\n";
    }
}
