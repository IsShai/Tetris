#include "plus.h"

Plus::Plus(Point & _head, const char _c) :Rotatable(_head, _c)
{
	int x = _head.getX(_head);
	int y = _head.getY(_head);
	char c1 = _c;
	bodyShape[0].set(x, y, _c);
	bodyShape[1].set(x + 1, y, c1);
	bodyShape[2].set(x + 1, y - 1, c1);
	bodyShape[3].set(x + 2, y, c1);
}

void Plus::takeShapeUp()
{
	bodyShape[0].set(START_X + 0, START_Y + 1, PLUS_CHAR);
	bodyShape[1].set(START_X + 1, START_Y + 1, PLUS_CHAR);
	bodyShape[2].set(START_X + 1, START_Y, PLUS_CHAR);
	bodyShape[3].set(START_X + 2, START_Y + 1, PLUS_CHAR);
}

