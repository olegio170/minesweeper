#include "render.h"

render::render()
{
	mainMenuElements = { "Start game",
		"Set beginer", 
		"Set intermediate",
		"Set expert",
		"Control info",
		"Exit" };
}

render::~render()
{
	deleteTableArr();
}

void render::setScreenSize(int w, int h)
{
	SCREENWIDTH = toRenderCord(w);
	SCREENHEIGHT = toRenderCord(h);
	maxTableW = SCREENWIDTH - 1;
	maxTableH = SCREENHEIGHT - 1;
}

void render::setMineField(cell** field)
{
	mineField = field;
}


int render::getMenuItemsCount()
{
	return mainMenuElements.size();
}


void render::printMainMenu(int active)
{
	system("cls");
	std::cout << "   [Main menu]\n\n";
	for (int i = 0; i < getMenuItemsCount(); i++)
	{
		if (i == active)
			std::cout << " > ";
		else
			std::cout << "   ";
		std::cout << mainMenuElements[i] << " \n";
	}
}

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

void render::printEndWon()
{
	std::cout << "\nCongratulations you won !!!\n";
	system("pause");
}

void render::printEndLoose()
{
	std::cout << "\nGame over !\n";
	system("pause");
}

void render::printControlInfo()
{
	system("cls");
	std::cout << "   [Control info] \n\n";
	std::cout << "   WASD       - movement \n";
	std::cout << "   O [letter] - flag/unflag cell \n";
	std::cout << "   Enter      - open cell \n";
	system("pause");
}

void render::printNewDifficulty(int bombsCount, int w, int h)
{
	std::cout << "\n\tBombs: " << bombsCount << "\n\tField: " << w << "*" << h;
}


void render::insertCell(int x, int y)
{
	int tabX = toRenderCord(x),
		tabY = toRenderCord(y);

	cell *element = &mineField[x][y];

	if (element->isOpen())
		table[tabX][tabY] = element->getValue();
	else if (element->isFlaged())
		table[tabX][tabY] = flag;
	else
		table[tabX][tabY] = square;
}

void render::insertAllCells()
{
	for (int i = 0; i < SCREENHEIGHT / 2; i++)
		for (int j = 0; j < SCREENWIDTH / 2; j++)
			insertCell(i, j);
}

void render::insertActive(int x, int y)
{
	x = toRenderCord(x);
	y = toRenderCord(y);

	table[x + 1][y] += 9;
	table[x - 1][y] += 9;

	table[x][y + 1] += 7;
	table[x][y - 1] += 7;
}

void render::insertActive(int x, int y, int lastActiveX, int lastActiveY)
{
	x = toRenderCord(x);
	y = toRenderCord(y);

	table[x + 1][y] += 9;
	table[x - 1][y] += 9;

	table[x][y + 1] += 7;
	table[x][y - 1] += 7;

	lastActiveX = lastActiveX * 2 + 1;
	lastActiveY = lastActiveY * 2 + 1;


	table[lastActiveX + 1][lastActiveY] -= 9;
	table[lastActiveX - 1][lastActiveY] -= 9;

	table[lastActiveX][lastActiveY + 1] -= 7;
	table[lastActiveX][lastActiveY - 1] -= 7;
}


void render::openAllBombs()
{
	for (int i = 0; i < SCREENHEIGHT / 2; i++)
	{
		for (int j = 0; j < SCREENWIDTH / 2; j++)
		{
			if (mineField[i][j].getValue() == '*')
			{
				mineField[i][j].open();
				insertCell(i, j);
			}
		}
	}
}

void render::prepareGameField()
{
	createTableArr();
	insertBorders();
}

void render::createTableArr()
{
	table = new char*[SCREENHEIGHT];
	for (int i = 0; i < SCREENHEIGHT; ++i)
		table[i] = new char[SCREENWIDTH];
}

void render::deleteTableArr()
{
	for (int i = 0; i < SCREENHEIGHT; i++)
		delete[] table[i];
	delete[] table;
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

void render::setColor(int background, int text)
{
	HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hStdOut, (WORD)((background << 4) | text));
}

int render::toRenderCord(int cord)
{
	return cord * 2 + 1;
}