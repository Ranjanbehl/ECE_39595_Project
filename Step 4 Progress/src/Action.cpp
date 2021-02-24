#include "Action.hpp"

Action::Action(std::string actionName,std::string actionType){
    this->name = actionName;
    this->type = actionType;
}

void Action::setMessage(std::string msg) {
    this->message = msg;
}

void Action::setIntValue(int v) {
    this->intVal = v;
}

void Action::setCharValue(char c) {
    this->charVal = c;
}

std::string Action::getName(){
    return this->name;
}

std::string Action::getType(){
    return this->type;
}

std::string Action::getMessage(){
    return this->message;
}

int Action::getIntValue() {
    return this->intVal;
}

char Action::getCharValue() {
    return this->charVal;
}
