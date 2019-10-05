#pragma once
#include "bomb.h"
#include "cube.h"
#include "el.h"
#include "joker.h"
#include "plus.h"
#include "rec.h"
#include "zee.h"


class Board
{
public:
	enum { TOP_RIGHT = 12, DOWN_RIGHT = 17 }; 
	char boardMatrix[DOWN_RIGHT][TOP_RIGHT];
	Board();//Constractor: Create the game board
	char getMatrix(int x, int y){return boardMatrix[y - (BOARD_y_SET - 1)][x - (BOARD_X_SET)];}
	void draw();
	void boardLocation(){gotoxy(BOARD_X_SET, BOARD_y_SET);}
	int canRemoveOneLine(Board &playBoard);
	void blinkingLine(Board & playBoard, int numOfLine);
	int removeLine(Board &playBoard);
	void updatePlayeBoard(Shape & shape);
	bool canNotRotate(Shape &shape, Board &playBoard);
	bool gameOverFunc(Board &playBoard);
	void printGameOver();
	bool Board::isOneOfTheChar(char c); // functuon return true when c is on of the in t
};
