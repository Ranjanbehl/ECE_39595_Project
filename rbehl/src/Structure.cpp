#include "Structure.hpp"

Room::Room(std::string roomName): Name(roomName){
    setId(std::stoi(roomName));
}

void Room::setId(int room) {
    this->Id = room;
}

void Room::setCreature(Creature Monster) {
    creatureVectors.push_back(Monster);
}

int Room::getWidth(){
    return this->width;
}

int Room::getHeight(){
    return this->height;
}

Passage::Passage() {
}

void Passage::setName(std::string passName) {
    this->name = passName;
}

void Passage::setId(int room1, int room2) {
    this->firstId = room1;
    this->secondId = room2;
}

void Passage::setPosX(int x){
    xCords.push_back(x);
}

void Passage::setPosY(int y){
    yCords.push_back(y);
}

std::vector<int> &Passage::getXPosVec(){
    return xCords;
}

std::vector<int> &Passage::getYPosVec(){
    return yCords;
}