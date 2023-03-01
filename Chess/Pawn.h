#pragma once
#include "Figure.h"
class Pawn :public Figure {
public:
	Pawn();
	void firstMove(Figure **enemies, Figure** friends, bool kingCheck, vector<Point> check_list);
	void friendOnCell(Figure** friends, Point a);

	void enPassant(Figure** enemies);
	bool pawnOnCell(Figure** enemies,Point a);
	void texture()override;
	void fillPosibleFields(Figure **enemies,Figure **friends, Board board[][SIZE], bool kingCheck, vector<Point> check_list)override;
    bool move(float x, float y, Figure** friends, Figure** enemies)override;
};//a