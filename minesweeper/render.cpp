#include "render.h"

void render::printTable(cell **mineField)
{	
	render::printPatternRow(leftTopCorner, horisontal, horisontalBottom, rightTopCorner);

	for (int i = 0; i < height; i++)
	{
		printCellRow(*(mineField + i));
		if(i != height-1)
			render::printPatternRow(verticalRight, horisontal, verticalHorisontal, verticalLeft);
	}
	render::printPatternRow(leftBottomCorner, horisontal, horisontalTop, rightBottomCorner);
}

void render::printPatternRow(char first, char main1, char main2, char last) {
	std::cout << first;

	for (int i = 0; i < width -1; i++)
		std::cout<< main1 << main2;

	std::cout << main1 << last << '\n';
}

void::render::printCellRow(cell *row)
{
	std::cout << (char)vertical;

	for (int i = 0; i < width - 1; i++, row++)
		std::cout << row->getValue() << (char)vertical;

	std::cout << row->getValue() << (char)vertical << '\n';

}