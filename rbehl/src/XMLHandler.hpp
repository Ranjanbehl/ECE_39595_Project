#ifndef __XMLHANDLER_H__
#define __XMLHANDLER_H__

#include <iostream>
#include <string>
#include <cstring>
#include <vector>
#include <algorithm>
#include <cstdlib>
#include <stack>
#include <functional>
#include <xercesc/sax2/SAX2XMLReader.hpp>
#include <xercesc/sax2/XMLReaderFactory.hpp>
#include <xercesc/sax2/DefaultHandler.hpp>
#include <xercesc/util/XMLString.hpp>
#include <xercesc/sax2/Attributes.hpp>
#include "Action.hpp"
#include "Creature.hpp"
#include "Displayable.hpp"
#include "Dungeon.hpp"
#include "Items.hpp"
#include "Scroll.hpp"
#include "Armor.hpp"
#include "Sword.hpp"
#include "Structure.hpp"
#include "Monster.hpp"
#include "Player.hpp"
#include "ItemAction.hpp"
#include "CreatureAction.hpp"

enum charType{  Default__ = 0, Room__ = 1 , Passage__ = 2 , Monster__ = 3 , Player__ = 4 , Scroll__ = 5 , Armor__ = 6 , Sword__ = 7 };
enum actionType{ Zero__ = 0, CreatureAction__ = 1 , ItemAction__ = 2 };

class XMLHandler: public xercesc::DefaultHandler{
public:
    void startElement(const XMLCh* uri, const XMLCh* localName, const XMLCh* qName, const xercesc::Attributes& attributes) ;
    void endElement(const XMLCh* uri, const XMLCh* localName, const XMLCh* qName) ;
    void characters(const XMLCh * const ch, const XMLSize_t length );

    Displayable* setDisplayable(enum charType type);
    Action* setAction();
    void addAction(enum actionType type);
    void setFunctionmode(enum charType type,std::string val);

    Dungeon* getDungeon();
    Creature* getCreature();
    Item* getItem();

    bool checkOwnershipStatus();
private:
    int DEBUG = 0;
    std::vector<Room> rooms; //can't not get rid of this for some reason
    void addRoom(Room room);
    int roomCount = 0;

    std::string data;
    Dungeon* dungeon;
    Room* room; 
    Passage* passage;
    Monster* monster;
    Player* player;
    Scroll* scrollItem;
    Armor* armor;
    Sword* sword;
    CreatureAction* creatureAction;
    ItemAction* itemAction;

    bool isposX = false;
    bool isposY = false;
    bool isWidth = false;
    bool isHeight = false;
    bool isType = false;
    bool isHp = false;
    bool isMaxHit = false;
    bool isVisible = false;
    bool isHpMoves = false;
    bool isActionMessage = false;
    bool isActionIntValue = false;
    bool isItemIntValue = false;
    bool isActionCharValue = false;
    actionType actionIcator = Zero__;
    std::stack <charType> hierarchy;
};

#endif // !1