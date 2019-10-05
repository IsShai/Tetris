#pragma once
#include <math.h>
#include <windows.h>
#include <conio.h>
#include <stdio.h> 
#include <stdlib.h>
#include <iostream>
#include <thread>
#include <chrono>
#include<mmstream.h>
#include <fstream> 
#include <string>
#pragma comment(lib,"Winmm.lib")

using std::this_thread::sleep_for;
using std::chrono::milliseconds;
using namespace std;
#define BOARD_X_SET 7
#define BOARD_y_SET 5
#define SHAPE_SIZE  4
#define FULL_RAW 10
//#define _WIN32_WINNT 0x0500


enum START_POINT { START_X = 10, START_Y = 5 };
enum SHAPE_TYPE { CUBE_INX = 0, EL_INX = 1, PLUS_INX = 2, ZEE_INX = 3, REC_INX = 4, JOKER_INX = 5, BOMB_INX = 6 };
enum SCORES {
	SINGLE_LINE_CLR = 100, DOUBLE_LINE_CLR = 300, TRIPLE_LINE_CLR = 500, TETRLIS_CLR = 800, SINGLE_LINE_CLR_JOKER = 50,
	BOMB_SCORE = -50
};
enum Directions { LEFT, RIGHT, DOWN, BOMB };
enum KEYS {
	RIGHT_KEY = 100, LEFT_KEY = 97, ROTATE = 119, JOKER_STOP = 115, ESC = 27, HARD_DROP = 32, SOFT_DROP = 120, KEEP_DOWN = 0
	, SPACE = 32
};
enum SHAPES_CHARS {
	CUBE_CHAR = 36, REC_CHAR = 35, BOMB_CHAR = 64, JOKER_CHAR = 74, WALL_SIDE = 33,
	WALL_DOWN = 42, NUM_OF_CHARS = 9, ZEE_CHAR = 90, PLUS_CHAR = 80, EL_CHAR = 76
};
enum SHAPE_RND_INX_IN_THE_ARRY {
	CUBE_MIN = 0, CUBE_MAX = 3, EL_MIN = 4, EL_MAX = 7, PLUS_MIN = 8, PLUS_MAX = 11, ZEE_MIN = 12, ZEE_MAX = 15
	, REC_MIN = 16, REC_MAX = 19, JOKER_MIN_MAX = 20, BOMB_MIN_MAX = 21
};
void gotoxy(int column, int line);
void ShowConsoleCursor();
void makeCmdScreenBigEnough();