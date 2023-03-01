#pragma once
#include "Point.h"
class Board {
	Point posithion;
	bool defByWhite;
	bool defByBlack;
public:
	Board();
	float getX();
	float getY();
	bool getDefByWhite();
	bool getDefByBlack();
	
	void setX(float x);
	void setY(float y);
	void setPosithion(Point a);
	void setDefByWhite(bool a);
	void setDefByBlack(bool a);
};