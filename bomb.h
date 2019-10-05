#pragma once

#include "shape.h"

class Bomb : public Shape
{
public:
	Bomb(Point & _head, const char _c);
	void takeShapeUp() override;
	virtual bool canMoveShapeDown(Board & playBoard, bool & bombWasActivated, int & bombScore);
	virtual void moveAllWayDown(Board & playBoard, int & bombScore, int & bombHeight);
	virtual bool canMoveShapeRightOrLeft(Board & playBoard, char keyPressed,
		bool & bombWasActivatedRL, int & bombScore) override;
	int updateAfterBombing(Board & playBoard, int x1, int y1);
	virtual int dropScore(int  hardDrop, int softDrop, int heightBomb);
	void cleanBomb();
	virtual string type() const override { return "bomb"; }

};