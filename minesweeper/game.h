#pragma once
#include "cell.h"
#include "render.h"


#define SCREENWIDTH 80// TODO: change location of this
#define SCREENHEIGHT 20

class game
{
public:
	game()
	{}
	void run();
private:
	int width, height;
	cell **mineField;
	bool inField(int coord, int end);
	void calcCellsCount();
	void createCellsArr();
	void setBombs(int count);
};

