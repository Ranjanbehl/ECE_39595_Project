#include "Items.hpp"

void Item::setOwner(Creature itemOwner) {
    return;
}

Scroll::Scroll(std::string scrollName) {
    name = scrollName;
    return;
}

void Scroll::setID(int room, int serial) {
    exit(0);
}

Armor::Armor(std::string armorName) {
    name = armorName;
    return;
}

void Armor::setName(std::string armorName) {
    exit(0);
}

void Armor::setID(int room, int serial) {
    exit(0);
}

Sword::Sword(std::string name){
    return;
}

void Sword::setID(int room, int serial) {
    exit(0);
}