#ifndef __DUNGEON_H__
#define __DUNGEON_H__
#include <iostream>
#include <string>
#include <cstdlib>
#include "Structure.hpp"// Room,Passage inherients from structure
#include "Creature.hpp"
#include "Displayable.hpp"// Structure,Item,Creature,Magic inherients from displayable

class Dungeon{
public:
    Dungeon(); //default constructor 
    Dungeon getDungeon(std::string name,int width,int gameHeight);
    void addRoom();
    void addCreature();
    void addPassage();
    void additem();
private:
    std::string dungeonName;
};

#endif // !__DUNGEON_H__