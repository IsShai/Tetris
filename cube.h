#pragma once
#include "shape.h"


class Cube :public Shape
{
public:
	Cube(Point & _head, char _c);
	void takeShapeUp();
	virtual string type() const override { return "cube"; }
};