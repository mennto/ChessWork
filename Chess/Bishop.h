#pragma once
#include "Figure.h"
//#include "King.h"
class Bishop :public Figure {
public:
	Bishop();
	bool enemyOnCell(Figure** enemies,Point a,Figure*&enemyObj);
	bool friendOnCell(Figure** friends, Point a);
	void texture()override;
	void fillPosibleFields(Figure **enemies,Figure **friends, Board board[][SIZE], bool kingCheck, vector<Point> check_list)override;
};