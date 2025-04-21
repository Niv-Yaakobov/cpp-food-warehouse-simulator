#include "../include/WareHouse.h"
#include "../include/Volunteer.h"
#include "../include/Customer.h"
#include "../include/Order.h"
#include "../include/helper.h"
#include <iostream>


WareHouse::WareHouse(const std::string& configFilePath)
    : isOpen(false),actionsLog(),volunteers(),pendingOrders(),inProcessOrders(),
    completedOrders(),customers(), customerCounter(0), volunteerCounter(0) {

    readConfigFile(configFilePath, customers, volunteers);
    customerCounter = customers.size();
    volunteerCounter = volunteers.size();
}
WareHouse::~WareHouse() {
    // Delete dynamically allocated objects in vectors
    for (auto customer : customers) {
        delete customer;
    }

    for (auto volunteer : volunteers) {
        delete volunteer;
    }

    for (auto order : pendingOrders) {
        delete order;
    }

    for (auto order : inProcessOrders) {
        delete order;
    }

    for (auto order : completedOrders) {
        delete order;
    }

    for (auto action : actionsLog) {
        delete action;
    }
}

// Copy constructor
WareHouse::WareHouse(const WareHouse& other): ordersCounter(other.ordersCounter),
    isOpen(other.isOpen),actionsLog(),volunteers(),pendingOrders(),inProcessOrders(),
    completedOrders(),customers(), customerCounter(other.customerCounter), 
    volunteerCounter(other.volunteerCounter)
 {

    // Deep copy customers
    for (Customer* customer : other.customers) {
        customers.push_back(customer->clone());
    }

    // Deep copy volunteers
    for (Volunteer* volunteer : other.volunteers) {
        volunteers.push_back(volunteer->clone());
    }

    // Deep copy pending orders
    for (Order* order : other.pendingOrders) {
        pendingOrders.push_back(order->clone());
    }

    // Deep copy in-process orders
    for (Order* order : other.inProcessOrders) {
        inProcessOrders.push_back(order->clone());
    }

    // Deep copy completed orders
    for (Order* order : other.completedOrders) {
        completedOrders.push_back(order->clone());
    }

    // Deep copy actions log
    for (BaseAction* action : other.actionsLog) {
        actionsLog.push_back(action->clone());
    }
}

// Assignment operator
WareHouse& WareHouse::operator=(const WareHouse& other) {
    if (this != &other) {
        // Clear existing resources
        deleteCustomerVector(customers);
        deleteVolunteerVector(volunteers);
        deleteOrderVector(pendingOrders);
        deleteOrderVector(inProcessOrders);
        deleteOrderVector(completedOrders);
        deleteBaseActionVector(actionsLog);

        // Copy data from other
        isOpen = other.isOpen;
        customerCounter = other.customerCounter;
        volunteerCounter = other.volunteerCounter;
        ordersCounter = other.ordersCounter;

        // Deep copy customers
        for (Customer* customer : other.customers) {
            customers.push_back(customer->clone());
        }

        // Deep copy volunteers
        for (Volunteer* volunteer : other.volunteers) {
            volunteers.push_back(volunteer->clone());
        }

        // Deep copy pending orders
        for (Order* order : other.pendingOrders) {
            pendingOrders.push_back(order->clone());
        }

        // Deep copy in-process orders
        for (Order* order : other.inProcessOrders) {
            inProcessOrders.push_back(order->clone());
        }

        // Deep copy completed orders
        for (Order* order : other.completedOrders) {
            completedOrders.push_back(order->clone());
        }

        // Deep copy actions log
        for (BaseAction* action : other.actionsLog) {
            actionsLog.push_back(action->clone());
        }
    }
    return *this;
}
// Move Constructor
WareHouse::WareHouse(WareHouse&& other) noexcept
    : ordersCounter(other.ordersCounter),
      isOpen(other.isOpen),
      actionsLog(std::move(other.actionsLog)),
      volunteers(std::move(other.volunteers)),
      pendingOrders(std::move(other.pendingOrders)),
      inProcessOrders(std::move(other.inProcessOrders)),
      completedOrders(std::move(other.completedOrders)),
      customers(std::move(other.customers)),
      customerCounter(other.customerCounter),
      volunteerCounter(other.volunteerCounter){
    // Set the source to a valid state
    other.isOpen = false;
    other.customerCounter = 0;
    other.volunteerCounter = 0;
    other.ordersCounter = 0;
}

// Move Assignment Operator
WareHouse& WareHouse::operator=(WareHouse&& other) noexcept {
    if (this != &other) {
        // Clear existing resources
        deleteCustomerVector(customers);
        deleteVolunteerVector(volunteers);
        deleteOrderVector(pendingOrders);
        deleteOrderVector(inProcessOrders);
        deleteOrderVector(completedOrders);
        deleteBaseActionVector(actionsLog);

        // Move data from other
        isOpen = other.isOpen;
        customerCounter = other.customerCounter;
        volunteerCounter = other.volunteerCounter;
        ordersCounter = other.ordersCounter;

        customers = std::move(other.customers);
        volunteers = std::move(other.volunteers);
        pendingOrders = std::move(other.pendingOrders);
        inProcessOrders = std::move(other.inProcessOrders);
        completedOrders = std::move(other.completedOrders);
        actionsLog = std::move(other.actionsLog);

        // Set the source to a valid state
        other.isOpen = false;
        other.customerCounter = 0;
        other.volunteerCounter = 0;
        other.ordersCounter = 0;
    }
    return *this;
}
WareHouse::WareHouse() : isOpen(false),actionsLog(),volunteers(),pendingOrders(),inProcessOrders(),
    completedOrders(),customers(), customerCounter(0), volunteerCounter(0){}


void WareHouse::deleteCustomerVector(vector<Customer*>& v){
    for(Customer* c :v){
        delete c;
    }
    v.clear();
}
void WareHouse::deleteVolunteerVector(vector<Volunteer*>& v){
    for(Volunteer* c :v){
        delete c;
    }
    v.clear();
}void WareHouse::deleteOrderVector(vector<Order*>& v){
    for(Order* c :v){
        delete c;
    }
    v.clear();
}void WareHouse::deleteBaseActionVector(vector<BaseAction*>& v){
    for(BaseAction* c :v){
        delete c;
    }
    v.clear();
}
void WareHouse::start() {
    isOpen = true;
    std::cout << "Warehouse is open !" << std::endl;
    while(isOpen){
        string action;

        std::getline(std::cin, action);

        vector<string> words = splitStringBySpace(action);
        BaseAction* newAction = createNewAction(words);

        if(newAction != nullptr){
            newAction->act(*this);
            if(newAction->readStatus(newAction->getStatus()) == "ERROR"){
                std::cout << newAction->getErrorText() <<std::endl;
            }
            actionsLog.push_back(newAction);
        }
    }
}

void WareHouse::addOrder(Order* order) {
    pendingOrders.push_back(order);
    ordersCounter ++ ;
}

void WareHouse::addAction(BaseAction* action) {
    actionsLog.push_back(action);
}

Customer& WareHouse::getCustomer(int customerId) const {
    for (Customer* c : customers){
        if (c->getId() == customerId)
            return (*c);
    }
    return *(customers.front());
}

Volunteer& WareHouse::getVolunteer(int volunteerId) const {
    for (Volunteer* v : volunteers){
        if (v->getId() == volunteerId)
            return (*v);
    }
     return *(volunteers.front());
}

bool WareHouse::volunteerIdExist(int volunteerId) const{
    for (Volunteer* v : volunteers){
        if (v->getId() == volunteerId)
            return (true);
    }
    return false;
}

Order& WareHouse::getOrder(int orderId) const {
    for (Order* o : pendingOrders){
        if (o->getId() == orderId)
            return (*o);
    }
    for (Order* o : inProcessOrders){
        if (o->getId() == orderId)
            return (*o);
    }
    for (Order* o : completedOrders){
        if (o->getId() == orderId)
            return (*o);
    }
    return *(pendingOrders.front());
}

const vector<BaseAction*>& WareHouse::getActions() const {
    return actionsLog; 
}

void WareHouse::close() {
    string ans = " ";
    for (Order* o : pendingOrders){
        string _id = std::to_string(o->getId());
        string _customerID = std::to_string(o->getCustomerId());
        string _orderStatus = o->OrderStatusToString();
        ans += "OrderID: " + _id + " CustomerID: " + _customerID + " OrderStatus: " +  _orderStatus + " \n";
    }
    for (Order* o : inProcessOrders){
        string _id = std::to_string(o->getId());
        string _customerID = std::to_string(o->getCustomerId());
        string _orderStatus = o->OrderStatusToString();
        ans += "OrderID: " + _id + " CustomerID: " + _customerID + " OrderStatus: " +  _orderStatus + " \n";
    }
    for (Order* o : completedOrders){
        string _id = std::to_string(o->getId());
        string _customerID = std::to_string(o->getCustomerId());
        string _orderStatus = o->OrderStatusToString();
        ans += "OrderID: " + _id + " CustomerID: " + _customerID + " OrderStatus: " +  _orderStatus + " \n";
    }
    std::cout << ans << std::endl;
    isOpen = false; // finish the loop
}

void WareHouse::open() {
    isOpen = true;
}

int WareHouse::getCustomerCounter() const {
    return customerCounter;
}

int WareHouse::getVolunteerCounter() const {
    return volunteerCounter;
}

void WareHouse::addCustomer(Customer* customer) {
    customers.push_back(customer);
    customerCounter++;
}

vector<Volunteer*>& WareHouse::getVolunteers(){
    return volunteers;
}
vector<Order*>& WareHouse::getPendingOrders(){
    return pendingOrders;
}
vector<Order*>& WareHouse::getInProcessOrders(){
    return inProcessOrders;
}
vector<Order*>& WareHouse::getCompletedOrders(){
    return completedOrders;
} 
vector<Customer*>& WareHouse::getCustomers(){
    return customers;
}

