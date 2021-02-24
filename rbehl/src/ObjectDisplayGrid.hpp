#pragma once
#include <string>
#include <stdlib.h>
#include <stack>
#include "GridChar.hpp"
#include "Displayable.hpp"
#include "Creature.hpp"

class ObjectDisplayGrid {
private:
    /** Keeps track of the characters on the screen */
	std::stack<GridChar*>** objectGrid;
	/** Keeps track of the consoles width and height */
	int height, width,refHeight;

	/** Number of lines for message writing */
	int messages;

public:
    /**
	 * Creates a new display grid using the given parameters and initializes ncurses.
	 * Screen height will be grid height + messages
	 * @param width     Screen width
	 * @param height    Grid height
	 * @param messages  Number of lines to reserve in the message area do
	 */
	ObjectDisplayGrid(int width, int height);

	/** Object deconstructor, to delete the grid character matrix and free ncurses data */
	~ObjectDisplayGrid();

	/**
	 * Refreshes the grid display
	 */
	virtual void update();

	/**
	 * Adds an object to the display grid
	 * @param ch  Object to display
	 * @param x   X position
	 * @param y   Y position
	 */
	virtual void addObjectToDisplay(GridChar* ch, int x, int y);
    virtual void deleteObjectToDisplay(int x,int y);
	/**
	 * Writes a line of text to the screen at the given line relative to the bottom
	 * @param line    line number
	 * @param message message to write
	 * @param update  If true, immediately updates the screen
	 */
	virtual void writeLine(int line, std::string message);

	virtual void setRefHeight(int topHeight);
	virtual int getRefHeight();

	virtual char getChar(int x, int y);

    /*ItemAction*/
    void hallucinateDisplay();
	void unHallucinateDisplay();
    char randomDisplayValue(int value);
    void setTeleport(Creature* targetCreature);
};