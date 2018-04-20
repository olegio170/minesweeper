#pragma once
#include "cell.h"
#include "render.h"

class game
{
public:
	game(int w, int h, render* render);
	~game();

	int getToOpen();
	cell** getMineField();

	void setFlag(int x, int y);
	void setBombs(int count);

	void openCell(int x, int y);
private:
	int width, height, toOpen;
	cell **mineField;
	render *renderPtr;

	bool inRange(int coord, int end);
	void createCellsArr();
	void deleteCellsArr();
};

