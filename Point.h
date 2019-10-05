#pragma once
#include "gotoxy.h"
class Point {

	int x, y;
	char c;
	int dir_x = 0;
	int dir_y = 1;
public:
	Point() { x = 12; y = 6; c = '$'; }
	Point(int x1, int y1, char c1) {
		set(x1, y1, c1);
	}
	void set(int x1, int y1, char c1) {
		x = x1;
		y = y1;
		c = c1;
	}
	void draw(char c1) {
		gotoxy(x, y);
		cout << c1;
		cout.flush();
	}
	void draw() {
		draw(c);
	}
	void move(char dir);
	//	void changeDir(Directions dir);
	void moveImpl()
	{
		x = (x + dir_x + 80) % 80;
		y = (y + dir_y + 24) % 24;
	}
	//void move(Directions dir)
	//{
	//	changeDir(dir);
	//	moveImpl();
	//}

	int getX(Point p)const {
		return x;
	}

	int getY(Point p) const
	{
		return y;
	}

	char getChar(Point p) const
	{
		return c;
	}
};
