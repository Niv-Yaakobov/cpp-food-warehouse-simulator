#pragma once
#include <string>
#include <vector>

#include "Order.h"
#include "Customer.h"

class BaseAction;
class Volunteer;

// Warehouse responsible for Volunteers, Customers Actions, and Orders.


class WareHouse {

    public:
        WareHouse();
        WareHouse(const string &configFilePath);
        void start();
        void addOrder(Order* order);
        void addAction(BaseAction* action);
        Customer &getCustomer(int customerId) const;
        Volunteer &getVolunteer(int volunteerId) const;
        Order &getOrder(int orderId) const;
        const vector<BaseAction*> &getActions() const;
        void close();
        void open();

        // Rule of Five
        WareHouse(const WareHouse& other);             // Copy constructor
        WareHouse(WareHouse&& other) noexcept;        // Move constructor
        WareHouse& operator=(const WareHouse& other);  // Copy assignment operator
        WareHouse& operator=(WareHouse&& other) noexcept; // Move assignment operator
        ~WareHouse();

        bool volunteerIdExist(int volunteerId) const;
        int getCustomerCounter() const;
        int getVolunteerCounter() const;
        void addCustomer(Customer* customer); //add the customer to the customers vector
        int ordersCounter = 0; 

        vector<Volunteer*>& getVolunteers();
        vector<Order*>& getPendingOrders();
        vector<Order*>& getInProcessOrders();
        vector<Order*>& getCompletedOrders(); 
        vector<Customer*>& getCustomers();

        void deleteCustomerVector(vector<Customer*>& v);
        void deleteVolunteerVector(vector<Volunteer*>& v);
        void deleteOrderVector(vector<Order*>& v);
        void deleteBaseActionVector(vector<BaseAction*>& v);

    private:
        bool isOpen;
        vector<BaseAction*> actionsLog;
        vector<Volunteer*> volunteers;
        vector<Order*> pendingOrders;
        vector<Order*> inProcessOrders;
        vector<Order*> completedOrders; 
        vector<Customer*> customers;
        int customerCounter; //For assigning unique customer IDs
        int volunteerCounter; //For assigning unique volunteer IDs
};