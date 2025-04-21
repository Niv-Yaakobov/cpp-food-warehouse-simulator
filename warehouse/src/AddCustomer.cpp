#include "../include/Action.h"

AddCustomer::AddCustomer(const string &customerName, const string &customerType, int distance, int maxOrders)
    : BaseAction(), customerName(customerName),customerType(fixType(customerType)), distance(distance), maxOrders(maxOrders) {
}

CustomerType AddCustomer::fixType(const string &customerType){
    if (customerType == "soldier") {
        return CustomerType::Soldier;
    } 
    return CustomerType::Civilian;
}

string AddCustomer::typeToString() const{
    return (customerType == CustomerType::Civilian ? "civilian" : "solider");
}

void AddCustomer::act(WareHouse &wareHouse) {
    Customer* newCustomer;
    int id = wareHouse.getCustomerCounter();
    if (customerType == CustomerType::Soldier)
        newCustomer = new SoldierCustomer(id,customerName,distance,maxOrders);
    else
        newCustomer = new CivilianCustomer(id,customerName,distance,maxOrders);

    wareHouse.addCustomer(newCustomer);
    complete();
}

AddCustomer* AddCustomer::clone() const {
    return new AddCustomer(*this);
}

string AddCustomer::toString() const {
    return "Customer " + 
           customerName +" "+ typeToString() +" " + std::to_string(distance) + " " + std::to_string(maxOrders ) + " " +
            readStatus(getStatus());
}