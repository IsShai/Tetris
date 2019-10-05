#include "Point.h"
#include"board.h"
#include "console.h"


HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
int main()
{
	makeCmdScreenBigEnough();
	ShowConsoleCursor();
	Console game;
	game.printFromTxtOpenGame();
	game.createManu();
	system("CLS");
	game.printFromTxtEndGame();
	return 0;
}




