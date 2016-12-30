#include "game.h"

#define SCREENWIDTH 80// TODO: change location of this
#define SCREENHEIGHT 20

int main()
{
	game game(SCREENWIDTH,SCREENHEIGHT);
	game.run();
	system("pause");
	return 0;
}