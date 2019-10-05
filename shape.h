#pragma once

#include "Point.h"

class Board;
class Shape
{
protected:
	Point bodyShape[SHAPE_SIZE];
	Point head;
	const char c;

public:
	//Point bodyShape[SHAPE_SIZE];
	//Shape(Point& _head, const char _c) : head(_head), c(_c) {};
	Point* getBodyshape() { return bodyShape; }
	Shape(Point& _head, const char _c) : head(_head), c(_c) {};
	void move(char keyPressed);
	virtual void takeShapeUp() {};
	virtual bool canMoveShapeDown(Board & playBoard, bool & bombWasActivated, int & bombScore);
	virtual void moveAllWayDown(Board & playBoard, int & bombScore, int & bombHeight);
	virtual bool canMoveShapeRightOrLeft(Board & playBoard, char keyPressed,
		bool & bombWasActivatedRL, int & bombScore);
	int findLowestY();
	virtual int dropScore(int  hardDrop, int softDrop, int heightBomb);
	virtual int calsScore(Board & gameBoard, int hightOfDropDown, int softDownCounter,
		int heightOfBombing, int bombScore);
	virtual void rotate();
	bool isOneOfTheChar(char c); // the function returns true when the char is one of the char played on this game 
	void drowShapes();
	virtual string type() const { return "shape"; }
};

class Rotatable : public Shape
{
public:
	Rotatable(Point& _head, const char _c) :Shape(_head, _c) {};
	void rotate();
};

