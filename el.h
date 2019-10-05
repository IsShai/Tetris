#pragma once
#include "shape.h"

class El :public Rotatable
{
public:
	El(Point & _head, const char _c);
	void takeShapeUp();
	virtual string type() const override { return "el"; }

};
