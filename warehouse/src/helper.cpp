#include <iostream>
#include <sstream>
#include <vector>
#include <string>
#include <fstream>
#include <algorithm>
#include "../include/helper.h"



vector<string> splitStringBySpace(const string& input) {
    std::istringstream iss(input);
    vector<string> words;

    string word;
    while (iss >> word) {
        words.push_back(word);
    }

    return words;
}

BaseAction* createNewAction(vector<string>& words){
    string firstWord = words[0];
    BaseAction* action = nullptr;
    if (firstWord == "step") {
        int numOfSteps = std::stoi(words[1]);
        action = new SimulateStep(numOfSteps);
    } 
    else if (firstWord == "order") {
        int customerId = std::stoi(words[1]);
        action = new AddOrder(customerId);
    } 
    else if (firstWord == "customer") {
        string customerName = words[1];
        string customerType = words[2];
        int customerDistance = std::stoi(words[3]);
        int maxOrders = std::stoi(words[4]);
        action = new AddCustomer(customerName,customerType,customerDistance,maxOrders);
    }
    else if (firstWord == "orderStatus") {
        int orderId = std::stoi(words[1]);
        action = new PrintOrderStatus(orderId);
    } 
    else if (firstWord == "customerStatus") {
        int customerId = std::stoi(words[1]);
        action = new PrintCustomerStatus(customerId);
    } 
    else if (firstWord == "volunteerStatus") {
        int volunteerId = std::stoi(words[1]);
        action = new PrintVolunteerStatus(volunteerId);
    } 
    else if (firstWord == "log") {
        action = new PrintActionsLog();

    } 
    else if (firstWord == "close") {
        action = new Close();

    } 
    else if (firstWord == "backup") {
        action = new BackupWareHouse();
    } 
    else if (firstWord == "restore") {
        action = new RestoreWareHouse();
    } 
    
    return action;
}

void readConfigFile(const std::string& filename, std::vector<Customer*>& customers, std::vector<Volunteer*>& volunteers) {
    std::ifstream inputFile(filename);

    if (!inputFile.is_open()) {
        std::cerr << "Error opening the file.\n";
        return;
    }

    std::string line;

    int customerId = 0;
    int volunteerId = 0;

    while (std::getline(inputFile, line)) {
        // Ignore comments
        size_t commentPos = line.find('#');
        if (commentPos != std::string::npos) {
            line.erase(commentPos);
        }

        // Skip empty lines
        if (line.empty()) {
            continue;
        }

        // Process lines with customer information
        if (line.find("customer") != std::string::npos) {
            std::istringstream iss(line);
            std::string customer, type, name;
            int distance, maxOrders;

            iss >> customer >> name >> type >> distance >> maxOrders;

            if (type == "soldier") {
                customers.push_back(new SoldierCustomer(customerId++, name, distance, maxOrders));
            } else if (type == "civilian") {
                customers.push_back(new CivilianCustomer(customerId++, name, distance, maxOrders));
            }
        }

        // Process lines with volunteer information
        else if (line.find("volunteer") != std::string::npos) {
            std::istringstream iss(line);
            std::string volunteer, role, name;
            int cooldownOrMaxDistance, distancePerStep = 0, maxOrders = -1;

            iss >> volunteer >> name >> role >> cooldownOrMaxDistance;

            if (role == "collector") {
                volunteers.push_back(new CollectorVolunteer(volunteerId++, name, cooldownOrMaxDistance));
            } else if (role == "limited_collector") {
                iss >> maxOrders;
                volunteers.push_back(new LimitedCollectorVolunteer(volunteerId++, name, cooldownOrMaxDistance, maxOrders));
            } else if (role == "driver") {
                iss >> distancePerStep;
                volunteers.push_back(new DriverVolunteer(volunteerId++, name, cooldownOrMaxDistance, distancePerStep));
            } else if (role == "limited_driver") {
                iss >> distancePerStep >> maxOrders;
                volunteers.push_back(new LimitedDriverVolunteer(volunteerId++, name, cooldownOrMaxDistance, distancePerStep, maxOrders));
            }
        }
    }

    inputFile.close();
}