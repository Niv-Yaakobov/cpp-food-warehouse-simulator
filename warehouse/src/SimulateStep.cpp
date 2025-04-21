#include "../include/Action.h"
#include "../include/Order.h"
#include "../include/Volunteer.h"
#include "../include/WareHouse.h"
#include <iostream>
#include <algorithm>

SimulateStep::SimulateStep(int numOfSteps) : numOfSteps(numOfSteps), ordersToDelete() {}

void SimulateStep::act(WareHouse &wareHouse) {
    int stepsLeft = numOfSteps;
    while(stepsLeft !=0){
        stageOne(wareHouse);
        deleteFromVector(wareHouse.getPendingOrders());
        stageTwo(wareHouse);
        stageThree(wareHouse);
        deleteFromVector(wareHouse.getInProcessOrders());
        stageFour(wareHouse);
        stepsLeft--;
    }
    complete(); 
}

std::string SimulateStep::toString() const {
    return "SimulateStep: " +std::to_string(numOfSteps)+ " "+readStatus(getStatus());
}

SimulateStep* SimulateStep::clone() const {
    return new SimulateStep(*this);
}

void SimulateStep::stageOne(WareHouse &wareHouse){
    for (Order* o : wareHouse.getPendingOrders()){
        if (o->getStatus() == OrderStatus::PENDING){
            for (Volunteer* v : wareHouse.getVolunteers()){
                if (v->getType() == "Collector" && v->canTakeOrder(*o)){
                    v->acceptOrder(*o);
                    o->setStatus(OrderStatus::COLLECTING);
                    o->setCollectorId(v->getId());
                    ordersToDelete.push_back(o);
                    wareHouse.getInProcessOrders().push_back(o);
                    break;
                }
            }

        }
        else if (o->getStatus() == OrderStatus::COLLECTING){
            for (Volunteer* v : wareHouse.getVolunteers()){
                if (v->getType() == "Driver" && v->canTakeOrder(*o)){
                    v->acceptOrder(*o);
                    o->setStatus(OrderStatus::DELIVERING);
                    o->setDriverId(v->getId());
                    ordersToDelete.push_back(o);
                    wareHouse.getInProcessOrders().push_back(o);
                    break;
                }
            }
        }
    }
}

void SimulateStep::stageTwo(WareHouse &wareHouse){
    for (Volunteer* volunteer: wareHouse.getVolunteers()){
        if(volunteer->isBusy()){
            volunteer->step();
        }
    }
}

void SimulateStep::stageThree(WareHouse &wareHouse){
    for(Volunteer* volunteer: wareHouse.getVolunteers()){
        if(volunteer->getType()== "Collector"){
            for(Order* order : wareHouse.getInProcessOrders()){
                if(volunteer->getCompletedOrderId()==order->getId() && order->getStatus() == OrderStatus::COLLECTING){
                    wareHouse.getPendingOrders().push_back(order);
                    ordersToDelete.push_back(order);
                }
            }
        }
        if(volunteer->getType()== "Driver"){
            for(Order* order : wareHouse.getInProcessOrders()){
                if(volunteer->getCompletedOrderId()==order->getId() && order->getStatus() == OrderStatus::DELIVERING){
                    wareHouse.getCompletedOrders().push_back(order);
                    order->setStatus(OrderStatus::COMPLETED);
                    ordersToDelete.push_back(order);
                }
            }
        }
    }
}

void SimulateStep::stageFour(WareHouse &wareHouse) {
    vector<Volunteer*>& vol = wareHouse.getVolunteers();
    long unsigned int c = 0;
    while (c < vol.size()) {
        if (!vol[c]->isBusy() && !vol[c]->hasOrdersLeft()) {
            delete vol[c];
            vol.erase(vol.begin() + c);
        } 
        else {
            ++c;
        }
    }
}

void SimulateStep::deleteFromVector(vector<Order*>& ve){

    for (long unsigned int i=0; i<ordersToDelete.size(); i++){
        long unsigned int c = 0;
        while (c < ve.size()) {
            if (ordersToDelete[i] == ve[c]) {
                ve.erase(ve.begin() + c);
            } 
            else {
                ++c;
            }
        }
    }
    ordersToDelete.clear();
}
