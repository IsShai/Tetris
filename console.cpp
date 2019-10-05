#include "gotoxy.h"
#include"console.h"


void slow_print(const string&, unsigned int);
void slow_print(const string& message, unsigned int millis_per_char)
{// slow print function
 // Range loops are "for each" constructs; here: for each character in the string
	for (const char c : message)
	{
		// flush is used to make sure the buffer is emptied to the terminal immediately
		cout << c << flush;

		// Ask the thread to sleep for at least n millis.
		sleep_for(milliseconds(millis_per_char));
	}
}
void Console::createManu()
{// this function creates thr manu
	for (size_t i = 0; i < MANU_FRAME_DOWN_RIGHT; i++)
	{
		for (size_t j = 0; j < MANU_FRAME_TOP_RIGHT; j++)
		{
			if ((i == 0 || i == MANU_FRAME_DOWN_RIGHT - 1) && j != 0 && j < MANU_FRAME_TOP_RIGHT - 1)
				manuMatrixFrame[i][j] = '-';
			else	if (j == 0 || j == MANU_FRAME_TOP_RIGHT - 1)
				manuMatrixFrame[i][j] = '|';
			else
				manuMatrixFrame[i][j] = ' ';

		}
	}
	printManuFrame();
	PlaySound("GameStart_Sound.wav", NULL, SND_FILENAME | SND_ASYNC);
	printButtons();
	//printDetailsFrame();
	mciSendString("open Mega_Hyper_Ultrastorm.mp3", NULL, 0, NULL);
	manuButtonsAction();
}

void Console::printFromTxtOpenGame()
{
	string line;
	ifstream inFile;
	inFile.open("tetris_txt_open_game.txt");
	if (inFile.is_open())
	{
		while (getline(inFile, line))
		{
			cout << line << '\n';
		}
		inFile.close();
	}

	else cout << "Unable to open file";
	Sleep(3000);
	system("CLS");
	return;
}
void Console::printFromTxtEndGame()
{
	string line;
	ifstream inFile;
	inFile.open("good_bye_txt.txt");
	if (inFile.is_open())
	{
		while (getline(inFile, line))
		{
			cout << line << '\n';
		}
		inFile.close();
	}

	else cout << "Unable to open file";
	Sleep(3000);
	system("CLS");
	return;

}
void Console::manuButtonsAction()
{// the function print the manu buttons
	char pressedBotton;
	char lastPressedInGame = 0;
	bool flag = true;
	while (flag)
	{
		if (lastPressedInGame == EXIT) {
			mciSendString("close Mega_Hyper_Ultrastorm.mp3 ", NULL, 0, NULL);
			break;
		}
		pressedBotton = _getch();
		if (pressedBotton == EXIT) {
			mciSendString("close Mega_Hyper_Ultrastorm.mp3 ", NULL, 0, NULL);
			flag = false;
		}
		if (pressedBotton == START_GAME) {

			cleanBoardAgain();
			printDetailsFrame();
			printKeyInstruction();
			mciSendString("play Mega_Hyper_Ultrastorm.mp3 repeat", NULL, 0, NULL);
			run(lastPressedInGame);
		}
	}

}
void Console::cleanBoardAgain()
{// clean the board
	gotoxy(4, 5); cout << "                                    " << endl;
	gotoxy(4, 6); cout << "                                              " << endl;
	gotoxy(4, 7); cout << "                                              " << endl;
	gotoxy(4, 8); cout << "                                                " << endl;
	gotoxy(4, 9); cout << "                                                          " << endl;
	gotoxy(4, 10); cout << "                                                              " << endl;
	gotoxy(40, 5); cout << "                                                                ";
	gotoxy(40, 6); cout << "                                                             " << endl;
}

void Console::printButtons()
{// print buttons printing 
	HANDLE  hConsole;
	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	WORD wOldColorAttrs;
	CONSOLE_SCREEN_BUFFER_INFO csbiInfo;
	/*
	* First save the current color information
	*/
	GetConsoleScreenBufferInfo(hConsole, &csbiInfo);
	wOldColorAttrs = csbiInfo.wAttributes;
	SetConsoleTextAttribute(hConsole, 10);
	const  string start = "(1) START NEW GAME";
	const  string pouse = "(2) PAUSE/RESUME ";
	const  string increase = "(3) INCREASE SPEED ";
	const  string decrease = "(4) DECREASE SPEED ";
	const string esc = "(ESC) BACK TO MANU";
	const string exitt = "(9) EXIT ";
	gotoxy(3, 1); slow_print(start, 30);
	gotoxy(24, 1); slow_print(pouse, 30);
	gotoxy(3, 3);  slow_print(increase, 30);
	gotoxy(24, 3); slow_print(decrease, 30);
	gotoxy(44, 1); slow_print(esc, 30);
	gotoxy(44, 3); slow_print(exitt, 30);

	SetConsoleTextAttribute(hConsole, wOldColorAttrs);
}
void Console::printManuFrame()
{// printing the frame of the manu
	for (size_t i = 0; i < MANU_FRAME_DOWN_RIGHT; i++)
	{
		for (size_t j = 0; j < MANU_FRAME_TOP_RIGHT; j++)
		{
			cout << manuMatrixFrame[i][j];
		}
		cout << endl;
	}
}
int Console::speedFunc(char keyPressed, int speed)
{// the function control on the speed by the user input 

	if (speed == MED_SPEED)
	{
		if (keyPressed == INCREASE_SPEED)
			return  HIGH_SPEED;
		if (keyPressed == DECREASE_SPEED)
			return LOW_SPEED;
	}
	if (speed == LOW_SPEED)
		if (keyPressed == INCREASE_SPEED)
			return MED_SPEED;
	if (speed == HIGH_SPEED)
		if (keyPressed == DECREASE_SPEED)
			return MED_SPEED;
	return speed;
}
void Console::printDetails(int score, int speedLevel, int brickCount, int nextShapeNumInTheArry)
{// printing the chaing values of the manu

	gotoxy(33, 10); cout << "        ";
	gotoxy(34, 13); cout << "         ";
	gotoxy(35, 17); cout << "          ";
	gotoxy(28, 20); cout << "          ";
	gotoxy(28, 21); cout << "          ";
	gotoxy(35, 10); cout << score;

	if (speedLevel == LOW_SPEED)
	{
		gotoxy(35, 13);  cout << "SLOW";
	}
	if (speedLevel == MED_SPEED)
	{
		gotoxy(35, 13); cout << "MEDIUM";
	}
	if (speedLevel == HIGH_SPEED)
	{
		gotoxy(35, 13); cout << "HIGH";
	}
	gotoxy(40, 17); cout << brickCount;
	printNextShape(nextShapeNumInTheArry);

}

void Console::printDetailsFrame()
{// print part of the manu
	gotoxy(25, 9); cout << " ____________________";
	gotoxy(25, 10); cout << "| SCORE:             |";
	gotoxy(25, 11); cout << "|                    |";
	gotoxy(25, 12); cout << "|                    |";
	gotoxy(25, 13); cout << "| SPEED:             |";
	gotoxy(25, 14); cout << "|                    |";
	gotoxy(25, 15); cout << "|                    |";
	gotoxy(25, 16); cout << "| SHAPES DROPPED:    |";
	gotoxy(25, 17); cout << "|                    |";
	gotoxy(25, 18); cout << "|                    |";
	gotoxy(25, 19); cout << "| NEXT SHAPE:        |";
	gotoxy(25, 20); cout << "|                    |";
	gotoxy(25, 21); cout << "|                    |";
	gotoxy(25, 22); cout << "|                    |";
	gotoxy(25, 23); cout << "|                    |";
	gotoxy(25, 24); cout << "|____________________|";

}


void Console::printKeyInstruction()
{// print the instuction
	gotoxy(45, 14); cout << " ___________________";
	gotoxy(45, 15); cout << "| LEFT        a     |";
	gotoxy(45, 16); cout << "| RIGHT       d     |";
	gotoxy(45, 17); cout << "| ROTATE      w     |";
	gotoxy(45, 18); cout << "| STOP JOKER  s     |";
	gotoxy(45, 19); cout << "| SOFT DROP   x     |";
	gotoxy(45, 20); cout << "| HARD DROP   space |";
	gotoxy(45, 21); cout << "|___________________|";


}

void Console::printNextShape(int nextRndNumber)
{// printing the next shape on the menu
 //gotoxy(40, 18); cout << "    ";
	gotoxy(32, 20); cout << "    ";
	gotoxy(32, 21); cout << "    ";
	gotoxy(32, 22); cout << "    ";
	gotoxy(32, 23); cout << "    ";
	Point p(32, 21, 'X');
	switch (nextRndNumber)
	{
	case(CUBE_INX): {
		Cube cube(p, CUBE_CHAR); cube.drowShapes();
		break; }
	case(EL_INX): {
		El el(p, EL_CHAR); el.drowShapes();
		break; }
	case(PLUS_INX): {
		p.set(32, 22, 'x');
		Plus plus(p, PLUS_CHAR); plus.drowShapes();
		break; }
	case(ZEE_INX): {
		Zee zee(p, ZEE_CHAR); zee.drowShapes();
		break; }
	case(REC_INX): {
		Rec rec(p, REC_CHAR); rec.drowShapes();
		break; }
	case(JOKER_INX): {
		Joker joker(p, JOKER_CHAR); joker.drowShapes();
		break; }
	case(BOMB_INX): {
		Bomb bomb(p, BOMB_CHAR); bomb.drowShapes();
		break; }
	}
	return;
}
void Console::pauseFunc(char keyPressed)
{ // pause function 
	char c;
	bool flag = true;
	if (keyPressed == PAUSE_RESUME)
	{
		PlaySound("sfx_sounds_pause5_out.wav", NULL, SND_FILENAME | SND_ASYNC);
		while (flag)
		{
			mciSendString("pause Mega_Hyper_Ultrastorm.mp3 ", NULL, 0, NULL);

			gotoxy(57, 6); cout << "PAUSE!!";
			gotoxy(45, 7); cout << "--->>> PRESS 2 TO RESUME <<<---";
			c = _getch();
			if (c == PAUSE_RESUME) {
				mciSendString("play Mega_Hyper_Ultrastorm.mp3 repeat", NULL, 0, NULL);

				flag = false;
			}
		}
	}
	gotoxy(57, 6); cout << "            ";
	gotoxy(45, 7); cout << "                                   ";

	return;
}

int Console::lotteryShape()
{ // the func returns a random number 
	int rnd = rand() % 22;

	if (rnd >= CUBE_MIN && rnd <= CUBE_MAX)
	{
		return CUBE_INX;//FOR CUBE
	}
	if (rnd >= EL_MIN && rnd <= EL_MAX)
	{
		return EL_INX;//FOR EL
	}
	if (rnd >= PLUS_MIN && rnd <= PLUS_MAX)
	{
		return PLUS_INX;//FOR PLUS
	}
	if (rnd >= ZEE_MIN && rnd <= ZEE_MAX)
	{
		return ZEE_INX;//FOR ZEE
	}
	if (rnd >= REC_MIN && rnd <= REC_MAX)
	{
		return REC_INX;//FOR REC
	}
	if (rnd == JOKER_MIN_MAX) return JOKER_INX;//FOR JOKER
	return BOMB_INX;//FOR BOMB

}


void Console::run(char& lastPressed)
{// this function runs the game 
	Board gameBoard;//The constractor create the defult boardGame
	Shape* shape[7];
	Point p;
	//p.set(12, 6, 'C');
	Cube cube(p, CUBE_CHAR);
	shape[0] = &cube;
	El el(p, EL_CHAR);
	shape[1] = &el;
	Plus plus(p, PLUS_CHAR);
	shape[2] = &plus;
	Zee zee(p, ZEE_CHAR);
	shape[3] = &zee;
	Rec rec(p, REC_CHAR);
	shape[4] = &rec;
	Joker joker(p, JOKER_CHAR);
	shape[5] = &joker;
	Bomb bomb(p, BOMB_CHAR);
	shape[6] = &bomb;
	int  hightOfDropDown = 0, removeLineCounter = 0, heightOfBombing;
	int rnd = 0, rndNext = 0;  // 1 for REC  , 0 for Cube 
	int countOfBricks = 0, softDownCounter = 0, speed = MED_SPEED;
	bool flag = true, jokerAlreadyStopped = false, bombWasActivatedDown = false, bombWasActivatedRL = false, rotateDone;
	int  bombScore = 0, totalScore = 0;
	char dummy, keyPressed;
	Point * bodyShape = new Point[4];


	gameBoard.draw();//Printing the board in the correct location
	rnd = lotteryShape();
	//rnd = 5;
	while (true) // might need to change it  
	{// this loop for every shape created 
	 //cout << rnd;
		rndNext = lotteryShape();
		bombScore = 0;
		softDownCounter = 0;
		removeLineCounter = 0;
		jokerAlreadyStopped = false;
		bombWasActivatedDown = false;
		flag = true;
		shape[rnd]->takeShapeUp(); // taking the shape  up again.
		while (flag)
		{// this loop is for each shape till it landed 
			rotateDone = false;
			bombWasActivatedRL = false;
			hightOfDropDown = 0;
			keyPressed = KEEP_DOWN;
			if (_kbhit()) // when there is any key in the buffer 
			{
				keyPressed = _getch(); // save the char that was pressed in keyPressed 
				if (keyPressed == ESC) // when pressed ESC - exit the game 
				{
					caseEsc(flag);
					break;
				}
				if (keyPressed == EXIT) {
					lastPressed = EXIT;
					break;
				}
				pauseFunc(keyPressed);
				speed = speedFunc(keyPressed, speed);
				if ((keyPressed == JOKER_STOP) && (shape[rnd]->type() == "joker")) // when we want to stop the joker 
				{
					flag = false;
					gameBoard.updatePlayeBoard(*shape[rnd]);
				}
				if (keyPressed == SOFT_DROP)
				{
					if ((!bombWasActivatedDown) &&
						(shape[rnd]->canMoveShapeDown(gameBoard, bombWasActivatedDown, bombScore)))

					{
						shape[rnd]->move(KEEP_DOWN);
						softDownCounter++;
						if (bombWasActivatedDown && (shape[rnd]->type() == "bomb"))  // the bomb was activated in this loop
						{
							Bomb* tempBomb = dynamic_cast<Bomb*>(shape[rnd]);
							flag = false;
							bodyShape = shape[rnd]->getBodyshape();
							heightOfBombing = bodyShape[0].getY(bodyShape[0]);
							tempBomb->cleanBomb();
						}
					}
				}
			}

			else
				keyPressed = KEEP_DOWN;
			Sleep(double(speed*1.5));

			//Sleep(speed);
			if ((!jokerAlreadyStopped) && (!shape[rnd]->canMoveShapeDown(gameBoard, bombWasActivatedDown, bombScore)))
				// check if the shape can move down.
			{
				flag = false;
				if (shape[rnd]->type() == "bomb") // for not printing the bomb after bombing 
				{
					Bomb* tempBomb = dynamic_cast<Bomb*>(shape[rnd]);
					bodyShape = shape[rnd]->getBodyshape();
					heightOfBombing = bodyShape[0].getY(bodyShape[0]);
					tempBomb->cleanBomb();
				}
				//if (rnd != BOMB) // NOT draw the bomb after bombing! 
				gameBoard.updatePlayeBoard(*shape[rnd]); // update the joker when s was not pressed 
			}

			if (!shape[rnd]->canMoveShapeRightOrLeft(gameBoard, keyPressed, bombWasActivatedRL, bombScore))
			{
				if ((bombWasActivatedRL) && (shape[rnd]->type() == "bomb"))
				{
					flag = false;
					// for not printing the bomb after bombing 
					bodyShape = shape[rnd]->getBodyshape();
					heightOfBombing = bodyShape[0].getY(bodyShape[0]);
					Bomb* tempBomb = dynamic_cast<Bomb*>(shape[rnd]);
					tempBomb->cleanBomb();
				}
				else keyPressed = KEEP_DOWN;
			}
			if (keyPressed == ROTATE) // when pressed rotate 
				caseRotate(keyPressed, gameBoard, *shape[rnd], rotateDone);
			if (keyPressed == HARD_DROP)
			{
				hightOfDropDown = shape[rnd]->findLowestY();
				shape[rnd]->moveAllWayDown(gameBoard, bombScore, heightOfBombing);
				break;
			}

			else
			{
				if (keyPressed != ROTATE  && flag && (!rotateDone)) // flag is here for not going down below the board level
					shape[rnd]->move(keyPressed); // continue going right/left
			}

			printDetails(totalScore, speed, countOfBricks, rndNext);
		}
		if (keyPressed == KEYS::ESC)
			break;
		if (keyPressed == EXIT)
			break;
		gameBoard.draw();//Print the borad again with the new shape

						 //Sleep(50);
		totalScore = totalScore +
			shape[rnd]->calsScore(gameBoard, hightOfDropDown, softDownCounter, heightOfBombing, bombScore);

		if (gameBoard.gameOverFunc(gameBoard))
		{
			mciSendString("stop Mega_Hyper_Ultrastorm.mp3 ", NULL, 0, NULL);
			mciSendString("close Mega_Hyper_Ultrastorm.mp3 ", NULL, 0, NULL);
			PlaySound("game_over_sound.wav", NULL, SND_FILENAME | SND_ASYNC);
			break;
		}
		while (_kbhit()) // clean the buffer for next interrtion
			dummy = _getch();
		countOfBricks++;
		rnd = rndNext;
		//rnd++;
		//rnd = rnd % 7;
	}
	return;
}

void Console::caseRotate(char & keyPressed, Board & gameBoard, Shape & shape, bool & rotateDone)
{// case when is rotate 
 //rotatble will be non-NULL only if dynamic_cast succeeds...
	Rotatable* rotatable = dynamic_cast<Rotatable*>(&shape);
	if (rotatable)
	{
		Point * bodyShape = new Point[4];
		bodyShape = shape.getBodyshape();
		if (gameBoard.canNotRotate(shape, gameBoard))
		{
			for (size_t i = 0; i < SHAPE_SIZE; i++)
			{
				bodyShape[i].draw(SPACE);
			}
			//shape.move(keyPressed); // send to rotate only shpes that can rotate 
			rotatable->rotate();
			for (size_t i = 0; i < SHAPE_SIZE; i++)
			{
				bodyShape[i].draw();
			}
			//keyPressed = KEEP_DOWN;
			shape.move(KEEP_DOWN);
			rotateDone = true;
		}
		else
			shape.move(KEEP_DOWN);
	}
	else
		shape.move(KEEP_DOWN);

}

void Console::caseEsc(bool & flag)
{// case when esc was pressed 
	mciSendString("stop Mega_Hyper_Ultrastorm.mp3 ", NULL, 0, NULL);
	mciSendString("close Mega_Hyper_Ultrastorm.mp3 ", NULL, 0, NULL);
	gotoxy(40, 5); cout << "you prssed ESC, the game is over...";
	gotoxy(40, 6); cout << "To start new game, please press(1)" << endl;
	flag = false;
}

