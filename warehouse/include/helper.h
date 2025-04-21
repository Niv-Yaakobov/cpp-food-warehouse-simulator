#pragma once
#include <string>
#include <vector>
#include <iostream>
#include "../include/Action.h"
#include "../include/Customer.h"
#include "../include/Volunteer.h"
using std::string;
using std::vector;
class BaseAction;


std::vector<std::string> splitStringBySpace(const string& input);
BaseAction* createNewAction(vector<string>& words);
void readConfigFile(const string& filename, vector<Customer*>& customers, vector<Volunteer*>& volunteers);

