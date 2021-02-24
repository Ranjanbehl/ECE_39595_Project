#include <iostream>
#include <string>
#include <sstream>
#include <atomic>
#include <thread>
#include <exception>
#include <xercesc/sax2/SAX2XMLReader.hpp>
#include <xercesc/sax2/XMLReaderFactory.hpp>
#include <xercesc/sax2/DefaultHandler.hpp>
#include <xercesc/util/XMLString.hpp>
#include <xercesc/util/XMLUni.hpp>
#include <xercesc/util/PlatformUtils.hpp>
#include "XMLHandler.hpp"
#include "Dungeon.hpp"
#include "Structure.hpp"
#include "ObjectDisplayGrid.hpp"
#include "KeyboardListener.hpp"
#include "GridChar.hpp"
#include "curses.h"

std::atomic_bool isRunning(true);


bool isWall(ObjectDisplayGrid* display,int x,int y){
    char c; 
    c = display->getChar(x,y);
    if(c == 'X'){
        return true;
    }
    else{
        return false;
    }
}

void runDisplay(ObjectDisplayGrid* display,Dungeon* dungeon){
   resizeterm(((dungeon->getHeight())+(dungeon->getTopHeight())+(dungeon->getBotHeight())),dungeon->getWidth()); // do this in ncurses 
   // std::cout << "# of cols is " << ((dungeon->getHeight())+(dungeon->getTopHeight())+(dungeon->getBotHeight())); // works 
   Player *player = dungeon->getPlayer();
   //player->setRefHeight(dungeon->getTopHeight()); // not needed anymore
   display->setRefHeight(dungeon->getTopHeight());
   std::string topMsg = "HP: " + std::to_string(player->getHp()) + "    " + "Score: " + std::to_string(player->getScore());
   display->writeLine(0,topMsg);
   //int numNewLines = (dungeon->getBotHeight())/2; // do I need this? 
   std::string pack = "Pack:\n";
   std::string info = "\nInfo:";
   display->writeLine(dungeon->getHeight(),pack);
    display->writeLine(dungeon->getHeight() + 2,info);
   display->update();
    /**Room 
     * Walls are X
     * floors are .
    */
    for(int i = 0; i< ((int)dungeon->getRooms().size()); i++){
        //std::cout <<"the size of the room vector is " + std::to_string(dungeon->getRooms().size()); // this works
        Room room = dungeon->getRooms()[i];
        int posY = room.getYPos();
        int posX = room.getXPos();
        int width = room.getWidth();
        int height = room.getHeight();
        char c;
        for(int j = posX; j < (posX + width); j++){
            for(int k = posY; k < (posY + height); k++){
                if(j == posX  || k == posY || j == (posX + width - 1) || k == (posY + height - 1)){
                    c = 'X';
                }else{
                    c = '.';
                }
                display->addObjectToDisplay(new GridChar(c),j,k);
            }
        }
        display->update();

    }
    /* Plot the passages 
    ** floors are #
    ** junctions are +
    */  
   for(int k = 0; k < ((int)dungeon->getPassages().size()); k++){
       Passage passage = dungeon->getPassages()[k];
       std::vector<int> xPos = passage.getXPosVec();
       std::vector<int> yPos = passage.getYPosVec();
       char c;
       for(int i = 1; i < (int)xPos.size(); i++){
           if(xPos[i] == xPos[i-1]){
               if(yPos[i] > yPos[i-1]){
                   //print upward 
                   for(int j = yPos[i-1]; j < yPos[i]; j++){
                       c = '#';
                       display->addObjectToDisplay(new GridChar(c),xPos[i],j);
                   }
               }
               else{
                   //print downward
                   for(int j = yPos[i-1]; j > yPos[i]; j--){
                       c = '#';
                       display->addObjectToDisplay(new GridChar(c),xPos[i],j);
                   }

               }
           }
           else if(yPos[i] == yPos[i-1]){
               if(xPos[i] > xPos[i-1]){
                   //print rightward
                   for(int j = xPos[i-1]; j < xPos[i]; j++){
                       c = '#';
                       display->addObjectToDisplay(new GridChar(c),j,yPos[i]);
                   }
               }
               else{
                   //print leftward
                   for(int j = xPos[i-1]; j > xPos[i]; j--){
                       c = '#';
                       display->addObjectToDisplay(new GridChar(c),j,yPos[i]);
                   }
               }
           }
       }
       c = '+';
       // first and last point
       display->addObjectToDisplay(new GridChar(c),xPos.back(),yPos.back());
       display->addObjectToDisplay(new GridChar(c),xPos.front(),yPos.front());
       display->update();
   }
    char c; // used for monsters and items types

    //do this inside the room function aswell lol
   /* Plot the Items
   ** sword is ")"
   ** armor is "]", 
   ** scroll is "?"
    ***NOTE*** 
   Dont plot the item if it is equipped by the player 
   */
  std::vector<Scroll*> scrollItems = dungeon->getScrolls();
  for(int i = 0; i < (int)scrollItems.size(); i++){
      if(scrollItems[i]->getOwnershipStatus() == false){
          //item isnt owned so print it if there is no wall
        c = '?';
        display->addObjectToDisplay(new GridChar(c),scrollItems[i]->getXPos(),scrollItems[i]->getYPos());
      }
  }
  std::vector<Sword*> swordItems = dungeon->getSwords();
  for(int i = 0; i < (int)swordItems.size(); i++){
      if(swordItems[i]->getOwnershipStatus() == false){
          //item isnt owned so print it 
        c = ')';
        display->addObjectToDisplay(new GridChar(c),swordItems[i]->getXPos(),swordItems[i]->getYPos());
      }
  }
  std::vector<Armor*> armorItems = dungeon->getArmors();
  for(int i = 0; i < (int)armorItems.size(); i++){
      if(armorItems[i]->getOwnershipStatus() == false){
          //item isnt owned so print it 
        c = ']';
        display->addObjectToDisplay(new GridChar(c),armorItems[i]->getXPos(),armorItems[i]->getYPos());
      }
  }

    //update do this inside the room function!
    /* Plot the Monsters
    ** Trolls are  a ‘T’
    ** Snakes are a ‘S’
    ** Hobgoblins are a ‘H'
    */
    std::string type;
    std::vector<Monster*> monsters = dungeon->getMonsters();
    for(int i = 0; i < (int)monsters.size(); i++){
        type = monsters[i]->getName();
        if(type == "Troll"){
            c = 'T';
            display->addObjectToDisplay(new GridChar(c),monsters[i]->getXPos(),monsters[i]->getYPos());
        }
        else if(type == "Snake"){
            c = 'S';
            display->addObjectToDisplay(new GridChar(c),monsters[i]->getXPos(),monsters[i]->getYPos());
        }
        else{
            //Hobgoblin//
            c = 'H';
            display->addObjectToDisplay(new GridChar(c),monsters[i]->getXPos(),monsters[i]->getYPos());
        }
        //update the screen
        display->update();
    }

    /* Plot the Player
    ** player is @ 
     */
    //plotting it last as if a monster exist in a players spot player overrides it 
    c = '@';
   display->addObjectToDisplay(new GridChar(c),player->getXPos(),player->getYPos());
   //refresh the screen aftering adding everything
   display->update();

  /*Letting the other threads catch up similar to await*/
    for (int i = 0; (isRunning && i < 5); i++) {
            std::this_thread::sleep_for(std::chrono::milliseconds(400));
        }
}

int main(int agrc, char* argv[]){
    std::string filename;
    Dungeon* parsedDungeon = NULL;
    filename = "../xmlFiles/" + ((std::string) argv[1]);
    try{
        xercesc::XMLPlatformUtils::Initialize();
    }
    catch (const xercesc::XMLException& toCatch) {
        char* message = xercesc::XMLString::transcode(toCatch.getMessage());
        std::cout << "Error during initialization! :\n";
        std::cout << "Exception message is: \n"
             << message << "\n";
        xercesc::XMLString::release(&message);
        return 1;
    }
    xercesc::SAX2XMLReader* parser = xercesc::XMLReaderFactory::createXMLReader();
    try {
        XMLHandler* handler = new XMLHandler();
        parser->setContentHandler(handler);
        parser->setErrorHandler(handler);
        parser->setFeature(xercesc::XMLUni::fgSAX2CoreValidation, true);
        parser->setFeature(xercesc::XMLUni::fgSAX2CoreNameSpaces, true);
        XMLCh * fileNameXMLEnc = xercesc::XMLString::transcode(filename.c_str()); //Encode string as UTF-16, but transcode needs casting as const char * (not std::string)
        parser->parse(fileNameXMLEnc);// parsing process
        xercesc::XMLString::release(&fileNameXMLEnc);
        parsedDungeon = handler->getDungeon();
		delete parser;
		//delete handler; 
    } catch (const xercesc::XMLException& toCatch) {
            char* message = xercesc::XMLString::transcode(toCatch.getMessage());
            std::cout << "Exception message is: \n"
                 << message << "\n";
            xercesc::XMLString::release(&message);
            return -1;
    }
    catch (const xercesc::SAXParseException& toCatch) {
        char* message = xercesc::XMLString::transcode(toCatch.getMessage());
        std::cout << "Exception message is: \n"
             << message << "\n";
        return -1;
    }
	catch(std::exception& e){ 
        std::cout << std::endl;
	    std::cout << e.what() << '\n';
	}
	catch(...){
        std::cout << std::endl;
        std::cout << "Unexpected Exception \n" ;
        return -1;
	}
    
    //do not delete handler for now, or else dungeon address will be erased
    xercesc::XMLPlatformUtils::Terminate(); //valgrind will say there's memory errors if not included
    /*Step 2 stuff*/
    //parsedDungeon is the dungeon from xmlhandler
    //Create and initialize the display
    //int width = parsedDungeon->getWidth();
    //int gameHeight = parsedDungeon->getHeight();
    //ObjectDisplayGrid display(width,gameHeight); // screen(a box) is displayed 
    //ObjectDisplayGrid* pDisplay = &display;
    //seed
     srand(time(NULL));
    ObjectDisplayGrid* pDisplay = parsedDungeon->getDisplay();
    // std::thread displayThread(&ObjectDisplayGrid::run,&display);
    /*Display Thread */
    std::thread displayThread(runDisplay,pDisplay,std::ref(parsedDungeon));
    /*keyboard listener Thread */
    Player* player = parsedDungeon->getPlayer(); // pass this into KeyboardListener
    KeyboardListener listener(pDisplay,player,parsedDungeon);
    std::thread keyboardThread(&KeyboardListener::listen,&listener);
    keyboardThread.join();
    isRunning = false;
    displayThread.join();
    delete(pDisplay);
    
    return 0;
}