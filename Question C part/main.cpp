#include <iostream>
#include "HashTable.h"
#include <fstream>
#include <sstream>

using namespace std;

void trim(std::string &str) {
    str.erase(0, str.find_first_not_of(" \t"));
    str.erase(str.find_last_not_of(" \t") + 1);
}

void readDataFromFile(const std::string& filename, HashTable& hashTable) {
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
            std::string regionKey = region + " (" + eventType + ")";
            hashTable.insert(regionKey, period, count);
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

    const int BUCKETS = 11; // Adjust based on expected number of regions
    HashTable hashTable(BUCKETS);

    readDataFromFile("Deaths_Births.txt", hashTable);
    
    while (select_option != 5) {
        cout << "1. Display data\n2. Search for births or deaths given region and period.\n3. Modify births for given region and period.\n4. Delete a region's deaths or births data.\n5. Exit program ";
        cin >> select_option;
        switch (select_option) {
            case 1: {
                hashTable.display();
                break;
            }
            case 2: {
                std::string region;
                int period;

                std::cout << "Enter the region (e.g., 'Wellington region (Births)'): ";
                std::cin.ignore(); 
                std::getline(std::cin, region);

                std::cout << "Enter the period (e.g., 2020): ";
                std::cin >> period;

                auto result = hashTable.search(region, period);

                if (result.has_value()) {
                    std::cout << region << " for period " << period << " has count: " << result.value() << std::endl;
                } else {
                    std::cout << "No data found for " << region << " and period " << period << std::endl;
                }
                break;
            }
            case 3: {
                std::string region;
                int period, newCount;

                std::cout << "Enter the region (e.g., 'Wellington region (Births)'): ";
                std::cin.ignore();
                std::getline(std::cin, region);

                std::cout << "Enter the period (e.g., 2020): ";
                std::cin >> period;

                std::cout << "Enter the new count: ";
                std::cin >> newCount;

                if (hashTable.modify(region, period, newCount)) {
                    std::cout << "Data modified successfully.\n";
                } else {
                    std::cout << "Failed to modify data. Region or period might not exist.\n";
                }
                break;
            }
            case 4: {
                std::string region;

                std::cout << "Enter the region to delete (e.g., 'Wellington region (Births)'): ";
                std::cin.ignore();
                std::getline(std::cin, region);

                if (hashTable.remove(region)) {
                    std::cout << "Data deleted successfully.\n";
                } else {
                    std::cout << "Failed to delete data. Region might not exist.\n";
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

    return 0;
}
