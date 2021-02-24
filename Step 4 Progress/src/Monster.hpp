#ifndef __MONSTER_H__
#define __MONSTER_H__

#include <iostream>
#include <string>
#include <cstdlib>
#include "Displayable.hpp"
#include "Creature.hpp"
//#include "Items.hpp" // dont include this 

class Monster: public Creature{
public:
    Monster();
    void setName(std::string monsterName);
    void setId(int room,int serial);
    std::string getName();
private:
    std::string name;
    int Id; //serial??
    int roomId;
};


#endif