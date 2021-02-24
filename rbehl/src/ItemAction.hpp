#ifndef __ITEMACTION_H__
#define __ITEMACTION_H__

#include <iostream>
#include <string>
#include <cstdlib>
#include "Action.hpp"
#include "Creature.hpp"

class Item;

class ItemAction:public Action{
public:
    ItemAction(Item* itemOwner,std::string name,std::string type);
private:
    Item* owner;
};

#endif