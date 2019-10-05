#include "joker.h"
#include "board.h"

Joker::Joker(Point & _head, const char _c) : Shape(_head, _c)
{
	int x = _head.getX(_head);
	int y = _head.getY(_head);
	char c1 = _c;
	for (int i = 0; i < SHAPE_SIZE; i++)
	{
		if (i == 0)
			c1 = JOKER_CHAR;
		else
			c1 = SPACE;
		bodyShape[i].set(x + i, y, c1);
	}

}

void Joker::takeShapeUp()
{
	for (int i = 0; i < SHAPE_SIZE; i++)
	{
		if (i == 0)
			bodyShape[0].set(START_X, START_Y, JOKER_CHAR);
		else
			bodyShape[i].set(START_X + i, START_Y, SPACE);
	}
}
bool Joker::canMoveShapeDown(Board & playBoard, bool & bombWasActivated, int & bombScore)
{
	int x, y;
	x = bodyShape[0].getX(bodyShape[0]); // get the x of the joker 
	y = bodyShape[0].getY(bodyShape[0]);  // get the y of the joker 

	for (int i = y - 5 + 1; i <= Board::DOWN_RIGHT - 2; i++)
	{// this look check if the joker has a blank cell it his row. 

		if (playBoard.boardMatrix[i][x - 7] == SPACE) // when there is a blank cell return true. 
		{
			return true; // the joker can still move doen 
		}
	}
	return false;
}

int Joker::calsScore(Board & gameBoard, int hightOfDropDown, int softDownCounter,
	int heightOfBombing, int bombScore)
{
	int removeLineCounter, scoreLine = 0, scoreDrop, totalScore;
	removeLineCounter = gameBoard.removeLine(gameBoard);//Remove lines if full and returns the number of the full lines		
	if (removeLineCounter != 0)
		scoreLine = SINGLE_LINE_CLR_JOKER;

	scoreDrop = dropScore(hightOfDropDown, softDownCounter, heightOfBombing);
	totalScore = scoreDrop + scoreLine + bombScore;  // sum of all score! 
	return totalScore;
}
