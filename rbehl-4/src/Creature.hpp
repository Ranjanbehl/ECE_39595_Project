#ifndef __CREATURE_H__
#define __CREATURE_H__

class Item;
#include <iostream>
#include <string>
#include <cstdlib>
#include "Displayable.hpp" //does this needs to be included if Structure includes it?
#include "CreatureAction.hpp"
#include "Items.hpp"

class Creature: public Displayable{
public:
    Creature();
    void setHp(int h);
    void setHpMoves(int hpm);
    void setDeathAction(CreatureAction* da);
    void setHitAction(CreatureAction* ha);
private:
    /* CreateAction exists in action.hpp */

    CreatureAction* deathAction;
    CreatureAction* hitAction;
};

#endif