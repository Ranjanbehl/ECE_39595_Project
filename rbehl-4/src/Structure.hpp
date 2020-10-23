#ifndef __STRUCTURE_H__
#define __STRUCTURE_H__

#include <iostream>
#include <string>
#include <cstdlib>
#include "Displayable.hpp"
#include "Creature.hpp"

class Structure: public Displayable{
public:
private:
};

class Room: public Structure{
public:
    Room(std::string roomName);
    void setId(int room);
    void setCreature(Creature Monster);
private:
    std::string Name;
    int Id;
};

class Passage: public Structure{
public:
    Passage();
    void setName(std::string passName);
    void setId(int room1,int room2);
private:
    int name;
    int Id;
};
#endif