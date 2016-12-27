#pragma once
#include <iostream>
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

class render
{
public:
	render(int w, int h): width(w), height(h)
	{}
	void render::printTable(cell **mineField);
private:
	int width, height;
	void printPatternRow(char first, char main1, char main2, char last);
	void printCellRow(cell *row);
};
