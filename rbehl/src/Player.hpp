#ifndef __PLAYER_H__
#define __PLAYER_H__

#include <iostream>
#include <string>
#include <cstdlib>
#include "Displayable.hpp" //does this needs to be included if Structure includes it?
#include "Creature.hpp"
#include "Items.hpp"

class Player: public Creature{
public:
    Player();
    void setID(int room,int serial);
    int getScore();
    void setScore();
    bool countMoves();
    void setHallucinate(int term);
    bool getHallucinateTerms();
    int getHallucinateCounter();
private:
    int Id; //serial??
    int roomId;
    int score;
    int refHeight;
    int moves;
    int hallucinateTerm;
    //Item* playerSword;
    //Item* playerArmor;
};

#endif