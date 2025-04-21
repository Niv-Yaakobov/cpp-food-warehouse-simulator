#include "../include/Volunteer.h"
#include "../include/Order.h"

Volunteer::Volunteer(int id, const std::string &name) : 
     completedOrderId(NO_ORDER), activeOrderId(NO_ORDER),id(id), name(name) {}

int Volunteer::getId() const {
    return id;
}

const std::string &Volunteer::getName() const {
    return name;
}

int Volunteer::getActiveOrderId() const {
    return activeOrderId;
}

int Volunteer::getCompletedOrderId() const {
    return completedOrderId;
}

bool Volunteer::isBusy() const {
    return activeOrderId != NO_ORDER;
}