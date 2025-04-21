#include "../include/Volunteer.h"
#include "../include/Order.h"

LimitedCollectorVolunteer::LimitedCollectorVolunteer(int id, const string& name, int coolDown, int maxOrders)
    : CollectorVolunteer(id, name, coolDown), maxOrders(maxOrders), ordersLeft(maxOrders) {}

LimitedCollectorVolunteer* LimitedCollectorVolunteer::clone() const {
    return new LimitedCollectorVolunteer(*this);
}

bool LimitedCollectorVolunteer::hasOrdersLeft() const {
    return ordersLeft > 0;
}

bool LimitedCollectorVolunteer::canTakeOrder(const Order& order) const {
    return CollectorVolunteer::canTakeOrder(order) && ordersLeft > 0;
}

void LimitedCollectorVolunteer::acceptOrder(const Order& order) {
    CollectorVolunteer::acceptOrder(order);
    ordersLeft--;
}

int LimitedCollectorVolunteer::getMaxOrders() const {
    return maxOrders;
}

int LimitedCollectorVolunteer::getNumOrdersLeft() const {
    return ordersLeft;
}

string LimitedCollectorVolunteer::toString() const {
    return "VolunteerID: " + std::to_string(getId())+ 
            " ,isBusy: " + (isBusy() ? "True" : "False") + 
            " ,OrderID: " + (isBusy() ? std::to_string(getActiveOrderId()) : "None") + 
            " ,TimeLeft: " + (getTimeLeft() == 0 ? "None" : std::to_string(getTimeLeft())) + 
            " ,OrdersLeft: " + std::to_string(getNumOrdersLeft());
}