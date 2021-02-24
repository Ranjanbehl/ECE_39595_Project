#ifndef __CREATURE_H__
#define __CREATURE_H__


#include <iostream>
#include <string>
#include <cstdlib>
#include <vector>
#include "Displayable.hpp" //does this needs to be included if Structure includes it?


class CreatureAction;
class Armor;
class Sword;
class Scroll;

class Creature: public Displayable{
public:
    Creature();
    void setDeathAction(CreatureAction* da);
    void setHitAction(CreatureAction* ha);
    void setArmor(Armor* armor);
    void setSword(Sword* sword);
    void setScroll(Scroll* scroll);
    Armor* &getArmor();
    Sword* &getSword();
    Scroll* &getScroll();
    std::vector<CreatureAction*> getDeathAction();
    std::vector<CreatureAction*> getHitAction();
private:
    /* CreateAction exists in CreatureAction.hpp */
    std::vector<CreatureAction*> deathVectors;
    std::vector<CreatureAction*> hitVectors;
    Armor* equippedArmor;
    Sword* equippedSword;
    Scroll* equippedScroll;
};

#endif