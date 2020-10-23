#ifndef __PLAYER_H__
#define __PLAYER_H__

#include <iostream>
#include <string>
#include <cstdlib>
#include "Displayable.hpp" //does this needs to be included if Structure includes it?
#include "Creature.hpp"
#include "Items.hpp"

class Player: public Creature{
public:
    void setWeapon(Item playerSword);
    void setArmor(Item playerArmor);
private:
    Item* creatureSword;
    Item* creatureArmor;
};

#endif