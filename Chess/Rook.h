#pragma once
#include "Figure.h"
class Rook :public Figure {
public:
	Rook();
	bool enemyOnCell(Figure** enemies, Point a, Figure*& enemyObj);
	bool friendOnCell(Figure** friends, Point a);
	Rook* getPointer();
	void texture()override;
	void fillPosibleFields(Figure** enemies, Figure** friends, Board board[][SIZE], bool kingCheck, vector<Point> check_list)override;
};