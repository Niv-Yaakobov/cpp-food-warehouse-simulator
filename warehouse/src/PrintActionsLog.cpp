#include "../include/Action.h"
#include <iostream>

PrintActionsLog::PrintActionsLog() : BaseAction(){}

void PrintActionsLog::act(WareHouse& wareHouse) {
    for (const BaseAction* action : wareHouse.getActions()) {
        std::cout << action->toString() << "\n";
    }
    complete();  
}

PrintActionsLog* PrintActionsLog::clone() const {
    return new PrintActionsLog(*this);
}

string PrintActionsLog::toString() const {
    return "ActionsLog " + readStatus(getStatus());
}