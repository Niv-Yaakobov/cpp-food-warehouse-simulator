#include "../include/Action.h"
#include <iostream>

PrintOrderStatus::PrintOrderStatus(int id) :BaseAction(), orderId(id) {}

void PrintOrderStatus::act(WareHouse &wareHouse) {
    int maxId =  wareHouse.ordersCounter;
    if(orderId < maxId && 0<= orderId){
        Order& O = wareHouse.getOrder(orderId);
        std::cout << O.toString() << std::endl;
        complete();
    }
    else{
        error("Order doesn't exist");
    }
}

PrintOrderStatus* PrintOrderStatus::clone() const {
    return new PrintOrderStatus(*this);
}

string PrintOrderStatus::toString() const {
    return "OrderStatus " + std::to_string(orderId) + " " + readStatus(getStatus());
}