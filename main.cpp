#include <iostream>
#include "Show_BNS_tree.h"
#include "Search_Birth.h"
#include "Modify.h"
#include "Delete_reg.h"
#include <algorithm>
#include <vector>
#include "BinarySearchTree.h"
#include <fstream>
#include <sstream>

using namespace std;

// Functions to open file and read each line while ignoring white space and new lines
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
        
        // Handling quoted regions that might contain newlines
        if (line.find('\"') != std::string::npos) {
            std::getline(iss, region, '\"');
            std::getline(iss, region, '\"'); // skip the first quote and read till the second quote
            std::getline(iss, count_str); // Remaining part contains count with a leading tab
            count_str.erase(0, count_str.find_first_not_of("\t")); // Remove leading tab
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

            // Append the event type to the region for differentiation
            std::string regionKey = region + " (" + eventType + ")";

            bst.insert(regionKey, period, count);
        } catch (const std::invalid_argument& e) {
            continue;
        } catch (const std::out_of_range& e) {
            continue;
        }
    }

    infile.close();
}

int main() {
    cout << "Program started!" << endl;

    int select_option = -1;
    int ExitFlag = 0;

    // Create objects for each class
    BinarySearchTree bst;
    Show_BNS_tree SBTobj; // Show_BNS_tree object
    Search_Birth SBobj; // Search_Birth object
    Modify Mobj; // Modify object
    Delete_reg Dobj; // Delete_reg object

    readDataFromFile("Deaths_Births.txt", bst);
    
    while (select_option != 5) {
        cout << "Enter an option (5 to exit): ";
        cin >> select_option;
        switch (select_option) {
            case 1: {
                // Display the tree in a detailed way
                SBTobj.display(bst);
                break;
            }
            case 2: {
                // Search for the number of births for a certain time period and region given by the user.
                SBobj.search(bst);
                break;
            }
            case 3: {
                // Modify the number of births for a certain period and region given by the user.
                Mobj.modify(bst);
                break;
            }
            case 4: {
                // Delete a registration based on region
                Dobj.remove(bst);
                break;
            }
            case 5: {
                cout << "Exiting program..." << endl;
                ExitFlag = 1;
                break;
            }
            default:
                cout << "Invalid Option!" << endl;
        }
    if (ExitFlag == 1)
        break;    
    }
}
           
