#include "Monster.hpp"

Monster::Monster() {
}

void Monster::setName(std::string monsterName) {
    this->name = monsterName;

}

void Monster::setId(int room, int serial) {
    this->Id = serial;
    this->roomId = room;
}

std::string Monster::getName(){
    return this->name;
}
