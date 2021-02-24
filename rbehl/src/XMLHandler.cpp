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
            hierarchy.push(Default__);
			std::string dungeonName = xmlChToString(getXMLChAttributeFromString(attributes,"name"));
            int dungeonWidth = std::stoi(xmlChToString(getXMLChAttributeFromString(attributes,"width")));
            int dungeonTopHeight = std::stoi(xmlChToString(getXMLChAttributeFromString(attributes,"topHeight")));
            int dungeonGameHeight = std::stoi(xmlChToString(getXMLChAttributeFromString(attributes,"gameHeight")));
            int dungeonBottomHeight = std::stoi(xmlChToString(getXMLChAttributeFromString(attributes,"bottomHeight")));

            //Assign Variables...
            this->dungeon = Dungeon::getDungeon(dungeonName,dungeonWidth,dungeonGameHeight,dungeonTopHeight,dungeonBottomHeight);


        } else if (case_insensitive_match(qNameStr,"Room") ) {
            hierarchy.push(Room__);
            std::string roomNum = xmlChToString(getXMLChAttributeFromString(attributes,"room")); 
            
            //Assign Variables...'
            room = new Room(roomNum);   
            //room = std::shared_ptr<Room> (new Room(roomNum)); // this is causing problems             
            
        } else if (case_insensitive_match(qNameStr,"Passage") ) {
            hierarchy.push(Passage__);
            std::string room1 = xmlChToString(getXMLChAttributeFromString(attributes,"room1"));
            std::string room2 = xmlChToString(getXMLChAttributeFromString(attributes,"room2"));

            //Assign Variables...
            passage = new Passage(); 
            passage->setId(stoi(room1),stoi(room2));

        }else if (case_insensitive_match(qNameStr,"Monster") || case_insensitive_match(qNameStr,"Player") ) {
            std::string creatureName = xmlChToString(getXMLChAttributeFromString(attributes,"name")); 
            int creatureRoom = std::stoi(xmlChToString(getXMLChAttributeFromString(attributes,"room")));
            int creatureSerial = std::stoi(xmlChToString(getXMLChAttributeFromString(attributes,"serial")));

            if (case_insensitive_match(qNameStr,"Monster")){
                hierarchy.push(Monster__);

                //Assign Variables
                monster = new Monster();
                monster->setName(creatureName);
                monster->setId(creatureRoom,creatureSerial);
                if (creatureName == "Troll"){
                    monster->setType('T');
                }else if (creatureName == "Snake"){
                    monster->setType('S');
                }else {
                    monster->setType('H');
                }

                
            }else{
                hierarchy.push(Player__);

                //Assign Variables
                player = new Player();
                player->setID(creatureRoom,creatureSerial);
                player->setType('@');
                
            }

        } else if (case_insensitive_match(qNameStr,"Scroll") || case_insensitive_match(qNameStr,"Armor") || case_insensitive_match(qNameStr,"Sword")) {
            std::string itemName = xmlChToString(getXMLChAttributeFromString(attributes,"name")); 
            int itemRoom = std::stoi(xmlChToString(getXMLChAttributeFromString(attributes,"room")));
            int itemSerial = std::stoi(xmlChToString(getXMLChAttributeFromString(attributes,"serial")));            
            
            if (case_insensitive_match(qNameStr,"Scroll")){
                hierarchy.push(Scroll__);

                //Assign Variables
                scrollItem = new Scroll(itemName); 
                scrollItem->setID(itemRoom,itemSerial);
                scrollItem->setType('?');
                
            }else if (case_insensitive_match(qNameStr,"Armor")){
                hierarchy.push(Armor__);;

                //Assign Variables
                armor = new Armor(itemName);
                armor->setID(itemRoom,itemSerial);
                armor->setType(']');
                
            }else{
                hierarchy.push(Sword__);

                //Assign Variables
                sword = new Sword(itemName);
                sword->setID(itemRoom,itemSerial);
                sword->setType(')');
            }

        } else if (case_insensitive_match(qNameStr,"CreatureAction") || case_insensitive_match(qNameStr,"ItemAction")) {
            std::string actionName = xmlChToString(getXMLChAttributeFromString(attributes,"name")); 
            std::string actionType = xmlChToString(getXMLChAttributeFromString(attributes,"type"));

            if (case_insensitive_match(qNameStr,"CreatureAction")){
                actionIcator = CreatureAction__;

                //Assign Variable
                //Creature* owner = getActionOwner();
                Creature* owner = getCreature();
                this->creatureAction = new CreatureAction(owner,actionName,actionType);

            }else{
                actionIcator = ItemAction__;

                //Assign Variable
                Item* owner = getItem();
                this->itemAction = new ItemAction(owner,actionName,actionType);
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
    char* qNameStr = xercesc::XMLString::transcode(qName);
    enum charType scope = hierarchy.top();

    if(isposX){
        if (scope == Passage__){
            passage->setPosX(stoi(data));
        }else{
        Displayable* displayable = setDisplayable(scope);
        displayable->setPosX(stoi(data));
        }
        isposX = false;
    } else if (isposY) {
        if (scope == Passage__){
            passage->setPosY(stoi(data));
        }else{
        Displayable* displayable = setDisplayable(scope);
        displayable->setPosY(stoi(data));
        }
        isposY = false;
    } else if (isVisible) {
        Displayable* displayable = setDisplayable(scope);
        displayable->setVisible();
        isVisible = false;
    } else if (isWidth) {
        Displayable* displayable = setDisplayable(scope);
        displayable->setWidth(stoi(data));
        isWidth = false;
    } else if (isHeight) {
        Displayable* displayable = setDisplayable(scope);
        displayable->setHeight(stoi(data));
        isHeight = false;
    } else if (isType) {
        Displayable* displayable = setDisplayable(scope);
        displayable->setType(data.at(0)); // charat
        isType = false;
    } else if (isMaxHit) {
        Displayable* displayable = setDisplayable(scope);
        displayable->setMaxHit(stoi(data));
        isMaxHit = false;
    } else if (isHp) {
        Displayable* displayable = setDisplayable(scope);
        displayable->setHp(stoi(data));
        isHp = false;
    } else if (isHpMoves) {
        Displayable* displayable = setDisplayable(scope);
        displayable->setHpMoves(stoi(data));
        isHpMoves = false;
    } else if (isActionMessage) {
        Action* action = setAction();
        action->setMessage(data);
        isActionMessage = false;
    } else if (isActionCharValue) {
        Action* action = setAction();
        action->setCharValue(data.at(0));
        isActionCharValue = false;
    } else if (isActionIntValue) {
        Action* action = setAction();
        action->setIntValue(stoi(data));
        isActionIntValue = false;
    } else if (isItemIntValue) {
        Displayable* displayable = setDisplayable(scope);
        displayable->setIntValue(stoi(data));
        isItemIntValue = false;
    } else if (case_insensitive_match(qNameStr,"Room")){
        dungeon->addRoom(*room);
        //delete(room); // remember to finish deconstuctor.
        hierarchy.pop();
    } else if (case_insensitive_match(qNameStr,"Passage")){
        dungeon->addPassage(*passage);
        hierarchy.pop();
    } else if (case_insensitive_match(qNameStr,"Monster")){
        monster->setPosX(monster->getXPos() + room->getXPos());
        monster->setPosY(monster->getYPos() + room->getYPos());
        dungeon->addMonster(monster);
        hierarchy.pop();
    } else if (case_insensitive_match(qNameStr,"Player")){
        player->setPosX(player->getXPos() + room->getXPos());
        player->setPosY(player->getYPos() + room->getYPos());
        dungeon->addPlayer(player);// pass by address (can't do by value since stack can't be transfered without dynamically allocating memory)
        hierarchy.pop();
    } else if (case_insensitive_match(qNameStr,"Scroll")){

        hierarchy.pop();
        scrollItem->setPosX(scrollItem->getXPos() + room->getXPos());
        scrollItem->setPosY(scrollItem->getYPos() + room->getYPos());
        
        //check if player ownership if it exists 
        if(scope == Player__){
            // won't happen
            scrollItem->setOwner((Creature*)player);
        }else if(scope == Monster__){
            //? What to do with this ?
            monster->setScroll(scrollItem);
            scrollItem->setOwner((Creature*) monster);
        }
        dungeon->addScroll(scrollItem);
        
    } else if (case_insensitive_match(qNameStr,"Armor")){

        hierarchy.pop();
        armor->setPosX(armor->getXPos() + room->getXPos());
        armor->setPosY(armor->getYPos() + room->getYPos());
        
        if (hierarchy.top() == Player__){         
            player->setArmor(armor);
            armor->setOwner((Creature*)player);
        } else if (hierarchy.top() == Monster__){      
            monster->setArmor(armor);
            armor->setOwner((Creature*)monster);            
        }
        dungeon->addArmor(armor);
    } else if (case_insensitive_match(qNameStr,"Sword")){

        hierarchy.pop();
        sword->setPosX(sword->getXPos() + room->getXPos());
        sword->setPosY(sword->getYPos() + room->getYPos());
        if (hierarchy.top() == Player__){
            player->setSword(sword);
            sword->setOwner((Creature*)player);
        } else if (scope == Monster__){
            monster->setSword(sword);
            sword->setOwner((Creature*)monster);            
        }
        dungeon->addSword(sword);
    } else if (case_insensitive_match(qNameStr,"ItemAction")){
        addAction(actionIcator);
    } else if (case_insensitive_match(qNameStr,"CreatureAction")){
        addAction(actionIcator);
    } else if (case_insensitive_match(qNameStr,"Dungeon")){
        hierarchy.pop();
    }

    xercesc::XMLString::release(&qNameStr);
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

void XMLHandler::setFunctionmode(enum charType type,std::string val){
    auto func = &Displayable::setPosX;
    if ( type == Room__ ){
        room->setFunctionAction(val,func);
    } 
}

Displayable* XMLHandler::setDisplayable(enum charType type){
    if ( type == Room__ ){
        return (Displayable*)(this->room);
    } else if ( type == Passage__ ){
        return (Displayable*)(this->passage);
    } else if ( type == Monster__ ){
        return (Displayable*)(this->monster);
    } else if ( type == Player__ ){
        return (Displayable*)(this->player);
    } else if ( type == Scroll__ ){
        return (Displayable*)(this->scrollItem);
    } else if ( type == Armor__ ){
        return (Displayable*)(this->armor);
    } else if ( type == Sword__ ){
        return (Displayable*)(this->sword);
    }
    return NULL;
}

Action* XMLHandler::setAction(){
    actionType type = this->actionIcator;
    if ( type == CreatureAction__ ){
        return (Action*)(this->creatureAction);
    } else if ( type == ItemAction__ ){
        return (Action*)(this->itemAction);
    }
    return NULL;
}

void XMLHandler::addAction(enum actionType type){
    if ( type == CreatureAction__ ){
        Creature* owner = getCreature();
        if (case_insensitive_match(this->creatureAction->getType(),"death")){
            owner->setDeathAction(this->creatureAction);
        } else {
            owner->setHitAction(this->creatureAction);
        }
    } else if ( type == ItemAction__ ){
        Item* owner = getItem();
        owner->setItemAction(this->itemAction);
    }
}

Dungeon* XMLHandler::getDungeon(){
    return this->dungeon;
}

Creature* XMLHandler::getCreature(){
    charType type = this->hierarchy.top();
    if ( type == Monster__ ){
        return (Creature*)(this->monster);
    } else if ( type == Player__ ){
        return (Creature*)(this->player);
    }
    return NULL;
}

Item* XMLHandler::getItem(){
    charType type = this->hierarchy.top();
    if ( type == Scroll__ ){
        return (Item*)(this->scrollItem);
    } else if ( type == Armor__ ){
        return (Item*)(this->armor);
    } else if ( type == Sword__ ){
        return (Item*)(this->sword);
    }
    return NULL;
}

bool XMLHandler::checkOwnershipStatus(){
    bool status;
    if(hierarchy.top() == Player__){
        //owned
        status = true;
    }
    else{
        status = false;
    }
    return status;
}
