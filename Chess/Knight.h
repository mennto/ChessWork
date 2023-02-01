#pragma once
#include "Figure.h"
class Knight :public Figure {
protected:
	vector <Point> helper;
public:
	Knight();
	void fillHelper();
	bool enemyOnCell(Figure** enemies, Point a);
	bool friendOnCell(Figure** friends, Point a);
	void texture()override;
	void fillPosibleFields(Figure** enemies, Figure** friends, Board board[][SIZE], bool kingCheck, vector<Point> check_list)override;
}; 