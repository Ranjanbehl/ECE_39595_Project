#include "Dungeon.hpp"
#include <memory>

Dungeon* Dungeon::instance = NULL;

Dungeon::Dungeon(){
}

Dungeon::Dungeon(std::string dungeonName,int dungeonWidth,int dungeonGameHeight,int dungeonTopHeight, int dungeonBottomHeight){
    this->dungeonName = dungeonName;
    this->gameHeight = dungeonGameHeight;
    this->topHeight = dungeonTopHeight;
    this->botHeight = dungeonBottomHeight;
    this->width = dungeonWidth;
    
    this->player = NULL;
}

Dungeon* Dungeon::getDungeon(std::string dungeonName,int dungeonWidth,int dungeonGameHeight,int dungeonTopHeight, int dungeonBottomHeight) {
    if(instance == NULL){
        //std::unique_ptr<Dungeon> instance = std::unique_ptr<Dungeon>(new Dungeon(name,width,gameHeight,top,bottom));
        instance = new Dungeon(dungeonName,dungeonWidth,dungeonGameHeight,dungeonTopHeight,dungeonBottomHeight);
    }
    return instance;
}

void Dungeon::addRoom(Room room){
   this->roomVectors.push_back(room);
//addMonster is within class Room/Passage
}
/*
void Dungeon::addItem(Item item){
   this->itemVectors.push_back(item);
}
*/
void Dungeon::addPassage(Passage passage){
    this->passageVectors.push_back(passage);
}

void Dungeon::addMonster(Monster* monster){
    this->monsterVectors.push_back(monster);
}

void Dungeon::addScroll(Scroll* scroll){
    this->scrollVectors.push_back(scroll);
}

void Dungeon::addSword(Sword* sword){
    this->swordVectors.push_back(sword);
}

void Dungeon::addArmor(Armor* armor){
   // std::cout << "adding armor" << std::endl;
    this->armorVectors.push_back(armor);
}

void Dungeon::addPlayer(Player* self){
    if(this->player != NULL){
        std::cout << "Error! player already exist, no addPlayer operation needed!" << std::endl;
    }else{
        player = self;
    }
}

ObjectDisplayGrid* Dungeon::getDisplay(){
    return new ObjectDisplayGrid(this->width,this->gameHeight);
}

int Dungeon::getWidth(){
    return this->width;
}

int Dungeon::getHeight(){
    return this->gameHeight;
}

int Dungeon::getTopHeight(){
    return this->topHeight;
}

int Dungeon::getBotHeight(){
    return this->botHeight;
}

Player* Dungeon::getPlayer(){
    return this->player;
}

std::vector<Room> &Dungeon::getRooms(){
    return roomVectors;
}

std::vector<Passage> &Dungeon::getPassages(){
    return passageVectors;
}

std::vector<Monster*> &Dungeon::getMonsters(){
    return monsterVectors;
}

std::vector<Scroll*> &Dungeon::getScrolls(){
    return scrollVectors;
}

std::vector<Sword*> &Dungeon::getSwords(){
    return swordVectors;
}

std::vector<Armor*> &Dungeon::getArmors(){
    return armorVectors;
}