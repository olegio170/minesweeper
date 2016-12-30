#pragma once
#include "cell.h"
#include "render.h"
#include "controller.h"

#define BOMBSCOUNT 20

class game
{
public:
	game(int w , int h): SCREENWIDTH(w), SCREENHEIGHT(h)
	{	
		if (~w & 1)
			SCREENWIDTH--;
		if (~h & 1)
			SCREENHEIGHT--;
		calcCellsCount();
		createCellsArr();
		toOpen = width*height - BOMBSCOUNT;
	}
	void run();
	int toOpenLeft();
	void decToOpen();
private:
	int SCREENWIDTH, SCREENHEIGHT, width, height,
		toOpen;
	cell **mineField;
	bool inField(int coord, int end);
	void calcCellsCount();
	void createCellsArr();
	void setBombs(int count);
};

