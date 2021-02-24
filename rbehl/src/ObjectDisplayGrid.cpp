#include "ObjectDisplayGrid.hpp"
#include <curses.h>
#include <time.h>
#include <chrono>
#include <stdlib.h>
#include <string>
#include <stack>
ObjectDisplayGrid::ObjectDisplayGrid(int _width, int _height): width(_width), height(_height){
   // create the 2D array of grid characters
	objectGrid = new std::stack<GridChar*>*[width];
	for (int i = 0; i < width; i++) {
		objectGrid[i] = new std::stack<GridChar*>[height];
		for (int j = 0; j < height; j++) {
		    GridChar* zero = new GridChar('\0');
            (objectGrid[i][j]).push(zero);
		}
    }
/*Beginning of Ncurses*/
initscr();
cbreak(); // always on by default but good practice to include
noecho(); 
clear();
refresh();
//resizeterm(width,height + this->refHeight + this->botHeight);
}

ObjectDisplayGrid::~ObjectDisplayGrid() {
	// free memory from the dynamically sized object grid
	for (int i = 0; i < width; i++) {
		// delete all character objects in the grid
		for (int j = 0; j < height; j++) {
			//delete objectGrid[i][j];
			while( !(objectGrid[i][j].empty()) )
			    objectGrid[i][j].pop();
		}
		// delete the column
		delete[] objectGrid[i];
	}
	// delete the array of columns
	delete[] objectGrid;
	objectGrid = NULL;

	// free ncurses data
	endwin();
}

void ObjectDisplayGrid::setRefHeight(int topHeight){
	this->refHeight = topHeight;
}

int ObjectDisplayGrid:: getRefHeight(){
	return this->refHeight;
}

void ObjectDisplayGrid::addObjectToDisplay(GridChar* ch, int x, int y) {
	// note grid objects start from 0,0 and go until width,height
	// x between 0 and width
	if ((0 <= x) && (x < width)) {
		// y between 0 and height
		if ((0 <= y) && (y < height)) {
            // add new character to the internal character list
            (objectGrid[x][y]).push(ch);
			// draws the character on the screen, note it is relative to 0,0 of the terminal
			mvaddch(y + this->refHeight, x, ch->getChar());
		}
	}
}

void ObjectDisplayGrid::deleteObjectToDisplay(int x,int y){
    // note grid objects start from 0,0 and go until width,height
    // x between 0 and width
    if ((0 <= x) && (x < width)) {
        // y between 0 and height
        if ((0 <= y) && (y < height)) {
            // if the stack isn't empty or only contain the base initialized variable '\0'
            if( !(objectGrid[x][y]).empty() && (objectGrid[x][y]).size() > 1 ){
                // deque the top character from the stack
                (objectGrid[x][y]).pop();
                // draws the character on the screen, note it is relative to 0,0 of the terminal
                mvaddch(y + this->refHeight, x, (objectGrid[x][y].top())->getChar());
            }
        }
    }
}


void ObjectDisplayGrid::update() {
	// refreshes ncurses
	refresh();
}

void ObjectDisplayGrid::writeLine(int line, std::string message) {
	
	// messages start from 0, height and go until width,(height + messages)
	mvaddstr(refHeight + line, 0, message.c_str());
	// clear after what we wrote to EOL
	clrtoeol();
     
    // for topMsg line is fine but for botMsg add height to line
    //mvaddstr(line, 0, message.c_str());
    // clear after what we wrote to EOL
    //clrtoeol();
}

/* Function that returns preexisting char from a given x,y */
char ObjectDisplayGrid::getChar(int x, int y){
	GridChar* c = new GridChar('\0');
	char cDisplayed;
	if( !(objectGrid[x][y].empty()) ) {
        c = objectGrid[x][y].top();
    }
	if(c == NULL){
		cDisplayed = '\0';
	}
	else{
	 cDisplayed = c->getChar();
	}
	return cDisplayed; 
}

void ObjectDisplayGrid::hallucinateDisplay() {
    for (int x = 0; x < width; x++) {
        for (int y = 0; y < height; y++) {
            int controlVal = time(NULL);
            //controlVal += controlVal % ( controlVal / 10 );
            if( objectGrid[x][y].size() > 1 ){

                int randVal = rand() % 10;
                mvaddch(y + this->refHeight, x, randomDisplayValue(randVal));
            }
        }
    }
    //update();
}

void ObjectDisplayGrid::unHallucinateDisplay(){
    for (int x = 0; x < width; x++) {
        for (int y = 0; y < height; y++) {
            if(objectGrid[x][y].size() > 1){
                GridChar* c = objectGrid[x][y].top();
                mvaddch(y + this->refHeight, x,c->getChar());
            }
            }
    }
    //update();
}


char ObjectDisplayGrid::randomDisplayValue(int value) {
    //enum displayType { floor__ = 0 ,wall__ = 1 , passage__ = 2, junction__ = 3, sword__ = 4, armor__ = 5, scroll__ = 6, troll__ = 7, snake__ = 8, habgo__ = 9};
    switch (value) {
        case 0:
            return '.';
        case 1:
            return 'X';
        case 2:
            return '#';
        case 3:
            return '+';
        case 4:
            return ')';
        case 5:
            return ']';
        case 6:
            return '?';
        case 7:
            return 'T';
        case 8:
            return 'S';
        case 9:
            return 'H';
        default:
            return '.';

    }
}

void ObjectDisplayGrid::setTeleport(Creature* targetCreature) {
    int x = 0 , y = 0;
    char dest = '\0';
    do {
        x = rand() % (width);
        y = rand() % (height);
        dest = getChar(x,y);

        if (objectGrid[x][y].size() > 1 && (dest == '.' || dest == '#')){
            deleteObjectToDisplay(targetCreature->getXPos(),targetCreature->getYPos());
            addObjectToDisplay(new GridChar (targetCreature->getType()),x,y);
            targetCreature->setPosX(x);
            targetCreature->setPosY(y);

            mvaddch(y + this->refHeight, x,targetCreature->getType());
            break;
        }

    } while (objectGrid[x][y].size() <= 1 || ( dest != '.' && dest != '#'));
}