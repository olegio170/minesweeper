#include "game.h"
#include <time.h>

void game::run()
{
	calcCellsCount();
	createCellsArr();
	setBombs(20);

	render render(width, height);
	render.printTable(mineField);
}

bool game::inField(int coord, int end)
{
	if (coord >= 0 && coord <= end)
		return true;
	else
		return false;
}

void game::calcCellsCount()
{
	width = (SCREENWIDTH - 2) / 2;
	height = (SCREENHEIGHT - 2) / 2;
}

void game::createCellsArr()
{
	mineField = new cell*[height];
	for (int i = 0; i < height; ++i)
		mineField[i] = new cell[width];
}

void game::setBombs(int count)
{
	srand(time(NULL));

	for (int ii = 0; ii < count; ii++)
	{
		int x = rand() % height;
		int y = rand() % width;

		// Check if bomb
		cell *bomb = &mineField[x][y];
		if (bomb->getValue() == '*')
			continue;

		bomb->setValue('*');
		for (int i = -1; i <= 1; i++)
		{
			for (int j = -1; j <= 1; j++)
			{
				if (!inField(x + i, height - 1) ||
					!inField(y + j, width - 1))
					continue;

				cell *element = &mineField[x + i][y + j];
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

	}
}