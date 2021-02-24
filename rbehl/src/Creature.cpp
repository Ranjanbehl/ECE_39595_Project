#include "Creature.hpp"
#include "Action.hpp"
#include "CreatureAction.hpp"

Creature::Creature() {
    equippedArmor = NULL;
    equippedSword = NULL;
    equippedScroll = NULL;
}

void Creature::setDeathAction(CreatureAction* da) {
    this->deathVectors.push_back(da);
}

void Creature::setHitAction(CreatureAction* ha) {
    this->hitVectors.push_back(ha);
}

void Creature::setArmor(Armor* armor) {
    this->equippedArmor = armor;
}

void Creature::setSword(Sword* sword) {
    this->equippedSword = sword;
}

void Creature::setScroll(Scroll* scroll){
    this->equippedScroll  = scroll;
}

Armor* &Creature::getArmor(){
    return equippedArmor;
}

Sword* &Creature::getSword(){
    return equippedSword;
}

Scroll* &Creature::getScroll(){
    return equippedScroll;
}

std::vector<CreatureAction*> Creature::getDeathAction() {
    return deathVectors;
}

std::vector<CreatureAction*> Creature::getHitAction() {
    return hitVectors;
}