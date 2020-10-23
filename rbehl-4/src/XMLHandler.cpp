#include "XMLHandler.hpp"

int case_insensitive_match(std::string s1, std::string s2) {
    //convert s1 and s2 into lower case strings
    std::transform(s1.begin(), s1.end(), s1.begin(), ::tolower); //std overloads tolower, ::tolower is the definition in the global namespace
    std::transform(s2.begin(), s2.end(), s2.begin(), ::tolower);
    if(s1.compare(s2) == 0)
        return 1;
    return 0;
}

inline std::string boolToString(bool booleanValue){
    return booleanValue ? "true": "false";
}

std::string xmlChToString(const XMLCh* xmlChName, int length = -1){
    //Xerces Parses file into XMLCh* string. So use Transcode to allocate a char* buffer
    char * chStarName = xercesc::XMLString::transcode(xmlChName); 
    if(length == -1){
        std::string StrName(chStarName);
        xercesc::XMLString::release(&chStarName);
        return StrName;
    }
    else{
        std::string StrName(chStarName,0,length);
        xercesc::XMLString::release(&chStarName);
        return StrName;
    }

}

const XMLCh* getXMLChAttributeFromString(const xercesc::Attributes& attributes, const char * strGet){
    XMLCh * xmlChGet = xercesc::XMLString::transcode(strGet);
    const XMLCh * xmlChAttr = attributes.getValue(xmlChGet);
    xercesc::XMLString::release((&xmlChGet));
    return xmlChAttr;
}

void XMLHandler::startElement(const XMLCh* uri, const XMLCh* localName, const XMLCh* qName, const xercesc::Attributes& attributes){

        char * qNameStr = xercesc::XMLString::transcode(qName);
        if (DEBUG == 1) {
            std::cout << ".startElement qName: " << qNameStr << std::endl;
        }
        if (case_insensitive_match(qNameStr,"Dungeon")) {
			std::string dun geonName = xmlChToString(getXMLChAttributeFromString(attributes,"name"));
            int dungeonWidth = std::stoi(xmlChToString(getXMLChAttributeFromString(attributes,"width")));
            int dungeonTopHeight = std::stoi(xmlChToString(getXMLChAttributeFromString(attributes,"topHeight")));
            int dungeonGameHeight = std::stoi(xmlChToString(getXMLChAttributeFromString(attributes,"gameHeight")));
            int dunegeonBottomHeight = std::stoi(xmlChToString(getXMLChAttributeFromString(attributes,"bottomHeight")));

            //Assign Variables... (ps. make sure Dunegon is only declared once)
            //if ( dunegon != NULL){
            //   
            //}
            std::cout << "Dungeon::getDungeon(std::string " + dungeonName << ",int " << dungeonWidth << ",int " << dungeonGameHeight << ")" << std::endl;

        } else if (case_insensitive_match(qNameStr,"Room") ) {
            indicator = Room__;
            std::string roomNum = xmlChToString(getXMLChAttributeFromString(attributes,"room")); 
            //Room qroom = Room(roomNum);
            //room.setId = Room(std::stoi(roomNum));
            //Assign Variables...
            std::cout << "Displayable::Displayable()" << std::endl;
            std::cout << "Structure::Structure()" << std::endl;
            std::cout << "Room::Room(" << roomNum << ")" << std::endl;
            //addRoom(qroom);

        } else if (case_insensitive_match(qNameStr,"Passage") ) {
            indicator = Passage__;
            std::string room1 = xmlChToString(getXMLChAttributeFromString(attributes,"room1"));
            std::string room2 = xmlChToString(getXMLChAttributeFromString(attributes,"room2"));

            //Assign Variables...
            std::cout << "Displayable::Displayable()" << std::endl;
            std::cout << "Structure::Structure()" << std::endl;
            std::cout << "Passage::Passage()" << std::endl;
            std::cout << "Passage::setID(" << room1 << "," << room2 << ")" << std::endl;

        }else if (case_insensitive_match(qNameStr,"Monster") || case_insensitive_match(qNameStr,"Player") ) {
            std::string creatureName = xmlChToString(getXMLChAttributeFromString(attributes,"name")); 
            int creatureRoom = std::stoi(xmlChToString(getXMLChAttributeFromString(attributes,"room")));
            int creatureSerial = std::stoi(xmlChToString(getXMLChAttributeFromString(attributes,"serial")));

            if (case_insensitive_match(qNameStr,"Monster")){
                indicator = Monster__;

                //Assign Variables
                std::cout << "Displayable::Displayable()" << std::endl;
                std::cout << "Creature::Creature()" << std::endl;
                std::cout << "Monster::Monster()" << std::endl;
                std::cout << "Monster::setID(" << creatureRoom << "," << creatureSerial << ")" << std::endl;
                std::cout << "Monster::setName(" + creatureName + ")" << std::endl;
            }else{
                indicator = Player__;

                //Assign Variables
                //if ( player != NULL )...
                std::cout << "Displayable::Displayable()" << std::endl;
                std::cout << "Creature::Creature()" << std::endl;
                std::cout << "Player::Player()" << std::endl;
            }

        } else if (case_insensitive_match(qNameStr,"Scroll") || case_insensitive_match(qNameStr,"Armor") || case_insensitive_match(qNameStr,"Sword")) {
            std::string itemName = xmlChToString(getXMLChAttributeFromString(attributes,"name")); 
            int itemRoom = std::stoi(xmlChToString(getXMLChAttributeFromString(attributes,"room")));
            int itemSerial = std::stoi(xmlChToString(getXMLChAttributeFromString(attributes,"serial")));            
            
            if (case_insensitive_match(qNameStr,"Scroll")){
                indicator = Scroll__;

                //Assign Variables
                std::cout << "Displayable::Displayable()" << std::endl;
                std::cout << "Item::Item()" << std::endl;
                std::cout << "Scroll::Scroll(" + itemName + ")" << std::endl;
                //delcare scroll here...
                std::cout << "Scroll::setID(" << itemRoom << "," << itemSerial << ")" << std::endl;
            }else if (case_insensitive_match(qNameStr,"Armor")){
                indicator = Armor__;

                //Assign Variables
                std::cout << "Displayable::Displayable()" << std::endl;
                std::cout << "Item::Item()" << std::endl;
                std::cout << "Armor::Armor(" + itemName + ")" << std::endl;
                //delcare armor here...
                std::cout << "Armor::setID(" << itemRoom << "," << itemSerial << ")" << std::endl;
            }else{
                indicator = Sword__;

                //Assign Variables
                std::cout << "Displayable::Displayable()" << std::endl;
                std::cout << "Item::Item()" << std::endl;
                std::cout << "Sword::Sword(" + itemName + ")" << std::endl;
                //delcare scroll here...
                std::cout << "Sword::setID(" << itemRoom << "," << itemSerial << ")" << std::endl;
            }

        } else if (case_insensitive_match(qNameStr,"CreatureAction") || case_insensitive_match(qNameStr,"ItemAction")) {
            std::string actionName = xmlChToString(getXMLChAttributeFromString(attributes,"name")); 
            std::string actionType = xmlChToString(getXMLChAttributeFromString(attributes,"type"));

            if (case_insensitive_match(qNameStr,"CreatureAction")){
                actionIcator = CreatureAction__;

                //Assign Variable
                std::cout << "Action::Action()" << std::endl;
                std::cout << "CreatureAction::CreatureAction(" << indicatorToChar(indicator) << ")" << std::endl;
            }else{
                actionIcator = ItemAction__;

                //Assign Variable
                std::cout << "Action::Action()" << std::endl;
                std::cout << "ItemAction::ItemAction(" << indicatorToChar(indicator) << ")" << std::endl;
            }
            
        } else if (case_insensitive_match(qNameStr,"posX")) {
            isposX = true;
        } else if (case_insensitive_match(qNameStr,"posY")) {
            isposY = true;
        } else if (case_insensitive_match(qNameStr,"visible")) {
            isVisible = true;
        } else if (case_insensitive_match(qNameStr,"width")) {
            isWidth = true;
        } else if (case_insensitive_match(qNameStr,"height")) {
            isHeight = true;
        } else if (case_insensitive_match(qNameStr,"type")) {
            isType = true;
        } else if (case_insensitive_match(qNameStr,"maxhit")) {
            isMaxHit = true;
        } else if (case_insensitive_match(qNameStr,"hp")) {
            isHp = true;
        } else if (case_insensitive_match(qNameStr,"hpMoves")) {
            isHpMoves = true;
        } else if (case_insensitive_match(qNameStr,"actionMessage")) {
            isActionMessage = true;
        } else if (case_insensitive_match(qNameStr,"actionCharValue")) {
            isActionCharValue = true;
        } else if (case_insensitive_match(qNameStr,"actionIntValue")) {
            isActionIntValue = true;
        } else if (case_insensitive_match(qNameStr,"ItemIntValue")) {
            isItemIntValue = true;
        } else if(case_insensitive_match(qNameStr,"Rooms") || case_insensitive_match(qNameStr,"Passages")){

        } else {
            std::cout <<"Unknown qname: " << qNameStr << std::endl;
        }
        xercesc::XMLString::release(&qNameStr);
}

void XMLHandler::endElement(const XMLCh* uri, const XMLCh* localName, const XMLCh* qName)  {
    if(isposX){
        std::cout << "Displayable::setPosX(" << data << ")" << std::endl;
        isposX = false;
    } else if (isposY) {
        std::cout << "Displayable::setPosY(" << data << ")" << std::endl;
        isposY = false;
    } else if (isVisible) {
        std::cout << "Displayable::setVisible()" << std::endl;
        isVisible = false;
    } else if (isWidth) {
        std::cout << "Displayable::setWidth(" << data << ")" << std::endl;
        isWidth = false;
    } else if (isHeight) {
        std::cout << "Displayable::setHeight(" << data << ")" << std::endl;
        isHeight = false;
    } else if (isType) {
        std::cout << "Displayable::setType(" << data << ")" << std::endl;
        isType = false;
    } else if (isMaxHit) {
        std::cout << "Displayable::setMaxHit(" << data << ")" << std::endl;
        isMaxHit = false;
    } else if (isHp) {
        std::cout << "Displayable::setHp(" << data << ")" << std::endl;
        isHp = false;
    } else if (isHpMoves) {
        std::cout << "Displayable::setHpMove(" << data << ")" << std::endl;
        isHpMoves = false;
    } else if (isActionMessage) {
        std::cout << "Action::setMessage(" << data << ")" << std::endl;
        isActionMessage = false;
    } else if (isActionCharValue) {
        std::cout << "Action::setCharValue(" << data << ")" << std::endl;
        isActionCharValue = false;
    } else if (isActionIntValue) {
        std::cout << "Action::setIntValue(" << data << ")" << std::endl;
        isActionIntValue = false;
    } else if (isItemIntValue) {
        std::cout << "Action::setIntValue(" << data << ")" << std::endl;
        isItemIntValue = false;
    }
    //char* qNameStr = xercesc::XMLString::transcode(qName);
    //xercesc::XMLString::release(&qNameStr);
}

void XMLHandler::addRoom (Room qroom){
    rooms[roomCount++] = qroom;
}

void XMLHandler::characters(const XMLCh * const ch, const XMLSize_t length) {
    data = xmlChToString(ch,(int)length);
    if (DEBUG == 1) {
        std::cout << ".characters: " << data << std::endl;
        std::cout.flush();
    }
}

std::string XMLHandler::indicatorToChar (charType indicator){
    if ( indicator == Default__ ){
        return "Default";
    } else if ( indicator == Passage__ ){
        return "Passage";
    } else if ( indicator == Monster__ ){
        return "Monster";
    } else if ( indicator == Player__ ){
        return "Player";
    } else if ( indicator == Scroll__ ){
        return "Scroll";
    } else if ( indicator == Armor__ ){
        return "Armor";
    } else if ( indicator == Sword__ ){
        return "Sword";
    }
    return NULL;
}