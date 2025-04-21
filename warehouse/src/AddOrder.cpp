#include "../include/Action.h"

AddOrder::AddOrder(int id) : BaseAction(), customerId(id) {}

void AddOrder::act(WareHouse &wareHouse) {
    if (customerId <= wareHouse.getCustomerCounter()){
        Customer& C = wareHouse.getCustomer(customerId);
        int orderId = wareHouse.ordersCounter;
        if (C.addOrder(orderId) != -1){
            Order* O = new Order(orderId,customerId, C.getCustomerDistance());
            wareHouse.addOrder(O);
            complete();
        }
        else{
            error("Cannot place this order");
        }
    }
    else{
        error("Cannot place this order, customer ID doesn't exist");
    }  
}

AddOrder* AddOrder::clone() const {
    return new AddOrder(*this);
}

string AddOrder::toString() const {
    return "Order " + std::to_string(customerId) + " " +readStatus(getStatus());
}