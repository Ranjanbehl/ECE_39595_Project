#ifndef __ITEMACTION_H__
#define __ITEMACTION_H__

#include <iostream>
#include <string>
#include <cstdlib>
#include "Action.hpp"
#include "Creature.hpp"

class ItemAction:public Action{
public:
    ItemAction(Item itemOwner);
private:
    Item owner;
};

#endif