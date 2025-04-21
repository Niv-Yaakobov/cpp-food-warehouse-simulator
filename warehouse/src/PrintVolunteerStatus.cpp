#include "../include/Action.h"
#include "../include/Volunteer.h"
#include <iostream>

PrintVolunteerStatus::PrintVolunteerStatus(int id) : BaseAction(), volunteerId(id) {}

void PrintVolunteerStatus::act(WareHouse &wareHouse) {
    if (wareHouse.volunteerIdExist(volunteerId)){
        Volunteer& v = wareHouse.getVolunteer(volunteerId);
        std::cout << v.toString() <<std::endl;
        complete();
    }
    else{
        error("Volunteer doesn't exist");
    }
    
}

PrintVolunteerStatus* PrintVolunteerStatus::clone() const {
    return new PrintVolunteerStatus(*this);
}

string PrintVolunteerStatus::toString() const {
    return "VolunteerStatus " + std::to_string(volunteerId) + " " + readStatus(getStatus());
}