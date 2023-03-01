#include "Board.h"
//a
Board::Board(){
	defByWhite = false;
	defByBlack = false;
}

float Board::getX(){
	return posithion.getX();
}

float Board::getY(){
	return posithion.getY();
}

bool Board::getDefByWhite(){
	return defByWhite;
}

bool Board::getDefByBlack() {
	return defByBlack;
}

void Board::setX(float x){
	posithion.setX(x);
}

void Board::setY(float y){
	posithion.setY(y);
}
void Board::setPosithion(Point a){
	posithion = a;
}

void Board::setDefByWhite(bool a){
	defByWhite = a;
}

void Board::setDefByBlack(bool a) {
	defByBlack = a;
}
