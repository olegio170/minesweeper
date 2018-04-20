#pragma once
#include <conio.h>
#include "render.h"
#include "cell.h"
#include "game.h"

class controller
{
public:
	controller();
	~controller();
	void mainMenuControl();
private:
	int SCREENHEIGHT,SCREENWIDTH, width, height,
		lastActiveX, lastActiveY,
		lastActiveMenu = 0, MAINMENUCOUNT,
		bombsCount = beginerBombsCount;

	render *renderPtr;
	game* gamePtr;
	cell** mineField;

	void setDefaultValues();
	void setDifficulty(int count, int width, int height);
	
	void gameControl();
	bool inRange(int coord, int end);
	void changeActive(int xOffset, int yOffset);
	void changeActiveMenu(int offset);
	bool handleCellChoose();
	
	void startGame();
};

