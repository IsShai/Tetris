#include "board.h"

Board::Board()//Constracton: create a default GAME BOARD
{

	for (size_t i = 0; i < DOWN_RIGHT; i++) {
		for (size_t j = 0; j < TOP_RIGHT; j++) {

			if (i == DOWN_RIGHT - 1) {
				boardMatrix[i][j] = WALL_DOWN;
			}
			else if (j == 0)
			{
				boardMatrix[i][j] = WALL_SIDE;
			}
			else if (j == TOP_RIGHT - 1)
			{
				boardMatrix[i][j] = WALL_SIDE;
			}
			else
				boardMatrix[i][j] = SPACE;
		}
	}
}

void Board::draw()// Printing the board
{

	int Color = 241;
	HANDLE  hConsole;
	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	WORD wOldColorAttrs;
	CONSOLE_SCREEN_BUFFER_INFO csbiInfo;
	/*
	* First save the current color information
	*/
	GetConsoleScreenBufferInfo(hConsole, &csbiInfo);
	wOldColorAttrs = csbiInfo.wAttributes;
	for (size_t i = 0; i < DOWN_RIGHT; i++) {
		gotoxy(BOARD_X_SET, BOARD_y_SET + (i));
		for (size_t j = 0; j < TOP_RIGHT; j++) {
			if ((i == 0 && j == 0) || (i == 0 && j == TOP_RIGHT - 1)) {
				SetConsoleTextAttribute(hConsole, BACKGROUND_RED);
				cout << boardMatrix[i][j];
				SetConsoleTextAttribute(hConsole, wOldColorAttrs);
			}
			else if (boardMatrix[i][j] != SPACE && i > 0) {
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), Color);
				cout << boardMatrix[i][j];
				SetConsoleTextAttribute(hConsole, wOldColorAttrs);
			}
			else
				cout << boardMatrix[i][j];
		}
		cout << endl;
		/*
		* Restore the original colors
		*/
		SetConsoleTextAttribute(hConsole, wOldColorAttrs);
	}

	return;
}

int Board::canRemoveOneLine(Board &playBoard)//Return the number of the full line in the board if full
{
	unsigned int counter;
	for (int i = DOWN_RIGHT - 2; i > 1; i--)
	{
		counter = 0;
		for (size_t j = 1; j < TOP_RIGHT - 1; j++)
		{
			if (playBoard.boardMatrix[i][j] != SPACE)
				counter++;
		}
		if (counter == FULL_RAW)//full of 10 blocks 
			return i;
	}
	return 0;
}
void Board::blinkingLine(Board &playBoard, int numOfLine)//Blinking affect when one line is full
{
	HANDLE  hConsole;
	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	WORD wOldColorAttrs;
	CONSOLE_SCREEN_BUFFER_INFO csbiInfo;
	/*
	* First save the current color information
	*/
	GetConsoleScreenBufferInfo(hConsole, &csbiInfo);
	wOldColorAttrs = csbiInfo.wAttributes;
	//---------------Mark the line bule 3 times... (on and off)-------//
	gotoxy(BOARD_X_SET + 1, BOARD_y_SET + numOfLine);
	for (size_t j = 1; j < TOP_RIGHT - 1; j++)
	{
		SetConsoleTextAttribute(hConsole, BACKGROUND_BLUE);
		cout << playBoard.boardMatrix[numOfLine][j];
	}
	Sleep(500);
	gotoxy(BOARD_X_SET + 1, BOARD_y_SET + +numOfLine);
	for (size_t j = 1; j < TOP_RIGHT - 1; j++)
	{
		SetConsoleTextAttribute(hConsole, wOldColorAttrs);
		cout << playBoard.boardMatrix[numOfLine][j];
	}
	Sleep(500);
	gotoxy(BOARD_X_SET + 1, BOARD_y_SET + numOfLine);
	for (size_t j = 1; j < TOP_RIGHT - 1; j++)
	{
		SetConsoleTextAttribute(hConsole, BACKGROUND_BLUE);
		cout << playBoard.boardMatrix[numOfLine][j];
	}
	Sleep(500);
	gotoxy(BOARD_X_SET + 1, BOARD_y_SET + numOfLine);
	//-------------Clear the line-----------//
	for (size_t j = 1; j < TOP_RIGHT - 1; j++)
	{
		SetConsoleTextAttribute(hConsole, wOldColorAttrs);
		playBoard.boardMatrix[numOfLine][j] = ' ';
		cout << playBoard.boardMatrix[numOfLine][j];
	}
	Sleep(500);
}
int Board::removeLine(Board &playBoard)//Removing lines if full line 
									   //(loop until all the full line removed)
{
	int counter = 0;
	int numOfLine = playBoard.canRemoveOneLine(playBoard);
	while (numOfLine != 0)
	{
		counter++;//lines that removed
		playBoard.blinkingLine(playBoard, numOfLine);
		for (size_t i = numOfLine; i > 1; --i)
		{
			for (size_t j = 1; j < TOP_RIGHT - 1; ++j)
			{
				playBoard.boardMatrix[i][j] = playBoard.boardMatrix[i - 1][j];

			}
		}
		playBoard.draw();
		numOfLine = playBoard.canRemoveOneLine(playBoard);
	}
	return counter;

}

void Board::updatePlayeBoard(Shape & shape)//Updating the board 
										   //after one line deleted...
{
	int x, y;
	char c;
	
	 Point * bodyShape = new Point [4];
	 bodyShape = shape.getBodyshape();
	
	for (size_t i = 0; i < SHAPE_SIZE; i++)
	{
		x = bodyShape[i].getX(bodyShape[i]);
		y = bodyShape[i].getY(bodyShape[i]);
		c = bodyShape[i].getChar(bodyShape[i]);
		boardMatrix[y - 5][x - 7] = c;
	}
	return;
}

void textcolor(unsigned short color) {
	HANDLE hcon = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hcon, color);
}

bool Board::gameOverFunc(Board &playBoard)
{// print the gameOVER 
	for (size_t j = 1; j < TOP_RIGHT - 1; ++j)
	{
		if ((playBoard.boardMatrix[0][j] != SPACE) && (playBoard.boardMatrix[1][j] != SPACE))
		{
			playBoard.printGameOver();
			return true;
		}
	}
	return false;
}

void Board::printGameOver()  // Print the game over helper 
{
	char c = 92; // char for un-printable char. 92 for '\'
	gotoxy(4, 5); cout << "                _    _       ___" << endl;
	gotoxy(4, 6); cout << "__ __ __ __    / _  /_) )\/) )_    __ __ __ __ " << endl;
	gotoxy(4, 7); cout << "-- -- -- --   (__/ / / (  ( (__    -- -- -- --" << endl;
	gotoxy(4, 8); cout << "             _       ___ __             " << endl;
	gotoxy(4, 9); cout << "__ __ __    / ) " << c << "  / )_  )_)   __ __ __ " << endl;
	gotoxy(4, 10); cout << "-- -- --   (_/   " << c << "/ (__ / " << c << "    -- -- --" << endl;

}


bool Board::canNotRotate(Shape & shape, Board &playBoard)
{// function returns true when the shape can do a rotation in thar spot on the board 
	int x, y;
	char ch;
	Point * bodyShape = new Point[4];
	
	//Shape* tmpShape = &shape;
	Rotatable* rotatableTempShape = dynamic_cast<Rotatable*>(&shape);

	if (rotatableTempShape) {
		rotatableTempShape->rotate();
		bodyShape = shape.getBodyshape();
		for (size_t i = 0; i < SHAPE_SIZE; i++)
		{
			x = bodyShape[i].getX(bodyShape[i]);
			y = bodyShape[i].getY(bodyShape[i]);
			y++;
			ch = playBoard.boardMatrix[y - 5][x - 7];
			if (isOneOfTheChar(ch) || (y == START_Y))
			{
				for (int i = 0; i<3; i++)
					rotatableTempShape->rotate();
				return false;

			}
		}
	}
	for (int i = 0; i<3; i++)
		rotatableTempShape->rotate();
	return true;
}

bool Board::isOneOfTheChar(char c) // the function returns true when the char is one of the char played on this game 
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