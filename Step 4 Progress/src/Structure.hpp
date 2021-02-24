#ifndef __STRUCTURE_H__
#define __STRUCTURE_H__

#include <iostream>
#include <string>
#include <cstdlib>
#include <vector>
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
    int getWidth();
    int getHeight();
private:
    std::string Name;
    int Id;
    std::vector<Creature> creatureVectors;
};

class Passage: public Structure{
public:
    Passage();
    void setName(std::string passName);
    void setId(int room1,int room2);
    void setPosX(int x);
    void setPosY(int y);
    std::vector<int> &getXPosVec();
    std::vector<int> &getYPosVec();

private:
    std::string name;
    int firstId; //ID of room1
    int secondId; //ID of room2
    std::vector<int> xCords;
    std::vector<int> yCords;
};
#endif