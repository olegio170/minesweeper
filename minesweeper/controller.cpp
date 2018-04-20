#include "controller.h"

controller::controller() 
{
	setDefaultValues();
	renderPtr = new render();
	MAINMENUCOUNT = renderPtr->getMenuItemsCount();
}

controller::~controller()
{
	delete renderPtr;
}

void controller::mainMenuControl()
{
	renderPtr->printMainMenu(0);

	char input;
	do
	{
		input = _getch();
		switch (input)
		{
		case 'w':
			changeActiveMenu(-1);
			break;
		case 's':
			changeActiveMenu(1);
			break;
		case 13: // Enter
			switch (lastActiveMenu)
			{
			case 0:
				startGame();
				renderPtr->printMainMenu(lastActiveMenu);
				renderPtr->deleteTableArr();
				setDefaultValues();
				delete gamePtr;
				break;
			case 1: // beginer
				setDifficulty(beginerBombsCount, beginerWidth, beginerHeight);
				break;
			case 2: // intermediate
				setDifficulty(intermediateBombsCount, intermediateWidth, intermediateHeight);
				break;
			case 3: // expert
				setDifficulty(expertBombsCount, expertWidth, expertHeight);
				break;
			case 4:
				renderPtr->printControlInfo();
				renderPtr->printMainMenu(lastActiveMenu);
				break;
			case 5:
				exit(0);
				break;
			default:
				break;
			}
			break;
		default:
			break;
		}
	} while (1);
}

void controller::gameControl()
{
	renderPtr->printTable();
	bool doInput = true;
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
			gamePtr->setFlag(lastActiveX, lastActiveY);
			break;
		case 13: // Enter
			doInput = handleCellChoose();
			break;
		case 27:// Esc
			doInput = false;
			break;
		default:
			break;
		}

	} while (doInput);

}


void controller::setDefaultValues()
{
	bombsCount = beginerBombsCount;
	width = beginerWidth;
	height = beginerHeight;
	lastActiveX = 0;
	lastActiveY = 0;
}

void controller::setDifficulty(int count, int w, int h)
{
	bombsCount = count;
	width = w;
	height = h;
	renderPtr->printNewDifficulty(bombsCount, w , h);
}

bool controller::inRange(int coord, int end)
{
	if (coord >= 0 && coord < end)
		return true;
	else
		return false;
}

void controller::changeActive(int xOffset, int yOffset)
{
	int x = lastActiveX + xOffset,
		y = lastActiveY + yOffset;

	if (!inRange(x, height) || !inRange(y, width))
		return;

	renderPtr->insertActive(x, y, lastActiveX, lastActiveY);
	renderPtr->printTable();

	lastActiveX = x;
	lastActiveY = y;
}

void controller::changeActiveMenu(int offset)
{
	int active = lastActiveMenu + offset;

	if (!inRange(active, MAINMENUCOUNT))
		return;

	renderPtr->printMainMenu(active);

	lastActiveMenu = active;
}

bool controller::handleCellChoose()
{
	bool doInput = true;
	cell *element = &mineField[lastActiveX][lastActiveY];

	if (element->isOpen() || element->isFlaged())
		return doInput;

	if (element->getValue() == '*')
	{
		renderPtr->openAllBombs();
		renderPtr->printTable();
		renderPtr->printEndLoose();
		doInput = false;
	}
	else {
		gamePtr->openCell(lastActiveX, lastActiveY);
		renderPtr->printTable();
		if (!gamePtr->getToOpen())
		{
			renderPtr->printEndWon();
			doInput = false;
		}
	}

	return doInput;
}

void controller::startGame()
{
	gamePtr = new game(width, height, renderPtr);
	gamePtr->setBombs(bombsCount);
	mineField = gamePtr->getMineField();
	
	renderPtr->setMineField(mineField);
	renderPtr->setScreenSize(width, height);
	renderPtr->prepareGameField();
	renderPtr->insertActive(0, 0);
	renderPtr->insertAllCells();
	
	gameControl();
}
