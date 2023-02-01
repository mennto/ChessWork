#pragma once
#include "Figure.h"
class King :public Figure {
protected:
	vector <Point> helper;
	bool check;
	bool leftCastling;
	bool rightCastling;
public:
	King();
	bool getCheck();

	bool isMate(Figure** friends);
	bool enemyFields(Figure *a,Point j);
	bool isCheck(Figure **enemies,vector<Point> &check_list);

	void fillHelper();

	bool move(float x, float y, Figure** friends, Figure** enemies)override;
	bool defCell(Figure** enemies, Point a);
	bool friendOnCell(Figure** friends, Point a);
	void texture()override;
	bool enemyOnCell(Figure** enemies, Point a);
	void castling(Figure** friends, Figure** enemies, Board board[][SIZE]);
	void fillPosibleFields(Figure** enemies, Figure** friends, Board board[][SIZE], bool kingCheck, vector<Point> check_list)override;
};