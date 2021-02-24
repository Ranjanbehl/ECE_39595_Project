#ifndef __SWORD_H__
#define __SWORD_H__

#include "Items.hpp"

class Sword: public Item{
public:
    Sword();
    Sword(std::string swordName);
private:
   // std::string name;
};
#endif