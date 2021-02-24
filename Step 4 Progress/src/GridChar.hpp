#pragma once

/**
 * This class in its current form is simply a wrapper around a character.
 * However, it can easily be expanded to include other behaviors for a grid character.
 */
class GridChar {
private:
	char dispch;

public:
	/**
	 * Creates a new grid character
	 * @param dispch Character to use for display
	 */
	GridChar(char dispch);

	/**
	 * Gets the character used to display this grid character
	 * @return  Character to display
	 */
	virtual char getChar();
};

