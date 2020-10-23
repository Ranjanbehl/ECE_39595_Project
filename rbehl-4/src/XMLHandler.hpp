#ifndef __XMLHANDLER_H__
#define __XMLHANDLER_H__

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <cstdlib>
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
#include "Structure.hpp"

enum charType{  Default__ = 0, Room__ = 1 , Passage__ = 2 , Monster__ = 3 , Player__ = 4 , Scroll__ = 5 , Armor__ = 6 , Sword__ = 7 };

class XMLHandler: public xercesc::DefaultHandler{
public:
    void startElement(const XMLCh* uri, const XMLCh* localName, const XMLCh* qName, const xercesc::Attributes& attributes) ;
    void endElement(const XMLCh* uri, const XMLCh* localName, const XMLCh* qName) ;
    //void fatalError(const xercesc::SAXParseException&);
    void characters(const XMLCh * const ch, const XMLSize_t length );
    std::string indicatorToChar (enum charType indicator);
    //std::string toString();
private:
    int DEBUG = 0;
    std::string data;
    Dungeon dungeon;
    std::vector<Room> rooms;
    int roomCount = 0;
    void addRoom(Room room);

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
    //enum charType{  Default__ = 0, Room__ = 1 , Passage__ = 2 , Monster__ = 3 , Player__ = 4 , Scroll__ = 5 , Armor__ = 6 , Sword__ = 7 };
    enum actionType{ Zero__ = 0, CreatureAction__ = 1 , ItemAction__ = 2 };
    charType indicator = Default__;
    actionType actionIcator = Zero__;
    
};

#endif // !1