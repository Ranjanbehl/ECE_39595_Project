#include "KeyboardListener.hpp"
#include <sstream>
#include <iostream>
#include <stdio.h>
#include <ctime>
#include <stdlib.h>
#include <thread>
#include <unistd.h>

#define KEY_UP 'k'
#define KEY_DOWN 'j'
#define KEY_LEFT 'h'
#define KEY_RIGHT 'l'
//STEP 3 //
#define INVENTORY 'i'
#define PICK_UP 'p'
#define DROP 'd'
//STEP 4//
#define CHANGE 'c'
#define END 'E'
#define HELP '?'
#define EXTRAHELP 'H'
#define READ 'r'
#define TAKE 'T'
#define WEAR 'w'


KeyboardListener::KeyboardListener(ObjectDisplayGrid* _display,Player* _player,Dungeon* _dungeon): display(_display),player(_player),dungeon(_dungeon){
    if (player->getArmor() != NULL){
        pack.push_back((Item*)player->getArmor());
    }
    if (player->getSword() != NULL){
        pack.push_back((Item*)player->getSword());
    }
    if (player->getScroll() != NULL){
        pack.push_back((Item*)player->getScroll());
    }
    return;
}

void KeyboardListener::listen(){
    running = true;
    char userInput;
    do{
        //get userinput
        userInput = getchar();
        if(player->getHp() <= 0){
            switch(userInput){
            case END:
                end(std::tolower(getchar()));
                break;
            default:
                break;   
            }
        }
        else{
        switch(userInput){
        
        case KEY_UP:
           // mvup();
           move("up");
            break;
        case KEY_DOWN:
            //mvdown();
            move("down");
            break;
        case KEY_LEFT:
           // mvleft();
           move("left");
            break;
        case KEY_RIGHT:
            //mvright();
            move("right");
            break;
        case DROP:
            drop(std::tolower(getchar()));
            break;
        case PICK_UP:
            addItem();
            break;
        case INVENTORY:
            show();
            break;
        case CHANGE:
            change();
            break;
        case END:
            end(std::tolower(getchar()));
            break;
        case HELP:
            help();
            break;
        case EXTRAHELP:
            extraHelp(std::tolower(getchar()));
            break;
        case READ:
            read(std::tolower(getchar()));
            break;
        case TAKE:
            take(std::tolower(getchar()));
            break;
        case WEAR:
            wear(std::tolower(getchar()));
            break;
        default:
			break;
        }
        }
        display->update();
    } while(running && userInput != EOF);
}

void KeyboardListener::move(std::string direction){
    int cX,cY,xOffset,yOffset;
    char c;
    cX = player->getXPos();
    cY = player->getYPos();

    if(direction == "up"){
        // (x,y) to (x,y+1)
        /* check if a wall exists */
        cY = cY + 1;
        xOffset = 0;
        yOffset = -1;
        if(wall(cX,cY,c)) {
            display->update();
        }else{
            check(cX,cY,xOffset,yOffset,c);
        }
    }
    else if(direction == "down"){
         // (x,y) to (x,y-1)
        /* check if a wall exists */
        cY = cY - 1;
        xOffset = 0;
        yOffset = 1;
        if(wall(cX,cY,c)) {
            display->update();
        }else{
            check(cX,cY,xOffset,yOffset,c);
        }
    }
    else if(direction == "left"){
        // (x,y) to (x-1,y)
        /* check if a wall exists */
        cX = cX - 1;
        xOffset = 1;
        yOffset = 0;
        if(wall(cX,cY,c)) {
            display->update();
        }else{
            check(cX,cY,xOffset,yOffset,c);
        }
    }else{
        //direction is right
        // (x,y) to (x + 1,y)
        /* check if a wall exists */
        cX = cX + 1;
        xOffset = -1;
        yOffset = 0;
        if(wall(cX,cY,c)) {
            display->update();
        }else{
            check(cX,cY,xOffset,yOffset,c);
        }
    }

    return;
}

bool KeyboardListener::wall(int cX,int cY,char c){
    /* check if a wall exists */
    bool isWall = false;
    c = display->getChar(cX,cY);
    if(c == 'X' || c == '\0'){
        //cannot move here
    isWall = true;
    }
    return isWall;
}

void KeyboardListener::check(int cX,int cY, int xOffset,int yOffset,char c){
    //player hp moves
    if(player->countMoves()){
        std::string msg = "HP: " + std::to_string(player->getHp()) + "    " + "Score: " + std::to_string(player->getScore());
        display->writeLine(-2,msg); // was -2
        display->update();
    }
    //check for hallucination
    if(player->getHallucinateTerms()){
        display->hallucinateDisplay();
        std::string msg = "You are hallucinated for " + std::to_string(player->getHallucinateCounter()) + " turns";
        display->writeLine(dungeon->getHeight() + 2,msg);
        display->update();
        if(player->getHallucinateCounter() == 0){
            display->unHallucinateDisplay();
        }
    }

    c = display->getChar(cX,cY);
    // if floor || door || passage || item
    if(c == '.' || c == '+' || c == '#' || c == ']' || c == ')' || c == '?'){
        //deque the original position stack.
        int X = cX + xOffset;
        int Y = cY + yOffset;
        display->deleteObjectToDisplay(X,Y);
        //add the character to the new dest
        display->addObjectToDisplay(new GridChar('@'),cX,cY);
        player->setPosX(cX);
        player->setPosY(cY);

        display->update();
    }
    // if monster
    else if (c == 'T' || c == 'H' || c == 'S'){
        Monster* targetMonster = findMonster(cX,cY);
        if ( targetMonster == NULL ){
            std::cout << "Error! No target monster found!" << std::endl;
        }else{
            hitMonster(targetMonster);
            display->update();
        }
    }       
}

void KeyboardListener::drop(char key){
    // remove item from inventory
    int pos = key - '0';
    if (pack.size() - 1 < pos ){
        display->writeLine(dungeon->getHeight() + 2,"Info: Invalid inventory number");
    }else{
        dropItem(player->getXPos(), player->getYPos(), pack[pos],1);
        pack.erase(pack.begin() + pos);
    }
    display->update();
    return;
}

void KeyboardListener::dropItem(int X,int Y,Item* target, int msg_mode){
    std::string msg;
    //update the item's positiontion
    target->setPosX(X);
    target->setPosY(Y);
    //set inventory ownership to false
    target->setInvOwnership(false);
    display->deleteObjectToDisplay(X,Y);
    char c = target->getType();
    if (c == ']' || c == ')' || c == '?'){
        display->addObjectToDisplay(new GridChar(c),X,Y);
        msg = "Info: dropping " + target->getName();
        if (target->getOwnershipStatus()){
            target->setDisown();
            if(c == ']'){
                player->setArmor(NULL);
            }else if (c == ')'){
                player->setSword(NULL);
            }else{
                player->setScroll(NULL);
            }
            msg = "Info: dropping an equipped " + target->getName();
        }
        if ( msg_mode == 1 ) {
            display->writeLine(dungeon->getHeight() + 2, msg);
        }
    }
    display->addObjectToDisplay(new GridChar('@'),X,Y);
}
void KeyboardListener::addItem(){
    int cX;
    int cY;
    char c;
    cX = player->getXPos();
    cY = player->getYPos();
    //remove the player from the stack
    display->deleteObjectToDisplay(cX,cY);
    c = display->getChar(cX,cY); // get the second char
    Item* item1 = NULL;
    //add item to inventory
    // c is armor
    if(c == ']'){
        std::vector<Armor*> armors = dungeon->getArmors();
        for(int i = 0; i< (int)armors.size(); i++){
            if(armors[i]->getXPos() == cX && armors[i]->getYPos() == cY && (armors[i]->getInvOwnershipStatus() == false)){
                item1 = (Item*)armors[i];
            }
        }
    }
    else if(c == ')'){
        std::vector<Sword*> swords = dungeon->getSwords();
        for(int i = 0; i < (int)swords.size(); i++){
            if(swords[i]->getXPos() == cX && swords[i]->getYPos() == cY && (swords[i]->getInvOwnershipStatus() == false)){
                item1 = (Item*)swords[i];
            }
        }
    }
    else if(c == '?') {
        // c is ?
        std::vector <Scroll*> scrollVector = dungeon->getScrolls();
        for (int i = 0; i < (int) scrollVector.size(); i++) {
            if (scrollVector[i]->getXPos() == cX && scrollVector[i]->getYPos() == cY && (scrollVector[i]->getInvOwnershipStatus() == false)) {
                item1 = (Item *) scrollVector[i];
            }
        }
    }else{
        // if c is NULL (ie c == '\0' or c == '.')
        display->addObjectToDisplay(new GridChar('@'),cX,cY);
        std::string err = "Info: no item here";
        display->writeLine(dungeon->getHeight() + 2,err);
        display->update();
        return;
    }
    // inventory ownership
    item1->setInvOwnership(true); //set to true
    pack.push_back(item1);
    display->deleteObjectToDisplay(cX,cY);
    display->addObjectToDisplay(new GridChar('@'),cX,cY);
    std::string updateMsg = "Info: adding " + item1->getName() + " to the pack";
    display->writeLine(dungeon->getHeight() + 2,updateMsg);
    display->update();
    return;
}

void KeyboardListener::show(){
    std::string inventoryMessage = "Pack:";
    for(int i = 0; i < (int)pack.size(); i++){
        inventoryMessage += " " + std::to_string(i) + ") ";
        //print armor
        if (pack[i]->getType() == ']'){
            if (pack[i]->getIntVal() >= 0){
                inventoryMessage += "+" + std::to_string(pack[i]->getIntVal()) + " Armor";
            }else{
                inventoryMessage += std::to_string(pack[i]->getIntVal()) + " Armor";
            }
        }//print sword
        else if (pack[i]->getType() == ')'){
            if (pack[i]->getIntVal() >= 0){
                inventoryMessage += "+" + std::to_string(pack[i]->getIntVal()) + " Sword";
            }else{
                inventoryMessage += std::to_string(pack[i]->getIntVal()) + " Armor";
            }
        }//print scroll
        else {
            inventoryMessage += pack[i]->getName();
        }
        if (pack[i]->getOwnershipStatus()){
            inventoryMessage += (pack[i]->getType() == ']') ? "(a)" : "(w)";
        }
    }
    display->writeLine(dungeon->getHeight() -2,inventoryMessage);
    display->update();
    return;
}

void KeyboardListener::change(){
    std::string msg;
    Player* player = dungeon->getPlayer();
    Armor* ownedArmor = player->getArmor();
    if(ownedArmor == NULL){
        msg = "Info: no armor equipped";
    }
    else{
        ownedArmor->setDisown();
        player->setArmor(NULL);
        msg = "Info: unequipped armor";
    }
    display->writeLine(dungeon->getHeight() + 1,msg);// needs to be 1 for some reason
    display->update(); 
}

void KeyboardListener::end(char key){
    if(key == 'y' || key == 'Y'){
        //end game
        //running = false;
      // delete(display);
      player->setHp(0);
      display->writeLine(dungeon->getHeight() + 2,"Info: Game has been killed!");
      display->update();
    }
    }

void KeyboardListener::help(){
    std::string help;
    help = "Info: Commands: c d E ? H i p r T w";
    display->writeLine(dungeon->getHeight() + 2,help);
    display->update();
}
void KeyboardListener::extraHelp(char key){
    std:: string moreInfo;
    if (key =='c'){
        moreInfo = "Info: Take off armor and place it in inventory";
        display->writeLine(dungeon->getHeight() + 2,moreInfo);
        display->update();
    }
    else if(key == 'd'){
        moreInfo = "Info: drop item <integer> from the pack";
        display->writeLine(dungeon->getHeight() + 2,moreInfo);
        display->update();
    }
    else if(key == 'E'){
        moreInfo = "Info: End the game";
        display->writeLine(dungeon->getHeight() + 2,moreInfo);
        display->update();
    }
    else if(key == '?'){
        moreInfo = "Info: Show the different commands in the info section of the display";
        display->writeLine(dungeon->getHeight() + 2,moreInfo);
        display->update();
    }
    else if(key == 'H'){
        moreInfo = "Info: Give more detailed information about the specified command";
        display->writeLine(dungeon->getHeight() + 2,moreInfo);
        display->update();
    }
    else if(key == 'i'){
        moreInfo = "Info: Show/display the inventory";
        display->writeLine(dungeon->getHeight() + 2,moreInfo);
        display->update();
    }
    else if(key == 'p'){
        moreInfo = "Info: Pick up an item from the dungeon floor";
        display->writeLine(dungeon->getHeight() + 2,moreInfo);
        display->update();
    }
    else if(key == 'r'){
        moreInfo = "Info: Read an item, has to be a scroll";
        display->writeLine(dungeon->getHeight() + 2,moreInfo);
        display->update();
    }
    else if(key == 'T'){
        moreInfo = "Info: Take out a weapon from inventory";
        display->writeLine(dungeon->getHeight() + 2,moreInfo);
        display->update();
    }
    else if(key == 'w'){
        moreInfo = "Info: Wear item from the inventory";
        display->writeLine(dungeon->getHeight() + 2,moreInfo);
        display->update();
    }
    else {
        moreInfo += "Info: ";
        moreInfo += key;
        moreInfo += " is not a command!";
        display->writeLine(dungeon->getHeight() + 2,moreInfo);
        display->update();
    }

}
void KeyboardListener::read(char key){
    std::string msg;
    int pos = key - '0';
    Item* item1 = (pack.size() - 1 < pos) ? NULL : pack[pos];
    if (item1 == NULL){
        msg = "Info: invalid inventory number " + std::to_string(pos);
    }
    else if(item1->getType() != '?'){
        //item is not a scroll
        msg = "Info: item " + std::to_string(pos) + " is not a scroll";
    }
    else{//equip the scroll
        ItemAction* scrollAction = item1->getItemAction();
        if (scrollAction->getName() == "BlessArmor" || scrollAction->getName() == "BlessSword"){
            // 'a' applies to armor, 'w' applies to sword
            Item* cursedItem = (scrollAction->getCharValue() == 'a') ? (Item*)player->getArmor() : (Item*)player->getSword();
            if (cursedItem != NULL){
                cursedItem->setIntValue(cursedItem->getIntVal() + scrollAction->getIntValue());
                msg = "Info: " + cursedItem->getName() + " cursed! " + std::to_string(scrollAction->getIntValue()) + " taken from its effectiveness";
                /*where " + cursedItem->getName() + " is the name of the item"*/
            }else{
                msg = "Info: scroll of cursing does nothing because " + scrollAction->getName() + " is used when the object has not worn or wielded";
                //when the object is not worn or wielded";
    
            }
        }else if (scrollAction->getName() == "Hallucinate"){
            msg = "Info: " + scrollAction->getMessage() + " It'll last for " + std::to_string(scrollAction->getIntValue()) + " terms!";
            player->setHallucinate(scrollAction->getIntValue());
        }
        pack.erase(pack.begin() + pos);
    }
    display->writeLine(dungeon->getHeight() + 2,msg);
    display->update();
}

void KeyboardListener::take(char key){
   std::string msg;
   int pos = key - '0';
   Item* item1 = (pack.size() - 1 < pos) ? NULL : pack[pos];
   if (item1 == NULL){
       msg = "Info: invalid inventory number " + std::to_string(pos);
   }
   else if(item1->getType() != ')'){
       //item is not a sword
        msg = "Info: item " + std::to_string(pos) + " is not a sword";
   }
   else if(player->getSword() != NULL){
       //player has already equipped a sword
       msg = "Info: a sword has already been equipped";
   }
   else {
       //equip the sword
       player->setSword((Sword *) item1);
       item1->setOwner(player);
       msg = "Info: item " + item1->getName() + " is equipped";
   }
   display->writeLine(dungeon->getHeight() + 2,msg);
   display->update();
}

void KeyboardListener::wear(char key){
   std::string msg;
   int pos = key - '0';
   Item* item1 = (pack.size() - 1 < pos) ? NULL : pack[pos];
   if (item1 == NULL){
       msg = "Info: invalid inventory number " + std::to_string(pos);
   }
   else if(item1->getType() != ']'){
       //item is not an armor
       msg = "Info: item " + std::to_string(pos) + " is not an armor";
   }
   else if(player->getArmor() != NULL){
       //player has already equipped an armor
       msg = "Info: an armor has already been equipped";
   }
   else{
       //equip the armor
       player->setArmor((Armor*)item1);
       item1->setOwner(player);
       msg = "Info: item " + item1->getName() + " is equipped";
   }
   display->writeLine(dungeon->getHeight() + 2,msg);
   display->update();
}

Monster* KeyboardListener::findMonster(int cX,int cY){
    std::vector<Monster*> monsters = dungeon->getMonsters();
    //Monster* pos = monsters.data();
    for (int i = 0; i < (int)monsters.size(); i++){
        if(monsters[i]->getXPos() == cX && monsters[i]->getYPos() == cY){
            return monsters[i];
        }
    }

    return NULL;
}

void KeyboardListener::hitMonster(Monster* targetMonster){
    int attackDamage,counterAttack;
    int playerMaxHit,monsterMaxHit;
    int playerDefense = 0,monsterDefense = 0;
    std::string msg;
    Player* player = dungeon->getPlayer();

    /* Setting up Monster defense */
    if( targetMonster->getArmor() != NULL ){
        monsterDefense += (targetMonster->getArmor())->getIntVal();
    }

    /* Setting up Player attack damage */
    playerMaxHit = player->getMaxHit();
    if( player->getSword() != NULL ){
        playerMaxHit += (player->getSword())->getIntVal();
    }
    attackDamage = (rand() % playerMaxHit + 1) - monsterDefense;

    /* If the damage isn't blocked */
    if ( attackDamage > 0 ){
        /* Hitting the monster */
        targetMonster->setHp((targetMonster->getHp()) - attackDamage);
        // Need to output a message indicating attackDamage Done
        msg = "Info: " + std::to_string(attackDamage) + " damage done!" +" monster remaining HP" + std::to_string(targetMonster->getHp());
        display->writeLine(dungeon->getHeight() + 2,msg);
        display->update();
    } else {
        // Need to output a message indicating no damage was done
         msg = "Info: no damage done!";
        display->writeLine(dungeon->getHeight() + 2,msg);
        display->update();
    }

    /* Check if Monster is still alive */
    if ( targetMonster->getHp() > 0 ){
        /* Still alive, preparing for counter attack */
        // check hit vector
        if (!(targetMonster->getHitAction().empty())){
            std::vector<CreatureAction*> hitVector = targetMonster->getHitAction();
            if (hitVector[0]->getName() == "Teleport"){
                msg = "Info: " + hitVector[0]->getMessage();
                display->setTeleport((Creature*)targetMonster);
                display->writeLine(dungeon->getHeight() + 2,msg);
                display->update();
                return;
            }
        }
        if ( player->getArmor() != NULL ){
            playerDefense += (player->getArmor())->getIntVal();
        }
        monsterMaxHit = targetMonster->getMaxHit();
        if ( targetMonster->getSword() != NULL ){
            monsterMaxHit += (targetMonster->getSword())->getIntVal();
        }
        counterAttack = (rand() % monsterMaxHit + 1) - playerDefense;
        
        /* If the counterAttack isn't blocked*/
        if ( counterAttack > 0 ){
            /*Hitting the player */
            player->setHp( (player->getHp()) - counterAttack );
            // Need to output a message indicating counter damage done
            msg = "HP: " + std::to_string(player->getHp()) + "    " + "Score: " + std::to_string(player->getScore());
            display->writeLine(-2,msg);//was -2
            display->update();
            if (!(player->getHitAction().empty())){
                std::vector<CreatureAction*> hitVector = player->getHitAction();
                if (hitVector[0]->getName() == "DropPack"){
                    if (pack.size() > 0 ) {
                        msg = "Info: " + hitVector[0]->getMessage();
                        int itemNum = rand() % pack.size();
                        dropItem(player->getXPos(),player->getYPos(),pack[itemNum],0);
                        pack.erase(pack.begin() + itemNum);
                    }else{
                        msg = "Info: drop pack was activated by the player has nothing to drop";
                    }
                    display->writeLine(dungeon->getHeight() + 2,msg);
                    display->update();
                }
            }
            /* Check if the player is dead */
            if ( player->getHp() <= 0 ){
                /* Dead, setup player death action */  
                msg = "Info: GAME OVER!";
                display->writeLine(dungeon->getHeight() + 2,msg);
                //updateDisplay action
                msg = "HP: " + std::to_string(player->getHp()) + "    " + "Score: " + std::to_string(player->getScore());
                display->writeLine(-2,msg);//was -2
                // death action
                display->addObjectToDisplay(new GridChar('+'),player->getXPos(),player->getYPos());
                display->update();
            }
        } else {
            // Need to output a message indicating no damage was done to the player
            msg = "Info: no damage taken!";
            display->writeLine(dungeon->getHeight() + 2,msg);
            display->update();
        }
    }else{
        /* Dead, setup monster death action */
        if (!(targetMonster->getDeathAction().empty())){
            std::vector<CreatureAction*> deathVector = targetMonster->getDeathAction();
            for(int i = 0; i < deathVector.size(); i++){
                if(deathVector[i]->getName() == "YouWin"){
                    msg = "Info: " + deathVector[i]->getMessage();
                    display->writeLine(dungeon->getHeight() + 2,msg);
                    display->update();
                }
            }
            }
          //msg = "Info: killed the monster!";
         // display->writeLine(dungeon->getHeight() + 2,msg);
          // remove the monster and drop items
          display->deleteObjectToDisplay(targetMonster->getXPos(),targetMonster->getYPos());
          // update the score
          player->setScore();
          msg = "HP: " + std::to_string(player->getHp()) + "    " + "Score: " + std::to_string(player->getScore());
          display->writeLine(-2,msg); // was -2 
          display->update();
    }
}
