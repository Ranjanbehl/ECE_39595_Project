#ifndef __DUNGEON_H__
#define __DUNGEON_H__
#include <iostream>
#include <string>
#include <cstdlib>
#include <vector>
#include "Structure.hpp"// Room,Passage inherients from structure
#include "Creature.hpp"
#include "Displayable.hpp"// Structure,Item,Creature,Magic inherients from displayable
#include "ObjectDisplayGrid.hpp" 
#include "Player.hpp"
#include "Items.hpp"
#include "Armor.hpp"
#include "Sword.hpp"
#include "Scroll.hpp"
#include "Monster.hpp"

class Dungeon{
public:
    Dungeon();// default constructor
    Dungeon(std::string dungeonName,int dungeonWidth,int dungeonGameHeight,int dungeonTopHeight, int dungeonBottomHeight); // constructor
    //remember to implement deconstructor 
    static Dungeon* getDungeon(std::string dungeonName,int dungeonWidth,int dungeonGameHeight,int dungeonTopHeight, int dungeonBottomHeight);
    void addRoom(Room room);
    void addPassage(Passage passage);
    //void addItem(Item item);
    void addMonster(Monster* monster);
    void addScroll(Scroll* scroll);
    void addSword(Sword* sword);
    void addArmor(Armor* armor);
    void addPlayer(Player* self);

    int getWidth();
    int getHeight();
    int getTopHeight();
    int getBotHeight();
    Player* getPlayer();
    ObjectDisplayGrid* getDisplay();
    std::vector<Room> &getRooms();
    std::vector<Passage> &getPassages();
    //vector<Item> getItems(); // use this instead 
    std::vector<Monster*> &getMonsters();
    std::vector<Scroll*> &getScrolls();
    std::vector<Sword*> &getSwords();
    std::vector<Armor*> &getArmors();

private:
    std::string dungeonName;
    int width;
    int gameHeight;
    int topHeight;
    int botHeight;
    static Dungeon* instance;
    Player* player; 
    std::vector<Room> roomVectors;
    std::vector<Passage> passageVectors;
    std::vector<Monster*> monsterVectors;
    std::vector<Scroll*> scrollVectors;
    std::vector<Sword*> swordVectors;
    std::vector<Armor*> armorVectors;
    friend class KeyboardListener;
};


#endif // !__DUNGEON_H__