#pragma once
#include "board.h"
#include "gotoxy.h"
class Console
{
	enum { MANU_FRAME_TOP_RIGHT = 70, MANU_FRAME_DOWN_RIGHT = 5 };
	enum { START_GAME = '1', PAUSE_RESUME = '2', INCREASE_SPEED = '3', DECREASE_SPEED = '4', MUSIC = '5', EXIT = '9' };
	char manuMatrixFrame[MANU_FRAME_DOWN_RIGHT][MANU_FRAME_TOP_RIGHT];
	enum SPEEDS { HIGH_SPEED = 100, MED_SPEED = 150, LOW_SPEED = 220 };
public:
	void printButtons();
	void printManuFrame();
	int speedFunc(char keyPressed, int speed);
	void printDetails(int score, int speedLevel, int brickCount, int nextShapeNumInTheArry);
	void printDetailsFrame();
	void printNextShape(int nextRndNumber);
	void pauseFunc(char keyPressed);
	int lotteryShape();
	void createManu();
	void manuButtonsAction();
	Console() {};
	void run(char &lastpressed);
	void Console::caseEsc(bool & flag);
	void caseRotate(char & keyPressed, Board & gameBoard, Shape & shape, bool & rotateDone);
	void Console::printKeyInstruction();
	void printFromTxtOpenGame();
	void printFromTxtEndGame();
	void cleanBoardAgain();
};