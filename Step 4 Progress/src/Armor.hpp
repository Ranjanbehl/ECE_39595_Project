#ifndef __ARMOR_H__
#define __ARMOR_H__
#include "Items.hpp"

class Armor: public Item{
public:
    Armor();
    Armor(std::string armorName);
    //void setName(std::string armorName);
private:
   // std::string name;
};
#endif