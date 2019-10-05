#include "bomb.h"
#include "board.h"

Bomb::Bomb(Point & _head, const char _c) : Shape(_head, _c)
{
	int x = _head.getX(_head);
	int y = _head.getY(_head);
	char c1 = _c;
	for (int i = 0; i < SHAPE_SIZE; i++)
	{
		if (i == 0)
			c1 = BOMB_CHAR;
		else
			c1 = SPACE;
		bodyShape[i].set(x + i, y, c1);
	}
}

void Bomb::takeShapeUp()
{// take the shape up the board
	{
		for (int i = 0; i < SHAPE_SIZE; i++)
		{
			if (i == 0)
				bodyShape[0].set(START_X, START_Y, BOMB_CHAR);
			else
				bodyShape[i].set(START_X + i, START_Y, SPACE);
		}
	}
}
bool Bomb::canMoveShapeDown(Board & playBoard, bool & bombWasActivated, int & bombScore)
{
	//	bool Board::canMoveShapeDown(

	int x, y, score;

	x = bodyShape[0].getX(bodyShape[0]);
	y = bodyShape[0].getY(bodyShape[0]);
	if (playBoard.boardMatrix[y - 4][x - 7] != SPACE)//check for bottom wall!!! _____
	{
		score = updateAfterBombing(playBoard, x, y); // update after the bombing 
		bombScore = score * (BOMB_SCORE);
		bombWasActivated = true;  // might be un-usefull
		return false;
	}

	return true;
}

void Bomb::moveAllWayDown(Board & playBoard, int & bombScore, int & bombHeight)
{// move the shape all the way down when pressed hard drop
	bool x = true;
	while (this->canMoveShapeDown(playBoard, x, bombScore))
		this->move(KEEP_DOWN);

	bombHeight = bodyShape[0].getY(bodyShape[0]);
	cleanBomb(); //// need to check it 
	playBoard.updatePlayeBoard(*this);
}


bool Bomb::canMoveShapeRightOrLeft(Board & playBoard, char keyPressed,
	bool & bombWasActivatedRL, int & bombScore)
{// function returns true when the shape can move right or left 
	int x, y, score;
	if (keyPressed == LEFT_KEY)
	{
		x = bodyShape[0].getX(bodyShape[0]);
		y = bodyShape[0].getY(bodyShape[0]);
		if (playBoard.boardMatrix[y - 5][x - 8] != SPACE)//check for left wall!!! _____
		{
			if (playBoard.boardMatrix[y - 5][x - 8] != WALL_SIDE)
			{
				score = updateAfterBombing(playBoard, x, y); // update after the bombing
				bombScore = score * (BOMB_SCORE);
				bombWasActivatedRL = true;
				return false;
			}
			return false;
		}
	}
	if (keyPressed == RIGHT_KEY)
	{
		x = bodyShape[0].getX(bodyShape[0]);
		y = bodyShape[0].getY(bodyShape[0]);
		if (playBoard.boardMatrix[y - 5][x - 6] != SPACE)//check for right wall!!! _____
		{
			if (playBoard.boardMatrix[y - 5][x - 6] != WALL_SIDE)
			{
				score = updateAfterBombing(playBoard, x, y); // update after the bombing
				bombScore = score * (BOMB_SCORE);
				bombWasActivatedRL = true;
				return false;
			}
			return false;
		}
	}
	return true;
}

int Bomb::updateAfterBombing(Board & playBoard, int x1, int y1)
{// this function get the baord the updating the board after the bomb. 
 // the function returns the number of blocks the bomb removed 

	int blockRemoved = 0;
	x1 = x1 - BOARD_X_SET;
	y1 = y1 - BOARD_y_SET;
	//cout << x1 << " " << y1;

	if ((playBoard.boardMatrix[y1][x1] != WALL_DOWN) && (playBoard.boardMatrix[y1][x1] != WALL_SIDE)) // check not to hit the board 
	{
		if (playBoard.boardMatrix[y1][x1] != SPACE) // if the cell is not a blank, so this is a shape. 
			blockRemoved++;  // count the number of blocks 
		playBoard.boardMatrix[y1][x1] = SPACE;  // put space in the cell after bombing 
	}
	//       next all conditions are the same as this, just the x1, y1 are different. 
	if ((playBoard.boardMatrix[y1][x1 + 1] != WALL_DOWN) && (playBoard.boardMatrix[y1][x1 + 1] != WALL_SIDE))
	{
		if (playBoard.boardMatrix[y1][x1 + 1] != SPACE)
			blockRemoved++;
		playBoard.boardMatrix[y1][x1 + 1] = SPACE;
	}

	if ((playBoard.boardMatrix[y1][x1 - 1] != WALL_DOWN) && (playBoard.boardMatrix[y1][x1 - 1] != WALL_SIDE))
	{
		if (playBoard.boardMatrix[y1][x1 - 1] != SPACE)
			blockRemoved++;
		playBoard.boardMatrix[y1][x1 - 1] = SPACE;
	}


	if ((playBoard.boardMatrix[y1 + 1][x1] != WALL_DOWN) && (playBoard.boardMatrix[y1 + 1][x1] != WALL_SIDE))
	{
		if (playBoard.boardMatrix[y1 + 1][x1] != SPACE)
			blockRemoved++;
		playBoard.boardMatrix[y1 + 1][x1] = SPACE;
	}

	if ((playBoard.boardMatrix[y1 + 1][x1 + 1] != WALL_DOWN) && (playBoard.boardMatrix[y1 + 1][x1 + 1] != WALL_SIDE))
	{
		if (playBoard.boardMatrix[y1 + 1][x1 + 1] != SPACE)
			blockRemoved++;
		playBoard.boardMatrix[y1 + 1][x1 + 1] = SPACE;
	}

	if ((playBoard.boardMatrix[y1 + 1][x1 - 1] != WALL_DOWN) && (playBoard.boardMatrix[y1 + 1][x1 - 1] != WALL_SIDE))
	{
		if (playBoard.boardMatrix[y1 + 1][x1 - 1] != SPACE)
			blockRemoved++;
		playBoard.boardMatrix[y1 + 1][x1 - 1] = SPACE;
	}

	if ((playBoard.boardMatrix[y1 - 1][x1 + 1] != WALL_DOWN) && (playBoard.boardMatrix[y1 - 1][x1 + 1] != WALL_SIDE))
	{
		if (playBoard.boardMatrix[y1 - 1][x1 + 1] != SPACE)
			blockRemoved++;
		playBoard.boardMatrix[y1 - 1][x1 + 1] = SPACE;
	}

	if ((playBoard.boardMatrix[y1 - 1][x1] != WALL_DOWN) && (playBoard.boardMatrix[y1 - 1][x1] != WALL_SIDE))
	{
		if (playBoard.boardMatrix[y1 - 1][x1] != SPACE)
			blockRemoved++;
		playBoard.boardMatrix[y1 - 1][x1] = SPACE;
	}

	if ((playBoard.boardMatrix[y1 - 1][x1 - 1] != WALL_DOWN) && (playBoard.boardMatrix[y1 - 1][x1 - 1] != WALL_SIDE))
	{
		if (playBoard.boardMatrix[y1 - 1][x1 - 1] != SPACE)
			blockRemoved++;
		playBoard.boardMatrix[y1 - 1][x1 - 1] = SPACE;
	}

	playBoard.draw();
	return blockRemoved;
}

int Bomb::dropScore(int  hardDrop, int softDrop, int heightBomb)
{// the function returns the score made by hard drop and soft drop

	int   y, distanceFast, distanceSlow, way;
	int score;
	y = heightBomb;
	if (hardDrop == 0) // when drop down was not pressed 
		hardDrop = y;
	way = y - BOARD_y_SET;
	distanceFast = y - hardDrop;
	distanceSlow = way - distanceFast;
	score = 2 * distanceFast + softDrop * 2;
	return score;

}
void Bomb::cleanBomb()
{// This function move the bomb position after bombing 
	for (int i = 0; i < SHAPE_SIZE; i++)
	{
		if (i == 0)
			bodyShape[0].set(START_X, START_Y + 1, SPACE);
		else
			bodyShape[i].set(START_X + i, START_Y + 1, SPACE);
	}

}