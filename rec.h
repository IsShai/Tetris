#pragma once
#include "shape.h"

class Rec :public Rotatable
{
public:
	Rec(Point & _head, const char _c);
	void takeShapeUp() override;
	virtual string type() const override { return "rec"; }

};


