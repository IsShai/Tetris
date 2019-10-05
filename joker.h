#pragma once

#include "shape.h"

class Joker : public Shape
{
public:
	Joker(Point & _head, const char _c);
	void takeShapeUp();
	virtual bool canMoveShapeDown(Board & playBoard, bool & bombWasActivated, int & bombScore);
	virtual int calsScore(Board & gameBoard, int hightOfDropDown, int softDownCounter,
		int heightOfBombing, int bombScore);
	virtual string type() const override { return "joker"; }
};