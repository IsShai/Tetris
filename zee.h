#pragma once
#include "shape.h"

class Zee : public Rotatable
{
public:

	Zee(Point & _head, const char _c);
	void takeShapeUp()override;
	virtual string type() const override { return "zee"; }
};
