#include "../include/Volunteer.h"
#include "../include/Order.h"

DriverVolunteer::DriverVolunteer(int id, const string& name, int maxDistance, int distancePerStep)
    : Volunteer(id, name), maxDistance(maxDistance), distancePerStep(distancePerStep), distanceLeft(0) {}

DriverVolunteer* DriverVolunteer::clone() const {
    return new DriverVolunteer(*this);
}

int DriverVolunteer::getDistanceLeft() const {
    return distanceLeft;
}

int DriverVolunteer::getMaxDistance() const {
    return maxDistance;
}

int DriverVolunteer::getDistancePerStep() const {
    return distancePerStep;
}

bool DriverVolunteer::decreaseDistanceLeft() {
    distanceLeft -= distancePerStep;
    if (distanceLeft < 0)
        distanceLeft = 0;
    return distanceLeft==0;
}

bool DriverVolunteer::hasOrdersLeft() const {
    return true;
}

bool DriverVolunteer::canTakeOrder(const Order& order) const {
    return (!isBusy() && order.getDistance() <= maxDistance);
}

void DriverVolunteer::acceptOrder(const Order& order) {
    activeOrderId = order.getId();
    distanceLeft = order.getDistance();
}

void DriverVolunteer::step() {
    if (decreaseDistanceLeft()) {
        completedOrderId = activeOrderId;
        activeOrderId = NO_ORDER;
    }
}
string DriverVolunteer::getType() const{
    return "Driver";
}

string DriverVolunteer::toString() const {
    return "VolunteerID: " + std::to_string(getId())+ 
            " ,isBusy: " + (isBusy() ? "True" : "False") + 
            " ,OrderID: " + (isBusy() ? std::to_string(getActiveOrderId()) : "None") + 
            " ,DistanceLeft: " + (getDistanceLeft() == 0 ? "None" : std::to_string(getDistanceLeft()))+
            " ,OrdersLeft: No Limit";

}