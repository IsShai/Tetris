#include "Point.h"

void Point::move(char dir)
{// move point , down/right/left
	switch (dir) {
	case RIGHT_KEY:
		dir_x = 1;
		dir_y = 0;
		break;
	case KEEP_DOWN:
		dir_x = 0;
		dir_y = 1;
		break;
	case LEFT_KEY:
		dir_x = -1;
		dir_y = 0;
		break;
	}
	x += dir_x;
	y += dir_y;  // update the cord of the points 

}
