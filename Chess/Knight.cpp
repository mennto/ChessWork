#include "Knight.h"
#define KNIGHT_SIZE 0.2
Knight::Knight(){
	fillHelper();
	value = 4;
}

void Knight::texture(){
	glLineWidth(5);
	glBegin(GL_LINE_STRIP);
	glColor3f(0.5, texture_color, 0.5);
	glVertex2f(location.getX() + KNIGHT_SIZE, location.getY() + KNIGHT_SIZE);
	glVertex2f(location.getX() + KNIGHT_SIZE, location.getY() + CELL - KNIGHT_SIZE);
	glVertex2f(location.getX() + CELL- KNIGHT_SIZE, location.getY() + CELL - KNIGHT_SIZE);
	glEnd();
}

void Knight::fillHelper(){
	int masX[] = { 1,2,2,1,-1,-2,-2,-1};
	int masY[] = { 2,1,-1,-2,-2,-1,1,2 };
	Point a;
	for (int i = 0; i < 8; i++) {
		a.x = masX[i];
		a.y = masY[i];
		helper.push_back(a);
	}
}

bool Knight::enemyOnCell(Figure** enemies, Point a){
	for (int i = 0; i < CNT; i++)
		if (enemies[i]->getLocation() == a)
			return true;
	return false;
}

bool Knight::friendOnCell(Figure** friends, Point a){
	for (int i = 0; i < CNT; i++)
		if (friends[i]->getLocation() == a) {
			friends[i]->setDefended(true);
			return true;
		}
	return false;
}

void Knight::fillPosibleFields(Figure** enemies, Figure** friends, Board board[][SIZE], bool kingCheck, vector<Point> check_list){
	popFields();
	Point a;
	for (int i = 0; i < 8; i++) {
		a.x = location.x+helper[i].x;
		a.y = location.y+helper[i].y;
		if (!friendOnCell(friends, a) || enemyOnCell(enemies, a)) {
			int b = a.x - 1;
			if (a.x >= 1 && a.x <= 8 &&
				a.y >= 1 && a.y <= 8) {
				if ((kingCheck && whenChecked(a, check_list)) || !kingCheck) {
					side ? board[(int)a.x - 1][(int)a.y - 1].setDefByWhite(true) : board[(int)a.x - 1][(int)a.y - 1].setDefByBlack(true);
					possible_fields.push_back(a);
				}
			}
		}
	}
	filed = true;
}
