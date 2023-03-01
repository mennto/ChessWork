#pragma once
#include "Figure.h"
//#include "King.h"
class Queen :public Figure {
protected:
	vector <Point> helper;
public:
	Queen();
	void fillHelper();
	void popHelper();
	int  findKing();
	bool enemyOnCell(Figure** enemies, Point a,Figure *&enemyObj);
	bool friendOnCell(Figure** friends, Point a);
	void texture()override;
	void fillPosibleFields(Figure** enemies, Figure** friends, Board board[][SIZE], bool kingCheck, vector<Point> check_list)override;
};//a