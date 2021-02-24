#ifndef __ITEMS_H__
#define __ITEMS_H__

class Creature;
#include <iostream>
#include <string>
#include <cstdlib>
#include "Displayable.hpp"
#include "Creature.hpp"
#include "ItemAction.hpp"
 

class Item: public Displayable{
public:
    Item();
    Item(std::string itemName);
    void setOwner(Creature* itemOwner);
    void setID(int room,int serial);
    void setItemAction(ItemAction* action);
    void setDisown();
    bool getOwnershipStatus();
    virtual std::string getName();
    virtual ItemAction* getItemAction();
protected:
    Creature* owner;
    ItemAction* itemAction;
    int roomId;
    int Id;
    bool owned; // true if item is owned by the player 
    std::string name;
};

#endif