#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include "RBinarySearchTree.h"
#include "HashTable.h"
#include "Delete_reg.h"
#include "Modify.h"
#include "Search_Birth.h"
#include "Show_BNS_tree.h"
#include "AVLTree.h"

using namespace std;

// Helper function to trim whitespace
void trim(string &str) {
    str.erase(0, str.find_first_not_of(" \t")); // Trim leading spaces
    str.erase(str.find_last_not_of(" \t") + 1); // Trim trailing spaces
}

// region-based Binary Search Tree
void readDataFromFileR(const string& filename, RBinarySearchTree& bst) {
    ifstream infile(filename);
    if (!infile.is_open()) {
        cerr << "Error opening file: " << filename << endl;
        return;
    }

    string line;
    while (getline(infile, line)) {
        istringstream iss(line);
        string period_str, eventType, region, count_str;

        // Get the important information from the file such as ->
        getline(iss, period_str, '\t'); // Read period
        getline(iss, eventType, '\t');  // Read event type (e.g., Births or Deaths)

        // regions that are not stated are not used
        if (line.find('\"') != string::npos) {
            getline(iss, region, '\"'); // Skip first quote
            getline(iss, region, '\"'); // Read region until the second quote
            getline(iss, count_str);    // Read the count after the second quote
            count_str.erase(0, count_str.find_first_not_of("\t")); // Remove tab
        } else {
            getline(iss, region, '\t'); // Read region
            getline(iss, count_str);    // Read count
        }

        trim(period_str);
        trim(eventType);
        trim(region);
        trim(count_str);

        try {
            int period = stoi(period_str); // Change period to integer
            int count = stoi(count_str);   // Change count to integer

            // Create a key for each event type and region, useful for later functions
            string regionKey = region + " (" + eventType + ")";

            // Insert the data into the binary search tree
            bst.insert(regionKey, period, count);
        } catch (const invalid_argument& e) {
            continue; // Skip lines with invalid data
        } catch (const out_of_range& e) {
            continue; // Skip lines with data out of range
        }
    }

    infile.close();
}

// births count based AVL Tree
void readDataFromFileB(const string& filename, AVLTree& avl) {
    ifstream infile(filename);
    if (!infile.is_open()) {
        cerr << "Error opening file: " << filename << endl;
        return;
    }

    string line;
    while (getline(infile, line)) {
        istringstream iss(line);
        string period_str, eventType, region, count_str;

        getline(iss, period_str, '\t'); // Read period
        getline(iss, eventType, '\t');  // Read event type

        if (eventType != "Births") continue; // Process only Births and skip lines that contain Deaths

        // regions that are not stated are not used
        if (line.find('\"') != string::npos) {
            getline(iss, region, '\"'); // Skip first quote
            getline(iss, region, '\"'); // Read region
            getline(iss, count_str);    // Read count
            count_str.erase(0, count_str.find_first_not_of("\t")); // Remove leading tab
        } else {
            getline(iss, region, '\t'); // Read region
            getline(iss, count_str);    // Read count
        }

        trim(period_str);
        trim(eventType);
        trim(region);
        trim(count_str);

        try {
            int period = stoi(period_str); // Change period to integer
            int count = stoi(count_str);   // Change count to integer

            // Insert the data into the AVL tree
            avl.insert(count, period, region);
        } catch (const invalid_argument& e) {
            continue; // Skip lines with invalid data
        } catch (const out_of_range& e) {
            continue; // Skip lines with data out of range
        }
    }

    infile.close();
}

// read data into a hash table
void HreadDataFromFile(const string& filename, HashTable& hashTable) {
    ifstream infile(filename);
    if (!infile.is_open()) {
        cerr << "Error opening file: " << filename << endl;
        return;
    }

    string line;
    while (getline(infile, line)) {
        istringstream iss(line);
        string period_str, eventType, region, count_str;

        // again get the important data
        getline(iss, period_str, '\t'); // Read period
        getline(iss, eventType, '\t');  // Read event type

        if (line.find('\"') != string::npos) {
            getline(iss, region, '\"'); // Skip first quote
            getline(iss, region, '\"'); // Read region
            getline(iss, count_str);    // Read count
            count_str.erase(0, count_str.find_first_not_of("\t")); // Remove tab
        } else {
            getline(iss, region, '\t'); // Read region
            getline(iss, count_str);    // Read count
        }

        trim(period_str);
        trim(eventType);
        trim(region);
        trim(count_str);

        try {
            int period = stoi(period_str); // Change period to integer
            int count = stoi(count_str);   // Change count to integer

            // Create a key for each event type and region, useful for later functions
            string regionKey = region + " (" + eventType + ")";

            // Insert the data into the hash table
            hashTable.insert(regionKey, period, count);
        } catch (const invalid_argument& e) {
            continue; // Skip lines with invalid data
        } catch (const out_of_range& e) {
            continue; // Skip lines with data out of range
        }
    }

    infile.close();
}

int main() {
    cout << "Program started!" << endl;

    int select_option = -1; // Initialize option for user selection
    int ExitFlag = 0;       // Flag to control program exit

    int dataStructure = -1; // Variable to select data structure type
    int treeOption = -1;    // Variable to select type of tree
    cout << "1. Binary Search Tree\n2. Hash Table.\n";
    cin >> dataStructure;    

    switch(dataStructure){
        case 1: {
            cout << "1. Binary Search Tree region based.\n2. Binary Search Tree Count of births based.\n";
            cin >> treeOption;
            if (treeOption == 1) { // Region-based BST - Part (A)
                RBinarySearchTree bst;  // Tree for region-based data
                Show_BNS_tree SBTobj;   // Object for displaying tree
                Search_Birth SBobj;     // Object for searching births
                Modify Mobj;            // Object for modifying data
                Delete_reg Dobj;        // Object for deleting region
                readDataFromFileR("Deaths_Births.txt", bst); // Load data

                while (select_option != 5) {
                    cout << "1. Display data\n2. Search for births or deaths given region and period.\n3. Modify births for given region and period.\n4. Delete a region's deaths or births data.\n5. Exit program\n";
                    cin >> select_option;

                    switch (select_option) {
                        case 1: {
                            SBTobj.display(bst); // Display the tree
                            break;
                        }
                        case 2: {
                            SBobj.search(bst); // Search for births/deaths
                            break;
                        }
                        case 3: {
                            Mobj.modify(bst); // Modify births data
                            break;
                        }
                        case 4: {
                            Dobj.remove(bst); // Delete a region's data
                            break;
                        }
                        case 5: {
                            cout << "Exiting program..." << endl;
                            ExitFlag = 1; // Set exit flag
                            break;
                        }
                        default:
                            cout << "Invalid Option!" << endl;
                    }
                    if (ExitFlag == 1)
                        break;    
                }
            } else if (treeOption == 2) { // Births count-based AVL Tree
                AVLTree avl; // Create the object for births count-based data

                readDataFromFileB("Deaths_Births.txt", avl); // Load data from the file
                select_option = -1;
                while (select_option != 4) {
                    cout << "1. Find Regions with the MINIMUM Number of Births\n";
                    cout << "2. Find Regions with the MAXIMUM Number of Births\n";
                    cout << "3. Display Binary Search Tree\n";
                    cout << "4. Exit\n";
                    cin >> select_option;

                    switch (select_option) {
                        case 1: {
                            // Find regions with the minimum number of births
                            auto minRegions = avl.findMinBirthsRegions();
                            cout << "Regions with the minimum number of births:\n";
                            for (const auto& region : minRegions) {
                                cout << region << "\n";
                            }
                            break;
                        }
                        case 2: {
                            // Find regions with the maximum number of births
                            auto maxRegions = avl.findMaxBirthsRegions();
                            cout << "Regions with the maximum number of births:\n";
                            for (const auto& region : maxRegions) {
                                cout << region << "\n";
                            }
                            break;
                        }
                        case 3: {
                            avl.displayInOrder(); // Display the tree in order (the region with the lowest count of births is at the top of the tree, while the regions with the highest towards the bottom)
                            break;
                        }
                        case 4: {
                            cout << "Exiting...\n";
                            return 0; // Exit program
                        }
                        default:
                            cout << "Invalid choice!\n";
                    }
                }
            } else {
                cout << "Invalid Option!";
            }
            break;
        }
        case 2: {
            const int BUCKETS = 11; // Efoson yparxoyn 11 perioxes vazoyme buckets = 11.
            HashTable hashTable(BUCKETS); // Hash table with a given number of buckets

            HreadDataFromFile("Deaths_Births.txt", hashTable); // data into hash table

            while (select_option != 5) {
                cout << "1. Display data\n2. Search for births or deaths given region and period.\n3. Modify births for given region and period.\n4. Delete a region's deaths or births data.\n5. Exit program\n";
                cin >> select_option;
                switch (select_option) {
                    case 1: {
                        hashTable.display(); // Display hash table, same display with (A) part or the region BST.
                        break;
                    }
                    case 2: {
                        string region;
                        int period;

                        cout << "Enter the region (e.g., 'Wellington region (Births)'): ";
                        cin.ignore(); 
                        getline(cin, region);

                        cout << "Enter the period (e.g., 2020): ";
                        cin >> period;

                        auto result = hashTable.search(region, period); // Search for specific region and period, same as (A)

                        if (result.has_value()) {
                            cout << region << " for period " << period << " has count: " << result.value() << endl;
                        } else {
                            cout << "No data found for " << region << " and period " << period << endl;
                        }
                        break;
                    }
                    case 3: {
                        string region; // Modify a registration, same as part A
                        int period, newCount;

                        cout << "Enter the region (e.g., 'Wellington region (Births)'): ";
                        cin.ignore();
                        getline(cin, region);

                        cout << "Enter the period (e.g., 2020): ";
                        cin >> period;

                        cout << "Enter the new count: ";
                        cin >> newCount;

                        if (hashTable.modify(region, period, newCount)) {
                            cout << "Data modified successfully.\n";
                        } else {
                            cout << "Failed to modify data. Region or period might not exist.\n";
                        }
                        break;
                    }
                    case 4: {
                        string region; // finally delete a registration same as Part A

                        cout << "Enter the region to delete (e.g., 'Wellington region (Births)'): ";
                        cin.ignore();
                        getline(cin, region);

                        if (hashTable.remove(region)) {
                            cout << "Data deleted successfully.\n";
                        } else {
                            cout << "Failed to delete data. Region might not exist.\n";
                        }
                        break;
                    }
                    case 5: {
                        ExitFlag = 1;
                        break;
                    }
                    default: {
                        cout << "Please enter a valid option (1-5)" << endl;
                    }
                }
                if (ExitFlag) {
                    cout << "Program terminated!" << endl;
                    break;
                }
            }
            break;
        }
        default:
            cout << "Invalid option";
    }
}
