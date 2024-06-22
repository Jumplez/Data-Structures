#include "Search_Birth.h"

void Search_Birth::search(const RBinarySearchTree& bst) {
    std::string region;
    int period;
    
    std::cout << "Regions are case and space sensitive!\n";
    std::cout << "Enter the region (e.g., 'Wellington region (Births)'): ";
    std::cin.ignore(); // To ignore the newline character left in the buffer
    std::getline(std::cin, region);

    std::cout << "Enter the period (e.g., 2020): ";
    std::cin >> period;

    auto result = bst.searchBirths(region, period);

    if (result.has_value()) {
        std::cout << region << ":" << result.value() << " during period " << period << ".\n";
    } else {
        std::cout << "No data found for the given region and period.\n";
    }
}
