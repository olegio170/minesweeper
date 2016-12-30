#include "render.h"

void render::printTable()
{	
	system("cls");
	for (int i = 0; i < SCREENHEIGHT; i++)
	{
		for (int j = 0; j < SCREENWIDTH; j++)
		{
			char element = table[i][j];
			switch (element)
			{
			case '*':
				setColor(0, 4);
				break;
			case '1':
				setColor(0, 9);
				break;
			case '2':
				setColor(0, 2);
				break;
			case '3':
				setColor(0, 4);
				break;
			default:
				setColor(0, 15);
				break;
			}
			std::cout << table[i][j];
		}
		std::cout << '\n';
	}
}

void render::createTableArr()
{
	table = new char*[SCREENHEIGHT];
	for (int i = 0; i < SCREENHEIGHT; ++i)
		table[i] = new char[SCREENWIDTH];
}

void render::insertBorders()
{
	// Set corners

	table[0][0] = leftTopCorner;
	table[0][maxTableW] =  rightTopCorner;
	table[maxTableH][0] = leftBottomCorner;
	table[maxTableH][maxTableW] = rightBottomCorner;

	// Top and bottom border
	int i; 
	for (i = 1; i < SCREENWIDTH - 3; i = i + 2)
	{
		table[0][i] = horisontal;
		table[0][i + 1] = horisontalBottom;

		table[maxTableH][i] = horisontal;
		table[maxTableH][i + 1] = horisontalTop;
	}
	table[0][i] = horisontal;
	table[maxTableH][i] = horisontal;
	
	// Left and right border 
	for (i = 1; i < SCREENHEIGHT - 3; i = i + 2)
	{
		table[i][0] = vertical;
		table[i + 1][0] = verticalRight;

		table[i][maxTableW] = vertical;
		table[i + 1][maxTableW] = verticalLeft;
	}
	table[i][0] = vertical;
	table[i][maxTableW] = vertical;

	// Between rows
	for (i = 2; i < SCREENHEIGHT - 1; i = i + 2)
	{
		int j;
		for (j = 1; j < SCREENWIDTH - 2; j = j + 2)
		{
			table[i][j] = horisontal;
			table[i][j + 1] = verticalHorisontal;
		}
		table[i][j] = horisontal;
	}

	// Between cols 
	for(i = 1; i < SCREENHEIGHT; i = i + 2)
	{
		for (int j = 2; j < SCREENWIDTH - 2; j = j + 2)
		{
			table[i][j] = vertical;
		}
	}
}

void render::insertAllCells()
{
	for (int i = 0; i < SCREENHEIGHT / 2; i++)
		for (int j = 0; j < SCREENWIDTH / 2; j++)
			insertCell(i, j);
}

void render::insertActive(int x, int y, int lastActiveX, int lastActiveY)
{
	x = x*2 + 1;
	y = y*2 + 1;
	
	lastActiveX = lastActiveX * 2 + 1;
	lastActiveY = lastActiveY * 2 + 1;

	table[lastActiveX + 1][lastActiveY] -= 9;
	table[lastActiveX - 1][lastActiveY] -= 9;

	table[lastActiveX][lastActiveY + 1] -= 7;
	table[lastActiveX][lastActiveY - 1] -= 7;

	table[x + 1][y] += 9;
	table[x - 1][y] += 9;
	
	table[x][y + 1] += 7;
	table[x][y - 1] += 7;
	
}

void render::insertCell(int x, int y)
{
	int tabX = x * 2 + 1,
		tabY = y * 2 + 1;
	cell *element = &mineField[x][y];

	if (element->isOpen())
		table[tabX][tabY] = element->getValue();
	else if (element->isFlaged())
		table[tabX][tabY] = flag;
	else
		table[tabX][tabY] = square;
}

void render::printGameEnd()
{
	std::cout << "\n\n\n\t\t\tGame over !";
	system("pause");
	exit(0);
}

void render::setColor(int background, int text)
{
	HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hStdOut, (WORD)((background << 4) | text));
}

void render::openAllBombs()
{
	for (int i = 0; i < SCREENHEIGHT / 2; i++)
	{	for (int j = 0; j < SCREENWIDTH / 2; j++)
		{
			if (mineField[i][j].getValue() == '*')
			{
				mineField[i][j].open();
				insertCell(i, j);
			}
		}
	}
	printTable();
	printGameEnd();
}


void render::printMainMenu(int active)
{
	std::cout << "   [Main menu]\n\n";
	for (int i = 0; i < MAINMENUCOUNT; i++)
	{
		if (i == active)
			std::cout << " > ";
		else
			std::cout << "   ";
		std::cout << mainMenuElements[i] << " \n";
	}
}
