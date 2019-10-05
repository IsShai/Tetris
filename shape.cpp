#include "shape.h"
#include "board.h"


void Shape::move(char keyPressed)
{// move the shape by the key that was pressed 

	size_t i;

	for (i = 0; i < SHAPE_SIZE; i++)
	{
		bodyShape[i].draw(SPACE);
	}
	/*if (keyPressed == ROTATE)
	rotate();*/
	for (i = 0; i < 4; i++)
	{
		if (bodyShape[i].getChar(bodyShape[i]) != SPACE)//Condition if the shape is BOMG or JOKER!
		{
			bodyShape[i].move(keyPressed);
			bodyShape[i].draw();
		}
	}

}

bool Shape::canMoveShapeDown(Board & playBoard, bool & bombWasActivated, int & bombScore)
{
	//----------Boolean function to limit the bloacks from left, right and down
	{
		int x, y, score;
		for (size_t i = 0; i < SHAPE_SIZE; i++)
		{
			if (bodyShape[i].getChar(bodyShape[i]) != SPACE)//Condition if the shape is BOMG or JOKER!
			{
				x = bodyShape[i].getX(bodyShape[i]);
				y = bodyShape[i].getY(bodyShape[i]);
				if (playBoard.boardMatrix[y - 4][x - 7] != SPACE)//check for bottom wall!!! _____
				{
					playBoard.updatePlayeBoard(*this);
					return false;
				}
			}
		}
	}
	return true;
}

void Shape::moveAllWayDown(Board & playBoard, int & bombScore, int & bombHeight)
{// move the shape all the way down when pressed hard drop
	bool x = true;
	while (canMoveShapeDown(playBoard, x, bombScore))
		move(KEEP_DOWN);
	playBoard.updatePlayeBoard(*this);
}

bool Shape::canMoveShapeRightOrLeft(Board & playBoard, char keyPressed,
	bool & bombWasActivatedRL, int & bombScore)
{// check if the shape can move right or left 
	int x, y, score;
	if (keyPressed == LEFT_KEY)
	{
		for (size_t i = 0; i < SHAPE_SIZE; i++)
		{
			if (bodyShape[i].getChar(bodyShape[i]) != SPACE)//Condition if the shape is BOMB or JOKER!
			{
				x = bodyShape[i].getX(bodyShape[i]);
				y = bodyShape[i].getY(bodyShape[i]);
				if (playBoard.boardMatrix[y - 5][x - 8] != SPACE)//check for left wall!!! _____
					return false;
			}
		}
	}
	if (keyPressed == RIGHT_KEY)
	{
		for (size_t i = 0; i < SHAPE_SIZE; i++)
		{
			if (bodyShape[i].getChar(bodyShape[i]) != SPACE)//Condition if the shape is BOMG or JOKER!
			{
				x = bodyShape[i].getX(bodyShape[i]);
				y = bodyShape[i].getY(bodyShape[i]);
				if (playBoard.boardMatrix[y - 5][x - 6] != SPACE)//check for right wall!!! _____
					return false;
			}
		}
	}
	return true;
}


int Shape::findLowestY()
{// the function finding the lowest y in the shape 

	int a, b, c, d;
	int max;
	a = bodyShape[0].getY(bodyShape[0]);
	b = bodyShape[1].getY(bodyShape[1]);
	c = bodyShape[2].getY(bodyShape[2]);
	d = bodyShape[3].getY(bodyShape[3]);
	max = a;

	if (b > max)
		max = b;
	if (c > max)
		max = c;
	if (d > max)
		max = d;
	return max;
}
int Shape::dropScore(int  hardDrop, int softDrop, int heightBomb)
{// the function returns the score made by hard drop and soft drop

	int   y, distanceFast, distanceSlow, way;
	int score;
	y = findLowestY(); // need to put the min 
	if (hardDrop == 0) // when drop down was not pressed 
		hardDrop = y;
	way = y - BOARD_y_SET;
	distanceFast = y - hardDrop;
	distanceSlow = way - distanceFast;
	score = 2 * distanceFast + softDrop * 2;
	return score;
}

int Shape::calsScore(Board & gameBoard, int hightOfDropDown, int softDownCounter,
	int heightOfBombing, int bombScore)
{// the function calc the total score 
	int removeLineCounter, scoreLine = 0, scoreDrop, totalScore;
	removeLineCounter = gameBoard.removeLine(gameBoard);//Remove lines if full and returns the number of the full lines	
	if (removeLineCounter == 1)
		scoreLine = SINGLE_LINE_CLR;
	if (removeLineCounter == 2)
		scoreLine = DOUBLE_LINE_CLR;
	if (removeLineCounter == 3)
		scoreLine = TRIPLE_LINE_CLR;
	if (removeLineCounter == 4)
		scoreLine = TETRLIS_CLR;


	scoreDrop = dropScore(hightOfDropDown, softDownCounter, heightOfBombing);
	totalScore = scoreDrop + scoreLine + bombScore;  // sum of all score! 
	return totalScore;
}

void Shape::rotate()
{// rotate function

	int x, y;
	int rX, rY, tmp;
	int pivX, pivY;
	pivX = bodyShape[2].getX(bodyShape[2]);
	pivY = bodyShape[2].getY(bodyShape[2]);
	char shapeChar = bodyShape[0].getChar(bodyShape[0]);
	for (size_t i = 0; i < SHAPE_SIZE; ++i)
	{
		char shapeChar = bodyShape[i].getChar(bodyShape[i]);
		x = bodyShape[i].getX(bodyShape[i]);
		y = bodyShape[i].getY(bodyShape[i]);
		rX = x - pivX;
		rY = y - pivY;
		tmp = rX;
		rX = -rY + pivX;
		rY = tmp + pivY;
		bodyShape[i].set(rX, rY, shapeChar);
	}

}
bool Shape::isOneOfTheChar(char c) // the function returns true when the char is one of the char played on this game 
{
	char arr[NUM_OF_CHARS] = { CUBE_CHAR, JOKER_CHAR, BOMB_CHAR , REC_CHAR, WALL_DOWN, WALL_SIDE, EL_CHAR
		, PLUS_CHAR, ZEE_CHAR };
	for (int i = 0; i < NUM_OF_CHARS; i++)
	{
		if (c == arr[i])
			return true;

	}
	return false;
}

void Shape::drowShapes()
{// draw the shape // for the next shape function

	for (size_t i = 0; i < 4; i++)
	{
		if (bodyShape[i].getChar(bodyShape[i]) != ' ')//Condition if the shape is BOMG or JOKER!
		{
			bodyShape[i].draw();
		}
	}
}


void Rotatable::rotate()
{
	int x, y;
	int rX, rY, tmp;
	int pivX, pivY;
	pivX = bodyShape[2].getX(bodyShape[2]);
	pivY = bodyShape[2].getY(bodyShape[2]);
	char shapeChar = bodyShape[0].getChar(bodyShape[0]);
	for (size_t i = 0; i < SHAPE_SIZE; ++i)
	{
		char shapeChar = bodyShape[i].getChar(bodyShape[i]);
		x = bodyShape[i].getX(bodyShape[i]);
		y = bodyShape[i].getY(bodyShape[i]);
		rX = x - pivX;
		rY = y - pivY;
		tmp = rX;
		rX = -rY + pivX;
		rY = tmp + pivY;
		bodyShape[i].set(rX, rY, shapeChar);
	}
}
