#include "Rook.h"
#define ROOK_SIZE 0.2
Rook::Rook(){
	value = 5;
}

void Rook::texture(){
	glBegin(GL_TRIANGLE_STRIP);
	glColor3f(0.5, texture_color, 0.5);
	glVertex2f(location.getX() + ROOK_SIZE, location.getY() + ROOK_SIZE);//2.3 2.2
	glVertex2f(location.getX() + CELL - ROOK_SIZE, location.getY() + ROOK_SIZE);//2.7 2.2
	glVertex2f(location.getX() + ROOK_SIZE, location.getY() + CELL - ROOK_SIZE);//2.3 2.7
	glVertex2f(location.getX() + CELL - ROOK_SIZE, location.getY() + CELL - ROOK_SIZE);//2.7 2.7
	glEnd();
}

bool Rook::enemyOnCell(Figure** enemies, Point a, Figure*& enemyObj) {
	for (int i = 0; i < CNT; i++)
		if (enemies[i]->getLocation() == a) {
			enemyObj = enemies[i];
			return true;
		}
	return false;
}

bool Rook::friendOnCell(Figure** friends, Point a) {
	for (int i = 0; i < CNT; i++)
		if (friends[i]->getLocation() == a) {
			friends[i]->setDefended(true);
			return true;
		}
	return false;
}

Rook* Rook::getPointer(){
	return this;
}

void Rook::fillPosibleFields(Figure** enemies, Figure** friends, Board board[][SIZE], bool kingCheck, vector<Point> check_list) {
	popFields();
	Point a;
	Figure* enemyObj;
	int x, y, dx = 1, dy = 1, kof = -1;
	int loop = 1;
	bool onCell = false;
	if (bound)
		fillBounded(friends, enemies, board);
	while (loop++ <= 4) {
		if (loop % 2) {
			x = location.x + dx;
			y = location.y;
		}
		else {
			x = location.x;
			y = location.y + dy;
		}
		while (x >= 1 && x <= 8 &&
			y >= 1 && y <= 8 && !onCell) {
			a.x = x;
			a.y = y;
			if (friendOnCell(friends, a))
				onCell = true;
			else if (enemyOnCell(enemies, a, enemyObj)) {
				if (enemyObj->getValue() == 10) {
					Point buf;
					buf = a;
					while (buf.x >= 1 && buf.x <= 8 &&
						buf.y >= 1 && buf.y <= 8) {
						side ? board[(int)buf.x - 1][(int)buf.y - 1].setDefByWhite(true) : board[(int)buf.x - 1][(int)buf.y - 1].setDefByBlack(true);
						if (loop % 2)
							buf.x += dx;
						else
							buf.y += dy;
					}
				}
				else {
					Point buf;
					buf = a;
					Figure* nextEnemy;
					while (buf.x >= 1 && buf.x <= 8 &&
						buf.y >= 1 && buf.y <= 8) {
						if (loop % 2)
							buf.x += dx;
						else
							buf.y += dy;
						if (enemyOnCell(enemies, buf, nextEnemy))
							if (nextEnemy->getValue() == 10)
								enemyObj->setBound(true);
							else
								break;
					}
				}
				if ((kingCheck && whenChecked(a, check_list)) || !kingCheck) {
					if ((bound && boundFields(a)) || !bound) {
						side ? board[(int)a.x - 1][(int)a.y - 1].setDefByWhite(true) : board[(int)a.x - 1][(int)a.y - 1].setDefByBlack(true);
						possible_fields.push_back(a);
						onCell = true;
					}
				}
			}
			else {
				if ((kingCheck && whenChecked(a, check_list)) || !kingCheck) {
					if ((bound && boundFields(a)) || !bound) {
						side ? board[(int)a.x - 1][(int)a.y - 1].setDefByWhite(true) : board[(int)a.x - 1][(int)a.y - 1].setDefByBlack(true);
						possible_fields.push_back(a);
					}
				}
			}
			if (loop % 2)
				x += dx;
			else
				y += dy;
		}
		onCell = false;
		if (loop % 2)
			dx *= kof;
		else
			dy *= kof;
	}
	filed = true;
}
