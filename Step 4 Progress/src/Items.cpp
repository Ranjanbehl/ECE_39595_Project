#include "Items.hpp"

Item::Item(){
    this->name = '\0';
}
Item::Item(std::string itemName){
    this->owner = NULL;
    owned = false;
    this->name = itemName;
}

void Item::setOwner(Creature* itemOwner) {
    this->owner = itemOwner;
    this->owned = true;
}

void Item::setID(int room,int serial){
    this->roomId = room;
    this->Id = serial;
}

bool Item::getOwnershipStatus(){
    return this->owned;
}

void Item::setItemAction(ItemAction* action){
    this->itemAction = action;
}

std::string Item::getName(){
    return this->name;
}

void Item::setDisown() {
    this->owned = false;
}

ItemAction* Item::getItemAction(){
    return this->itemAction;
}