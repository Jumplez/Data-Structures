#include "Delete_reg.h"
#include <iostream>

void Delete_reg::remove(BinarySearchTree& bst) {
    std::string region;

    std::cout << "Enter the region to delete (e.g., 'Athens (Births)'): ";
    std::cin.ignore(); // To ignore the newline character left in the buffer
    std::getline(std::cin, region);

    bool deleted = bst.deleteRegion(region);

    if (deleted) {
        std::cout << "The region has been deleted successfully.\n";
    } else {
        std::cout << "No data found for the given region.\n";
    }
}
