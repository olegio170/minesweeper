#pragma once
#include <iostream>
#include <vector>
#include <string>
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

// Difficulty

#define beginerBombsCount 10
#define beginerWidth 9
#define beginerHeight 9

#define intermediateBombsCount 40
#define intermediateWidth 16
#define intermediateHeight 16

#define expertBombsCount 99
#define expertWidth 30
#define expertHeight 16

class render
{
public:
	render();
	~render();

	void setScreenSize(int w, int h);
	void setMineField(cell** field);
	
	int  getMenuItemsCount();

	void printMainMenu(int active);
	void printTable();
	void printEndWon();
	void printEndLoose();
	void printControlInfo();
	void printNewDifficulty(int bombsCount, int w, int h);
	
	void insertCell(int x, int y);
	void insertAllCells();
	void insertActive(int x, int y);
	void insertActive(int x, int y, int lastActiveX, int lastActiveY);

	void openAllBombs();
	void prepareGameField();
	void deleteTableArr();
private:
	std::vector<std::string> mainMenuElements;
	int SCREENWIDTH, SCREENHEIGHT, maxTableH, maxTableW;
	char **table;
	cell **mineField;
	
	void createTableArr();
	void insertBorders();
	void setColor(int text, int background);
	int toRenderCord(int cord);
};
