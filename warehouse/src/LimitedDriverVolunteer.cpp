#include "../include/Volunteer.h"
#include "../include/Order.h"

LimitedDriverVolunteer::LimitedDriverVolunteer(int id, const string& name, int maxDistance, int distancePerStep, int maxOrders)
    : DriverVolunteer(id, name, maxDistance, distancePerStep), maxOrders(maxOrders), ordersLeft(maxOrders) {}

LimitedDriverVolunteer* LimitedDriverVolunteer::clone() const {
    return new LimitedDriverVolunteer(*this);
}

int LimitedDriverVolunteer::getMaxOrders() const {
    return maxOrders;
}

int LimitedDriverVolunteer::getNumOrdersLeft() const {
    return ordersLeft;
}

bool LimitedDriverVolunteer::hasOrdersLeft() const {
    return ordersLeft > 0;
}

bool LimitedDriverVolunteer::canTakeOrder(const Order& order) const {
    return DriverVolunteer::canTakeOrder(order) && hasOrdersLeft();
}

void LimitedDriverVolunteer::acceptOrder(const Order& order) {
    DriverVolunteer::acceptOrder(order);
    ordersLeft--;
}

string LimitedDriverVolunteer::toString() const {
    return "VolunteerID: " + std::to_string(getId())+ 
        " ,isBusy: " + (isBusy() ? "True" : "False") + 
        " ,OrderID: " + (isBusy() ? std::to_string(getActiveOrderId()) : "None" )+ 
        " ,DistanceLeft: " + (getDistanceLeft() == 0 ? "None" : std::to_string(getDistanceLeft()))+
        " ,OrdersLeft: " + std::to_string(getNumOrdersLeft());
}