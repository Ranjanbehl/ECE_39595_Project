#ifndef __ITEMS_H__
#define __ITEMS_H__

class Creature;
#include <iostream>
#include <string>
#include <cstdlib>
#include "Displayable.hpp"
#include "Creature.hpp" 

class Item: public Displayable{
public:
    void setOwner(Creature itemOwner);
protected:
    Creature* owner;
};

class Scroll: public Item{
public:
    Scroll(std::string scrollName);
    void setID(int room,int serial);
private:
    int Id; //does it get inherented from displayable???
    std::string name;
};

class Armor: public Item{
public:
    Armor(std::string armorName);
    void setName(std::string armorName);
    void setID(int room,int serial);
private:
    std::string name;
    int id;
};

class Sword: public Item{
public:
    Sword(std::string swordName);
    void setID(int room,int serial);
private:
    std::string name;
    int id;
};

#endif