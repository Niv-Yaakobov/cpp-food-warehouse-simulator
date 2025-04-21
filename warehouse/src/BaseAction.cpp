#include "../include/Action.h"

BaseAction::BaseAction() : errorMsg(""), status(ActionStatus::ERROR) {}

ActionStatus BaseAction::getStatus() const {
    return status;
}

void BaseAction::complete() {
    status = ActionStatus::COMPLETED;
}

void BaseAction::error(string errorMsg) {
    status = ActionStatus::ERROR;
    this->errorMsg = errorMsg;
}

string BaseAction::getErrorMsg() const {
    return errorMsg;
}

string BaseAction::readStatus(ActionStatus status) const{
    return (status == ActionStatus::COMPLETED ? "COMPLETED" : "ERROR");
}
string BaseAction::getErrorText() const{
    return "ERROR: " + errorMsg;
}