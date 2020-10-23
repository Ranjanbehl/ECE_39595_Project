#ifndef __MONSTER_H__
#define __MONSTER_H__

#include <iostream>
#include <string>
#include <cstdlib>
#include "Displayable.hpp" //does this needs to be included if Structure includes it?
#include "Creature.hpp"
//#include "Items.hpp" // dont include this 


class Monster: public Creature{
public:
    Monster();
    void setName(std::string monsterName);
    void setID(int room,int serial);
private:
    std::string name;
    int Id;
};

#endif