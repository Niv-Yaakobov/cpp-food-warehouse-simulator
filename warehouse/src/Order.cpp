#include "../include/Order.h"  

// Constructor
Order::Order(int id, int customerId, int distance)
    : id(id), customerId(customerId), distance(distance),
      status(OrderStatus::PENDING), collectorId(NO_VOLUNTEER), driverId(NO_VOLUNTEER) {}

Order* Order::clone() const{
    return new Order(*this);
}

int Order::getDistance()const{
    return distance;
}
// Getter for order id
int Order::getId() const {
    return id;
}

// Getter for customerId
int Order::getCustomerId() const {
    return customerId;
}

// Setter for status
void Order::setStatus(OrderStatus newStatus) {
    status = newStatus;
}

// Setter for collectorId
void Order::setCollectorId(int newCollectorId) {
    collectorId = newCollectorId;
}

// Setter for driverId
void Order::setDriverId(int newDriverId) {
    driverId = newDriverId;
}

// Getter for collectorId
int Order::getCollectorId() const {
    return collectorId;
}

// Getter for driverId
int Order::getDriverId() const {
    return driverId;
}

// Getter for status
OrderStatus Order::getStatus() const {
    return status;
}
const std::string Order::OrderStatusToString() const {
    switch (status) {
        case OrderStatus::PENDING:
            return "Pending";
        case OrderStatus::COLLECTING:
            return "Collecting";
        case OrderStatus::DELIVERING:
            return "Delivering";
        default:
            return "Completed";
    }
}

const string Order::toString() const {
    return "Order ID: " + std::to_string(id) +
           ", Status: " + OrderStatusToString() +
           ", Customer ID: " + std::to_string(customerId) +
           ", Collector ID: " + (collectorId == -1 ? "None" : std::to_string(collectorId)) +
           ", Driver ID: " + (driverId == -1 ? "None" : std::to_string(driverId));
}
