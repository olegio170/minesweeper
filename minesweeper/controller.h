#pragma once
#include <conio.h>
#include "render.h"
#include "cell.h"

class controller
{
public:
	controller(cell** fieldPtr, render* rendPtr, int w, int h) : mineField(fieldPtr)
		, renderPtr(rendPtr), width(w), height(h)
	{}
	void startGameControl();
private:
	render* renderPtr;
	cell** mineField;
	int width, height, lastActiveX = 0, lastActiveY = 0;
	void changeActive(int xOffset, int yOffset);
	void openCell(int x, int y);
	void setFlag(int x, int y);
	bool inField(int x, int y);
	void handleChoose();
};

