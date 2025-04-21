#include "../include/Action.h"

extern WareHouse* backup;

BackupWareHouse::BackupWareHouse() : BaseAction() {}

void BackupWareHouse::act(WareHouse &wareHouse){
    if (backup == nullptr) {
        backup = new WareHouse(wareHouse);
    }
    else{
        *backup = wareHouse;
    }
    complete();
}

BackupWareHouse* BackupWareHouse::clone() const {
    return new BackupWareHouse(*this);
}

string BackupWareHouse::toString() const{
    return "Backup " + readStatus(getStatus());
}