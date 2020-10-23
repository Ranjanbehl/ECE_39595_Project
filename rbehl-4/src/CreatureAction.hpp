#ifndef __CREATUREACTION_H__
#define __CREATUREACTION_H__

#include <iostream>
#include <string>
#include <cstdlib>
#include "Action.hpp"

class Creature;

class CreatureAction: public Action{
public:
    CreatureAction(Creature creatureOwner);
private:
    Creature* owner;
};

#endif