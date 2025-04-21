#include "../include/Action.h"
#include <iostream>

PrintCustomerStatus::PrintCustomerStatus(int customerId) : BaseAction(), customerId(customerId) {}

void PrintCustomerStatus::act(WareHouse &wareHouse) {
    if (customerId < wareHouse.getCustomerCounter() && customerId >= 0){
        Customer& C = wareHouse.getCustomer(customerId);
        string result = "CustomerID: " + std::to_string(customerId) + '\n';
        for (int i : C.getOrdersIds()){
            Order& order = wareHouse.getOrder(i);
            result += " orderID: " + std::to_string(i)+ '\n' + " orderStatus: " + order.OrderStatusToString() + '\n';
        }
        result += " numOrdersLeft: " + std::to_string(C.getMaxOrders() - C.getNumOrders());
        std::cout<< result << std::endl;
        complete();  
    }
    else{
        error("Customer doesn't exist");
    }
}

PrintCustomerStatus* PrintCustomerStatus::clone() const {
    return new PrintCustomerStatus(*this);
}

string PrintCustomerStatus::toString() const {
    return "CustomerStatus: " +
         std::to_string(customerId) + " "
         + readStatus(getStatus());
}