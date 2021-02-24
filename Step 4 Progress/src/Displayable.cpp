#include "Displayable.hpp"

Displayable::Displayable(){
    hitPoint = 0;
    hpMoves = 0;
    maxHit = 0;
    xPos = 0;
    yPos = 0;
    width = 0;
    height = 0;
    intVal = 0;
    show = true;
    cType = '\0';

}

void Displayable::setInvisible() {
    this->show = false;
}

void Displayable::setVisible() {
    this->show = true;
}

void Displayable::setHpMoves(int moves) {
    this->hpMoves = moves;
}

void Displayable::setMaxHit(int maxHitPoint) {
    this->maxHit = maxHitPoint;
}

void Displayable::setHp(int Hp) {
    this->hitPoint = Hp;
}

void Displayable::setType(char t) {
    this->cType = t;
}

void Displayable::setIntValue(int v) {
    this->intVal = v;
}

void Displayable::setPosX(int x) {
    this->xPos = x;
}

void Displayable::setPosY(int y) {
    this->yPos = y;
}

void Displayable::setWidth(int x) {
    this->width = x;
}

void Displayable::setHeight(int y) {
    this->height = y; 
}

void Displayable::setFunctionAction(std::string val, void (Displayable::*func)(int) ){
    //(*func)(stoi(val));
}

int Displayable::getXPos(){
    return this->xPos;
}

int Displayable::getYPos(){
    return this->yPos;
}

int Displayable::getHp(){
    return this->hitPoint;
}

int Displayable::getMaxHit(){
    return this->maxHit;
}

int Displayable::getIntVal(){
    return this->intVal;
}

int Displayable::getHpMoves(){
    return this->hpMoves;
}

char Displayable::getType(){
    return this->cType;
}