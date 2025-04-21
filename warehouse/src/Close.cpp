#include "../include/Action.h"
#include <iostream>

Close::Close() : BaseAction() {}

void Close::act(WareHouse &wareHouse){
    wareHouse.close();
    complete();
}

Close* Close::clone() const {
    return new Close(*this);
}

string Close::toString() const{
    return "close " + readStatus(getStatus());
}