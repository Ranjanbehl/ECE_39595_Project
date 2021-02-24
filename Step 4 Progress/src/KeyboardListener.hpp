#pragma once
#include <string>
#include <stack>
#include "ObjectDisplayGrid.hpp"
#include "Dungeon.hpp"
#include "Sword.hpp"
#include "Armor.hpp"
#include "Scroll.hpp"
#include "Player.hpp"
#include "CreatureAction.hpp"

class KeyboardListener {
private:
    /** Object display grid reference to write errors */
    ObjectDisplayGrid* display;
    Player* player;
    Dungeon* dungeon;
    /** set to false to stop running the keyboard listener */
    bool running = false;
    //std::stack<Item> pack; // use vector
    std::vector<Item*> pack; // inventory
    //std::stack<Item*> temp; // for item display
public:
    /**
     * Creates a new keyboard listener
     * @param grid  Object display grid reference
     */
    KeyboardListener(ObjectDisplayGrid* _display,Player* _player,Dungeon* _dungeon);

    /*movement function*/
    void move(std::string dirction);
    bool wall(int cX,int cY,char c);
    void check(int cX,int cY,int xOffset,int yOffset,char c);

    /*Drop Function & Add Function */
    void drop(char key);
    void dropItem (int X,int Y,Item* target,int msg_mode);

    void addItem();
    /*Function that shows inventory*/
    void show();

    //step 4 functions
    void change();
    void end(char key);
    void help();
    void extraHelp(char key);
    void read(char key);
    void take(char key);
    void wear(char key);
    
    /*Function to deal with monsters*/
    Monster* findMonster(int cX,int cY);
    void hitMonster(Monster* targetMonster);

    void listen();
};
