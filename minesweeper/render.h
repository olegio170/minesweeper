#pragma once
#include <iostream>
#include <windows.h> 
#include "cell.h"

// Corners
#define rightTopCorner 191
#define leftBottomCorner 192
#define rightBottomCorner 217
#define leftTopCorner 218

// Others
#define horisontal 196
#define horisontalTop 193
#define horisontalBottom 194

#define vertical 179
#define verticalRight 195
#define verticalLeft 180

#define verticalHorisontal 197

#define square 176
#define flag 213

#define MAINMENUCOUNT 3

class render
{
public:
	render(int w, int h, cell **field): SCREENWIDTH(w), SCREENHEIGHT(h), mineField(field)	
	{
		maxTableW = SCREENWIDTH - 1;
		maxTableH = SCREENHEIGHT - 1;

		createTableArr();
		insertBorders();
		insertAllCells();

		table[2][1] += 9;
		table[0][1] += 9;

		table[1][2] += 7;
		table[1][0] += 7;
	}
	void insertAllCells();
	void insertActive(int x, int y, int lastActiveX, int lastActiveY);
	void insertCell(int x, int y);
	void printGameEnd();
	void printTable();
	void openAllBombs();
	void printMainMenu(int active);
private:
	int SCREENWIDTH, SCREENHEIGHT,maxTableH,maxTableW;
	char **table;
	void createTableArr();
	void insertBorders();
	void setColor(int text, int background);
	cell **mineField;

	char mainMenuElements[MAINMENUCOUNT][30] =
	{ "Start game", "Options","Exit" };
};
