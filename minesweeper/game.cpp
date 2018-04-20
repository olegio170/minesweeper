#include "game.h"
#include <time.h>

game::game(int w, int h, render* render) : width(w), height(h), renderPtr(render)
{
	createCellsArr();
}

game::~game()
{
	deleteCellsArr();
}


int game::getToOpen()
{
	return toOpen;
}

cell** game::getMineField()
{
	return mineField;
}


void game::setFlag(int x, int y)
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

void game::setBombs(int count)
{
	srand(time(NULL));

	toOpen = width*height - count;
	int ii = 0;
	while (ii < count)
	{
		int x = rand() % height;
		int y = rand() % width;

		// Check if bomb
		cell *bomb = &mineField[x][y];
		if (bomb->getValue() == '*')
			continue;

		bomb->setValue('*');

		cell *element;
		for (int i = -1; i <= 1; i++)
		{
			for (int j = -1; j <= 1; j++)
			{
				if (!inRange(x + i, height) ||
					!inRange(y + j, width))
					continue;

				element = &mineField[x + i][y + j];
				switch (element->getValue())
				{
				case ' ':
					element->setValue('1');
					break;
				case '*':
					break;
				default:
					element->incrementValue();
					break;
				}
			}
		}
		ii++;
	}
}

void game::openCell(int x, int y)
{
	if (!inRange(x, height) || !inRange(y, width) || mineField[x][y].getValue() == '*' || !mineField[x][y].open())
		return;

	toOpen--;
	renderPtr->insertCell(x, y);

	if (mineField[x][y].getValue() == ' ')
	{
		openCell(x + 1, y);
		openCell(x - 1, y);

		openCell(x, y + 1);
		openCell(x, y - 1);
	}
}


bool game::inRange(int coord, int end)
{
	if (coord >= 0 && coord < end)
		return true;
	else
		return false;
}

void game::createCellsArr()
{
	mineField = new cell*[height];
	for (int i = 0; i < height; i++)
		mineField[i] = new cell[width];
}

void game::deleteCellsArr()
{
	for (int i = 0; i < height; i++)
		delete[] mineField[i];
	delete[] mineField;
}