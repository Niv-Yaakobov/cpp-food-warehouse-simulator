#include "../include/Volunteer.h"
#include "../include/Order.h"

CollectorVolunteer::CollectorVolunteer(int id, const string& name, int coolDown) : Volunteer(id, name), coolDown(coolDown), timeLeft(0) {}

CollectorVolunteer* CollectorVolunteer::clone() const {
    return new CollectorVolunteer(*this);
}

void CollectorVolunteer::step() {
    if (decreaseCoolDown()) {
        completedOrderId = activeOrderId;
        activeOrderId = NO_ORDER;
    }
}

int CollectorVolunteer::getCoolDown() const {
    return coolDown;
}

int CollectorVolunteer::getTimeLeft() const {
    return timeLeft;
}

bool CollectorVolunteer::decreaseCoolDown() {
    timeLeft--;
    if (timeLeft > 0)
        return false;
    return true;
}

bool CollectorVolunteer::hasOrdersLeft() const {
    return true;
}

bool CollectorVolunteer::canTakeOrder(const Order& order) const {
    return !isBusy();
}

void CollectorVolunteer::acceptOrder(const Order& order) {
    activeOrderId = order.getId();
    timeLeft = coolDown;
}
string CollectorVolunteer::getType() const{
    return "Collector";
}

string CollectorVolunteer::toString() const {
    return "VolunteerID: " + std::to_string(getId())+ 
            " ,isBusy: " + (isBusy() ? "True" : "False") + 
            " ,OrderID: " + (isBusy()? std::to_string(getActiveOrderId()) : "None") + 
            " ,TimeLeft: " + (getTimeLeft() == 0 ? "None" : std::to_string(getTimeLeft())) + 
            " ,OrdersLeft: No Limit";
}