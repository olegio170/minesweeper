#include "controller.h"

void controller::startGameControl()
{
	char input;
	do
	{	
		input = _getch();
		switch (input)
		{
		case 'w':
			changeActive(-1, 0);
			break;
		case 'a':
			changeActive(0, -1);
			break;
		case 's':
			changeActive(1, 0);
			break;
		case 'd':
			changeActive(0, 1);
			break;
		case 'o':
			setFlag(lastActiveX,lastActiveY);
			break;
		case 13: // Enter
			handleChoose();
			break;
		default:
			break;
		}
		int a = 0;
		
	} while (1);
	
}

void controller::changeActive(int xOffset, int yOffset)
{
	int x = lastActiveX + xOffset,
		y = lastActiveY + yOffset;

	if (!inField(x,y))
		return;

	renderPtr->insertActive(x, y, lastActiveX, lastActiveY);
	renderPtr->printTable();

	lastActiveX = x;
	lastActiveY = y;
}

void controller::openCell(int x, int y)
{
	if (!inField(x, y) || !mineField[x][y].open() || mineField[x][y].getValue() == '*')
		return;
	
	renderPtr->insertCell(x,y);

	if (mineField[x][y].getValue() == ' ')
	{
		openCell(x + 1, y);
		openCell(x - 1, y);

		openCell(x, y + 1);
		openCell(x, y - 1);
	}
}

bool controller::inField(int x, int y)
{
	if (x < 0 || x >= height || y < 0 || y >= width)
		return false;
	else
		return true;
}

void controller::setFlag(int x, int y)
{
	 cell *cellPtr = &mineField[x][y];

	 if (cellPtr->isOpen())
		 return;

	if (!cellPtr->isFlaged())
		cellPtr->setFlag();
	else
		cellPtr->unSetFlag();
	 
	renderPtr->insertCell(x, y);
	renderPtr->printTable();
}

void controller::handleChoose()
{
	cell *element = &mineField[lastActiveX][lastActiveY];
	
	if (element->isFlaged())
		return;
	
	if (element->getValue() == '*')
		renderPtr->openAllBombs();
	else {
		openCell(lastActiveX, lastActiveY);
		renderPtr->printTable();
	}
}