#include "../include/Action.h"

extern WareHouse* backup;

RestoreWareHouse::RestoreWareHouse() : BaseAction() {}

void RestoreWareHouse::act(WareHouse &wareHouse){
    if (backup == nullptr) {
        error("No backup available");
    }
    else{
        wareHouse = *backup;
        complete();
    }
}

RestoreWareHouse* RestoreWareHouse::clone() const {
    return new RestoreWareHouse(*this);
}

string RestoreWareHouse::toString() const{
    return "Restore " + readStatus(getStatus());
}