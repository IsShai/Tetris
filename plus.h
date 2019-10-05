#pragma once
#include "shape.h"

class Plus :public Rotatable
{
public:

	Plus(Point & _head, const char _c);
	void takeShapeUp() override;
	virtual string type() const override { return "plus"; }
};


